// PuyoPuyo.cpp: CPuyoPuyo クラスのインプリメンテーション
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
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CPuyoPuyo::CPuyoPuyo()
//:m_puyoState(puyoUpperSide)
{

}

CPuyoPuyo::~CPuyoPuyo()
{
	
}

//----------------------//
// プヨプヨクラスの構築 //
//----------------------//
void CPuyoPuyo::Create(const uchar* randomTable)
{
	//----------------//
	// プヨプヨの作成 //
	//----------------//
	// 1つめ属性
	m_Puyo[0].SetAttr(static_cast<puyoAttr>(randomTable[GetRandom(0, RANDOM_MAX)]));
	// 2つめ属性
	m_Puyo[1].SetAttr(static_cast<puyoAttr>(randomTable[GetRandom(0, RANDOM_MAX)]));

	// 位置
	m_Puyo[0].SetPos(static_cast<uchar>(FIRST_PUYO_X), static_cast<uchar>(FIRST_PUYO_Y));
	m_Puyo[1].SetPos(static_cast<uchar>(FIRST_PUYO_X), static_cast<uchar>(FIRST_PUYO_Y));

	// プヨ状態
	m_puyoState = puyoUpperSide;
}

//---------------------------//
// プヨプヨのキー制御		 //
//---------------------------//
void CPuyoPuyo::CtrlPuyo(const puyoCtrl CtrlKey)
{
	CPuyo			tmpPuyo[2];		// 仮プヨプヨ
	puyoState		tmpState;		// 仮状態

	// 仮を作っておく
	tmpPuyo[0] = m_Puyo[0];
	tmpPuyo[1] = m_Puyo[1];
	tmpState   = m_puyoState;

	// キー別に処理する
	switch(CtrlKey)
	{
		case puyoDOWN:		// 下
		{
			// 最初だけ
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
		case puyoLEFT:			// 左
		{
			m_Puyo[0].Subtrc_x(1);
			m_Puyo[1].Subtrc_x(1);
			break;
		}
		case puyoRIGHT:			// 右
		{
			m_Puyo[0].Add_x(1);
			m_Puyo[1].Add_x(1);
			break;
		}
		case puyoLEFT_ROLL:		// 左回転
		case puyoRIGHT_ROLL:	// 右回転
		{
			// プヨプヨの回転制御
			RollPuyo(CtrlKey);
			break;
		}
		default:
			break;
	}
	// 同じところに移動した場合
	if (m_Puyo[0] == m_Puyo[1])
	{
		m_Puyo[0] = tmpPuyo[0];
		m_Puyo[1] = tmpPuyo[1];
		m_puyoState = tmpState;
	}
}
//---------------------------//
// プヨプヨの回転制御		 //
//---------------------------//
void CPuyoPuyo::RollPuyo(const puyoCtrl roll)
{
	// 最初
	if (m_Puyo[0].GetPos_y() == FIRST_PUYO_Y)
	{
		return;
	}

	// 状態 別に処理する
	switch(m_puyoState)
	{
	  // 下向き
	  case puyoLowSide:
		m_Puyo[1].Set_x(static_cast<uchar>
		(roll == puyoLEFT_ROLL ? m_Puyo[0].GetPos_x() + 1 : m_Puyo[0].GetPos_x() - 1));
		m_Puyo[1].Set_y(m_Puyo[0].GetPos_y());
		m_puyoState = roll == puyoLEFT_ROLL ? puyoRightSide : puyoLeftSide;
		break;
	  // 上向き
	  case puyoUpperSide:
		m_Puyo[1].Set_x(static_cast<uchar>
		(roll == puyoLEFT_ROLL ? m_Puyo[0].GetPos_x() - 1 : m_Puyo[0].GetPos_x() + 1));
		m_Puyo[1].Set_y(m_Puyo[0].GetPos_y());
		m_puyoState = roll == puyoLEFT_ROLL ? puyoLeftSide : puyoRightSide;
		break;
	  // 右向き
	  case puyoRightSide:
		m_Puyo[1].Set_y(static_cast<uchar>
		(roll == puyoLEFT_ROLL ? m_Puyo[0].GetPos_y() - 1 : m_Puyo[0].GetPos_y() + 1));
		m_Puyo[1].Set_x(m_Puyo[0].GetPos_x());
		m_puyoState = roll == puyoLEFT_ROLL ? puyoUpperSide : puyoLowSide;
		break;
	  // 左向き
	  case puyoLeftSide:
		m_Puyo[1].Set_y(static_cast<uchar>
		(roll == puyoLEFT_ROLL ? m_Puyo[0].GetPos_y() + 1 : m_Puyo[0].GetPos_y() - 1));
		m_Puyo[1].Set_x(m_Puyo[0].GetPos_x());
		m_puyoState = roll == puyoLEFT_ROLL ? puyoLowSide : puyoUpperSide;
		break;
	}
}

