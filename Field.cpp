// Field.cpp: CField �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "puyo1.h"
#include "Field.h"
#include "PuyoPuyo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

CField::CField()
{

}

CField::~CField()
{
}

//--------//
// �\�z   //
//--------//
void CField::Create()
{
	// �}�X���̏�����
	for(int i = 0; i < FIELD_WIDTH; i ++)
	{
		for(int j = 0; j < FIELD_HEIGHT; j ++)
		{
			m_PuyoMass[i][j].Create(i * PUYO_SIZE, j * PUYO_SIZE);
		}
	}
}

//----------------------//
// �v���������邩�̊m�F	//
//----------------------//
BOOL CField::CanMovedPuyo(const CPuyoPuyo& pPuyoPuyo, const puyoCtrl /*key*/) const
{
	// ���݂����邩�m�F
	if ((m_PuyoMass[pPuyoPuyo.GetPosition_x(0)][pPuyoPuyo.GetPosition_y(0)].m_Attr != puyoNONE)	// �F
	||  (m_PuyoMass[pPuyoPuyo.GetPosition_x(1)][pPuyoPuyo.GetPosition_y(1)].m_Attr != puyoNONE)	// �F
	||	(FIELD_WIDTH <= pPuyoPuyo.GetPosition_x(0))		// ��
	||  (FIELD_WIDTH <= pPuyoPuyo.GetPosition_x(1))		
	||  (FIELD_HEIGHT <= pPuyoPuyo.GetPosition_y(0))	// �c
	||  (FIELD_HEIGHT <= pPuyoPuyo.GetPosition_y(1))
	||  (0 > pPuyoPuyo.GetPosition_x(0))
	||  (0 > pPuyoPuyo.GetPosition_x(1)))
	{
		return FALSE;	// �����Ȃ�
	}
	return TRUE;		// ������
}

//--------------------------------//
// �t�B�[���h�Ƀv���v����ۑ����� //
//--------------------------------//
void CField::SetFieldPuyo(const CPuyoPuyo& pPuyoPuyo)
{
	cuchar puyo_x0 = pPuyoPuyo.GetPosition_x(0);
	cuchar puyo_y0 = pPuyoPuyo.GetPosition_y(0);
	cuchar puyo_x1 = pPuyoPuyo.GetPosition_x(1);
	cuchar puyo_y1 = pPuyoPuyo.GetPosition_y(1);
	
	// �v��1
	m_PuyoMass[puyo_x0][puyo_y0].m_Attr
	= pPuyoPuyo.GetAttr(0);
	// �v��2
	m_PuyoMass[puyo_x1][puyo_y1].m_Attr 
	= pPuyoPuyo.GetAttr(1);
}

//------------------------//
// x���̃v���𗎂Ƃ�����  //
//------------------------//	
BOOL CField::DropField(const uchar x)
{
	BOOL bFlg = FALSE;

	// ��ԉ��͌��Ȃ�����-2
	uchar y = FIELD_HEIGHT - 2;

	//y��0�܂ŉ񂷂��߂ɃJ�E���^
	for (int count = 0; count < FIELD_HEIGHT - 1; count++, y--)
	{
		if ((m_PuyoMass[x][y].m_Attr != puyoNONE)
		&&  (m_PuyoMass[x][y + 1].m_Attr == puyoNONE))
		{
			m_PuyoMass[x][y + 1].m_Attr = m_PuyoMass[x][y].m_Attr;
			m_PuyoMass[x][y].m_Attr = puyoNONE; 
			bFlg = TRUE;
		}
	}
	return bFlg;
}