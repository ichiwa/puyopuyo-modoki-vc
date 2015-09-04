// puyo1View.cpp : CPuyo1View クラスの動作の定義を行います。
//

#include "stdafx.h"
#include "puyo1.h"

#include "puyo1Doc.h"
#include "puyo1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPuyo1View

IMPLEMENT_DYNCREATE(CPuyo1View, CView)

BEGIN_MESSAGE_MAP(CPuyo1View, CView)
	//{{AFX_MSG_MAP(CPuyo1View)
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPuyo1View クラスの構築/消滅

CPuyo1View::CPuyo1View()
{
	// TODO: この場所に構築用のコードを追加してください。
	m_pThread = NULL;
	m_pButton = NULL;
}

CPuyo1View::~CPuyo1View()
{
	
}

BOOL CPuyo1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return CView::PreCreateWindow(cs);
}

//--------------------//
// 破棄メッセージ	  //
//--------------------//
void CPuyo1View::OnDestroy() 
{
	CView::OnDestroy();
	
	// TODO: この位置にメッセージ ハンドラ用のコードを追加してください
	
	if (m_pThread)
	{
		delete m_pThread;	// スレッド破棄
	}
	if (m_pButton)
	{
		delete m_pButton;	// ボタン破棄
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPuyo1View クラスの描画

void CPuyo1View::OnDraw(CDC* pDC)
{
	CPuyo1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: この場所にネイティブ データ用の描画コードを追加します。

	// ゲーム待機中
	if (pDoc->m_Game.IsGameStandby())
	{
		CRect rect;
		GetClientRect(&rect);

		// テキスト描画をする
		DrawText(pDC, rect);
	}
	// ゲーム中
	else
	{
		// バックバッファの描画
		pDoc->m_Game.BackDrawScreen();
	}
}
//--------------//
// テキスト描画 //
//--------------//
void CPuyo1View::DrawText(CDC* pDC, const CRect &Rect)
{
	// 塗りつぶし
	pDC->FillSolidRect(Rect, BACK_BRUSH);
	 
	// タイトル用に変更
	pDC->SelectObject(m_TextFont);
	pDC->SetTextColor(TITLE_BRUSH);

	// タイトルテキスト描画
	pDC->TextOut(10, 40, TITLE_TEXT);
	
	// 元に戻す
	pDC->SelectStockObject(SYSTEM_FONT);
	pDC->SetTextColor(INFO_BRUSH);

	// 開始テキストの描画
	pDC->TextOut(Rect.Width() / 2 - 100, Rect.Height() / 2 - 100, STRAT_TEXT);
	// キーテキスト1表示
	pDC->TextOut(Rect.Width() / 2 - 90, Rect.Height() / 2 + 20, KEY_TEXT1);
	// キーテキスト2表示
	pDC->TextOut(Rect.Width() / 2 - 90, Rect.Height() / 2 + 40, KEY_TEXT2);	
	// 
}
/////////////////////////////////////////////////////////////////////////////
// CPuyo1View クラスの診断

#ifdef _DEBUG
void CPuyo1View::AssertValid() const
{
	CView::AssertValid();
}

void CPuyo1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPuyo1Doc* CPuyo1View::GetDocument() // 非デバッグ バージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPuyo1Doc)));
	return (CPuyo1Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPuyo1View クラスのメッセージ ハンドラ

int CPuyo1View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: この位置に固有の作成用コードを追加してください

	// 開始ボタン作成
    CRect rect;
	int left = FIELD_WIDTH * PUYO_SIZE / 2 - 50;
	int top = FIELD_HEIGHT * PUYO_SIZE / 2 - 80;
	int right = left + 80;
	int bottom = top + 50;	
	rect.SetRect(left, top, right, bottom);
	
    m_pButton = new CButton();
	m_pButton->Create("開始", BS_PUSHBUTTON, rect, this, BUTTONID);
	m_pButton->ShowWindow(SW_SHOW);
	
	// テキストフォント作成
	m_TextFont.CreateFont(40, 0, 0, 0, FW_BOLD, FALSE, TRUE, FALSE, SHIFTJIS_CHARSET, 
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_ROMAN, NULL);	
	
	return 0;
}

//---------------------//
// コマンドメッセージ  //
//---------------------//
BOOL CPuyo1View::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください

	// ボタン
	if (wParam == BUTTONID)
	{
		CDC* pDC = this->GetDC();
		CRect rect;
		GetClientRect(&rect);

		// スクリーンアウト
		while(ScreenOut(pDC, rect))
		{
			Sleep(1);
		}
		// ボタン非表示
		m_pButton->LockWindowUpdate();
		m_pButton->ShowWindow(SW_HIDE);

		//----------------//
		// スレッドの作成 //
		//----------------//
		m_pThread = AfxBeginThread(DrawThread, this);
		
		// タイマーの作成
		StartTimer();
	}
	return CView::OnCommand(wParam, lParam);
}
//-------------------//
// スクリーンアウト  //
//-------------------//
BOOL CPuyo1View::ScreenOut(CDC* pDC, const CRect &Rect)
{
	static uint y = 0;

	// 6本ずつ線を書く
	for (int i = 0; i < 6; i ++)
	{
		// 上から消してく
		pDC->MoveTo(0, y);
		pDC->LineTo(Rect.Width(), y);
		
		y ++;

		if (y >= (uint)Rect.Height())
		{
			return FALSE;
		}
	}
	return TRUE;
}
//------------//
// キー処理   //
//------------//
void CPuyo1View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// スタンバイ中は無視
	if (GetDocument()->m_Game.IsGameStandby())
	{
		return;
	}

	puyoCtrl CtrlKey = puyoDisregard;		// 無視キー
	
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
    switch (nChar) 
	{
	  // 左　
	  case VK_LEFT:  
		CtrlKey = puyoLEFT;
		break;
	  // 右 　
	  case VK_RIGHT:
		CtrlKey = puyoRIGHT;
		break;
	  // 下 
      case VK_DOWN:  
		CtrlKey = puyoDOWN;
		break;
	  // 左回転
	  case 	VK_Z:
		CtrlKey = puyoLEFT_ROLL;
	  	break;
	  // 右回転
	  case 	VK_X:
		CtrlKey = puyoRIGHT_ROLL;
		break;
    }
	
	// 移動に成功すれば再描画
	if ((!CtrlKey == puyoDisregard)
	&& (GetDocument()->m_Game.KeyControl(CtrlKey)))
	{
		// 再描画
		Invalidate(FALSE);
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
//----------------------//
// タイマーコールバック //
//----------------------//
void CPuyo1View::OnTimer(UINT nIDEvent) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	
	if (nIDEvent == MOVE_TIMERID)
	{
		EndTimer();

//		TRACE("%d,%d\n", 
//			GetDocument()->m_Game.m_PuyoPuyo.GetPosition_x(0),
//			GetDocument()->m_Game.m_PuyoPuyo.GetPosition_y(0));

		// キーメッセージを送る
		OnKeyDown(VK_DOWN, 0, 0);
		
		StartTimer();

		// 再描画
		Invalidate(FALSE);
	}

	CView::OnTimer(nIDEvent);
}
//--------------------//
// KillTimer Wrapping //
//--------------------//
void CPuyo1View::EndTimer()
{
	// タイマー止める
	KillTimer(MOVE_TIMERID);	
}
//--------------------//
// SetTimer Wrapping  //
//--------------------//
void CPuyo1View::StartTimer()
{
	// タイマー開始
	SetTimer(MOVE_TIMERID, TIMER_INVAL, NULL);
}

///////////////////////////////////////
// ワーカースレッド	(fps描画)		 //
///////////////////////////////////////
UINT DrawThread(LPVOID pParam)
{
	DWORD		frames		 = 0;									// フレーム数
	DWORD		beforeTime	 = 0;									// 開始時間
	CPuyo1View* View		 = static_cast<CPuyo1View*>(pParam);	// view
	CDC*		pDC			 = View->GetDC();						// 描画hdc
	CPuyo1Doc* pDoc			 = View->GetDocument();					// doc

	// 描画用クライアント領域の作成
	CRect rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = PUYO_SIZE * FIELD_WIDTH;
	rect.bottom = PUYO_SIZE * FIELD_HEIGHT + PUYO_SIZE;

	// ゲームの初期化
	pDoc->m_Game.Create(pDC, &rect);
	pDoc->m_Game.m_hwnd = View->m_hWnd;
	
	beforeTime = timeGetTime();
	
	// ゲームスタート

	while (1)
	{
		DWORD nowTime;			// 現在時間
		DWORD progress;			// 進んだ時間
		DWORD idealTime = 0;	// 描画時間
	
		nowTime = timeGetTime();
		progress = nowTime - beforeTime;
		idealTime = static_cast<DWORD>(frames * (1000.0f / FPS));

		// 再描画
		InvalidateRect(View->m_hWnd, NULL, FALSE);
		
		// 描画時間まで待機
		if (idealTime > progress)
		{
			Sleep(idealTime - progress);
		}

		// 描画
		pDoc->m_Game.ForeDrawScreen();

		// 次
		frames ++;
		
	}
	return 0;
}
