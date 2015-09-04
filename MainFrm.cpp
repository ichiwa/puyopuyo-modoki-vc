// MainFrm.cpp : CMainFrame クラスの動作の定義を行います。
//

#include "stdafx.h"
#include "puyo1.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame クラスの構築/消滅

CMainFrame::CMainFrame()
{
	// TODO: この位置にメンバの初期化処理コードを追加してください。
	
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: この位置で CREATESTRUCT cs を修正して、Window クラスやスタイルを
	//       修正してください

	// 縮小、拡大、システムメニュー消去
	cs.style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

	int left = 0;
	int top = 0;
	int right = FIELD_WIDTH * PUYO_SIZE;
	int bottom = FIELD_HEIGHT * PUYO_SIZE - PUYO_SIZE;	

	// 指定するクライアント領域
	CRect	rect(left, top, right, bottom);
	// 指定されたクライアント領域を確保するために必要なウィンドウ座標
	::AdjustWindowRectEx(&rect, cs.style, TRUE, cs.dwExStyle);
	// 幅
	int Width = rect.Width();
	// 高さ
	int Height = rect.Height();

	// サイズ計算
	CRect	rcArea;
	::SystemParametersInfo(SPI_GETWORKAREA, NULL, &rcArea, NULL);
	int x = rcArea.left + (rcArea.Width() - Width) / 2;
	int y = rcArea.top + (rcArea.Height() - Height) / 2;

	// サイズ変更
	cs.x = x;
	cs.y = y;
	cs.cx = Width ;
	cs.cy = Height;

	// 表示名
	cs.lpszName = "超とこぷよモドキ";
	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame クラスの診断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame メッセージ ハンドラ

