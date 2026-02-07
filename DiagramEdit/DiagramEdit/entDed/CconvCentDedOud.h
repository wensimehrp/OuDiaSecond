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
//	CconvCentDedOud.h
// $Id: CconvCentDed.h 378 2016-11-16 21:10:54Z okm $
// ****************************************************************
*/
#ifndef  CconvCentDedOud_h
#define  CconvCentDedOud_h

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
//	CconvCentDedOud
// ****************************************************************
/**
	@brief
	  DiagramEdit のエンティティクラスのオブジェクトの属性データの内容を、
	他のデータ形式に変換する関数を収録しています。

	OuPropertiesText::CNodeContainer オブジェクトとの間の変換をサポートしています。 
	
*/
class CconvCentDedOud
{
public:
	// ********************************
	///@name COuErrorInfo::m_strReason , m_Prop の Name
	// ********************************
	///@{
	
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
		  OuPropertiesText オブジェクトに、
		  CentDedEki の属性を追加します。
		@param aCentDedEki [in]
		  CentDedEki を指定してください。
		@param pCNodeContainer [in,out]
		  この関数は、このオブジェクトに、aCentDedEki の内容を追加します。
		@return
		  成功したら 0 以上、エラーなら負の数です。
	 */
	int CentDedEki_To_OuPropertiesText( 
			const CentDedEki& aCentDedEki , 
			OuPropertiesText::CNodeContainer* pCNodeContainer ) ;
		
	// ********************************
	//	CentDedEkiCont
	// ********************************
	
	/**
		  OuPropertiesText オブジェクトに、
		  CentDedEkiCont の属性を追加します。

		  この関数は、 CentDedEki オブジェクトを "Eki" Directory として追加します。
		@param aCentDedEkiCont [in]
		  CentDedEkiCont を指定してください。
		@param pCNodeContainer [in,out]
		  この関数は、このオブジェクトに、aCentDedEkiCont の内容を追加します。
		@return
		  成功したら 0 以上、エラーなら負の数です。
	 */
	int CentDedEkiCont_To_OuPropertiesText( 
			const CentDedEkiCont& aCentDedEkiCont , 
			OuPropertiesText::CNodeContainer* pCNodeContainer ) ;
		
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
		  OuPropertiesText オブジェクトに、
		  CentDedRessyasyubetsu::CdDiagramLineStyle の属性を追加します。
		@param aCdDiagramLineStyle [in]
		  CentDedRessyasyubetsu::CdDiagramLineStyle を指定してください。
		@param pCNodeContainer [in,out]
		  この関数は、このオブジェクトに、内容を追加します。
		@return
		  成功したら 0 以上、エラーなら負の数です。
		  現在のところ、 0 しか返しません。
	 */
	int CdDiagramLineStyle_To_OuPropertiesText( 
			const CentDedRessyasyubetsu::CdDiagramLineStyle& aCdDiagramLineStyle , 
			OuPropertiesText::CNodeContainer* pCNodeContainer ) ;
	
	/**
		  OuPropertiesText オブジェクトに、
		  CentDedRessyasyubetsu の属性を追加します。
		@param aCentDedRessyasyubetsu [in]
		  CentDedRessyasyubetsu を指定してください。
		@param pCNodeContainer [in,out]
		  この関数は、このオブジェクトに、CDedRosenFileData の内容を追加します。
		@return
		  成功したら 0 以上、エラーなら負の数です。
			-	-11 ;	//	Syubetsumei が指定されていません。
			-	-52 ;	//	DiagramSenStyle の値が不正です。
	 */
	int CentDedRessyasyubetsu_To_OuPropertiesText( 
			const CentDedRessyasyubetsu& aCentDedRessyasyubetsu , 
			OuPropertiesText::CNodeContainer* pCNodeContainer ) ;
	
	

	/**
		CentDedRessyasyubetsu::CdDiagramLineStyle の値をもとに、
		CDcdFreeLine::CdLineProp オブジェクトに属性を
		設定します。
	 @param aLineStyle
		線の形状を指定してください。
	 @param pCdLineProp [out]
		この関数はこのオブジェクトに、
		属性を設定します。

	 */
	void CentDedRessyasyubetsu_to_CDcdFreeLineProp(
		const CentDedRessyasyubetsu::CdDiagramLineStyle& aLineStyle , 
		CdDcdFreeLineProp* pCdLineProp )	;

	// ********************************
	//	CentDedRessyasyubetsuCont
	// ********************************
	
	/**
	  OuPropertiesText オブジェクトに、
	  CentDedRessyasyubetsuCont の内容を追加します。
	  この関数は、 CentDedRessyasyubetsu オブジェクトを 
	  "Ressyasyubetsu" Directory として追加します。
	@param aCentDedRessyasyubetsuCont [in]
	  CentDedRessyasyubetsuCont を指定してください。
	@param pCNodeContainer [in,out]
	  この関数は、このオブジェクトに、CDedRosenFileData の内容を追加します。
	@return
	  成功したら 0 以上、エラーなら負の数です。
		-	-11 ;	//	Syubetsumei が指定されていません。
		-	-52 ;	//	DiagramSenStyle の値が不正です。
	 */
	int CentDedRessyasyubetsuCont_To_OuPropertiesText( 
			const CentDedRessyasyubetsuCont& aCentDedRessyasyubetsuCont , 
			OuPropertiesText::CNodeContainer* pCNodeContainer ) ;
			
	// ********************************
	//	CentDedEkiJikoku
	// ********************************
	/**
		CentDedEkijikoku の属性を文字列に変換します。
	@param pCentDedEkijikoku[in]
		変換を行うオブジェクトを指定してください。
	@return
		変換結果を返します。
	*/
	tstring CentDedEkiJikoku_To_string( 
		const CentDedEkiJikoku* pCentDedEkijikoku ) ;
		
	// ********************************
	//	CentDedRessya
	// ********************************
	/**
	@return
		ERessyahoukou と文字列との間のコンバータオブジェクトを返します。
	*/
	static const CEnumToString<ERessyahoukou>& getERessyahoukouToString() ;

	/**
		  OuPropertiesText オブジェクトに、
		  CentDedRessya の属性を追加します。
		@param pCentDedRessya [in]
		  CentDedRessya を指定してください。
		@param pCNodeContainer [in,out]
		  この関数は、このオブジェクトに、 CentDedRessya の内容を追加します。
		@return
		  成功したら 0 以上、エラーなら負の数です。
			-	-12 ;	//	Ressyahoukou の値が不正です。
	 */
	int CentDedRessya_To_OuPropertiesText( 
			const CentDedRessya* pCentDedRessya , 
			OuPropertiesText::CNodeContainer* pCNodeContainer ) ;
		
	// ********************************
	//	CentDedRessyaCont
	// ********************************
	
	/**
		  OuPropertiesText オブジェクトに、
		  CentDedRessyaCont の属性を追加します。
		@param pCentDedRessyaCont [in]
		  CentDedRessya を指定してください。
		@param pCNodeContainer [in,out]
		  この関数は、このオブジェクトに、 CDedRosenFileData の内容を追加します。
		@return
		  成功したら 0 以上、エラーなら負の数です。
			-	-12 ;	//	Ressyahoukou の値が不正です。
	 */
	int CentDedRessyaCont_To_OuPropertiesText( 
			const CentDedRessyaCont* pCentDedRessyaCont , 
			OuPropertiesText::CNodeContainer* pCNodeContainer ) ;
		
	// ********************************
	//	CentDedDia
	// ********************************
	
	/**
		  OuPropertiesText オブジェクトに、
		  CentDedDia の属性を追加します。
		@param pCentDedDia [in]
		  CentDedDia を指定してください。
		@param pCNodeContainer [in,out]
		  この関数は、このオブジェクトに、 pCentDedDia の内容を追加します。
		@return
		  成功したら 0 以上、エラーなら負の数です。
		-	-12 ;	//	DiagramEkiatsukai の値が不正です。
	 */
	int CentDedDia_To_OuPropertiesText( 
			const CentDedDia* pCentDedDia , 
			OuPropertiesText::CNodeContainer* pCNodeContainer ) ;
		
	// ********************************
	//	CentDedDiaCont
	// ********************************
	
	/**
		  OuPropertiesText オブジェクトに、
		  CentDedDiaCont の属性を追加します。
		@param pCentDedDiaCont [in]
		  CentDedDiaCont を指定してください。
		@param pCNodeContainer [in,out]
		  この関数は、このオブジェクトに、 CDedRosenFileData の内容を追加します。
		@return
		  成功したら 0 以上、エラーなら負の数です。
		-	-12 ;	//	DiagramEkiatsukai の値が不正です。
	 */
	int CentDedDiaCont_To_OuPropertiesText( 
			const CentDedDiaCont* pCentDedDiaCont , 
			OuPropertiesText::CNodeContainer* pCNodeContainer ) ;
		
	// ********************************
	//	CentDedRosen
	// ********************************
	
	/**
		  OuPropertiesText オブジェクトに、
		  CentDedRosen の属性を追加します。
		@param pCentDedRosen [in]
		  CentDedRosen を指定してください。
		@param pCNodeContainer [in,out]
		  この関数は、このオブジェクトに、 CDedRosenFileData の内容を反映します。
		  pCNodeContainer がそれまで保持していたオブジェクトは破棄します。
		@return
		  成功したら 0 以上、エラーなら負の数です。
			-	-22 ;	//	Ekijikokukeisiki の値が不正です。
			-	-32 ;	//	Ekikibo の値が不正です。
			-	-111 ;	//	Syubetsumei が指定されていません。
			-	-152 ;	//	DiagramSenStyle の値が不正です。
			-	-212 ;	//	DiagramEkiatsukai の値が不正です。
	 */
	int CentDedRosen_To_OuPropertiesText( 
			const CentDedRosen* pCentDedRosen , 
			OuPropertiesText::CNodeContainer* pCNodeContainer ) ;
		
};	

} //namespace entDed

#endif /*CconvCentDedOud_h*/
	
