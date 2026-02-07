/*
	OuDiaSecond Copyright (C) 2017-2018 diagram_mania

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
/*─
// ****************************************************************
//	CconvCDedRosenFileData.h
// ****************************************************************
*/
#ifndef  CconvCDedRosenFileData_h
#define  CconvCDedRosenFileData_h
/** @file */
#include "CconvCdDedDispProp.h"
#include "str¥OuPropertiesText¥CNodeContainer.h"
#include "str¥OuPropertiesText¥ErrorInfo¥COuErrorInfoContainer.h"

namespace DedRosenFileData{

// ****************************************************************
//	CconvCDedRosenFileData
// ****************************************************************
/**
@brief
  『路線ファイル』データ ( CDedRosenFileData ) と
  他のデータ形式との間の相互変換機能です。
	
	 『路線ファイル』データと  OuPropertiesText::CNodeContainer オブジェクトとの間の
	変換をサポートしています。 
	
	<H4>
	【路線ファイル (.ded) 】
	</H4>
	  『路線ファイル』は、路線ファイルデータクラスを
	 CDedRosenFileData_To_string() で文字列に変換し、その文字列全体を
	保存したテキストファイルです。
	
	   CDedRosenFileData_To_string() 関数は、
	   CDedRosenFileData オブジェクトが保持するデータを
	以下の手順で文字列に変換します。
	  この文字列をファイルに保存することにより、
	 『路線ファイル』となります。
*/
class CconvCDedRosenFileData
{
public:
	// ********************************
	///@name COuErrorInfo::m_strReason , m_Prop に指定するための文字列
	// ********************************
	///@{
	/**
		OuErrorInfo::m_strReason に指定するためのエラー文字列。
		FileType が不正です。
	@param FileType
		FileType
	*/
	static const TCHAR* ERRREASON_FileTypeIsInvalid(){	return _T("FileType Is Invalid.") ;};
	static const TCHAR* ERRPROP_FileType(){	return _T("FileType") ;};
	/**
		OuErrorInfo::m_strReason に指定するためのエラー文字列。
		Rosen Directory が見つかりません。
	*/
	static const TCHAR* ERRREASON_RosenDirectoryIsNotFound(){	return _T("Rosen Directory is not found.") ;};
	/**
		OuErrorInfo::m_strReason に指定するためのエラー文字列。
		DispProp Directory が見つかりません。
	*/
	static const TCHAR* ERRREASON_DispPropnDirectoryIsNotFound(){	return _T("DispProp Directory is not found.") ;};
	///@}
public:
	// ********************************
	//	CdDedDispProp
	// ********************************
	/** 25.5.27filetype更新_by_d_mania
	@return
	PropertyTextアイテム "FileType" の値です。
	*/
	static tstring getFileType() { return _T("OuDiaSecond.1.16"); };
	/** 24.10.7filetype更新_by_d_mania
	@return
	PropertyTextアイテム "FileType" の値です。
	*/
	static tstring getFileTypeS15() { return _T("OuDiaSecond.1.15"); };
	/** 23.1.6filetype更新_by_d_mania
	@return
	PropertyTextアイテム "FileType" の値です。
	*/
	static tstring getFileTypeS14() { return _T("OuDiaSecond.1.14"); };
	/** 22.1.10filetype更新_by_d_mania
	@return
	PropertyTextアイテム "FileType" の値です。
	*/
	static tstring getFileTypeS13() { return _T("OuDiaSecond.1.13"); };
	/** 21.9.16filetype更新_by_d_mania
	@return
	PropertyTextアイテム "FileType" の値です。
	*/
	static tstring getFileTypeS12() { return _T("OuDiaSecond.1.12"); };
	/** 21.5.18filetype更新_by_d_mania
	@return
	PropertyTextアイテム "FileType" の値です。
	*/
	static tstring getFileTypeS11() { return _T("OuDiaSecond.1.11"); };
	/** 20.11.8filetype更新_by_d_mania
	@return
	PropertyTextアイテム "FileType" の値です。
	*/
	static tstring getFileTypeS10() { return _T("OuDiaSecond.1.10"); };
	/** 20.3.12filetype更新_by_d_mania
	@return
	PropertyTextアイテム "FileType" の値です。
	*/
	static tstring getFileTypeS09() { return _T("OuDiaSecond.1.09"); };
	/** 19.12.23filetype更新_by_d_mania
	@return
	PropertyTextアイテム "FileType" の値です。
	*/
	static tstring getFileTypeS08() { return _T("OuDiaSecond.1.08"); };
	/** 19.7.26filetype更新_by_d_mania
	@return
	PropertyTextアイテム "FileType" の値です。
	*/
	static tstring getFileTypeS07() { return _T("OuDiaSecond.1.07"); };
	/** 19.3.29filetype更新_by_d_mania
	@return
	PropertyTextアイテム "FileType" の値です。
	*/
	static tstring getFileTypeS06() { return _T("OuDiaSecond.1.06"); };

	/** 18.10.1filetype更新_by_d_mania
	@return
	PropertyTextアイテム "FileType" の値です。
	*/
	static tstring getFileTypeS05() { return _T("OuDiaSecond.1.05"); };

	/** 18.3.27filetype更新_by_d_mania
	@return
	PropertyTextアイテム "FileType" の値です。
	*/
	static tstring getFileTypeS04() { return _T("OuDiaSecond.1.04"); };

	/** 17.12.7filetype更新_by_d_mania
	@return
	PropertyTextアイテム "FileType" の値です。
	*/
	static tstring getFileTypeS03() { return _T("OuDiaSecond.1.03"); };

	/** 17.10.30filetype更新_by_d_mania
	@return
	PropertyTextアイテム "FileType" の値です。
	*/
	static tstring getFileTypeS02() { return _T("OuDiaSecond.1.02"); };

	/** 17.9.25filetype更新_by_d_mania
	@return
	PropertyTextアイテム "FileType" の値です。
	*/
	static tstring getFileTypeS01() { return _T("OuDiaSecond.1.01"); };

	/** 17.4.14filetypeをオリジナル版に更新_by_d_mania
	 @return
		PropertyTextアイテム "FileType" の値です。
	*/
	static tstring getFileTypeS00(){	return _T("OuDiaSecond.1.00") ; } ;
	
	/**17.4.14オリジナルファイルを変換無しで読み込めるように追加_by_d_mania
	 @return
		PropertyTextアイテム "FileType" の値です。
	*/
	static tstring getFileTypeOud(){	return _T("OuDia.1.02") ; } ;
	
	// ********************************
	///@name	OuPropertiesText への変換
	// ********************************
	///@{
	/**
		  OuPropertiesText オブジェクトに、
		  CDedRosenFileData の属性を追加します。
		@param aCDedRosenFileData [in]
		  CDedRosenFileData を指定してください。
		  pCNodeContainer には、"FileType" PropertyString を含みます。
		@param pCNodeContainer [out]
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
	int CDedRosenFileData_to_OuPropertiesText( 
			const CDedRosenFileData* pCDedRosenFileData , 
			OuPropertiesText::CNodeContainer* pCNodeContainer ) ;
	
	/**
		  OuPropertiesText オブジェクトから、
		  CDedRosenFileData_to_OuPropertiesText() 関数によって作成された
		アイテムを読み込み、 CDedRosenFileData オブジェクトに反映します。
		
		@param pCDedRosenFileData [out]
		  この関数はこのオブジェクトに、属性を反映します。
		  このオブジェクトがそれまで保持していたデータは破棄します。
		@param pCNodeContainer [in]
		  属性を保持している OuPropertiesText オブジェクトを指定してください。
		@param pCOuErrorInfoContainer [out]
		  この関数はエラーが発生したら、エラーの情報をこのオブジェクトに追加します。
		  不要であればNULLを指定してください。
		@return
		  成功したら 0 以上、エラーなら負の数です。
			-	-1 ;	//	FileType が正しくありません。
			-	-2 ;	//	Rosen Directoryが見つかりません。
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
			-	-3 ;	//	DispProp Directoryが見つかりません。
			-	-512 ;	//	JikokuhyouFont の内容が不正です。
			-	-522 ;	//	DiaEkimeiFont の内容が不正です。
			-	-532 ;	//	DiaJikokuFont の内容が不正です。
			-	-582 ;	//	DisplayRessyabangou が不正です。
			-	-592 ;	//	DisplayRessyamei が不正です。
			-	-602 ;	//	DiaRessyajouhouHyoujiEkiOrderKudari が不正です。
			-	-612 ;	//	DiaRessyajouhouHyoujiEkiOrderNobori が不正です。
	*/
	int CDedRosenFileData_from_OuPropertiesText( 
			CDedRosenFileData* pCDedRosenFileData ,
			const OuPropertiesText::CNodeContainer* pCNodeContainer ,
			OuPropertiesText::ErrorInfo::COuErrorInfoContainer* pCOuErrorInfoContainer ) ;
	
	/**
		  OuPropertiesText オブジェクトが
		このクラスで解釈可能なフォーマットか否かを判定します。
	@param pCNodeContainer [in]
		  属性を保持している OuPropertiesText オブジェクトを指定してください。
	@return
		-	0 ;	//	解釈可能です。
		-	-1 ;	//	FileType が正しくありません。
		
	@note
		FileType の値を判定します。
	*/
	int isEncodeAbleFormat( 
			const OuPropertiesText::CNodeContainer* pCNodeContainer ) ;
	
	
	///@}
	// ********************************
	///@name 路線ファイル形式文字列への変換
	// ********************************
	///@{
	/**
		  CDedRosenFileData の保持するデータから、
		『路線ファイル』(.ded) 形式の文字列を作成します。
	
		@param aCDedRosenFileData [in]
		  CDedRosenFileData を指定してください。
		@param pString [out]
		  この関数は、この文字列オブジェクトに、
		『路線ファイル』(.ded) 形式の文字列を設定します。
		  このオブジェクトがそれまで保持していた文字列は破棄します。
		@return
		  成功したら 0 以上、エラーなら負の数です。
		-	-22 ;	//	Ekijikokukeisiki の値が不正です。
		-	-32 ;	//	Ekikibo の値が不正です。
		-	-111 ;	//	Syubetsumei が指定されていません。
		-	-152 ;	//	DiagramSenStyle の値が不正です。
		-	-212 ;	//	DiagramEkiatsukai の値が不正です。
	*/
	int CDedRosenFileData_to_string( 
			const CDedRosenFileData& aCDedRosenFileData , 
			tstring* pString  ) ;
	
	/**
		  CDedRosenFileData_to_string() で生成した
		『路線ファイル』(.ded) 形式の文字列を解釈し、
		 CDedRosenFileData オブジェクトに反映します。
		
		@param pCDedRosenFileData [out]
		  この関数はこのオブジェクトに、属性を反映します。
		  このオブジェクトがそれまで保持していたデータは破棄します。
		@param aString [in]
		  CDedRosenFileData_to_string() で生成した
		『路線ファイル』(.oud) 形式の文字列を指定してください。
		@param pCOuErrorInfoContainer [in]
		  この関数はエラーが発生したら、エラーの情報をこのオブジェクトに追加します。
		@return
		  成功したら 0 以上、エラーなら負の数です。
			-	-1 ;	//	ディレクトリが途中で閉じています。	
			-	-1001 ;	//	FileType が正しくありません。
			-	-1002 ;	//	Rosen Directoryが見つかりません。
			-	-1022 ;	//	Ekijikokukeisiki の値が不正です。
			-	-1032 ;	//	Ekikibo の値が不正です。
			-	-1101 ;	//	Eki がディレクトリではありません。
			-	-1111 ;	//	Syubetsumei が指定されていません。
			-	-1152 ;	//	DiagramSenStyle の値が不正です。
			-	-1201 ;	//	Ressyasyubetsu がディレクトリではありません。
			-	-1211 ;	//	DiaName が指定されていません。
			-	-1212 ;	//	RessyaContが見つかりません。
			-	-1352 ;	//	起点時刻の設定が不適切です。
			-	-1003 ;	//	DispProp Directoryが見つかりません。
			-	-1512 ;	//	JikokuhyouFont の内容が不正です。
			-	-1522 ;	//	DiaEkimeiFont の内容が不正です。
			-	-1532 ;	//	DiaJikokuFont の内容が不正です。
			-	-1582 ;	//	DisplayRessyabangou が不正です。
			-	-1592 ;	//	DisplayRessyamei が不正です。
			-	-1602 ;	//	DiaRessyajouhouHyoujiEkiOrderKudari が不正です。
			-	-1612 ;	//	DiaRessyajouhouHyoujiEkiOrderNobori が不正です。
	*/
	int CDedRosenFileData_from_string( 
			CDedRosenFileData* pCDedRosenFileData ,
			const tstring& aString ,
			OuPropertiesText::ErrorInfo::COuErrorInfoContainer* pCOuErrorInfoContainer ) ;

	/**
		ファイルの内容を格納した文字列が
		このクラスで解釈可能なフォーマットか否かを判定します。
	@param aString [in]
		  CDedRosenFileData_to_string() で生成した
		『路線ファイル』(.oud) 形式の文字列を指定してください。
	@return
		-	0 ;	//	解釈可能です。
		-	-1 ;	//	FileType が正しくありません。
		-	-1001 ;	//	FileType が正しくありません。
	@note
		FileType の値を判定します。
	*/
	int isEncodeAbleFormat( 
			const tstring& aString  ) ;
	///@}	
};

} //namespace DedRosenFileData

#endif /*CconvCDedRosenFileData_h*/
