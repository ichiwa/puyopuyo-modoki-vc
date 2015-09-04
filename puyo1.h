// puyo1.h : PUYO1 アプリケーションのメイン ヘッダー ファイル
//

#if !defined(AFX_PUYO1_H__6267A328_66A5_4C3E_89BE_7E2BC7E77408__INCLUDED_)
#define AFX_PUYO1_H__6267A328_66A5_4C3E_89BE_7E2BC7E77408__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CPuyo1App:
// このクラスの動作の定義に関しては puyo1.cpp ファイルを参照してください。
//

class CPuyo1App : public CWinApp
{
public:
	CPuyo1App();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CPuyo1App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション
	//{{AFX_MSG(CPuyo1App)
	afx_msg void OnAppAbout();
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_PUYO1_H__6267A328_66A5_4C3E_89BE_7E2BC7E77408__INCLUDED_)
