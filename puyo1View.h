// puyo1View.h : CPuyo1View �N���X�̐錾����уC���^�[�t�F�C�X�̒�`�����܂��B
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
protected: // �V���A���C�Y�@�\�݂̂���쐬���܂��B
	CPuyo1View();
	DECLARE_DYNCREATE(CPuyo1View)

// �A�g���r���[�g
public:
	CPuyo1Doc* GetDocument();

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CPuyo1View)
	public:
	virtual void OnDraw(CDC* pDC);  // ���̃r���[��`�悷��ۂɃI�[�o�[���C�h����܂��B
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	void				EndTimer();		// �^�C�}�[�G���h
	void				StartTimer();	// �^�C�}�[�X�^�[�g
	virtual ~CPuyo1View();
private:
	BOOL				ScreenOut(CDC* pDC, const CRect &Rect);// �X�N���[���A�E�g
	void				DrawText(CDC* pDC, const CRect &Rect); // �e�L�X�g�`��
private:
	CWinThread*			m_pThread;		// �X���b�h
	CButton*			m_pButton;		// �{�^��	
	CFont				m_TextFont;		// �`��p�t�H���g
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CPuyo1View)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // puyo1View.cpp �t�@�C�����f�o�b�O���̎��g�p����܂��B
inline CPuyo1Doc* CPuyo1View::GetDocument()
   { return (CPuyo1Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

// ��Ɨp�X���b�h
UINT DrawThread(LPVOID pParam);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B


#endif // !defined(AFX_PUYO1VIEW_H__AD2135D2_95A8_404B_BE92_2A43FE8C6E9F__INCLUDED_)
