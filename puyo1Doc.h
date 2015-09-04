// puyo1Doc.h : CPuyo1Doc クラスの宣言およびインターフェイスの定義をします。
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PUYO1DOC_H__52F18A46_6357_4815_B19D_7E232FDEDE85__INCLUDED_)
#define AFX_PUYO1DOC_H__52F18A46_6357_4815_B19D_7E232FDEDE85__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Game.h"

class CPuyo1Doc : public CDocument
{
protected: // シリアライズ機能のみから作成します。
	CPuyo1Doc();
	DECLARE_DYNCREATE(CPuyo1Doc)

// アトリビュート
public:

// オペレーション
public:

//オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CPuyo1Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	CGame		m_Game;			// ゲームクラス		
	virtual ~CPuyo1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CPuyo1Doc)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_PUYO1DOC_H__52F18A46_6357_4815_B19D_7E232FDEDE85__INCLUDED_)
