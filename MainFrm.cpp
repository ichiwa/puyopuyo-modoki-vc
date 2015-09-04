// MainFrm.cpp : CMainFrame �N���X�̓���̒�`���s���܂��B
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
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame �N���X�̍\�z/����

CMainFrame::CMainFrame()
{
	// TODO: ���̈ʒu�Ƀ����o�̏����������R�[�h��ǉ����Ă��������B
	
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: ���̈ʒu�� CREATESTRUCT cs ���C�����āAWindow �N���X��X�^�C����
	//       �C�����Ă�������

	// �k���A�g��A�V�X�e�����j���[����
	cs.style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

	int left = 0;
	int top = 0;
	int right = FIELD_WIDTH * PUYO_SIZE;
	int bottom = FIELD_HEIGHT * PUYO_SIZE - PUYO_SIZE;	

	// �w�肷��N���C�A���g�̈�
	CRect	rect(left, top, right, bottom);
	// �w�肳�ꂽ�N���C�A���g�̈���m�ۂ��邽�߂ɕK�v�ȃE�B���h�E���W
	::AdjustWindowRectEx(&rect, cs.style, TRUE, cs.dwExStyle);
	// ��
	int Width = rect.Width();
	// ����
	int Height = rect.Height();

	// �T�C�Y�v�Z
	CRect	rcArea;
	::SystemParametersInfo(SPI_GETWORKAREA, NULL, &rcArea, NULL);
	int x = rcArea.left + (rcArea.Width() - Width) / 2;
	int y = rcArea.top + (rcArea.Height() - Height) / 2;

	// �T�C�Y�ύX
	cs.x = x;
	cs.y = y;
	cs.cx = Width ;
	cs.cy = Height;

	// �\����
	cs.lpszName = "���Ƃ��Ղ惂�h�L";
	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame �N���X�̐f�f

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
// CMainFrame ���b�Z�[�W �n���h��

