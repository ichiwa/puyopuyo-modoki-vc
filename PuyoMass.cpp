// PuyoMass.cpp: CPuyoMass �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "puyo1.h"
#include "PuyoMass.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

CPuyoMass::CPuyoMass()
:m_Attr(puyoNONE)
{
	m_Posi.x = 0;
	m_Posi.y = 0;
}

CPuyoMass::~CPuyoMass()
{

}

//------//
// �\�z //
//------//
void CPuyoMass::Create(int x, int y)
{
	m_Posi.x = x;					// �}�X�ʒux
	m_Posi.y = y;					// �}�X�ʒuy
}