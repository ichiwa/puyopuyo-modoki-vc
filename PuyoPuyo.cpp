// PuyoPuyo.cpp: CPuyoPuyo �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "puyo1.h"
#include "PuyoPuyo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

int GetRandom(int min, int max);

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

CPuyoPuyo::CPuyoPuyo()
//:m_puyoState(puyoUpperSide)
{

}

CPuyoPuyo::~CPuyoPuyo()
{
	
}

//----------------------//
// �v���v���N���X�̍\�z //
//----------------------//
void CPuyoPuyo::Create(const uchar* randomTable)
{
	//----------------//
	// �v���v���̍쐬 //
	//----------------//
	// 1�ߑ���
	m_Puyo[0].SetAttr(static_cast<puyoAttr>(randomTable[GetRandom(0, RANDOM_MAX)]));
	// 2�ߑ���
	m_Puyo[1].SetAttr(static_cast<puyoAttr>(randomTable[GetRandom(0, RANDOM_MAX)]));

	// �ʒu
	m_Puyo[0].SetPos(static_cast<uchar>(FIRST_PUYO_X), static_cast<uchar>(FIRST_PUYO_Y));
	m_Puyo[1].SetPos(static_cast<uchar>(FIRST_PUYO_X), static_cast<uchar>(FIRST_PUYO_Y));

	// �v�����
	m_puyoState = puyoUpperSide;
}

//---------------------------//
// �v���v���̃L�[����		 //
//---------------------------//
void CPuyoPuyo::CtrlPuyo(const puyoCtrl CtrlKey)
{
	CPuyo			tmpPuyo[2];		// ���v���v��
	puyoState		tmpState;		// �����

	// ��������Ă���
	tmpPuyo[0] = m_Puyo[0];
	tmpPuyo[1] = m_Puyo[1];
	tmpState   = m_puyoState;

	// �L�[�ʂɏ�������
	switch(CtrlKey)
	{
		case puyoDOWN:		// ��
		{
			// �ŏ�����
			if (m_Puyo[0].GetPos_y() == FIRST_PUYO_Y)
			{
				m_Puyo[0].Add_y(1);
			}
			else
			{
				m_Puyo[0].Add_y(1);
				m_Puyo[1].Add_y(1);
			}
			break;
		}
		case puyoLEFT:			// ��
		{
			m_Puyo[0].Subtrc_x(1);
			m_Puyo[1].Subtrc_x(1);
			break;
		}
		case puyoRIGHT:			// �E
		{
			m_Puyo[0].Add_x(1);
			m_Puyo[1].Add_x(1);
			break;
		}
		case puyoLEFT_ROLL:		// ����]
		case puyoRIGHT_ROLL:	// �E��]
		{
			// �v���v���̉�]����
			RollPuyo(CtrlKey);
			break;
		}
		default:
			break;
	}
	// �����Ƃ���Ɉړ������ꍇ
	if (m_Puyo[0] == m_Puyo[1])
	{
		m_Puyo[0] = tmpPuyo[0];
		m_Puyo[1] = tmpPuyo[1];
		m_puyoState = tmpState;
	}
}
//---------------------------//
// �v���v���̉�]����		 //
//---------------------------//
void CPuyoPuyo::RollPuyo(const puyoCtrl roll)
{
	// �ŏ�
	if (m_Puyo[0].GetPos_y() == FIRST_PUYO_Y)
	{
		return;
	}

	// ��� �ʂɏ�������
	switch(m_puyoState)
	{
	  // ������
	  case puyoLowSide:
		m_Puyo[1].Set_x(static_cast<uchar>
		(roll == puyoLEFT_ROLL ? m_Puyo[0].GetPos_x() + 1 : m_Puyo[0].GetPos_x() - 1));
		m_Puyo[1].Set_y(m_Puyo[0].GetPos_y());
		m_puyoState = roll == puyoLEFT_ROLL ? puyoRightSide : puyoLeftSide;
		break;
	  // �����
	  case puyoUpperSide:
		m_Puyo[1].Set_x(static_cast<uchar>
		(roll == puyoLEFT_ROLL ? m_Puyo[0].GetPos_x() - 1 : m_Puyo[0].GetPos_x() + 1));
		m_Puyo[1].Set_y(m_Puyo[0].GetPos_y());
		m_puyoState = roll == puyoLEFT_ROLL ? puyoLeftSide : puyoRightSide;
		break;
	  // �E����
	  case puyoRightSide:
		m_Puyo[1].Set_y(static_cast<uchar>
		(roll == puyoLEFT_ROLL ? m_Puyo[0].GetPos_y() - 1 : m_Puyo[0].GetPos_y() + 1));
		m_Puyo[1].Set_x(m_Puyo[0].GetPos_x());
		m_puyoState = roll == puyoLEFT_ROLL ? puyoUpperSide : puyoLowSide;
		break;
	  // ������
	  case puyoLeftSide:
		m_Puyo[1].Set_y(static_cast<uchar>
		(roll == puyoLEFT_ROLL ? m_Puyo[0].GetPos_y() + 1 : m_Puyo[0].GetPos_y() - 1));
		m_Puyo[1].Set_x(m_Puyo[0].GetPos_x());
		m_puyoState = roll == puyoLEFT_ROLL ? puyoLowSide : puyoUpperSide;
		break;
	}
}

