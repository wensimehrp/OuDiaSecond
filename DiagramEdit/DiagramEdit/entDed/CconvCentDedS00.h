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
//	CconvCentDedS00.h
// $Id: CconvCentDedS00.h 378 2016-11-16 21:10:54Z okm $
// ****************************************************************
*/
#ifndef  CconvCentDedS00_h
#define  CconvCentDedS00_h

/** @file */

#include "str¥OuPropertiesText¥CNodeContainer.h"
#include "str¥OuPropertiesText¥ErrorInfo¥COuErrorInfoContainer.h"
#include "str¥CEnumToString.h"
#include "DcdCd¥DcDrawProp¥CdDcdFreeLineProp.h"
#include "DcdCd¥DcDrawProp¥CdColorProp.h"

#include "CentDedEki.h"
#include "CentDedRessyasyubetsu.h"
#include "CentDedEkiJikoku.h"
#include "CentDedRessya.h"
#include "CentDedRessyaCont.h"
#include "CentDedDia.h"
#include "CentDedRosen.h"

namespace entDed{
	using namespace OuLib::Str;

// ****************************************************************
//	CconvCentDedS00
// ****************************************************************
/**
	@brief
	  DiagramEdit のエンティティクラスのオブジェクトの属性データの内容を、
	他のデータ形式に変換する関数を収録しています。

	OuPropertiesText::CNodeContainer オブジェクトとの間の変換をサポートしています。 

	このクラスでは、OuDiaSecond1.00形式のファイルの読み込みに対応します
	
*/
class CconvCentDedS00
{
public:
	// ********************************
	///@name COuErrorInfo::m_strReason , m_Prop の Name
	// ********************************
	///@{
	

	/**
	"TrackName" が正しくありません。
	@param TrackName
	指定されている種別名
	*/
	static const TCHAR* ERRREASON_TrackNameIsInvalid() { return _T("TrackName is invalid."); };

	/**
	"TrackRyakusyou" が正しくありません。
	@param TrackRyakusyou
	指定されている種別名
	*/
	static const TCHAR* ERRREASON_TrackRyakusyouIsInvalid() { return _T("TrackRyakusyou is invalid."); };

	/**
		"Ekijikokukeisiki" が正しくありません。
		@param Ekijikokukeisiki
			指定されている駅時刻形式
	*/
	static const TCHAR* ERRREASON_EkijikokukeisikiIsInvalid(){	return _T("Ekijikokukeisiki is invalid.") ;};

	/**
		"Ekikibo" が正しくありません。
		@param Ekikibo
			指定されている駅規模
	*/
	static const TCHAR* ERRREASON_EkikiboIsInvalid(){	return _T("Ekikibo is invalid.") ;};

	/**
		"DiagramRessyajouhouHyouji" が正しくありません。
		@param DiagramRessyajouhouHyoujiKudari
			指定されている内容
		@param DiagramRessyajouhouHyoujiNobori
			指定されている内容
	*/
	static const TCHAR* ERRREASON_DiagramRessyajouhouHyoujiIsInvalid(){	return _T("DiagramRessyajouhouHyouji is invalid.") ;};

	/**
		"Eki" がディレクトリではありません。
		@param Index
			対象となる Eki の番号(0起点)を指定してください。
	*/
	static const TCHAR* ERRREASON_EkiIsNotDirectory(){	return _T("Eki Is Not Directory.") ;};
	static const TCHAR* ERRPROP_Index(){	return _T("Index") ;};

	/**
		"Syubetsumei" が正しくありません。
		@param Syubetsumei
			指定されている種別名
	*/
	static const TCHAR* ERRREASON_SyubetsumeiIsInvalid(){	return _T("Syubetsumei is invalid.") ;};
	/**
		"DiagramSenStyle" が正しくありません。
		@param DiagramSenStyle
			指定されている値
	*/
	static const TCHAR* ERRREASON_DiagramSenStyleIsInvalid(){	return _T("DiagramSenStyle is invalid.") ;};

	/**
		"Ressyasyubetsu" がディレクトリではありません。
		@param Index
			対象となる Ressyasyubetsu の番号(0起点)を指定してください。
	*/
	static const TCHAR* ERRREASON_RessyasyubetsuIsNotDirectory(){	return _T("Ressyasyubetsu is invalid.") ;};

	/**
		"DiaName" が正しくありません。
	*/
	static const TCHAR* ERRREASON_DiaNameInvalid(){	return _T("DiaName is invalid.") ;};

	/**
		"RessyaCont" が見つかりません。
		@param Ressyahoukou
			見つからなかったRessyaContの列車方向。 "Kudari" か "Nobori" のいずれかです。
	*/
	static const TCHAR* ERRREASON_ResyaContIsNotExist(){	return _T("Ressyahoukou is Not Exist.") ;};

	static const TCHAR* ERRPROP_Ressyahoukou(){	return _T("Ressyahoukou") ;};

	/**
		起点時刻が不正です。
	@param Jikoku
		指定された時刻
	*/
	static const TCHAR* ERRREASON_KitenjikokuIsInvalid(){	return _T("Kitenjikoku Is Invelid.") ;};

	static const TCHAR* ERRPROP_Jikoku(){	return _T("Jikoku") ;};

	/**
		ダイヤグラムの既定の駅間幅が不正です。
	@param Value
		設定されている値
	*/
	static const TCHAR* ERRREASON_DiagramDgrYZahyouKyoriDefaultIsInvalid(){	return _T("DiagramDgrYZahyouKyoriDefault Is Invelid.") ;};

	static const TCHAR* ERRPROP_Value(){	return _T("Value") ;};
	/**
		値の形式が正しくありません。
	@param Name
		項目名
	@param Value
		設定されている値
	*/
	static const TCHAR* ERRREASON_InvalidValueFormat(){	return _T("Invalid Value Format.") ;};

	static const TCHAR* ERRPROP_Name(){	return _T("Name") ;};



	///@}
 public:

	// ********************************
	//	CentDedEki
	// ********************************
	/**
	@return
		CentDedEki::EEkijikokukeisiki と文字列の間のコンバータオブジェクトを返します。
	*/
	static const CEnumToString< CentDedEki::EEkijikokukeisiki >& getEEkijikokukeisikiToString();

	/**
	@return
		CentDedEki::EEkikibo と文字列の間のコンバータオブジェクトを返します。
	*/
	static const CEnumToString< CentDedEki::EEkikibo >& getEEkikiboToString();

	/**
	@return
		CentDedEki::EDiagramRessyajouhouHyouji と文字列の間のコンバータオブジェクトを返します。
	*/
	static const CEnumToString< CentDedEki::EDiagramRessyajouhouHyouji >& 
		getEDiagramRessyajouhouHyoujiToString() ;
		
	/**
		  OuPropertiesText オブジェクトから、
		  CentDedEki_To_OuPropertiesText() 関数によって作成された
		アイテムを読み込み、 CentDedEki オブジェクトに反映します。
		
		@param pCentDedEki [out]
		  この関数はこのオブジェクトに、属性を反映します。
		@param pCNodeContainer [in]
		  属性を保持している OuPropertiesText オブジェクトを指定してください。
		@param pCOuErrorInfoContainer [in,out]
		  この関数はエラーが発生したら、エラーの情報をこのオブジェクトに追加します。
		@return
		  成功したら 0 以上、エラーなら負の数です。
			-	-22 ;	//	Ekijikokukeisiki の値が不正です。
			-	-32 ;	//	Ekikibo の値が不正です。
			-	-41 ;	//	DiagramRessyajouhouHyoujiKudari の値が不正です。
			-	-42 ;	//	DiagramRessyajouhouHyoujiNobori の値が不正です。
	 */
	int CentDedEki_From_OuPropertiesText( 
			CentDedEki* pCentDedEki ,
			const OuPropertiesText::IfNodeContainerConst* pCNodeContainer ,
			OuPropertiesText::ErrorInfo::COuErrorInfoContainer* pCOuErrorInfoContainer ) ;
	
	// ********************************
	//	CentDedEkiCont
	// ********************************
		
	/**
		  OuPropertiesText オブジェクトから、
		  CentDedEki_To_OuPropertiesText() 関数によって作成された
		アイテムを読み込み、 CentDedEki オブジェクトに反映します。
		
		@param pCentDedEkiCont [in,out]
		  この関数はこのオブジェクトに、属性を追加します。
		@param pCNodeContainer [in]
		  属性を保持している OuPropertiesText オブジェクトを指定してください。
		@param pCOuErrorInfoContainer [in,out]
		  この関数はエラーが発生したら、エラーの情報をこのオブジェクトに追加します。
		@return
		  成功したら 0 以上、エラーなら負の数です。
			-	-22 ;	//	Ekijikokukeisiki の値が不正です。
			-	-32 ;	//	Ekikibo の値が不正です。
			-	-41 ;	//	DiagramRessyajouhouHyoujiKudari の値が不正です。
			-	-42 ;	//	DiagramRessyajouhouHyoujiNobori の値が不正です。
			-	-101 ;	//	Eki がディレクトリではありません。
	 */
	int CentDedEkiCont_From_OuPropertiesText( 
			CentDedEkiCont* aCentDedEkiCont ,
			const OuPropertiesText::IfNodeContainerConst* pCNodeContainer ,
			OuPropertiesText::ErrorInfo::COuErrorInfoContainer* pCOuErrorInfoContainer ) ;
	
	// ********************************
	//	CentDedRessyasyubetsu
	// ********************************
	/**
	@return
		CentDedRessyasyubetsu::ESenStyle と 文字列との間のコンバータオブジェクトを
		返します。
	*/
	static const CEnumToString< CentDedRessyasyubetsu::ESenStyle >& 
		getESenStyleToString();
	static const CEnumToString< CentDedRessyasyubetsu::EStopMarkDrawType >& 
		getEStopMarkDrawTypeToString() ;
	
	/**
		  OuPropertiesText オブジェクトから、
		  CentDedRessyasyubetsu_To_OuPropertiesText() 関数によって作成された
		アイテムを読み込み、 CentDedRessyasyubetsu オブジェクトに反映します。
		
		@param pCdDiagramLineStyle [out]
		  この関数はこのオブジェクトに、属性を反映します。
		@param pCNodeContainer [in]
		  属性を保持している OuPropertiesText オブジェクトを指定してください。
		@param pCOuErrorInfoContainer [in,out]
		  この関数はエラーが発生したら、エラーの情報をこのオブジェクトに追加します。
		@return
		  成功したら 0 以上、エラーなら負の数です。
			-	-52 ;	//	DiagramSenStyle の値が不正です。
	 */
	int CdDiagramLineStyle_From_OuPropertiesText( 
			CentDedRessyasyubetsu::CdDiagramLineStyle* pCdDiagramLineStyle ,
			const OuPropertiesText::IfNodeContainerConst* pCNodeContainer ,
			OuPropertiesText::ErrorInfo::COuErrorInfoContainer* pCOuErrorInfoContainer ) ;
		
	/**
		  OuPropertiesText オブジェクトから、
		  CentDedRessyasyubetsu_To_OuPropertiesText() 関数によって作成された
		アイテムを読み込み、 CentDedRessyasyubetsu オブジェクトに反映します。
		
		@param pCentDedRessyasyubetsu [out]
		  この関数はこのオブジェクトに、属性を反映します。
		@param pCNodeContainer [in]
		  属性を保持している OuPropertiesText オブジェクトを指定してください。
		@param pCOuErrorInfoContainer [in,out]
		  この関数はエラーが発生したら、エラーの情報をこのオブジェクトに追加します。
		@return
		  成功したら 0 以上、エラーなら負の数です。
			-	-11 ;	//	Syubetsumei が指定されていません。
			-	-52 ;	//	DiagramSenStyle の値が不正です。
			-	-101 ;	//	値の形式が正しくありません。
	 */
	int CentDedRessyasyubetsu_From_OuPropertiesText( 
			CentDedRessyasyubetsu* pCentDedRessyasyubetsu ,
			const OuPropertiesText::IfNodeContainerConst* pCNodeContainer ,
			OuPropertiesText::ErrorInfo::COuErrorInfoContainer* pCOuErrorInfoContainer ) ;
	
	// ********************************
	//	CentDedRessyasyubetsuCont
	// ********************************
		
	/**
	  OuPropertiesText オブジェクトから、
	  CentDedRessyasyubetsuCont_To_OuPropertiesText() 関数によって作成された
	アイテムを読み込み、 CentDedRessyasyubetsu オブジェクトに反映します。
	
	@param pCentDedRessyasyubetsuCont [in,out]
	  この関数はこのオブジェクトに、属性を上書きします。
	  pCentDedRessyasyubetsuCont の要素数が少ない場合は、
	  要素を追加します。
	@param pCNodeContainer [in]
	  属性を保持している OuPropertiesText オブジェクトを指定してください。
	@param pCOuErrorInfoContainer [in,out]
	  この関数はエラーが発生したら、エラーの情報をこのオブジェクトに追加します。
	@return
	  成功したら 0 以上、エラーなら負の数です。
		-	-11 ;	//	Syubetsumei が指定されていません。
		-	-52 ;	//	DiagramSenStyle の値が不正です。
		-	-101 ;	//	Ressyasyubetsu がディレクトリではありません。
	 */
	int CentDedRessyasyubetsuCont_From_OuPropertiesText( 
			CentDedRessyasyubetsuCont* pCentDedRessyasyubetsuCont ,
			const OuPropertiesText::IfNodeContainerConst* pCNodeContainer ,
			OuPropertiesText::ErrorInfo::COuErrorInfoContainer* pCOuErrorInfoContainer ) ;

	
	// ********************************
	//	CentDedEkiJikoku
	// ********************************

	/**
		CentDedEkijikoku_To_string() で生成した文字列を、
		CentDedEkijikoku の属性に反映します。
	@param pCentDedEkijikoku[out]
		この関数はこのオブジェクトに、属性を反映します。
	@param strValue[in]
		属性を保持する文字列を指定してください。
	@return
		成功したら 0 以上、エラーなら負の数です。
		- 現在のところ、エラーはありません。
		
	*/
	int CentDedEkiJikoku_From_string( 
			CentDedEkiJikoku* pCentDedEkijikoku , 
			const tstring strValue,
			const int iMainTrack) ;
	
	// ********************************
	//	CentDedRessya
	// ********************************
	/**
	@return
		ERessyahoukou と文字列との間のコンバータオブジェクトを返します。
	*/
	static const CEnumToString<ERessyahoukou>& getERessyahoukouToString() ;
		
	/**
		  OuPropertiesText オブジェクトから、
		  CentDedRessya_To_OuPropertiesText() 関数によって作成された
		アイテムを読み込み、 CentDedRessya オブジェクトに反映します。
		
		  ただし、
	
			- 列車方向
			- オブジェクトが包含する 『駅時刻』 の数
	
		は、変更しません。この値は、関数呼出元によって設定されている
		必要があります。
		@param pCentDedRessya [in,out]
		  この関数はこのオブジェクトに、列車の属性を反映します。
			ただし、オブジェクトの属性『列車方向』と
			包含する 『駅時刻』 の数は変更しません。
			この値は、関数呼出元によって設定されている必要があります。
		@param pCNodeContainer [in]
		  属性を保持している OuPropertiesText オブジェクトを指定してください。
		@param pCOuErrorInfoContainer [out]
		  この関数はエラーが発生したら、エラーの情報をこのオブジェクトに追加します。
		@return
		  成功したら 0 以上、エラーなら負の数です。
			- 現在のところ、エラーはありません。
	 */
	int CentDedRessya_From_OuPropertiesText( 
			CentDedRessya* pCentDedRessya ,
			const OuPropertiesText::IfNodeContainerConst* pCNodeContainer ,
			OuPropertiesText::ErrorInfo::COuErrorInfoContainer* pCOuErrorInfoContainer ) ;
	
	
	// ********************************
	//	CentDedRessyaCont
	// ********************************
		
	/**
		  OuPropertiesText オブジェクトから、
		  CentDedRessya_To_OuPropertiesText() 関数によって作成された
		アイテムを読み込み、 CentDedRessyaCont オブジェクトに反映します。
		
		@param pCentDedRessyaCont [in,out]
			この関数はこのコンテナの末尾に、
			OuPropertiesText オブジェクトに保存されている属性のオブジェクトを
			追加します。¥n
			ただし、追加されるオブジェクトの 『駅時刻』 の数は、
			m_iEkiCount に決まっています。 aCdConectedString に保存されている
			列車がこれより多い『駅時刻』を保持していた場合は、終着駅寄りの時刻が
			切捨てとなります。
		@param pCNodeContainer [in]
		  属性を保持している OuPropertiesText オブジェクトを指定してください。
		@param pCOuErrorInfoContainer [out]
		  この関数はエラーが発生したら、エラーの情報をこのオブジェクトに追加します。
		@return
		  成功したら 0 以上、エラーなら負の数です。
			- 現在のところ、エラーはありません。
	 */
	int CentDedRessyaCont_From_OuPropertiesText( 
			CentDedRessyaCont* pCentDedRessyaCont ,
			const OuPropertiesText::IfNodeContainerConst* pCNodeContainer ,
			OuPropertiesText::ErrorInfo::COuErrorInfoContainer* pCOuErrorInfoContainer ) ;
	
	
	// ********************************
	//	CentDedDia
	// ********************************
		
	/**
		  OuPropertiesText オブジェクトから、
		  CentDedDia_To_OuPropertiesText() 関数によって作成された
		アイテムを読み込み、 CentDedDia オブジェクトに反映します。
		
		@param pCentDedDia [in,out]
		  この関数はこのオブジェクトに、属性を反映します。
		  このオブジェクトには、あらかじめ 『駅の数』・『列車種別数』
		が設定されていなくてはなりません。
		@param pCNodeContainer [in]
		  属性を保持している OuPropertiesText オブジェクトを指定してください。
		@param pCOuErrorInfoContainer [out]
		  この関数はエラーが発生したら、エラーの情報をこのオブジェクトに追加します。
		@return
		  成功したら 0 以上、エラーなら負の数です。
		-	-11 ;	//	DiaName が指定されていません。
		-	-12 ;	//	RessyaContが見つかりません。
	 */
	int CentDedDia_From_OuPropertiesText( 
			CentDedDia* pCentDedDia ,
			const OuPropertiesText::IfNodeContainerConst* pCNodeContainer ,
			OuPropertiesText::ErrorInfo::COuErrorInfoContainer* pCOuErrorInfoContainer ) ;
	
	// ********************************
	//	CentDedDiaCont
	// ********************************
	
	/**
		  OuPropertiesText オブジェクトから、
		  CentDedDiaCont_To_OuPropertiesText() 関数によって作成された
		アイテムを読み込み、 CentDedDiaCont オブジェクトに反映します。
		
		@param pCentDedDiaCont [in,out]
		  この関数はこのオブジェクトに、属性を反映します。
		  このオブジェクトには、あらかじめ 『駅の数』・『列車種別数』
		が設定されていなくてはなりません。
		@param pCNodeContainer [in]
		  属性を保持している OuPropertiesText オブジェクトを指定してください。
		@param pCOuErrorInfoContainer [out]
		  この関数はエラーが発生したら、エラーの情報をこのオブジェクトに追加します。
		@return
		  成功したら 0 以上、エラーなら負の数です。
		-	-11 ;	//	DiaName が指定されていません。
		-	-12 ;	//	RessyaContが見つかりません。
	 */
	int CentDedDiaCont_From_OuPropertiesText( 
			CentDedDiaCont* pCentDedDiaCont ,
			const OuPropertiesText::IfNodeContainerConst* pCNodeContainer ,
			OuPropertiesText::ErrorInfo::COuErrorInfoContainer* pCOuErrorInfoContainer ) ;
	
	// ********************************
	//	CentDedRosen
	// ********************************
		
	/**
		  OuPropertiesText オブジェクトから、
		  CentDedRosen_To_OuPropertiesText() 関数によって作成された
		アイテムを読み込み、 CentDedRosen オブジェクトに反映します。
		
		@param pCentDedRosen [out]
		  この関数はこのオブジェクトに、属性を反映します。
		@param pCNodeContainer [in]
		  属性を保持している OuPropertiesText オブジェクトを指定してください。
		@param pCOuErrorInfoContainer [out]
		  この関数はエラーが発生したら、エラーの情報をこのオブジェクトに追加します。
		@return
		  成功したら 0 以上、エラーなら負の数です。
			-	-22 ;	//	Ekijikokukeisiki の値が不正です。
			-	-32 ;	//	Ekikibo の値が不正です。
			-	-41 ;	//	DiagramRessyajouhouHyoujiKudari の値が不正です。
			-	-42 ;	//	DiagramRessyajouhouHyoujiNobori の値が不正です。
			-	-101 ;	//	Eki がディレクトリではありません。
			-	-111 ;	//	Syubetsumei が指定されていません。
			-	-152 ;	//	DiagramSenStyle の値が不正です。
			-	-201 ;	//	Ressyasyubetsu がディレクトリではありません。
			-	-211 ;	//	DiaName が指定されていません。
			-	-212 ;	//	RessyaContが見つかりません。
			-	-352 ;	//	起点時刻の設定が不適切です。
			-	-353 ;	//	ダイヤグラムの既定の駅間幅が不正です。
	 */
	int CentDedRosen_From_OuPropertiesText( 
			CentDedRosen* pCentDedRosen ,
			const OuPropertiesText::IfNodeContainerConst* pCNodeContainer ,
			OuPropertiesText::ErrorInfo::COuErrorInfoContainer* pCOuErrorInfoContainer ) ;
	
	/**
		旧形式ファイルを読み込み、分岐駅設定を認識できた場合、
		基幹駅・分岐駅間での、停車・通過の摺り合わせを行います。
	
	*/
	void AdjustBrunch(
		const CentDedEkiCont* pCentDedEkiCont,
		CentDedDiaCont* pCentDedDiaCont);
	
};	

} //namespace entDed

#endif /*CconvCentDedS00_h*/
	
