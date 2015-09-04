// puyo1View.cpp : CPuyo1View �N���X�̓���̒�`���s���܂��B
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
// CPuyo1View �N���X�̍\�z/����

CPuyo1View::CPuyo1View()
{
	// TODO: ���̏ꏊ�ɍ\�z�p�̃R�[�h��ǉ����Ă��������B
	m_pThread = NULL;
	m_pButton = NULL;
}

CPuyo1View::~CPuyo1View()
{
	
}

BOOL CPuyo1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ���̈ʒu�� CREATESTRUCT cs ���C������ Window �N���X�܂��̓X�^�C����
	//  �C�����Ă��������B

	return CView::PreCreateWindow(cs);
}

//--------------------//
// �j�����b�Z�[�W	  //
//--------------------//
void CPuyo1View::OnDestroy() 
{
	CView::OnDestroy();
	
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����Ă�������
	
	if (m_pThread)
	{
		delete m_pThread;	// �X���b�h�j��
	}
	if (m_pButton)
	{
		delete m_pButton;	// �{�^���j��
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPuyo1View �N���X�̕`��

void CPuyo1View::OnDraw(CDC* pDC)
{
	CPuyo1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: ���̏ꏊ�Ƀl�C�e�B�u �f�[�^�p�̕`��R�[�h��ǉ����܂��B

	// �Q�[���ҋ@��
	if (pDoc->m_Game.IsGameStandby())
	{
		CRect rect;
		GetClientRect(&rect);

		// �e�L�X�g�`�������
		DrawText(pDC, rect);
	}
	// �Q�[����
	else
	{
		// �o�b�N�o�b�t�@�̕`��
		pDoc->m_Game.BackDrawScreen();
	}
}
//--------------//
// �e�L�X�g�`�� //
//--------------//
void CPuyo1View::DrawText(CDC* pDC, const CRect &Rect)
{
	// �h��Ԃ�
	pDC->FillSolidRect(Rect, BACK_BRUSH);
	 
	// �^�C�g���p�ɕύX
	pDC->SelectObject(m_TextFont);
	pDC->SetTextColor(TITLE_BRUSH);

	// �^�C�g���e�L�X�g�`��
	pDC->TextOut(10, 40, TITLE_TEXT);
	
	// ���ɖ߂�
	pDC->SelectStockObject(SYSTEM_FONT);
	pDC->SetTextColor(INFO_BRUSH);

	// �J�n�e�L�X�g�̕`��
	pDC->TextOut(Rect.Width() / 2 - 100, Rect.Height() / 2 - 100, STRAT_TEXT);
	// �L�[�e�L�X�g1�\��
	pDC->TextOut(Rect.Width() / 2 - 90, Rect.Height() / 2 + 20, KEY_TEXT1);
	// �L�[�e�L�X�g2�\��
	pDC->TextOut(Rect.Width() / 2 - 90, Rect.Height() / 2 + 40, KEY_TEXT2);	
	// 
}
/////////////////////////////////////////////////////////////////////////////
// CPuyo1View �N���X�̐f�f

#ifdef _DEBUG
void CPuyo1View::AssertValid() const
{
	CView::AssertValid();
}

void CPuyo1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPuyo1Doc* CPuyo1View::GetDocument() // ��f�o�b�O �o�[�W�����̓C�����C���ł��B
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPuyo1Doc)));
	return (CPuyo1Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPuyo1View �N���X�̃��b�Z�[�W �n���h��

int CPuyo1View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: ���̈ʒu�ɌŗL�̍쐬�p�R�[�h��ǉ����Ă�������

	// �J�n�{�^���쐬
    CRect rect;
	int left = FIELD_WIDTH * PUYO_SIZE / 2 - 50;
	int top = FIELD_HEIGHT * PUYO_SIZE / 2 - 80;
	int right = left + 80;
	int bottom = top + 50;	
	rect.SetRect(left, top, right, bottom);
	
    m_pButton = new CButton();
	m_pButton->Create("�J�n", BS_PUSHBUTTON, rect, this, BUTTONID);
	m_pButton->ShowWindow(SW_SHOW);
	
	// �e�L�X�g�t�H���g�쐬
	m_TextFont.CreateFont(40, 0, 0, 0, FW_BOLD, FALSE, TRUE, FALSE, SHIFTJIS_CHARSET, 
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_ROMAN, NULL);	
	
	return 0;
}

//---------------------//
// �R�}���h���b�Z�[�W  //
//---------------------//
BOOL CPuyo1View::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������

	// �{�^��
	if (wParam == BUTTONID)
	{
		CDC* pDC = this->GetDC();
		CRect rect;
		GetClientRect(&rect);

		// �X�N���[���A�E�g
		while(ScreenOut(pDC, rect))
		{
			Sleep(1);
		}
		// �{�^����\��
		m_pButton->LockWindowUpdate();
		m_pButton->ShowWindow(SW_HIDE);

		//----------------//
		// �X���b�h�̍쐬 //
		//----------------//
		m_pThread = AfxBeginThread(DrawThread, this);
		
		// �^�C�}�[�̍쐬
		StartTimer();
	}
	return CView::OnCommand(wParam, lParam);
}
//-------------------//
// �X�N���[���A�E�g  //
//-------------------//
BOOL CPuyo1View::ScreenOut(CDC* pDC, const CRect &Rect)
{
	static uint y = 0;

	// 6�{����������
	for (int i = 0; i < 6; i ++)
	{
		// �ォ������Ă�
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
// �L�[����   //
//------------//
void CPuyo1View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// �X�^���o�C���͖���
	if (GetDocument()->m_Game.IsGameStandby())
	{
		return;
	}

	puyoCtrl CtrlKey = puyoDisregard;		// �����L�[
	
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����邩�܂��̓f�t�H���g�̏������Ăяo���Ă�������
    switch (nChar) 
	{
	  // ���@
	  case VK_LEFT:  
		CtrlKey = puyoLEFT;
		break;
	  // �E �@
	  case VK_RIGHT:
		CtrlKey = puyoRIGHT;
		break;
	  // �� 
      case VK_DOWN:  
		CtrlKey = puyoDOWN;
		break;
	  // ����]
	  case 	VK_Z:
		CtrlKey = puyoLEFT_ROLL;
	  	break;
	  // �E��]
	  case 	VK_X:
		CtrlKey = puyoRIGHT_ROLL;
		break;
    }
	
	// �ړ��ɐ�������΍ĕ`��
	if ((!CtrlKey == puyoDisregard)
	&& (GetDocument()->m_Game.KeyControl(CtrlKey)))
	{
		// �ĕ`��
		Invalidate(FALSE);
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
//----------------------//
// �^�C�}�[�R�[���o�b�N //
//----------------------//
void CPuyo1View::OnTimer(UINT nIDEvent) 
{
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����邩�܂��̓f�t�H���g�̏������Ăяo���Ă�������
	
	if (nIDEvent == MOVE_TIMERID)
	{
		EndTimer();

//		TRACE("%d,%d\n", 
//			GetDocument()->m_Game.m_PuyoPuyo.GetPosition_x(0),
//			GetDocument()->m_Game.m_PuyoPuyo.GetPosition_y(0));

		// �L�[���b�Z�[�W�𑗂�
		OnKeyDown(VK_DOWN, 0, 0);
		
		StartTimer();

		// �ĕ`��
		Invalidate(FALSE);
	}

	CView::OnTimer(nIDEvent);
}
//--------------------//
// KillTimer Wrapping //
//--------------------//
void CPuyo1View::EndTimer()
{
	// �^�C�}�[�~�߂�
	KillTimer(MOVE_TIMERID);	
}
//--------------------//
// SetTimer Wrapping  //
//--------------------//
void CPuyo1View::StartTimer()
{
	// �^�C�}�[�J�n
	SetTimer(MOVE_TIMERID, TIMER_INVAL, NULL);
}

///////////////////////////////////////
// ���[�J�[�X���b�h	(fps�`��)		 //
///////////////////////////////////////
UINT DrawThread(LPVOID pParam)
{
	DWORD		frames		 = 0;									// �t���[����
	DWORD		beforeTime	 = 0;									// �J�n����
	CPuyo1View* View		 = static_cast<CPuyo1View*>(pParam);	// view
	CDC*		pDC			 = View->GetDC();						// �`��hdc
	CPuyo1Doc* pDoc			 = View->GetDocument();					// doc

	// �`��p�N���C�A���g�̈�̍쐬
	CRect rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = PUYO_SIZE * FIELD_WIDTH;
	rect.bottom = PUYO_SIZE * FIELD_HEIGHT + PUYO_SIZE;

	// �Q�[���̏�����
	pDoc->m_Game.Create(pDC, &rect);
	pDoc->m_Game.m_hwnd = View->m_hWnd;
	
	beforeTime = timeGetTime();
	
	// �Q�[���X�^�[�g

	while (1)
	{
		DWORD nowTime;			// ���ݎ���
		DWORD progress;			// �i�񂾎���
		DWORD idealTime = 0;	// �`�掞��
	
		nowTime = timeGetTime();
		progress = nowTime - beforeTime;
		idealTime = static_cast<DWORD>(frames * (1000.0f / FPS));

		// �ĕ`��
		InvalidateRect(View->m_hWnd, NULL, FALSE);
		
		// �`�掞�Ԃ܂őҋ@
		if (idealTime > progress)
		{
			Sleep(idealTime - progress);
		}

		// �`��
		pDoc->m_Game.ForeDrawScreen();

		// ��
		frames ++;
		
	}
	return 0;
}
