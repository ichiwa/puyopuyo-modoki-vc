// puyo1Doc.cpp : CPuyo1Doc �N���X�̓���̒�`���s���܂��B
//

#include "stdafx.h"
#include "puyo1.h"

#include "puyo1Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPuyo1Doc

IMPLEMENT_DYNCREATE(CPuyo1Doc, CDocument)

BEGIN_MESSAGE_MAP(CPuyo1Doc, CDocument)
	//{{AFX_MSG_MAP(CPuyo1Doc)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPuyo1Doc �N���X�̍\�z/����

CPuyo1Doc::CPuyo1Doc()
{
	// TODO: ���̈ʒu�ɂP�x�����Ă΂��\�z�p�̃R�[�h��ǉ����Ă��������B

}

CPuyo1Doc::~CPuyo1Doc()
{
}

BOOL CPuyo1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���̈ʒu�ɍď�����������ǉ����Ă��������B
	// (SDI �h�L�������g�͂��̃h�L�������g���ė��p���܂��B)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPuyo1Doc �V���A���C�[�[�V����

void CPuyo1Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���̈ʒu�ɕۑ��p�̃R�[�h��ǉ����Ă��������B
	}
	else
	{
		// TODO: ���̈ʒu�ɓǂݍ��ݗp�̃R�[�h��ǉ����Ă��������B
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPuyo1Doc �N���X�̐f�f

#ifdef _DEBUG
void CPuyo1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPuyo1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPuyo1Doc �R�}���h
