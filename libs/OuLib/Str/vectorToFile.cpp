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
//	vectorToFile.cpp
// ****************************************************************
//【概要】
//	vector<char> の内容をファイルへ書き出し
//	ファイルの内容の vector<char> への読み込み
//	を行う下請関数です。
*/
#include "vectorToFile.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <tchar.h>
#include <wchar.h>
#include "Str\strToWstr.h"

namespace OuLib{
namespace Str{

// ****************************************************************

int vectorToFile( const std::vector<TCHAR>& aVector ,
					const tstring& strFilename ) 
{
	int	iRv = 0 ;
	if ( strFilename.empty() )
	{
		iRv = -1 ;	//	ファイルオープンエラー
	}
	if ( iRv >= 0 )
	
	{
		//FILE*	pFile = _tfopen( strFilename.c_str() , _T("wb") ) ;
		FILE*	pFile;
		errno_t err;
		err = _tfopen_s(&pFile,strFilename.c_str(), _T("wb"));
		
		if (err == 0 ){
			//if (pFile != NULL) {
			int	iReadBytes = 0 ;
			iReadBytes = fwrite( &aVector.front() , 1 , 
								aVector.size() , pFile ) ;
			if ( iReadBytes != aVector.size() ){
				iRv = -2 ;	//	書き込みに失敗しました。
			}
			if ( fclose( pFile ) != 0 ){
				if ( iRv >= 0 ){
					iRv = -2 ;	//	書き込みに失敗しました。
				}
			}
		}	else	{
			iRv = -1 ;	//	ファイルオープンエラー
		}
	}
	return ( iRv ) ;
}


int vectorFromFile( std::vector<TCHAR>* pVector ,
					const tstring& strFilename ) 
{
	int	iRv = 0 ;
	
	if ( strFilename.empty() )
	{
		iRv = -1 ;	//	ファイルオープンエラー
	}
	
	
	if ( iRv >= 0 ){
		pVector->clear() ;
	}
	if ( iRv >= 0 ){
		
		
		//FILE*	pFile = _tfopen( strFilename.c_str() , _T("rb") ) ;
		FILE*	pFile;
		errno_t err;
		err = _tfopen_s(&pFile, strFilename.c_str(), _T("rb"));

		if (err == 0) {
		//if ( pFile != NULL ){
			TCHAR	szLs[1024] ;
			int	iReadBytes = 0 ;
			do{
				iReadBytes = fread( szLs , 1 , sizeof(szLs) , pFile ) ;
				if ( iReadBytes > 0 ){
					pVector->insert( pVector->end() , szLs , 
													szLs + iReadBytes ) ;
				}	else if ( iReadBytes < 0 ){
					iRv = -2 ;	//	読み込みに失敗しました。
				}
			}	while ( iReadBytes > 0 && iRv >= 0 ) ;
			if ( fclose( pFile ) != 0 ){
				if ( iRv >= 0 ){
					iRv = -2 ;	//	読み込みに失敗しました。
				}
			}
		}	else	{
			iRv = -1 ;	//	ファイルオープンエラー
		}

	}
	return ( iRv ) ;
}



int stringToFile( const tstring& aString , 
					const tstring& strFilename ) 
{
	int	iRv = 0 ;
	if ( strFilename.empty() )
	{
		iRv = -1 ;	//	ファイルオープンエラー
	}
	if ( iRv >= 0 ){
		//FILE*	pFile = _tfopen( strFilename.c_str() , _T("wt") ) ;

		FILE*	pFile;
		errno_t err;
		err = _tfopen_s(&pFile, strFilename.c_str(), _T("w , ccs=UTF-8"));

		if (err == 0) {
		//if ( pFile != NULL ){
			int	iReadBytes = 0 ;
			iReadBytes = fwrite( aString.c_str() , sizeof(TCHAR) , 
								aString.size() , pFile ) ;
			if ( iReadBytes != aString.size() ){
				iRv = -2 ;	//	書き込みに失敗しました。
			}
			if ( fclose( pFile ) != 0 ){
				if ( iRv >= 0 ){
					iRv = -2 ;	//	書き込みに失敗しました。
				}
			}
		}	else	{
			iRv = -1 ;	//	ファイルオープンエラー
		}
	}
	return ( iRv ) ;
}

int stringToFileANSI(const tstring& aString,
	const tstring& strFilename)
{
	int	iRv = 0;
	if (strFilename.empty())
	{
		iRv = -1;	//	ファイルオープンエラー
	}
	if (iRv >= 0) {
		//FILE*	pFile = _tfopen( strFilename.c_str() , _T("wt") ) ;

		FILE*	pFile;
		errno_t err;
		err = _tfopen_s(&pFile, strFilename.c_str(), _T("wt"));
		std::string aStringTemp = stringOf(aString);
		if (err == 0) {
			//if ( pFile != NULL ){
			int	iReadBytes = 0;
			iReadBytes = fwrite(aStringTemp.c_str(), sizeof(char),
				aStringTemp.size(), pFile);
			if (iReadBytes != aStringTemp.size()) {
				iRv = -2;	//	書き込みに失敗しました。
			}
			if (fclose(pFile) != 0) {
				if (iRv >= 0) {
					iRv = -2;	//	書き込みに失敗しました。
				}
			}
		}
		else {
			iRv = -1;	//	ファイルオープンエラー
		}
	}
	return (iRv);
}




int stringFromFile( tstring* pString , 
					const tstring& strFilename,
					const bool bUTF8Force)
{
	int	iRv = 0 ;
	
	if ( strFilename.empty() )
	{
		iRv = -1 ;	//	ファイルオープンエラー
	}
	
	if ( iRv >= 0 ){
		pString->erase() ;
	}
	// --------------------------------
	//	ファイルサイズを先読みして、
	//	string にメモリ確保
	// --------------------------------
	if ( iRv >= 0 ){
		long lSize = 0 ;
		struct _stat aStat ;
		if (_tstat( strFilename.c_str() , &aStat ) == 0 ){
			lSize = aStat.st_size ;
			if ( lSize > 0 ){
				pString->reserve( lSize ) ;
			}
		}
	}
	// --------------------------------
	bool bUTF8 = true;
	//初期値true,SJIS想定での読み込みdoループ初回に、BOMをチェック、
	//UTF-8BOMが確認できた場合は、trueのままで、BOMが無い場合はfalseにする。
	//trueの場合、doループから抜け、pStringへの書き出しはスキップし、fcloseのみ行う。
	//初期値がtrueなのは、doループの初回かどうかを確かめるため(2周目以降は、falseになるため、チェックに入らない)
	//その後、UTF-8想定での読み込みに入る。

	//ShiftJIS
	if ( iRv >= 0 && !bUTF8Force)
	{
		FILE*	pFile;
		errno_t err;
		err = _tfopen_s(&pFile, strFilename.c_str(), _T("rt"));

		if (err == 0) {
			char szLsc[1024 + 1];
			std::string aStringTemp;
			int	iReadBytes = 0 ;
			do{
				iReadBytes = fread(szLsc, 1, sizeof(szLsc) - sizeof(char), pFile);
				if (bUTF8)
				{
					if (iReadBytes / sizeof(char) < 3)
					{
						bUTF8 = false;
					}
					else if(szLsc[0] == '\xEF' &&
						szLsc[1] == '\xBB' &&
						szLsc[2] == '\xBF')
					{
						//bUTF8 = true;
						break;
					}
					else
					{
						bUTF8 = false;
					}

				}
				if ( iReadBytes > 0 )
				{
					int cBytes = iReadBytes / sizeof(char);
					szLsc[cBytes] = '\0' ;
					int idx ;
					for (idx = 0; szLsc[idx] != '\0'; idx++) {};
					if (idx != cBytes)
					{
						iRv = -3 ;	//	ファイルには'\0' が含まれます。
					}	else	{
						aStringTemp += szLsc;
					}
				}	
				else if ( iReadBytes < 0 )
				{
					iRv = -2 ;	//	読み込みに失敗しました。
				}
			}	while ( iReadBytes > 0 && iRv >= 0 ) ;
			if (!bUTF8)
			{
				tstring aStringWTemp = tstringOf(aStringTemp);

				for (int idx = 1; idx < (int)aStringWTemp.length(); idx++)
				{
					tstring Moji5c = _T("―ソЫⅨ噂浬欺圭構蚕十申曾箪貼能表暴予禄兔喀媾彌拿杤歃濬畚秉綵臀藹觸軆鐔饅鷭偆砡纊犾");
						/*{ _T("―"), _T("ソ"), _T("Ы"), _T("Ⅸ"), _T("噂"),
						_T("浬"), _T("欺"), _T("圭"), _T("構."), _T("蚕"),
						_T("十"), _T("申"), _T("曾"), _T("箪"), _T("貼"),
						_T("能"), _T("表"), _T("暴"), _T("予"), _T("禄"),
						_T("兔"), _T("喀"), _T("媾"), _T("彌"), _T("拿"),
						_T("杤"), _T("歃"), _T("濬"), _T("畚"), _T("秉"),
						_T("綵"), _T("臀"), _T("藹"), _T("觸"), _T("軆"),
						_T("鐔"), _T("饅"), _T("鷭"), _T("偆"), _T("砡"),
						_T("纊"), _T("犾") };*/
					if (aStringWTemp[idx] == '\\')
					{
						for (int idx5c = 0; idx5c < (int)Moji5c.length(); idx5c++)
						{
							if (aStringWTemp[idx - 1] == Moji5c[idx5c])
							{
								//int c = 0;
								aStringWTemp.erase(idx, 1);
								break;
							}
						}
					}
				}

				*pString = aStringWTemp;
				//*pString = tstringOf(aStringTemp);
			}
			if ( fclose( pFile ) != 0 ){
				if ( iRv >= 0 ){
					iRv = -2 ;	//	読み込みに失敗しました。
				}
			}
		}	else	{
			iRv = -1 ;	//	ファイルオープンエラー
		}

	}
	//UTF-8
	if (iRv >= 0 && bUTF8)
	{
		FILE*	pFile;
		errno_t err;
		err = _tfopen_s(&pFile, strFilename.c_str(), _T("r, ccs=UTF-8"));

		if (err == 0) {
			TCHAR	szLs[1024 + 1];
			//char szLsc[1024 + 1];
			//std::string aStringTemp;
			int	iReadBytes = 0;
			do {
				//iReadBytes = fread(szLsc, 1, sizeof(szLsc) - sizeof(char), pFile);
				iReadBytes = fread( szLs , 1 , sizeof(szLs) - sizeof(TCHAR), pFile ) ;
				if (iReadBytes > 0)
				{
					int tBytes = iReadBytes / sizeof(TCHAR);
					//int cBytes = iReadBytes / sizeof(char);
					szLs[tBytes] = '\0' ;
					//szLsc[cBytes] = '\0';
					int idx;
					for ( idx = 0 ; szLs[idx] != '\0' ; idx ++ ){} ;
					//for (idx = 0; szLsc[idx] != '\0'; idx++) {};
					if ( idx != tBytes)
					//if (idx != cBytes)
					{
						iRv = -3;	//	ファイルには'\0' が含まれます。
					}
					else {
						*pString += szLs ;
						//mbstowcs(szLs, szLsc, 1025);
						//aStringTemp += szLsc;
						//*pString += szLsc;
					}
				}
				else if (iReadBytes < 0)
				{
					iRv = -2;	//	読み込みに失敗しました。
				}
			} while (iReadBytes > 0 && iRv >= 0);
			//*pString = tstringOf(aStringTemp);
			if (fclose(pFile) != 0) {
				if (iRv >= 0) {
					iRv = -2;	//	読み込みに失敗しました。
				}
			}
		}
		else {
			iRv = -1;	//	ファイルオープンエラー
		}

	}
	return ( iRv ) ;
}


} //namespace Str{
} //namespace OuLib{
