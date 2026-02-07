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
//	CentDedDia.cpp
// ****************************************************************
*/
#include "stdafx.h"
#include "CentDedDia.h"
#include "CentDedDiaCont.h"

using namespace std ;

#ifdef _MFC_VER 
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif


namespace entDed{

// ****************************************************************
//	CentDedDia
// ****************************************************************

// ********************************
//	コンストラクタ
// ********************************
	CentDedDia::CentDedDia(const tstring& strName)
		: m_strName(strName)
		, m_iJikokuhyouMainBackColorIndex(0)
		, m_iJikokuhyouSubBackColorIndex(1)
		, m_iJikokuhyouBackPatternIndex(0)
		, m_bWaitOperationUpdate(false)
		, m_bPatternDiagramPreviewEnable(false)
		, m_iPatternDiagramPreviewCycleSecond(600)
		, m_iPatternDiagramPreviewRange(21600)
	{
		m_CentDedRessyaCont[0] = new CXRessyaCont(
			this,
			Ressyahoukou_Kudari);
		m_CentDedRessyaCont[1] = new CXRessyaCont(
			this,
			Ressyahoukou_Nobori);
	}

CentDedDia::CentDedDia( 
		int iEkiCount )
	:m_iJikokuhyouMainBackColorIndex(0)
	, m_iJikokuhyouSubBackColorIndex(1)
	, m_iJikokuhyouBackPatternIndex(0)
	, m_bWaitOperationUpdate(false)
	, m_bPatternDiagramPreviewEnable(false)
	, m_iPatternDiagramPreviewCycleSecond(600)
	, m_iPatternDiagramPreviewRange(21600)
{
	m_CentDedRessyaCont[0] = new CXRessyaCont( 
		this , 
		iEkiCount , Ressyahoukou_Kudari ) ;
	m_CentDedRessyaCont[1] = new CXRessyaCont( 
		this , 
		iEkiCount , Ressyahoukou_Nobori ) ;
}

CentDedDia::CentDedDia( 
		const tstring& strName ,
		int iEkiCount ) :
	m_strName( strName )
	, m_iJikokuhyouMainBackColorIndex(0)
	, m_iJikokuhyouSubBackColorIndex(1)
	, m_iJikokuhyouBackPatternIndex(0)
	, m_bWaitOperationUpdate(false)
	, m_bPatternDiagramPreviewEnable(false)
	, m_iPatternDiagramPreviewCycleSecond(600)
	, m_iPatternDiagramPreviewRange(21600)
{
	m_CentDedRessyaCont[0] = new CXRessyaCont( 
		this , 
		iEkiCount , Ressyahoukou_Kudari ) ;
	m_CentDedRessyaCont[1] = new CXRessyaCont( 
		this , 
		iEkiCount , Ressyahoukou_Nobori ) ;
}


CentDedDia::CentDedDia(
	const tstring & strName, 
	const int & iJikokuhyouMainBackColorIndex, 
	const int & iJikokuhyouSubBackColorIndex, 
	const int & iJikokuhyouBackPatternIndex, 
	int iEkiCount) :
	m_strName(strName),
	m_iJikokuhyouMainBackColorIndex(iJikokuhyouMainBackColorIndex),
	m_iJikokuhyouSubBackColorIndex(iJikokuhyouSubBackColorIndex),
	m_iJikokuhyouBackPatternIndex(iJikokuhyouBackPatternIndex),
	m_bWaitOperationUpdate(false),
	m_bPatternDiagramPreviewEnable(false),
	m_iPatternDiagramPreviewCycleSecond(600),
	m_iPatternDiagramPreviewRange(21600)
{
	m_CentDedRessyaCont[0] = new CXRessyaCont(
		this,
		iEkiCount, Ressyahoukou_Kudari);
	m_CentDedRessyaCont[1] = new CXRessyaCont(
		this,
		iEkiCount, Ressyahoukou_Nobori);
}

CentDedDia::CentDedDia( const CentDedDia& value ) :
	m_strName( value.m_strName ) ,
	m_iJikokuhyouMainBackColorIndex(value.m_iJikokuhyouMainBackColorIndex),
	m_iJikokuhyouSubBackColorIndex(value.m_iJikokuhyouSubBackColorIndex),
	m_iJikokuhyouBackPatternIndex(value.m_iJikokuhyouBackPatternIndex),
	m_bWaitOperationUpdate(false),
	m_bPatternDiagramPreviewEnable(value.m_bPatternDiagramPreviewEnable),
	m_iPatternDiagramPreviewCycleSecond(value.m_iPatternDiagramPreviewCycleSecond),
	m_iPatternDiagramPreviewRange(value.m_iPatternDiagramPreviewRange),
	m_contCustomizeRessyaIndexKudari(value.m_contCustomizeRessyaIndexKudari),
	m_contCustomizeRessyaIndexNobori(value.m_contCustomizeRessyaIndexNobori),
	m_contOperationTableContent(value.m_contOperationTableContent),
	m_contInOutLinkCodeContent(value.m_contInOutLinkCodeContent)
{
	m_CentDedRessyaCont[0] = new CXRessyaCont( this , *value.m_CentDedRessyaCont[0] ) ;
	m_CentDedRessyaCont[1] = new CXRessyaCont( this , *value.m_CentDedRessyaCont[1] ) ;
}

CentDedDia& CentDedDia::operator=( const CentDedDia& value )
{
	super::operator=( value ) ; 
	// --------------------------------
	CentDedDiaCont* pDiaCont = dynamic_cast<CentDedDiaCont*>( getParent() ) ;
	if ( pDiaCont != NULL )
	{
		/*
		△上書き(operator=): このオブジェクトが親オブジェクト CentDedDiaCont の子である場合で、代入元のダイヤ名が空文字列である場合、もしくは同じ名前のダイヤが CentDedDiaCont にある場合は例外スロー。
	　	  (代入元が、CentDedDiaCont::set()に渡すとエラーになるようなオブジェクトである場合は、代入は例外スローとします)
		*/
		int iResult = pDiaCont->setable( value , pDiaCont->getIndex( this ) ) ;
		if( iResult < 0 )
		{
			throw LException() ;
		}
	}

	// --------------------------------
	m_strName = value.m_strName ;
	*m_CentDedRessyaCont[0] = *value.m_CentDedRessyaCont[0] ;	
	*m_CentDedRessyaCont[1] = *value.m_CentDedRessyaCont[1] ;
	m_iJikokuhyouMainBackColorIndex = value.m_iJikokuhyouMainBackColorIndex;
	m_iJikokuhyouSubBackColorIndex = value.m_iJikokuhyouSubBackColorIndex;
	m_iJikokuhyouBackPatternIndex = value.m_iJikokuhyouBackPatternIndex;
	m_bPatternDiagramPreviewEnable = value.m_bPatternDiagramPreviewEnable;
	m_iPatternDiagramPreviewCycleSecond = value.m_iPatternDiagramPreviewCycleSecond;
	m_iPatternDiagramPreviewRange = value.m_iPatternDiagramPreviewRange;
	m_contCustomizeRessyaIndexKudari = value.m_contCustomizeRessyaIndexKudari;
	m_contCustomizeRessyaIndexNobori = value.m_contCustomizeRessyaIndexNobori;
	m_contOperationTableContent = value.m_contOperationTableContent;
	m_contInOutLinkCodeContent = value.m_contInOutLinkCodeContent;

	return *this ;
}
		
CentDedDia::‾CentDedDia()
{
	delete m_CentDedRessyaCont[0] ;
	delete m_CentDedRessyaCont[1] ;

}

	// ********************************
	//@name CChildBase-操作
	// ********************************
void CentDedDia::setParent( CParentBase* pParent )
{
	super::setParent( pParent ) ; 
	adjust() ;
}
	// ********************************
	//@name CentDedDia-属性
	// ********************************
void CentDedDia::setName( const tstring& value )
{
	//	△上書き(operator=): このオブジェクトが親オブジェクト CentDedDiaCont の子である場合で、
	//	ダイヤ名が空文字列である場合は例外スロー。
	if ( value.length() == 0 )
	{
		throw LException() ;
	}
	// --------------------------------
	CentDedDiaCont* pDiaCont = dynamic_cast<CentDedDiaCont*>( getParent() ) ;
	if ( pDiaCont != NULL )
	{
		/*
		△上書き(operator=): このオブジェクトが親オブジェクト CentDedDiaCont の子である場合で、
			もしくは同じ名前のダイヤが CentDedDiaCont にある場合は例外スロー。
		*/
		int iResult = pDiaCont->findCentDedDiaByName( value ) ;
		if( iResult >= 0 && iResult != pDiaCont->getIndex( this ) )
		{
			throw LException() ;
		}
	}
	// --------------------------------
	m_strName = value ; 
}

void CentDedDia::setPatternDiagramPreviewCycleSecond(const int& value)
{
	m_iPatternDiagramPreviewCycleSecond = value;

	m_iPatternDiagramPreviewRange =
		min(value * 60, 6 * 60 * 60);

}

const CustomizeJikokuhyouContent CentDedDia::getcontCustomizeRessyaIndex(
	ERessyahoukou eRessyahoukou, int iIndex) const
{
	if (eRessyahoukou == ERessyahoukou::Ressyahoukou_Kudari)
	{
		if (iIndex < 0 || iIndex >= (int)m_contCustomizeRessyaIndexKudari.size())
		{
			return CustomizeJikokuhyouContent();
		}
		else
		{
			return m_contCustomizeRessyaIndexKudari[iIndex];
		}
	}
	else
	{
		if (iIndex < 0 || iIndex >= (int)m_contCustomizeRessyaIndexNobori.size())
		{
			return CustomizeJikokuhyouContent();
		}
		else
		{
			return m_contCustomizeRessyaIndexNobori[iIndex];
		}
	}
	return CustomizeJikokuhyouContent();
}





	// ********************************
	//@name CentDedDia-操作
	// ********************************
void CentDedDia::adjustByEkijikokukeisiki(
		const CentDedEkiCont* pCentDedEkiCont ,
		int iEkiIndex )
{
	int iRv = 0 ;

	//		INT_MAX は、末尾を指定したことになります。
	if ( iRv >= 0 )
	{
		if ( iEkiIndex == INT_MAX )
		{
			iEkiIndex = pCentDedEkiCont->size() - 1 ;
		}
		if ( !( 0 <= iEkiIndex && iEkiIndex < pCentDedEkiCont->size() ) )
		{
			iRv = -1 ;	//	iEkiIndex が正しくありません。
		}
	}
	if ( iRv >= 0 )
	{
		for ( int iRessyahoukou = Ressyahoukou_Kudari ;
			iRessyahoukou <= Ressyahoukou_Nobori ;
			iRessyahoukou ++ )
		{
			ERessyahoukou eRessyahoukou = (ERessyahoukou)iRessyahoukou ;

			int iEkiOrder = pCentDedEkiCont->EkiOrderOfEkiIndex( eRessyahoukou , iEkiIndex ) ;
			CentDedEkiCont::CdDedEki aDedEki = pCentDedEkiCont->getMuPtr( eRessyahoukou )->get( iEkiOrder ) ;

			CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont( eRessyahoukou ) ;

			pCentDedRessyaCont->adjustByEkijikokukeisiki( iEkiOrder , 
				aDedEki.getChakujikokuHyouji() , 
				aDedEki.getHatsujikokuHyouji() ) ;

		}
	}
}

void CentDedDia::adjustOperation(
	const CentDedEkiCont * pCentDedEkiCont)
{
	for (int iRessyahoukou = Ressyahoukou_Kudari;
		iRessyahoukou <= Ressyahoukou_Nobori;
		iRessyahoukou++)
	{
		ERessyahoukou eRessyahoukou = (ERessyahoukou)iRessyahoukou;

		const Mu<CentDedEkiCont::CdDedEki>* pMuCentDedEki = pCentDedEkiCont->getMuPtr(eRessyahoukou);
		CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont(eRessyahoukou);

		pCentDedRessyaCont->adjustOperation(
			pCentDedEkiCont,
			pMuCentDedEki);

	}
}

void CentDedDia::adjust()
{
	int iRessyahoukou = 0 ; 
	for ( iRessyahoukou = Ressyahoukou_Kudari ; 
			iRessyahoukou <= Ressyahoukou_Nobori ; 
			iRessyahoukou ++ ){
		m_CentDedRessyaCont[iRessyahoukou]->adjust() ;
	}
}

void CentDedDia::clearCustomizeRessyaIndex()
{
	m_contCustomizeRessyaIndexKudari.clear();
	m_contCustomizeRessyaIndexNobori.clear();

	
	for (int idx = 0; idx < getCentDedRessyaCont(Ressyahoukou_Kudari)->size(); idx++)
	{
		m_contCustomizeRessyaIndexKudari.push_back(CustomizeJikokuhyouContent({ idx }));
	}

	for (int idx = 0; idx < getCentDedRessyaCont(Ressyahoukou_Nobori)->size(); idx++)
	{
		m_contCustomizeRessyaIndexNobori.push_back(CustomizeJikokuhyouContent({ idx }));
	}
}

void CentDedDia::omitInvalidRessyaFromCustomizeRessyaIndex(
	const vector<bool> contHidden)
{
	clearCustomizeRessyaIndex();

	const CentDedRessyaCont* pRessyaContKudari = getCentDedRessyaCont(Ressyahoukou_Kudari);
	const Mu<const CentDedRessya*>* pCentDedRessyaContKudari = pRessyaContKudari->getMuPtr();

	//const Mu<const CentDedRessya*>* pCentDedRessyaContKudari = getCentDedRessyaCont(Ressyahoukou_Kudari)->getMuPtr();
	for (int idx = m_contCustomizeRessyaIndexKudari.size() - 1; idx >= 0; idx--)
	{
		const CentDedRessya* pCentDedRessya = pCentDedRessyaContKudari->get(idx);
		//NULL列車の場合は、空行のまま残します。
		if (pCentDedRessya->isNull())
		{
			continue;
		}

		//運休が有効の場合は、contCustomizeRessyaIndexから削除する
		if (pCentDedRessya->isCanceled())
		{
			m_contCustomizeRessyaIndexKudari.erase(m_contCustomizeRessyaIndexKudari.begin() + idx);
			continue;
		}

		//隠し種別の場合は、contCustomizeRessyaIndexから削除する
		if (contHidden[pCentDedRessya->getRessyasyubetsuIndex()])
		{
			m_contCustomizeRessyaIndexKudari.erase(m_contCustomizeRessyaIndexKudari.begin() + idx);
			continue;
		}

		//有効な始発駅もしくは有効な終着駅が無い場合は、contCustomizeRessyaIndexから削除する
		if (pCentDedRessya->getValidSihatsuEki() < 0 || pCentDedRessya->getValidSyuuchakuEki() < 0)
		{
			m_contCustomizeRessyaIndexKudari.erase(m_contCustomizeRessyaIndexKudari.begin() + idx);
		}
	}
	const CentDedRessyaCont* pRessyaContNobori = getCentDedRessyaCont(Ressyahoukou_Nobori);
	const Mu<const CentDedRessya*>* pCentDedRessyaContNobori = pRessyaContNobori->getMuPtr();
	//const Mu<const CentDedRessya*>* pCentDedRessyaContNobori = getCentDedRessyaCont(Ressyahoukou_Nobori)->getMuPtr();
	for (int idx = m_contCustomizeRessyaIndexNobori.size() - 1; idx >= 0; idx--)
	{
		const CentDedRessya* pCentDedRessya = pCentDedRessyaContNobori->get(idx);
		//NULL列車の場合は、空行のまま残します。
		if (pCentDedRessya->isNull())
		{
			continue;
		}

		//運休が有効の場合は、contCustomizeRessyaIndexから削除する
		if (pCentDedRessya->isCanceled())
		{
			m_contCustomizeRessyaIndexNobori.erase(m_contCustomizeRessyaIndexNobori.begin() + idx);
			continue;
		}

		//隠し種別の場合は、contCustomizeRessyaIndexから削除する
		if (contHidden[pCentDedRessya->getRessyasyubetsuIndex()])
		{
			m_contCustomizeRessyaIndexNobori.erase(m_contCustomizeRessyaIndexNobori.begin() + idx);
			continue;
		}

		//有効な始発駅もしくは有効な終着駅が無い場合は、contCustomizeRessyaIndexから削除する
		if (pCentDedRessya->getValidSihatsuEki() < 0 || pCentDedRessya->getValidSyuuchakuEki() < 0)
		{
			m_contCustomizeRessyaIndexNobori.erase(m_contCustomizeRessyaIndexNobori.begin() + idx);
		}
	}
}

void CentDedDia::copyCustomizeRessyaIndexByPatternDiagramPreview()
{
	if (!m_bPatternDiagramPreviewEnable)
	{
		return;
	}
	deque<CustomizeJikokuhyouContent> contCustomizeRessyaIndexKudariTemp;
	deque<CustomizeJikokuhyouContent> contCustomizeRessyaIndexNoboriTemp;

	contCustomizeRessyaIndexKudariTemp.insert(contCustomizeRessyaIndexKudariTemp.begin(), m_contCustomizeRessyaIndexKudari.begin(), m_contCustomizeRessyaIndexKudari.end());
	contCustomizeRessyaIndexNoboriTemp.insert(contCustomizeRessyaIndexNoboriTemp.begin(), m_contCustomizeRessyaIndexNobori.begin(), m_contCustomizeRessyaIndexNobori.end());

	deque<CustomizeJikokuhyouContent> contCustomizeRessyaIndexKudariShift = contCustomizeRessyaIndexKudariTemp;
	deque<CustomizeJikokuhyouContent> contCustomizeRessyaIndexNoboriShift = contCustomizeRessyaIndexNoboriTemp;

	for (int iShiftSecond = m_iPatternDiagramPreviewCycleSecond; iShiftSecond <= m_iPatternDiagramPreviewRange; iShiftSecond += m_iPatternDiagramPreviewCycleSecond)
	{
		for (int idx = 0; idx < (int)contCustomizeRessyaIndexKudariShift.size(); idx++)
		{
			contCustomizeRessyaIndexKudariShift[idx].iShiftSecond = iShiftSecond;
		}
		for (int idx = 0; idx < (int)contCustomizeRessyaIndexNoboriShift.size(); idx++)
		{
			contCustomizeRessyaIndexNoboriShift[idx].iShiftSecond = iShiftSecond;
		}

		contCustomizeRessyaIndexKudariTemp.insert(contCustomizeRessyaIndexKudariTemp.end(), contCustomizeRessyaIndexKudariShift.begin(), contCustomizeRessyaIndexKudariShift.end());
		contCustomizeRessyaIndexNoboriTemp.insert(contCustomizeRessyaIndexNoboriTemp.end(), contCustomizeRessyaIndexNoboriShift.begin(), contCustomizeRessyaIndexNoboriShift.end());

		for (int idx = 0; idx < (int)contCustomizeRessyaIndexKudariShift.size(); idx++)
		{
			contCustomizeRessyaIndexKudariShift[idx].iShiftSecond = -iShiftSecond;
		}
		for (int idx = 0; idx < (int)contCustomizeRessyaIndexNoboriShift.size(); idx++)
		{
			contCustomizeRessyaIndexNoboriShift[idx].iShiftSecond = -iShiftSecond;
		}

		contCustomizeRessyaIndexKudariTemp.insert(contCustomizeRessyaIndexKudariTemp.begin(), contCustomizeRessyaIndexKudariShift.begin(), contCustomizeRessyaIndexKudariShift.end());
		contCustomizeRessyaIndexNoboriTemp.insert(contCustomizeRessyaIndexNoboriTemp.begin(), contCustomizeRessyaIndexNoboriShift.begin(), contCustomizeRessyaIndexNoboriShift.end());
	}
	m_contCustomizeRessyaIndexKudari.assign(contCustomizeRessyaIndexKudariTemp.begin(), contCustomizeRessyaIndexKudariTemp.end());
	m_contCustomizeRessyaIndexNobori.assign(contCustomizeRessyaIndexNoboriTemp.begin(), contCustomizeRessyaIndexNoboriTemp.end());
}

void CentDedDia::clearOperationTableContent()
{
	m_contOperationTableContent.clear();
}

void CentDedDia::clearInOutLinkCodeContent()
{
	m_contInOutLinkCodeContent.clear();
}

	// ********************************
	//@name CentDedDia-駅数・列車種別数の変更
	// ********************************

int CentDedDia::isExistRessyaOfRessyasyubetsu( 
		int iRessyasyubetsuIndex ,
		ERessyahoukou* peRessyahoukou ,
		int* piRessyaIndex ) const
{
	int iRv = 0 ;
	ERessyahoukou eRessyahoukouFound = Ressyahoukou_Kudari ;
	int iRessyaIndexFound = -1 ;
	// --------------------------------
	if ( iRv >= 0 ){
			int iRessyahoukou = 0 ;
			for ( iRessyahoukou = Ressyahoukou_Kudari ; 
					iRv == 0 && iRessyahoukou <= Ressyahoukou_Nobori ; 
					iRessyahoukou ++ ){
				ERessyahoukou	eRessyahoukou = (ERessyahoukou)iRessyahoukou ;
				
				iRv = m_CentDedRessyaCont[iRessyahoukou]->
					isExistRessyaOfRessyasyubetsu( 
						iRessyasyubetsuIndex , &iRessyaIndexFound ) ;
				if ( iRv == 1 ){
					eRessyahoukouFound = eRessyahoukou ;
				}
			}
	}
	// --------------------------------
	if ( peRessyahoukou != NULL ){
		*peRessyahoukou = eRessyahoukouFound ;
	}
	if ( piRessyaIndex != NULL ){
		*piRessyaIndex = iRessyaIndexFound ;
	}

	return ( iRv ) ;
}

int CentDedDia::isExistRessyaOfEkiTrack2(
	int iEkiIndex,
	int iEkiTrack2Index,
	ERessyahoukou* peRessyahoukou,
	int* piRessyaIndex) const
{
	int iRv = 0;
	ERessyahoukou eRessyahoukouFound = Ressyahoukou_Kudari;
	int iRessyaIndexFound = -1;
	// --------------------------------
	if (iRv >= 0) {
		int iRessyahoukou = 0;
		for (iRessyahoukou = Ressyahoukou_Kudari;
			iRv == 0 && iRessyahoukou <= Ressyahoukou_Nobori;
			iRessyahoukou++) {
			ERessyahoukou	eRessyahoukou = (ERessyahoukou)iRessyahoukou;

			iRv = m_CentDedRessyaCont[iRessyahoukou]->
				isExistRessyaOfEkiTrack2(
					m_CentDedRessyaCont[iRessyahoukou]->EkiOrderOfEkiIndex(iEkiIndex),
					iEkiTrack2Index, &iRessyaIndexFound);
			if (iRv == 1) {
				eRessyahoukouFound = eRessyahoukou;
			}
		}
	}
	// --------------------------------
	if (peRessyahoukou != NULL) {
		*peRessyahoukou = eRessyahoukouFound;
	}
	if (piRessyaIndex != NULL) {
		*piRessyaIndex = iRessyaIndexFound;
	}

	return (iRv);
}

int CentDedDia::isExistRessyaOfOuterTerminal(
	int iEkiIndex,
	int iOuterTerminalIndex,
	ERessyahoukou* peRessyahoukou,
	int* piRessyaIndex) const
{
	int iRv = 0;
	ERessyahoukou eRessyahoukouFound = Ressyahoukou_Kudari;
	int iRessyaIndexFound = -1;
	// --------------------------------
	if (iRv >= 0) {
		int iRessyahoukou = 0;
		for (iRessyahoukou = Ressyahoukou_Kudari;
			iRv == 0 && iRessyahoukou <= Ressyahoukou_Nobori;
			iRessyahoukou++) {
			ERessyahoukou	eRessyahoukou = (ERessyahoukou)iRessyahoukou;

			iRv = m_CentDedRessyaCont[iRessyahoukou]->
				isExistRessyaOfOuterTerminal(
					m_CentDedRessyaCont[iRessyahoukou]->EkiOrderOfEkiIndex(iEkiIndex),
					iOuterTerminalIndex, &iRessyaIndexFound);
			if (iRv == 1) {
				eRessyahoukouFound = eRessyahoukou;
			}
		}
	}
	// --------------------------------
	if (peRessyahoukou != NULL) {
		*peRessyahoukou = eRessyahoukouFound;
	}
	if (piRessyaIndex != NULL) {
		*piRessyaIndex = iRessyaIndexFound;
	}

	return (iRv);
}
	// ********************************
	//@name CentDedRosen-子オブジェクトの増減の通知
	// ********************************
void CentDedDia::onEkiInsert( int iEkiIndex, const vector<int>& iMainTrack)
{
	int iRessyahoukou = 0 ; 
	for ( iRessyahoukou = Ressyahoukou_Kudari ; 
			iRessyahoukou <= Ressyahoukou_Nobori ; 
			iRessyahoukou ++ ){
		if ( iRessyahoukou == Ressyahoukou_Kudari )
		{ 
			m_CentDedRessyaCont[iRessyahoukou]->onEkiInsert( 
				m_CentDedRessyaCont[iRessyahoukou]->EkiOrderOfEkiIndex( iEkiIndex ),
				iMainTrack[iRessyahoukou]) ;
		}	
		else if ( iRessyahoukou == Ressyahoukou_Nobori )
		{ 
			m_CentDedRessyaCont[iRessyahoukou]->onEkiInsert( 
				m_CentDedRessyaCont[iRessyahoukou]->EkiOrderOfEkiIndex( iEkiIndex ) + 1,
				iMainTrack[iRessyahoukou]) ;
			//	この +1 の意味・・・
			//	４駅の路線に、始発駅である駅Index0を追加する場合、
			//	上りのコンテナの駅Order 4(末尾)  に追加しなくてはなりません。 
		}
	}
}

void CentDedDia::onEkiErase( int iEkiIndex  )
{
	int iRessyahoukou = 0 ; 
	for ( iRessyahoukou = Ressyahoukou_Kudari ; 
			iRessyahoukou <= Ressyahoukou_Nobori ; 
			iRessyahoukou ++ ){
		m_CentDedRessyaCont[iRessyahoukou]->onEkiErase( 
			m_CentDedRessyaCont[iRessyahoukou]->EkiOrderOfEkiIndex( iEkiIndex ) ) ;
	}
}

void CentDedDia::onRessyasyubetsuInsert( int iRessyasyubetsuIndex )
{
	int iRessyahoukou = 0 ;
	for ( iRessyahoukou = Ressyahoukou_Kudari ; 
		iRessyahoukou <= Ressyahoukou_Nobori ; iRessyahoukou ++ ){
		m_CentDedRessyaCont[iRessyahoukou]->onRessyasyubetsuInsert( iRessyasyubetsuIndex ) ;
	}
}

void CentDedDia::onRessyasyubetsuErase( int iRessyasyubetsuIndex )
{
	int iRessyahoukou = 0 ;
	for ( iRessyahoukou = Ressyahoukou_Kudari ; 
		iRessyahoukou <= Ressyahoukou_Nobori ; iRessyahoukou ++ ){
		m_CentDedRessyaCont[iRessyahoukou]->onRessyasyubetsuErase( iRessyasyubetsuIndex ) ;
	}
}

void CentDedDia::adjustBrunchLoopByBrunchEdit(
	int iEkiIndex, bool bOriginSide, 
	deque<int>& iEkiIndexBrunchOriginSide,
	deque<int>& iEkiIndexLoop, 
	deque<int>& iEkiIndexBrunchTerminalSide,
	vector<int> &iOuterTerminalEkimeiMap)
{
	//int iRessyahoukou = 0;
	//for (iRessyahoukou = Ressyahoukou_Kudari;
	//	iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++) {
	//for (int idx = 0; idx < (int)iEkiIndexBrunchOriginSide.size(); idx++)
	//{
	//	iEkiOrderBrunchOriginSide.push_back(
	//		m_CentDedRessyaCont[iRessyahoukou]->EkiOrderOfEkiIndex(
	//			iEkiIndexBrunchOriginSide[idx]));
	//}
	//for (int idx = 0; idx < (int)iEkiIndexLoop.size(); idx++)
	//{
	//	iEkiOrderLoop.push_back(
	//		m_CentDedRessyaCont[iRessyahoukou]->EkiOrderOfEkiIndex(
	//			iEkiIndexLoop[idx]));
	//}
	//for (int idx = 0; idx < (int)iEkiIndexBrunchTerminalSide.size(); idx++)
	//{
	//	iEkiOrderBrunchTerminalSide.push_back(
	//		m_CentDedRessyaCont[iRessyahoukou]->EkiOrderOfEkiIndex(
	//			iEkiIndexBrunchTerminalSide[idx]));
	//}
	m_CentDedRessyaCont[Ressyahoukou_Kudari]->adjustBrunchLoopByBrunchEdit(
		iEkiIndex, bOriginSide,
		iEkiIndexBrunchOriginSide, iEkiIndexLoop, iEkiIndexBrunchTerminalSide,
		iOuterTerminalEkimeiMap);


	deque<int> iEkiOrderBrunchOriginSide;
	deque<int> iEkiOrderLoop;
	deque<int> iEkiOrderBrunchTerminalSide;
	//if (iResult == -1)
	//{
	//	return iResult;
	//}
	for (int idx = 0; idx < (int)iEkiIndexBrunchOriginSide.size(); idx++)
	{
		iEkiOrderBrunchTerminalSide.push_front(
			m_CentDedRessyaCont[Ressyahoukou_Nobori]->EkiOrderOfEkiIndex(
				iEkiIndexBrunchOriginSide[idx]));
	}
	for (int idx = 0; idx < (int)iEkiIndexLoop.size(); idx++)
	{
		iEkiOrderLoop.push_front(
			m_CentDedRessyaCont[Ressyahoukou_Nobori]->EkiOrderOfEkiIndex(
				iEkiIndexLoop[idx]));
	}
	for (int idx = 0; idx < (int)iEkiIndexBrunchTerminalSide.size(); idx++)
	{
		iEkiOrderBrunchOriginSide.push_front(
			m_CentDedRessyaCont[Ressyahoukou_Nobori]->EkiOrderOfEkiIndex(
				iEkiIndexBrunchTerminalSide[idx]));
	}
	//if (iResult == INT_MAX)
	//{
	//	return INT_MIN;
	//}
	//else if (iResult == INT_MIN)
	//{
	//	return INT_MAX;
	//}
	//else if (iResult >= 0)
	//{
	//	iResult = (int)iEkiIndexLoop.size() - iResult - 1;
	//}

	m_CentDedRessyaCont[Ressyahoukou_Nobori]->adjustBrunchLoopByBrunchEdit(
		m_CentDedRessyaCont[Ressyahoukou_Nobori]->EkiOrderOfEkiIndex(iEkiIndex),
		!bOriginSide, iEkiOrderBrunchOriginSide,
		iEkiOrderLoop, iEkiOrderBrunchTerminalSide,
		iOuterTerminalEkimeiMap);
	//}
}

void CentDedDia::adjustBrunchLoopByLoopEdit(
	int iEkiIndex, int iPosition,
	deque<int>& iEkiIndexBrunchOriginSide, 
	deque<int>& iEkiIndexLoop, 
	deque<int>& iEkiIndexBrunchTerminalSide,
	vector<int> &iOuterTerminalEkimeiMap)
{
	//int iRessyahoukou = 0;
	//for (iRessyahoukou = Ressyahoukou_Kudari;
	//	iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++) {
		//deque<int> iEkiOrderBrunchOriginSide;
		//deque<int> iEkiOrderLoop;
		//deque<int> iEkiOrderBrunchTerminalSide;
		//for (int idx = 0; idx < (int)iEkiIndexBrunchOriginSide.size(); idx++)
		//{
		//	iEkiOrderBrunchOriginSide.push_back(
		//		m_CentDedRessyaCont[iRessyahoukou]->EkiOrderOfEkiIndex(
		//			iEkiIndexBrunchOriginSide[idx]));
		//}
		//for (int idx = 0; idx < (int)iEkiIndexLoop.size(); idx++)
		//{
		//	iEkiOrderLoop.push_back(
		//		m_CentDedRessyaCont[iRessyahoukou]->EkiOrderOfEkiIndex(
		//			iEkiIndexLoop[idx]));
		//}
		//for (int idx = 0; idx < (int)iEkiIndexBrunchTerminalSide.size(); idx++)
		//{
		//	iEkiOrderBrunchTerminalSide.push_back(
		//		m_CentDedRessyaCont[iRessyahoukou]->EkiOrderOfEkiIndex(
		//			iEkiIndexBrunchTerminalSide[idx]));
		//}
		m_CentDedRessyaCont[Ressyahoukou_Kudari]->adjustBrunchLoopByLoopEdit(
			iEkiIndex,iPosition,
			iEkiIndexBrunchOriginSide, iEkiIndexLoop, iEkiIndexBrunchTerminalSide,
			iOuterTerminalEkimeiMap);
	//}

	deque<int> iEkiOrderBrunchOriginSide;
	deque<int> iEkiOrderLoop;
	deque<int> iEkiOrderBrunchTerminalSide;
	for (int idx = 0; idx < (int)iEkiIndexBrunchOriginSide.size(); idx++)
	{
		iEkiOrderBrunchTerminalSide.push_front(
			m_CentDedRessyaCont[Ressyahoukou_Nobori]->EkiOrderOfEkiIndex(
				iEkiIndexBrunchOriginSide[idx]));
	}
	for (int idx = 0; idx < (int)iEkiIndexLoop.size(); idx++)
	{
		iEkiOrderLoop.push_front(
			m_CentDedRessyaCont[Ressyahoukou_Nobori]->EkiOrderOfEkiIndex(
				iEkiIndexLoop[idx]));
	}
	for (int idx = 0; idx < (int)iEkiIndexBrunchTerminalSide.size(); idx++)
	{
		iEkiOrderBrunchOriginSide.push_front(
			m_CentDedRessyaCont[Ressyahoukou_Nobori]->EkiOrderOfEkiIndex(
				iEkiIndexBrunchTerminalSide[idx]));
	}
	m_CentDedRessyaCont[Ressyahoukou_Nobori]->adjustBrunchLoopByLoopEdit(
		m_CentDedRessyaCont[Ressyahoukou_Nobori]->EkiOrderOfEkiIndex(iEkiIndex),
		iEkiIndexLoop.size() - iPosition - 1,
		iEkiOrderBrunchOriginSide, iEkiOrderLoop, iEkiOrderBrunchTerminalSide,
		iOuterTerminalEkimeiMap);
}

void CentDedDia::adjustBrunchLoopEkiTrack2(
	const deque<int>& iEkiIndexBrunchLoop, 
	const std::vector<int>& iEkiTrack2Map)
{
	int iRessyahoukou = 0;
	for (iRessyahoukou = Ressyahoukou_Kudari;
		iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++) {
		deque<int> iEkiOrderBrunchLoop;
		for (int idx = 0; idx < (int)iEkiIndexBrunchLoop.size(); idx++)
		{
			iEkiOrderBrunchLoop.push_back(
				m_CentDedRessyaCont[iRessyahoukou]->EkiOrderOfEkiIndex(
					iEkiIndexBrunchLoop[idx]));
		}
		m_CentDedRessyaCont[iRessyahoukou]->adjustBrunchLoopEkiTrack2(
			iEkiOrderBrunchLoop,
			iEkiTrack2Map);
	}
}

void CentDedDia::adjustBrunchLoopOuterTerminal(
	const deque<int>& iEkiIndexBrunchLoop,
	const std::vector<int>& iOuterTerminalEkimeiMap)
{
	int iRessyahoukou = 0;
	for (iRessyahoukou = Ressyahoukou_Kudari;
		iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++) 
	{
		deque<int> iEkiOrderBrunchLoop;
		for (int idx = 0; idx < (int)iEkiIndexBrunchLoop.size(); idx++)
		{
			iEkiOrderBrunchLoop.push_back(
				m_CentDedRessyaCont[iRessyahoukou]->EkiOrderOfEkiIndex(
					iEkiIndexBrunchLoop[idx]));
		}
		m_CentDedRessyaCont[iRessyahoukou]->adjustBrunchLoopOuterTerminal(
			iEkiOrderBrunchLoop,
			iOuterTerminalEkimeiMap);
	}
}

void CentDedDia::mergeOuterTerminal(
	const deque<int> &iEkiIndexBrunchOriginSide,
	const deque<int> &iEkiIndexLoop,
	const deque<int> &iEkiIndexBrunchTerminalSide,
	const vector<vector<int>> &iOuterTerminalMapCont)
{

	m_CentDedRessyaCont[Ressyahoukou_Kudari]->mergeOuterTerminal(
		iEkiIndexBrunchOriginSide, iEkiIndexLoop, iEkiIndexBrunchTerminalSide,
		iOuterTerminalMapCont);


	deque<int> iEkiOrderBrunchOriginSide;
	deque<int> iEkiOrderLoop;
	deque<int> iEkiOrderBrunchTerminalSide;

	for (int idx = 0; idx < (int)iEkiIndexBrunchOriginSide.size(); idx++)
	{
		iEkiOrderBrunchTerminalSide.push_front(
			m_CentDedRessyaCont[Ressyahoukou_Nobori]->EkiOrderOfEkiIndex(
				iEkiIndexBrunchOriginSide[idx]));
	}
	for (int idx = 0; idx < (int)iEkiIndexLoop.size(); idx++)
	{
		iEkiOrderLoop.push_front(
			m_CentDedRessyaCont[Ressyahoukou_Nobori]->EkiOrderOfEkiIndex(
				iEkiIndexLoop[idx]));
	}
	for (int idx = 0; idx < (int)iEkiIndexBrunchTerminalSide.size(); idx++)
	{
		iEkiOrderBrunchOriginSide.push_front(
			m_CentDedRessyaCont[Ressyahoukou_Nobori]->EkiOrderOfEkiIndex(
				iEkiIndexBrunchTerminalSide[idx]));
	}
	vector<vector<int>> iOuterTerminalMapContNobori;
	for (int idx = iOuterTerminalMapCont.size() - 1; idx >= 0 ; idx--)
	{
		iOuterTerminalMapContNobori.push_back(iOuterTerminalMapCont[idx]);
	}

	m_CentDedRessyaCont[Ressyahoukou_Nobori]->mergeOuterTerminal(
		iEkiOrderBrunchOriginSide,iEkiOrderLoop, iEkiOrderBrunchTerminalSide,
		iOuterTerminalMapContNobori);
	//}
}

} //namespace entDed
