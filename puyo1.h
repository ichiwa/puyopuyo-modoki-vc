// puyo1.h : PUYO1 �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C��
//

#if !defined(AFX_PUYO1_H__6267A328_66A5_4C3E_89BE_7E2BC7E77408__INCLUDED_)
#define AFX_PUYO1_H__6267A328_66A5_4C3E_89BE_7E2BC7E77408__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // ���C�� �V���{��

/////////////////////////////////////////////////////////////////////////////
// CPuyo1App:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� puyo1.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CPuyo1App : public CWinApp
{
public:
	CPuyo1App();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CPuyo1App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
	//{{AFX_MSG(CPuyo1App)
	afx_msg void OnAppAbout();
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_PUYO1_H__6267A328_66A5_4C3E_89BE_7E2BC7E77408__INCLUDED_)
