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
//	CconvCdDedDispProp.cpp
// ****************************************************************
*/
#include "stdafx.h"
#include "CconvCdDedDispProp.h"
#include "NsOu\OuNew.h"
#include "NsOu\dynamic_castOu.h"
#include "str\strToInt.h"
#include "str\CdConnectedString2.h"
#include "str\OuPropertiesText\ErrorInfo\COuErrorInfo.h"
#include "DcdCd\DcDrawProp\CdColorProp.h"
#include "DcdCd\DcDrawProp\CconvDcDrawProp.h"

namespace DedRosenFileData{

using namespace std ;
using namespace OuPropertiesText ;
using namespace OuPropertiesText::ErrorInfo ;
// --------------------------------
//	下請関数
// --------------------------------


/**
 	CdFontProp の属性を、文字列に変換します。
  @param aCdFontProp [in]
 	変換対象となる CdFontProp を指定してください。
  @return
 	変換結果を返します。
 */
static tstring CdFontProp_to_string( const CdFontProp& aCdFontProp )
{
	CconvDcDrawProp	aConv ;
	return aConv.CdFontProp_to_string( aCdFontProp ) ;
}


/**
 	 CdFontProp_to_string() で作成した文字列を解釈し、
 	CdFontProp オブジェクトの属性に反映します。
  @param pCdFontProp [out]
 	この関数はこのオブジェクトの属性に、文字列の内容を反映します。
  @param aString [in]
 	 CdFontProp_to_string() で作成した文字列を指定してください。
  @return
 	成功したら 0 以上、エラーなら負の数です。
 	-	-12 ;	//	PointTextHeight の値が不正
 	-	-22 ;	//	LogicalunitTextHeight の値が不正
 	-	-32 ;	//	LogicalunitCellHeight の値が不正
 	-	-42 ;	//	Facename の値が不正
 	-	-52 ;	//	Bold の値が不正
 	-	-62 ;	//	Itaric の値が不正
 	-	-72 ;	//	Underine の値が不正
 	-	-82 ;	//	StrikeOut の値が不正
 */
static int CdFontProp_from_string( CdFontProp* pCdFontProp , const tstring& aString  )
{
	CconvDcDrawProp	aConv ;
	return aConv.CdFontProp_from_string( pCdFontProp , aString ) ;
}

/**
	aCdColorProp を文字列に変換します。
@param aCdColorProp [in]
	変換元の値を指定してください。
@return
	変換結果を返します。
*/
static tstring CdColorProp_to_string( const CdColorProp& aCdColorProp )
{

	CconvDcDrawProp	aConv ;
	return aConv.CdColorProp_to_string( aCdColorProp ) ;
}


/**
	文字列を aCdColorProp に変換します。
@param aString [in]
	変換元の値を指定してください。
@return
	変換結果を返します。
 */
static CdColorProp CdColorProp_from_string( const tstring& aString  )
{
	CconvDcDrawProp	aConv ;
	return aConv.CdColorProp_from_string( aString ) ;
}



// ****************************************************************
//	CconvCdDedDispProp
// ****************************************************************
const TCHAR nameJikokuhyouFont[]=_T("JikokuhyouFont") ;
const TCHAR nameJikokuhyouVFont[]=_T("JikokuhyouVFont") ;
const TCHAR nameDiaEkimeiFont[]=_T("DiaEkimeiFont") ;
const TCHAR nameDiaJikokuFont[]=_T("DiaJikokuFont") ;
const TCHAR nameDiaRessyaFont[]=_T("DiaRessyaFont") ;
const TCHAR nameOperationTableFont[] = _T("OperationTableFont");
const TCHAR nameAllOperationTableJikokuFont[] = _T("AllOperationTableJikokuFont");
const TCHAR nameCommentFont[]=_T("CommentFont") ;
const TCHAR nameDiaMojiColor[]=_T("DiaMojiColor") ;
const TCHAR nameDiaBackColor[]=_T("DiaBackColor") ;
const TCHAR nameDiaRessyaColor[]=_T("DiaRessyaColor") ;
const TCHAR nameDiaJikuColor[]=_T("DiaJikuColor") ;
const TCHAR nameJikokuhyouBackColor[] = _T("JikokuhyouBackColor");
const TCHAR nameStdOpeTimeLowerColor[] = _T("StdOpeTimeLowerColor");
const TCHAR nameStdOpeTimeHigherColor[] = _T("StdOpeTimeHigherColor");
const TCHAR nameStdOpeTimeUndefColor[] = _T("StdOpeTimeUndefColor");
const TCHAR nameStdOpeTimeIllegalColor[] = _T("StdOpeTimeIllegalColor");
const TCHAR nameOperationStringColor[] = _T("OperationStringColor");
const TCHAR nameOperationGridColor[] = _T("OperationGridColor");
const TCHAR nameEkimeiLength[] = _T("EkimeiLength") ;
const TCHAR nameJikokuhyouRessyaWidth[] = _T("JikokuhyouRessyaWidth") ;
const TCHAR nameDiaRessyajouhouHyoujiEkiOrderKudari[]=_T("DiaRessyajouhouHyoujiEkiOrderKudari") ;
const TCHAR nameDiaRessyajouhouHyoujiEkiOrderNobori[]=_T("DiaRessyajouhouHyoujiEkiOrderNobori") ;
const TCHAR nameAnySecondIncDec1[] = _T("AnySecondIncDec1") ;
const TCHAR nameAnySecondIncDec2[] = _T("AnySecondIncDec2") ;
const TCHAR nameDisplayRessyamei[] = _T("DisplayRessyamei");
const TCHAR nameDisplayOuterTerminalEkimeiOriginSide[] = _T("DisplayOuterTerminalEkimeiOriginSide");
const TCHAR nameDisplayOuterTerminalEkimeiTerminalSide[] = _T("DisplayOuterTerminalEkimeiTerminalSide");
const TCHAR nameDiagramDisplayOuterTerminal[] = _T("DiagramDisplayOuterTerminal");
const TCHAR nameSecondRoundChaku[] = _T("SecondRoundChaku");
const TCHAR nameSecondRoundHatsu[] = _T("SecondRoundHatsu");
const TCHAR nameDisplay2400[] = _T("Display2400");
const TCHAR nameOperationNumberRows[] = _T("OperationNumberRows");
const TCHAR nameDisplayInOutLinkCode[] = _T("DisplayInOutLinkCode");

int CconvCdDedDispProp::toOuPropertiesText( 
			const CdDedDispProp& aCdDedDispProp , 
			OuPropertiesText::CNodeContainer* pCNodeContainer ) 
{
	int iRv = 0 ;

	//1.JikokuhyouFont
	for ( int idx = 0 ; iRv >= 0 && idx < CentDedRessyasyubetsu::JIKOKUHYOUFONT_COUNT ; idx ++ )
	{
		tstring	strValue = CdFontProp_to_string( aCdDedDispProp.getJikokuhyouFont(idx) ) ;
		pCNodeContainer->insertInName(
			OuNew< OuPropertiesText::CNode >( 
				new OuPropertiesText::CPropertyString( nameJikokuhyouFont , strValue ) ) ) ;
	}

	//JikokuhyouVFont
	{
		tstring	strValue = CdFontProp_to_string( aCdDedDispProp.getJikokuhyouVFont() ) ;
		pCNodeContainer->setValue( nameJikokuhyouVFont , strValue ) ;
	}

	//2.DiaEkimeiFont
	if ( iRv >= 0 ){
		tstring	strValue = CdFontProp_to_string( aCdDedDispProp.getDiaEkimeiFont() ) ;
		pCNodeContainer->setValue( nameDiaEkimeiFont , strValue ) ;
	}
	//3.DiaJikokuFont
	if ( iRv >= 0 ){
		tstring	strValue = CdFontProp_to_string( aCdDedDispProp.getDiaJikokuFont() ) ;
		pCNodeContainer->setValue( nameDiaJikokuFont , strValue ) ;
	}
	//4.DiaRessyaFont
	if ( iRv >= 0 ){
		tstring	strValue = CdFontProp_to_string( aCdDedDispProp.getDiaRessyaFont() ) ;
		pCNodeContainer->setValue( nameDiaRessyaFont , strValue ) ;
	}
	//4.1.OperationTableFont
	if (iRv >= 0) {
		tstring	strValue = CdFontProp_to_string(aCdDedDispProp.getOperationTableFont());
		pCNodeContainer->setValue(nameOperationTableFont, strValue);
	}
	//4.2.AllOperationTableJikokuFont
	if (iRv >= 0) {
		tstring	strValue = CdFontProp_to_string(aCdDedDispProp.getAllOperationTableJikokuFont());
		pCNodeContainer->setValue(nameAllOperationTableJikokuFont, strValue);
	}
	//5.CommentFont
	if ( iRv >= 0 ){
		tstring	strValue = CdFontProp_to_string( aCdDedDispProp.getViewCommentFont() ) ;
		pCNodeContainer->setValue( nameCommentFont , strValue ) ;
	}
	//6.DiaMojiColor
	if ( iRv >= 0 )
	{
		pCNodeContainer->setValue( 
			nameDiaMojiColor , 
			CdColorProp_to_string( aCdDedDispProp.getDiaMojiColor() ) );
	}
	//7.DiaBackColor
	if (iRv >= 0) {
		for (int idx = 0; iRv >= 0 && idx < CentDedEki::DIAGRAMBACKCOLOR_COUNT; idx++)
		{
			tstring	strValue = CdColorProp_to_string(aCdDedDispProp.getDiaBackColor(idx));
			pCNodeContainer->insertInName(
				OuNew< OuPropertiesText::CNode >(
					new OuPropertiesText::CPropertyString(nameDiaBackColor, strValue)));
		}
	}

	//8.DiaRessyaColor
	//	todo: このフィールドは、ファイルフォーマット改訂時に廃止します。
	if ( iRv >= 0 )
	{
		pCNodeContainer->setValue( 
			nameDiaRessyaColor , 
			CdColorProp_to_string( aCdDedDispProp.getDiaRessyaColor() ) ) ;
	}

	//9.DiaJikuColor
	if ( iRv >= 0 ){
		pCNodeContainer->setValue( 
			nameDiaJikuColor , 
			CdColorProp_to_string( aCdDedDispProp.getDiaJikuColor() ) ) ;
	}
	//9.1.JikokuhyouBackColor
	if (iRv >= 0) {
		for (int idx = 0; iRv >= 0 && idx < CentDedDia::JIKOKUHYOUCOLOR_COUNT; idx++)
		{
			tstring	strValue = CdColorProp_to_string(aCdDedDispProp.getJikokuhyouBackColor(idx));
			pCNodeContainer->insertInName(
				OuNew< OuPropertiesText::CNode >(
					new OuPropertiesText::CPropertyString(nameJikokuhyouBackColor, strValue)));
		}
	}
	//9.5.StdOpeTimeLowerColor
	if (iRv >= 0) {
		pCNodeContainer->setValue(
			nameStdOpeTimeLowerColor,
			CdColorProp_to_string(aCdDedDispProp.getStdOpeTimeLowerColor()));
	}
	//9.6.StdOpeTimeHigherColor
	if (iRv >= 0) {
		pCNodeContainer->setValue(
			nameStdOpeTimeHigherColor,
			CdColorProp_to_string(aCdDedDispProp.getStdOpeTimeHigherColor()));
	}
	//9.7.StdOpeTimeUndefColor
	if (iRv >= 0) {
		pCNodeContainer->setValue(
			nameStdOpeTimeUndefColor,
			CdColorProp_to_string(aCdDedDispProp.getStdOpeTimeUndefColor()));
	}
	//9.8.StdOpeTimeIllegalColor
	if (iRv >= 0) {
		pCNodeContainer->setValue(
			nameStdOpeTimeIllegalColor,
			CdColorProp_to_string(aCdDedDispProp.getStdOpeTimeIllegalColor()));
	}
	//9.9.OperationStringColor
	if (iRv >= 0) {
		pCNodeContainer->setValue(
			nameOperationStringColor,
			CdColorProp_to_string(aCdDedDispProp.getOperationStringColor()));
	}
	//9.10.OperationGridColor
	if (iRv >= 0) {
		pCNodeContainer->setValue(
			nameOperationGridColor,
			CdColorProp_to_string(aCdDedDispProp.getOperationGridColor()));
	}
	//10.EkimeiLength
	if ( iRv >= 0 ){
		pCNodeContainer->setValue( nameEkimeiLength , 
			stringOf( aCdDedDispProp.getEkimeiLength() ) ) ;
	}

	//11.JikokuhyouRessyaWidth
	if ( iRv >= 0 )
	{
		//	デフォルト値の場合は、出力はしません。
		pCNodeContainer->setValue( nameJikokuhyouRessyaWidth , 
			stringOf( aCdDedDispProp.getJikokuhyouRessyaWidth() ) ) ;
	}

	//12.AnySecondIncDec1
	if ( iRv >= 0 )
	{
		//	デフォルト値の場合は、出力はしません。
		pCNodeContainer->setValue( nameAnySecondIncDec1 , 
			stringOf( aCdDedDispProp.getAnySecondIncDec1() ) ) ;
	}
	
	//13.AnySecondIncDec2
	if ( iRv >= 0 )
	{
		//	デフォルト値の場合は、出力はしません。
		pCNodeContainer->setValue( nameAnySecondIncDec2 , 
			stringOf( aCdDedDispProp.getAnySecondIncDec2() ) ) ;
	}

	//14.DisplayRessyamei
	if (iRv >= 0)
	{
		if (aCdDedDispProp.getDisplayRessyamei()) 
		{
			pCNodeContainer->setValue(nameDisplayRessyamei, _T("1"));
		}
		else
		{
			pCNodeContainer->setValue(nameDisplayRessyamei, _T("0"));
		}
	}

	//15.DisplayOuterTerminalEkimeiOriginSide
	if (iRv >= 0)
	{
		if (aCdDedDispProp.getDisplayOuterTerminalO())
		{
			pCNodeContainer->setValue(nameDisplayOuterTerminalEkimeiOriginSide, _T("1"));
		}
		else
		{
			pCNodeContainer->setValue(nameDisplayOuterTerminalEkimeiOriginSide, _T("0"));
		}
	}

	//16.DisplayOuterTerminalEkimeiTerminalSide
	if (iRv >= 0)
	{
		if (aCdDedDispProp.getDisplayOuterTerminalT())
		{
			pCNodeContainer->setValue(nameDisplayOuterTerminalEkimeiTerminalSide, _T("1"));
		}
		else
		{
			pCNodeContainer->setValue(nameDisplayOuterTerminalEkimeiTerminalSide, _T("0"));
		}
	}

	//17.DiagramDisplayOuterTerminal
	if (iRv >= 0)
	{
		//	デフォルト値の場合は、出力はしません。
		pCNodeContainer->setValue(nameDiagramDisplayOuterTerminal,
			stringOf(aCdDedDispProp.getDiagramDisplayOuterTerminal()));
	}

	//18.SecondRoundChaku
	if (iRv >= 0)
	{
		pCNodeContainer->setValue(nameSecondRoundChaku,
			stringOf(aCdDedDispProp.getSecondRoundChaku()));
	}

	//19.SecondRoundHatsu
	if (iRv >= 0)
	{
		pCNodeContainer->setValue(nameSecondRoundHatsu,
			stringOf(aCdDedDispProp.getSecondRoundHatsu()));
	}

	//20.Display2400
	if (iRv >= 0)
	{
		if (aCdDedDispProp.getDisplay2400())
		{
			pCNodeContainer->setValue(nameDisplay2400, _T("1"));
		}
		else
		{
			pCNodeContainer->setValue(nameDisplay2400, _T("0"));
		}
	}

	//21.OperationNumberRows
	if (iRv >= 0)
	{
		pCNodeContainer->setValue(nameOperationNumberRows,
			stringOf(aCdDedDispProp.getOperationNumberRows()));
	}

	//22.DisplayInOutLinkCode
	if (iRv >= 0)
	{
		if (aCdDedDispProp.getDisplayInOutLinkCode())
		{
			pCNodeContainer->setValue(nameDisplayInOutLinkCode, _T("1"));
		}
		else
		{
			pCNodeContainer->setValue(nameDisplayInOutLinkCode, _T("0"));
		}
	}
	return (iRv);
}

int CconvCdDedDispProp::fromOuPropertiesText( 
			CdDedDispProp* pCdDedDispProp ,
			const OuPropertiesText::IfNodeContainerConst* pCNodeContainer ,
			OuPropertiesText::ErrorInfo::COuErrorInfoContainer* pCOuErrorInfoContainer ) 
{
	int iRv = 0 ;
	
	CdDedDispProp aCdDedDispProp ;	

	// --------------------------------
	//1.JikokuhyouFont
	//	数が足りない場合、指定のない要素は設定をしません。
	for ( int idx = 0 ; iRv >= 0 && idx < CentDedRessyasyubetsu::JIKOKUHYOUFONT_COUNT ; idx ++ )
	{

		Ou< const OuPropertiesText::CNode > pNode = pCNodeContainer->getInName(
			nameJikokuhyouFont , idx ) ;
		Ou< const OuPropertiesText::CPropertyString > pPropertyString = 
			dynamic_castOu< const OuPropertiesText::CPropertyString >( pNode ) ;

		if ( pPropertyString != NULL )
		{

			tstring	strValue = pPropertyString->getValue() ;
			CdFontProp	aCdFontProp ;
			int iResult = CdFontProp_from_string( &aCdFontProp , strValue ) ;
			if ( iResult < 0 ){
				COuErrorInfo aCOuErrorInfo( ERRREASON_InvalidValue() ) ;
				aCOuErrorInfo.getProp()->setValue( ERRPROP_Name() , nameJikokuhyouFont ) ; 
				aCOuErrorInfo.getProp()->setValue( ERRPROP_Value() , strValue ) ; 
				iRv = -12 ;	//	JikokuhyouFont の内容が不正です。
			}	else	{
				aCdDedDispProp.setJikokuhyouFont( idx , aCdFontProp ) ;
			}		
		}
	}

	//JikokuhyouVFont
	{
		tstring	strValue = pCNodeContainer->getValue(	nameJikokuhyouVFont ) ; 
		if ( strValue.length() > 0 )
		{
			CdFontProp	aCdFontProp ;
			int iResult = CdFontProp_from_string( &aCdFontProp , strValue ) ;
			if ( iResult < 0 ){
				COuErrorInfo aCOuErrorInfo( ERRREASON_InvalidValue() ) ;
				aCOuErrorInfo.getProp()->setValue( ERRPROP_Name() , nameJikokuhyouVFont ) ; 
				aCOuErrorInfo.getProp()->setValue( ERRPROP_Value() , strValue ) ; 
				iRv = -13 ;	//	JikokuhyouVFont の内容が不正です。
			}	else	{
				aCdDedDispProp.setJikokuhyouVFont( aCdFontProp ) ;
			}
		}
	}
	//2.DiaEkimeiFont
	if ( iRv >= 0 ){
		tstring	strValue = pCNodeContainer->getValue( nameDiaEkimeiFont ) ;
		CdFontProp	aCdFontProp ;
		int iResult = CdFontProp_from_string( &aCdFontProp , strValue ) ;
		if ( iResult < 0 ){
			COuErrorInfo aCOuErrorInfo( ERRREASON_InvalidValue() ) ;
			aCOuErrorInfo.getProp()->setValue( ERRPROP_Name() , nameDiaEkimeiFont ) ; 
			aCOuErrorInfo.getProp()->setValue( ERRPROP_Value() , strValue ) ; 
			iRv = -22 ;	//	DiaEkimeiFont の内容が不正です。
		}	else	{
			aCdDedDispProp.setDiaEkimeiFont( aCdFontProp ) ;
		}		
	}
	//3.DiaJikokuFont
	if ( iRv >= 0 ){
		tstring	strValue = pCNodeContainer->getValue( nameDiaJikokuFont ) ;
		CdFontProp	aCdFontProp ;
		int iResult = CdFontProp_from_string( &aCdFontProp , strValue ) ;
		if ( iResult < 0 ){
			COuErrorInfo aCOuErrorInfo( ERRREASON_InvalidValue() ) ;
			aCOuErrorInfo.getProp()->setValue( ERRPROP_Name() , nameDiaJikokuFont ) ; 
			aCOuErrorInfo.getProp()->setValue( ERRPROP_Value() , strValue ) ; 
			iRv = -32 ;	//	DiaJikokuFont の内容が不正です。
		}	else	{
			aCdDedDispProp.setDiaJikokuFont( aCdFontProp ) ;
		}		
	}
	//4.DiaRessyaFont
	if ( iRv >= 0 ){
		tstring	strValue = pCNodeContainer->getValue( nameDiaRessyaFont ) ;
		
		//	この属性は、あとから追加したため、空の場合でもエラーにはしません
		if ( !strValue.empty() ){
			CdFontProp	aCdFontProp ;
			int iResult = CdFontProp_from_string( &aCdFontProp , strValue ) ;
			if ( iResult < 0 ){
				COuErrorInfo aCOuErrorInfo( ERRREASON_InvalidValue() ) ;
				aCOuErrorInfo.getProp()->setValue( ERRPROP_Name() , nameDiaRessyaFont ) ; 
				aCOuErrorInfo.getProp()->setValue( ERRPROP_Value() , strValue ) ; 
				iRv = -32 ;	//	DiaRessyaFont の内容が不正です。
			}	else	{
				aCdDedDispProp.setDiaRessyaFont( aCdFontProp ) ;
			}
		}
	}
	//4.1.OperationTableFont
	if (iRv >= 0) {
		tstring	strValue = pCNodeContainer->getValue(nameOperationTableFont);

		//	この属性は、あとから追加したため、空の場合でもエラーにはしません
		if (!strValue.empty()) {
			CdFontProp	aCdFontProp;
			int iResult = CdFontProp_from_string(&aCdFontProp, strValue);
			if (iResult < 0) {
				COuErrorInfo aCOuErrorInfo(ERRREASON_InvalidValue());
				aCOuErrorInfo.getProp()->setValue(ERRPROP_Name(), nameOperationTableFont);
				aCOuErrorInfo.getProp()->setValue(ERRPROP_Value(), strValue);
				iRv = -42;	//	OperationTableFont の内容が不正です。
			}
			else {
				aCdDedDispProp.setOperationTableFont(aCdFontProp);
			}
		}
	}
	//4.2.AllOperationTableJikokuFont
	if (iRv >= 0) {
		tstring	strValue = pCNodeContainer->getValue(nameAllOperationTableJikokuFont);

		//	この属性は、あとから追加したため、空の場合でもエラーにはしません
		if (!strValue.empty()) {
			CdFontProp	aCdFontProp;
			int iResult = CdFontProp_from_string(&aCdFontProp, strValue);
			if (iResult < 0) {
				COuErrorInfo aCOuErrorInfo(ERRREASON_InvalidValue());
				aCOuErrorInfo.getProp()->setValue(ERRPROP_Name(), nameAllOperationTableJikokuFont);
				aCOuErrorInfo.getProp()->setValue(ERRPROP_Value(), strValue);
				iRv = -52;	//	AllOperationTableJikokuFont の内容が不正です。
			}
			else {
				aCdDedDispProp.setAllOperationTableJikokuFont(aCdFontProp);
			}
		}
	}
	//5.CommentFont
	if ( iRv >= 0 ){
		tstring	strValue = pCNodeContainer->getValue( nameCommentFont ) ;
		CdFontProp	aCdFontProp ;
		int iResult = CdFontProp_from_string( &aCdFontProp , strValue ) ;
		if ( iResult < 0 ){
				COuErrorInfo aCOuErrorInfo( ERRREASON_InvalidValue() ) ;
				aCOuErrorInfo.getProp()->setValue( ERRPROP_Name() , nameCommentFont ) ; 
				aCOuErrorInfo.getProp()->setValue( ERRPROP_Value() , strValue ) ; 
			iRv = -32 ;	//	CommentFont の内容が不正です。
		}	else	{
			aCdDedDispProp.setViewCommentFont( aCdFontProp ) ;
		}		
	}
	//6.DiaMojiColor
	if ( iRv >= 0 )
	{
		tstring	strValue = pCNodeContainer->getValue( nameDiaMojiColor ) ;
		aCdDedDispProp.setDiaMojiColor( 
			CdColorProp_from_string( strValue ) ) ;
	}
	//7.DiaHaikeiColor
	if (iRv >= 0)
	{
		for (int idx = 0; iRv >= 0 && idx < CentDedEki::DIAGRAMBACKCOLOR_COUNT; idx++)
		{

			Ou< const OuPropertiesText::CNode > pNode = pCNodeContainer->getInName(
				nameDiaBackColor, idx);
			Ou< const OuPropertiesText::CPropertyString > pPropertyString =
				dynamic_castOu< const OuPropertiesText::CPropertyString >(pNode);

			if (pPropertyString != NULL)
			{

				tstring	strValue = pPropertyString->getValue();
				CdColorProp	aCdColorProp;
				aCdDedDispProp.setDiaBackColor(
					idx, CdColorProp_from_string(strValue));
			}
		}
	}
	//8.DiaRessyaColor
	//	todo: このフィールドは、ファイルフォーマット改訂時に廃止します。
	if ( iRv >= 0 )
	{
		tstring	strValue = pCNodeContainer->getValue( nameDiaRessyaColor ) ;
		aCdDedDispProp.setDiaRessyaColor( 
			CdColorProp_from_string( strValue ) ) ;
	}
	//9.DiaJikuColor
	if ( iRv >= 0 )
	{
		tstring	strValue = pCNodeContainer->getValue( nameDiaJikuColor ) ;
		aCdDedDispProp.setDiaJikuColor( 
			CdColorProp_from_string( strValue ) ) ;
	}
	//9.1.JikokuhyouBackColor1-4
	if (iRv >= 0)
	{
		for (int idx = 0; iRv >= 0 && idx < CentDedDia::JIKOKUHYOUCOLOR_COUNT; idx++)
		{

			Ou< const OuPropertiesText::CNode > pNode = pCNodeContainer->getInName(
				nameJikokuhyouBackColor, idx);
			Ou< const OuPropertiesText::CPropertyString > pPropertyString =
				dynamic_castOu< const OuPropertiesText::CPropertyString >(pNode);

			if (pPropertyString != NULL)
			{

				tstring	strValue = pPropertyString->getValue();
				CdColorProp	aCdColorProp;
				//int iResult = CdColorProp_from_string(&aCdColorProp, strValue);
				//if (iResult < 0) {
				//	COuErrorInfo aCOuErrorInfo(ERRREASON_InvalidValue());
				//	aCOuErrorInfo.getProp()->setValue(ERRPROP_Name(), nameJikokuhyouBackColor);
				//	aCOuErrorInfo.getProp()->setValue(ERRPROP_Value(), strValue);
				//	iRv = -12;	//	JikokuhyouFont の内容が不正です。
				//}
				//else {
					aCdDedDispProp.setJikokuhyouBackColor(
						idx, CdColorProp_from_string( strValue));
				//}
			}
		}
	}
	//9.5.StdOpeTimeLowerColor
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(nameStdOpeTimeLowerColor);
		if (!strValue.empty()) {
			aCdDedDispProp.setStdOpeTimeLowerColor(
				CdColorProp_from_string(strValue));
		}
	}
	//9.6.StdOpeTimeHigherColor
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(nameStdOpeTimeHigherColor);
		if (!strValue.empty()) {
			aCdDedDispProp.setStdOpeTimeHigherColor(
				CdColorProp_from_string(strValue));
		}
	}
	//9.7.StdOpeTimeUndefColor
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(nameStdOpeTimeUndefColor);
		if (!strValue.empty()) {
			aCdDedDispProp.setStdOpeTimeUndefColor(
				CdColorProp_from_string(strValue));
		}
	}
	//9.8.StdOpeTimeIllegalColor
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(nameStdOpeTimeIllegalColor);
		if (!strValue.empty()) {
			aCdDedDispProp.setStdOpeTimeIllegalColor(
				CdColorProp_from_string(strValue));
		}
	}
	//9.9.OperationStringColor
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(nameOperationStringColor);
		if (!strValue.empty()) {
			aCdDedDispProp.setOperationStringColor(
				CdColorProp_from_string(strValue));
		}
	}
	//9.10.OperationGridColor
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(nameOperationGridColor);
		if (!strValue.empty()) {
			aCdDedDispProp.setOperationGridColor(
				CdColorProp_from_string(strValue));
		}
	}
	//10.EkimeiLength
	if ( iRv >= 0 ){
		tstring	strValue = pCNodeContainer->getValue( nameEkimeiLength ) ;
		if ( !strValue.empty() ){
			int iValue = intOf( strValue ) ;
			if ( iValue > 0 ){
				aCdDedDispProp.setEkimeiLength( iValue ) ;
			}
		}	
	}
	//11.EkimeiLength
	if ( iRv >= 0 )
	{
		tstring	strValue = pCNodeContainer->getValue( nameJikokuhyouRessyaWidth ) ;
		if ( !strValue.empty() )
		{
			int iValue = intOf( strValue ) ;
			if ( iValue > 0 )
			{
				aCdDedDispProp.setJikokuhyouRessyaWidth( iValue ) ;
			}
		}	
	}
	//12.AnySecondIncDec1
	if ( iRv >= 0 )
	{
		tstring	strValue = pCNodeContainer->getValue( nameAnySecondIncDec1 ) ;
		if ( !strValue.empty() )
		{
			int iValue = intOf( strValue ) ;
			if ( iValue >= -60 )
			{
				aCdDedDispProp.setAnySecondIncDec1( iValue ) ;
			}
		}	
	}
	//13.AnySecondIncDec2
	if ( iRv >= 0 )
	{
		tstring	strValue = pCNodeContainer->getValue( nameAnySecondIncDec2 ) ;
		if ( !strValue.empty() )
		{
			int iValue = intOf( strValue ) ;
			if ( iValue >= -60 )
			{
				aCdDedDispProp.setAnySecondIncDec2( iValue ) ;
			}
		}	
	}
	//14.DisplayRessyamei
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(nameDisplayRessyamei);
		if (strValue == _T("0"))
		{
			aCdDedDispProp.setDisplayRessyamei(false);
		}
		else
		{
			aCdDedDispProp.setDisplayRessyamei(true);
		}
	}
	//15.DisplayOuterTerminalEkimeiOriginSide
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(nameDisplayOuterTerminalEkimeiOriginSide);
		if (strValue == _T("1"))
		{
			aCdDedDispProp.setDisplayOuterTerminalO(true);
		}
		else
		{
			aCdDedDispProp.setDisplayOuterTerminalO(false);
		}
	}
	//16.DisplayOuterTerminalEkimeiTerminalSide
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(nameDisplayOuterTerminalEkimeiTerminalSide);
		if (strValue == _T("1"))
		{
			aCdDedDispProp.setDisplayOuterTerminalT(true);
		}
		else
		{
			aCdDedDispProp.setDisplayOuterTerminalT(false);
		}
	}
	//17.DiagramDisplayOuterTerminal
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(nameDiagramDisplayOuterTerminal);
		if (!strValue.empty())
		{
			int iValue = intOf(strValue);
			if (iValue >= 0)
			{
				aCdDedDispProp.setDiagramDisplayOuterTerminal(iValue);
			}
		}
	}
	//18.SecondRoundChaku
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(nameSecondRoundChaku);
		if (!strValue.empty())
		{
			int iValue = intOf(strValue);
			if (iValue >= 0)
			{
				aCdDedDispProp.setSecondRoundChaku(iValue);
			}
		}
	}
	//19.SecondRoundHatsu
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(nameSecondRoundHatsu);
		if (!strValue.empty())
		{
			int iValue = intOf(strValue);
			if (iValue >= 0)
			{
				aCdDedDispProp.setSecondRoundHatsu(iValue);
			}
		}
	}
	//20.Display2400
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(nameDisplay2400);
		if (strValue == _T("1"))
		{
			aCdDedDispProp.setDisplay2400(true);
		}
		else
		{
			aCdDedDispProp.setDisplay2400(false);
		}
	}
	//21.OperationNumberRows
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(nameOperationNumberRows);
		if (!strValue.empty())
		{
			int iValue = intOf(strValue);
			if (iValue >= 0)
			{
				aCdDedDispProp.setOperationNumberRows(iValue);
			}
		}
	}
	//22.DisplayInOutLinkCode
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(nameDisplayInOutLinkCode);
		if (strValue == _T("1"))
		{
			aCdDedDispProp.setDisplayInOutLinkCode(true);
		}
		else
		{
			aCdDedDispProp.setDisplayInOutLinkCode(false);
		}
	}
	// --------------------------------
	if ( iRv >= 0 ){
		*pCdDedDispProp = aCdDedDispProp ;	
	}

	return ( iRv ) ;
}
} //namespace DedRosenFileData
