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
//	CentDedEkiJikoku.h
//	$Id: CentDedEkiJikoku.h 378 2016-11-16 21:10:54Z okm $
// ****************************************************************
*/
/** @file */
#ifndef  CentDedEkiJikoku_h
#define  CentDedEkiJikoku_h

#include "CdDedJikoku.h"
#include "CentDedBeforeOperationCont.h"
//#include "CentDedBeforeOperation.h"
#include "CentDedAfterOperationCont.h"
//#include "CentDedAfterOperation.h"

namespace entDed{
	using namespace OuLib::NsMu ;
	using namespace std ;

// ****************************************************************
//	CentDedEkiJikoku
// ****************************************************************
/**
@brief
  DiagramEdit の、１列車の１駅における時刻を表します。

  属性として、『着時刻』『発時刻』と
『駅扱』｛運行なし,経由なし,通過,停車｝
を保持します。
	
制約
 -------------------------------- 
○駅扱が『運行なし』または『経由なし』の場合、着時刻・発時刻はNULL。
　入線は、番線Index・入線時刻ともにNULL

操作のエラー検査・修正
 -------------------------------- 
○setEkiatsukai:駅扱が『運行なし』または『経由なし』の場合、着時刻・発時刻はNULL。
　入線は、番線Index・入線時刻ともにNULLを設定する。

△setEkiatsukai(その他、駅扱が変化したとき):adjustを実行する
　(駅扱が『運行なし』または『経由なし』の場合、
　入線は、番線Index・入線時刻ともにNULL にするため)

○setChakuJikoku:m_eEkiatsukai == Ekiatsukai_None の駅に対して
		着・発のいずれかに 非Null 時刻を設定すると、this の
		m_eEkiatsukai = Ekiatsukai_Teisya となります。

○setHatsuJikoku:m_eEkiatsukai == Ekiatsukai_None の駅に対して
		着・発のいずれかに 非Null 時刻を設定すると、this の
		m_eEkiatsukai = Ekiatsukai_Teisya となります。

△setParent:adjustを実行する

 制約に合うように属性を修正(adjust)
 -------------------------------- 
	
○CentDedEkiJikokuTrackCont(入線コンテナ)に、adjust()を委譲します。

 */
class CentDedEkiJikoku : public CChildBase
{
	typedef CChildBase	super ;
public:
	// ****************************************************************
	//	インナータイプ
	// ****************************************************************
	/**
		代入演算子でスローされる例外です。
	*/
	class LException
	{
	};	

	/**
	  このクラスに包含される『前作業』(CentDedBeforeOperation) オブジェクト
	のコンテナです。
	*/
	class CXBeforeOperationCont : public CentDedBeforeOperationCont
	{
	public:
		// ********************************
		///@name CentDedBeforeOperationCont-関連
		// ********************************
		///@{
		/**
		@return
			このコンテナが CentDedEkiJikoku に包含されている場合は、
			CentDedEkiJikoku のアドレス。
			そうでないならNULL。
		*/
		virtual CentDedEkiJikoku* getEkiJikoku();
		/**
		@return
			このコンテナが CentDedEkiJikoku に包含されている場合は、
			CentDedEkiJikoku のアドレス。
			そうでないならNULL。
		*/
		virtual const CentDedEkiJikoku* getEkiJikoku()const;
		///@}
	};

	/**
	  このクラスに包含される『後作業』(CentDedAfterOperation) オブジェクト
	のコンテナです。
	*/
	class CXAfterOperationCont : public CentDedAfterOperationCont
	{
	public:
		// ********************************
		///@name CentDedAfterOperationCont-関連
		// ********************************
		///@{
		/**
		@return
			このコンテナが CentDedEkiJikoku に包含されている場合は、
			CentDedEkiJikoku のアドレス。
			そうでないならNULL。
		*/
		virtual CentDedEkiJikoku* getEkiJikoku();
		/**
		@return
			このコンテナが CentDedEkiJikoku に包含されている場合は、
			CentDedEkiJikoku のアドレス。
			そうでないならNULL。
		*/
		virtual const CentDedEkiJikoku* getEkiJikoku()const;
		///@}
	};

	/**
		『駅扱』を表す列挙です。
	 */
	enum EEkiatsukai
	{
		/**
			運行なし(規定値) 。
		
			この場合、
			着時刻 ( m_jikokuChakujikoku )・
			発時刻 ( m_jikokuHatsujikoku )
			は、『Null状態』となります。
		 */
		Ekiatsukai_None ,
		/**
			 停車
		 */
		Ekiatsukai_Teisya ,
		/**
			 通過
		 */
		Ekiatsukai_Tsuuka ,
		/** 
			経由なし
		
			この場合、
			着時刻 ( m_jikokuChakujikoku )・
			発時刻 ( m_jikokuHatsujikoku )
			は、『Null状態』となります。
		 */
		//Ekiatsukai_Keiyunasi ,
	};
	// ****************************************************************


private:
	// ********************************
	///@name 属性
	// ********************************
	///@{
	/**
		駅扱。
	 */
	EEkiatsukai	m_eEkiatsukai ;
	
	/**
		着時刻。
	
		m_eEkiatsukai が
		運行なし ( Ekiatsukai_None ) の場合は、
		この値は意味を持ちません。
	 */
	CdDedJikoku	m_jikokuChakujikoku ;
	
	/**
		発時刻。
	
		m_eEkiatsukai が
		運行なし ( Ekiatsukai_None ) の場合は、
		この値は意味を持ちません。
	 */
	CdDedJikoku	m_jikokuHatsujikoku ;

	/**
		列車の番線
	*/
	int m_iRessyaTrackIndex = INT_MIN;
	///@}
	// ********************************
	///@name 包含
	// ********************************
	///@{
	/**
		この駅における前作業です
		初期状態では要素0です
		時系列順に作業が収められます。
	*/
	CXBeforeOperationCont m_CentDedBeforeOperationCont;
	/**
		この駅における後作業です
		初期状態では要素0です
		時系列順に作業が収められます。
	*/
	CXAfterOperationCont m_CentDedAfterOperationCont;
	///@}

public:
	// ********************************
	//	コンストラクタ
	// ********************************
	/** デフォルトコンストラクタ */
	CentDedEkiJikoku() ;
	
	/**
	 @param eEkiatsukai [in]
		駅扱。
	 @param jikokuChakujikoku [in]
		着時刻。	
		m_eEkiatsukai が
		運行なし ( Ekiatsukai_None ) の場合は、
		この値は意味を持ちません。
	 @param jikokuHatsujikoku [in]
		発時刻。	
		m_eEkiatsukai が
		運行なし ( Ekiatsukai_None ) の場合は、
		この値は意味を持ちません。
	 */
	CentDedEkiJikoku( 
		EEkiatsukai	eEkiatsukai , 
		CdDedJikoku	jikokuChakujikoku , 
		CdDedJikoku	jikokuHatsujikoku ) ;

	/**
	 @param eEkiatsukai [in]
		駅扱。
	 @param jikokuChakujikoku [in]
		着時刻。
		m_eEkiatsukai が
		運行なし ( Ekiatsukai_None ) の場合は、
		この値は意味を持ちません。
	 @param jikokuHatsujikoku [in]
		発時刻。
		m_eEkiatsukai が
		運行なし ( Ekiatsukai_None ) の場合は、
		この値は意味を持ちません。
	 */
	CentDedEkiJikoku(
		EEkiatsukai	eEkiatsukai,
		CdDedJikoku	jikokuChakujikoku,
		CdDedJikoku	jikokuHatsujikoku,
		int iRessyaTrackIndex);
	
	/** 
	△operator= : CentDedEkiJikokuCont::set()が失敗するような代入はエラー
	このクラスでは、失敗することはありません。
	
	@exception LException 
	*/
	CentDedEkiJikoku& operator=( const CentDedEkiJikoku& value ) ;
public:
	// ********************************
	///@name CChildBase-操作
	// ********************************
	///@{
	virtual void setParent( CParentBase* pParent );
	///@}


public:
	// ********************************
	///@name CentDedEkiJikoku-属性
	// ********************************
	///@{
	/** @see m_eEkiatsukai */
	EEkiatsukai	getEkiatsukai()const;

	/** @see m_eEkiatsukai */
	CentDedEkiJikoku& setEkiatsukai( EEkiatsukai value );
	
	/**
		着時刻を参照することができます。
	 @param bHatsuIfNull [in]
		- true ; 着時刻が Null 時刻で、発時刻が Null 時刻でない場合は、
			発時刻を返します。
		- false ; 着時刻が Null 時刻なら、発時刻に関わらず
			 Null 時刻を返します。
	 @return
			着時刻を返します。
	 */
	CdDedJikoku	getChakujikoku( bool bHatsuIfNull = false )const;

	/**
		「入換着時刻を当駅の着時刻にする」を考慮した着時刻を返します
	*/
	CdDedJikoku getVirtualChakujikoku()const;

	/**
		着時刻を設定します。
		- 	m_eEkiatsukai == Ekiatsukai_Noneの駅に対して
			着・発のいずれかに 非Null 時刻を設定すると、this の
			m_eEkiatsukai = Ekiatsukai_Teisya となります。
	 */
	CentDedEkiJikoku& setChakujikoku( const CdDedJikoku& value );

	/**
		発時刻を参照することができます。
	 @param bChakuIfNull [in]
		- true ; 発時刻が Null 時刻で、着時刻が Null 時刻でない場合は、
			着時刻を返します。
		- false ; 発時刻が Null 時刻なら、着時刻に関わらず
			 Null 時刻を返します。
	 @return
			発時刻を返します。
	 */
	CdDedJikoku	getHatsujikoku( bool bChakuIfNull = false )const;

	/**
		「入換発時刻を当駅の発時刻にする」を考慮した発時刻を返します
	*/
	CdDedJikoku getVirtualHatsujikoku()const;

	/**
		発時刻を設定します。
		- 	m_eEkiatsukai == Ekiatsukai_Noneの駅に対して
			着・発のいずれかに 非Null 時刻を設定すると、this の
			m_eEkiatsukai = Ekiatsukai_Teisya となります。
	 */
	CentDedEkiJikoku& setHatsujikoku( const CdDedJikoku& value ) ;

	/**
		m_iRessyaTrackIndexを返します
	*/
	int getRessyaTrackIndex()const;

	/**
		m_iRessyaTrackIndexに代入します。
	*/
	CentDedEkiJikoku& setRessyaTrackIndex(const int value);

	/**
	 @param eEkiatsukai [in]
		駅扱。
	 @param jikokuChakujikoku [in]
		着時刻。	¥n
		m_eEkiatsukai が
		着時刻 ( Ekiatsukai_None ) の場合は、
		この値は意味を持ちません。
	 @param jikokuHatsujikoku [in]
		発時刻。	¥n
		m_eEkiatsukai が
		着時刻 ( Ekiatsukai_None ) の場合は、
		この値は意味を持ちません。
	
		- 	Ekiatsukai_None を設定すると、
			着・発時刻はどちらも Null 時刻となります。
		- 	Ekiatsukai_Teisya ・着・発時刻がどちらも Null 時刻の場合、
			m_eEkiatsukai = Ekiatsukai_None となります。
	 */
	CentDedEkiJikoku& set( 
		EEkiatsukai	eEkiatsukai , 
		CdDedJikoku	jikokuChakujikoku , 
		CdDedJikoku	jikokuHatsujikoku ) ;

	/**
	 @param eEkiatsukai [in]
		駅扱。
	 @param jikokuChakujikoku [in]
		着時刻。	¥n
		m_eEkiatsukai が
		着時刻 ( Ekiatsukai_None ) の場合は、
		この値は意味を持ちません。
	 @param jikokuHatsujikoku [in]
		発時刻。	¥n
		m_eEkiatsukai が
		着時刻 ( Ekiatsukai_None ) の場合は、
		この値は意味を持ちません。

		- 	Ekiatsukai_Noneを設定すると、
			着・発時刻はどちらも Null 時刻となります。
		- 	Ekiatsukai_Teisya ・着・発時刻がどちらも Null 時刻の場合、
			m_eEkiatsukai = Ekiatsukai_None となります。
	 */
	CentDedEkiJikoku& set(
		EEkiatsukai	eEkiatsukai,
		CdDedJikoku	jikokuChakujikoku,
		CdDedJikoku	jikokuHatsujikoku,
		int iRessyaTrackIndex);
	///@}
	// ********************************
	///@name CentDedEkiJikoku-包含
	// ********************************
	///@{
	/** @see m_CentDedBeforeOperationCont */
	CentDedBeforeOperationCont* getCentDedBeforeOperationCont()
	{
		return &m_CentDedBeforeOperationCont;
	}
	/** @see m_CentDedBeforeOperationCont */
	const CentDedBeforeOperationCont*	getCentDedBeforeOperationCont()const
	{
		return &m_CentDedBeforeOperationCont;
	}
	void setCentDedBeforeOperationCont(CentDedBeforeOperationCont value);


	/** @see m_CentDedAfterOperationCont */
	CentDedAfterOperationCont* getCentDedAfterOperationCont()
	{
		return &m_CentDedAfterOperationCont;
	}
	/** @see m_CentDedAfterOperationCont */
	const CentDedAfterOperationCont*	getCentDedAfterOperationCont()const
	{
		return &m_CentDedAfterOperationCont;
	}
	void setCentDedAfterOperationCont(CentDedAfterOperationCont value);
	///@}

	// ********************************
	///@name CentDedEkiJikoku-操作
	// ********************************
	///@{
	/**
	駅時刻形式に合わせて、着時刻・発時刻を再設定します。

	- [駅時刻形式に着時刻あり・発時刻なし、
	  駅時刻に着時刻なし、発時刻あり]
	  着時刻には発時刻をコピー、発時刻はNULL。
	- [駅時刻形式に着時刻なし・発時刻あり
	  駅時刻に着時刻あり、発時刻なし]
	  発時刻には着時刻をコピー、着時刻はNULL。
	- [駅が始発駅・
	  駅時刻形式に着時刻あり・発時刻あり、
	  駅時刻に着時刻あり、発時刻なし]
	  発時刻には着時刻をコピー、着時刻はNULL。
	- [駅が終着駅・
	  駅時刻形式に着時刻あり・発時刻あり
	  駅時刻に着時刻なし、発時刻あり]
	  着時刻には発時刻をコピー、発時刻はNULL。

	@param bChakujikokuHyouji [in]
		駅時刻形式。
		着時刻表示あり。
	@param bHatsujikokuHyouji [in]
		駅時刻形式。
		発時刻表示あり。
	@param bIsSihatsueki [in]
		true: 始発駅
	@param bSyuuchakueki [in]
		true: 終着駅
	*/
	void adjustByEkijikokukeisiki(
		bool bChakujikokuHyouji , bool bHatsujikokuHyouji ,
		bool bIsSihatsueki , bool bSyuuchakueki ) ;

	/**
		列車情報が変更になったときに、前後作業を修正します。
	@param iType[in]
		この値により処理が変わります。
		INT_MIN: 作業をすべて削除します。
			有効始発駅〜有効終着駅の外側にある場合
		-2:前作業の先頭が、先端作業かの確認、
			増解結作業の確認。
			有効始発駅
		-1:前作業は削除確定、後作業は駅扱い及び発時刻の有無による修正、
			・発時刻が無い→後作業削除
			・経由無し・運行無し→(前)後作業削除
			増解結作業の確認。
			中間駅
		0:発着時刻両方の有無による修正、
			・発着時刻いずれかが無い→前後作業削除
			・経由無し・運行無し→前後作業削除
			増解結作業の確認。
			中間駅
		1:前作業は駅扱い及び着時刻の有無による修正、後作業は削除確定、
			・着時刻が無い→前作業削除
			・経由無し・運行無し→前(後)作業削除
			増解結作業の確認。
			中間駅
		2:後作業の末尾が、終端作業かの確認、
			増解結作業の確認。
			有効終着駅
		INT_MAX:駅扱い及び発着時刻の有無による修正、
			・着時刻が無い→前作業削除
			・発時刻が無い→後作業削除
			・経由無し・運行無し→前後作業削除
			増解結作業の確認。
			中間駅
		(1)有効な始発駅以前・有効な終着駅以降の作業をクリア
		(2)有効な始発駅の前作業先頭を、先端作業(前列車接続etc)にする、
			有効な終着駅の後作業末尾を、終端作業(次列車接続etc)にする
		(3)その他の先端作業、終端作業を削除
		(4)増解結作業の前後作業に、先端・終端作業があるかチェック
		※駅設定に依らないところのみを修正する方針で
	*/
	void adjustOperation(int iType);

	///@}
public:
	// ********************************
	///@name CentDedRosen-子オブジェクトの増減の通知
	// ********************************
	///@{

	///@}
};


} //namespace entDed


#endif /*CentDedEkiJikoku_h*/
