// puyo1View.h : CPuyo1View クラスの宣言およびインターフェイスの定義をします。
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PUYO1VIEW_H__AD2135D2_95A8_404B_BE92_2A43FE8C6E9F__INCLUDED_)
#define AFX_PUYO1VIEW_H__AD2135D2_95A8_404B_BE92_2A43FE8C6E9F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCritticalSection;

class CPuyo1View : public CView
{
protected: // シリアライズ機能のみから作成します。
	CPuyo1View();
	DECLARE_DYNCREATE(CPuyo1View)

// アトリビュート
public:
	CPuyo1Doc* GetDocument();

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CPuyo1View)
	public:
	virtual void OnDraw(CDC* pDC);  // このビューを描画する際にオーバーライドされます。
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	void				EndTimer();		// タイマーエンド
	void				StartTimer();	// タイマースタート
	virtual ~CPuyo1View();
private:
	BOOL				ScreenOut(CDC* pDC, const CRect &Rect);// スクリーンアウト
	void				DrawText(CDC* pDC, const CRect &Rect); // テキスト描画
private:
	CWinThread*			m_pThread;		// スレッド
	CButton*			m_pButton;		// ボタン	
	CFont				m_TextFont;		// 描画用フォント
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CPuyo1View)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // puyo1View.cpp ファイルがデバッグ環境の時使用されます。
inline CPuyo1Doc* CPuyo1View::GetDocument()
   { return (CPuyo1Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

// 作業用スレッド
UINT DrawThread(LPVOID pParam);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。


#endif // !defined(AFX_PUYO1VIEW_H__AD2135D2_95A8_404B_BE92_2A43FE8C6E9F__INCLUDED_)
