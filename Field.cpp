// Field.cpp: CField クラスのインプリメンテーション
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
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CField::CField()
{

}

CField::~CField()
{
}

//--------//
// 構築   //
//--------//
void CField::Create()
{
	// マス情報の初期化
	for(int i = 0; i < FIELD_WIDTH; i ++)
	{
		for(int j = 0; j < FIELD_HEIGHT; j ++)
		{
			m_PuyoMass[i][j].Create(i * PUYO_SIZE, j * PUYO_SIZE);
		}
	}
}

//----------------------//
// プヨが動けるかの確認	//
//----------------------//
BOOL CField::CanMovedPuyo(const CPuyoPuyo& pPuyoPuyo, const puyoCtrl /*key*/) const
{
	// 存在があるか確認
	if ((m_PuyoMass[pPuyoPuyo.GetPosition_x(0)][pPuyoPuyo.GetPosition_y(0)].m_Attr != puyoNONE)	// 色
	||  (m_PuyoMass[pPuyoPuyo.GetPosition_x(1)][pPuyoPuyo.GetPosition_y(1)].m_Attr != puyoNONE)	// 色
	||	(FIELD_WIDTH <= pPuyoPuyo.GetPosition_x(0))		// 横
	||  (FIELD_WIDTH <= pPuyoPuyo.GetPosition_x(1))		
	||  (FIELD_HEIGHT <= pPuyoPuyo.GetPosition_y(0))	// 縦
	||  (FIELD_HEIGHT <= pPuyoPuyo.GetPosition_y(1))
	||  (0 > pPuyoPuyo.GetPosition_x(0))
	||  (0 > pPuyoPuyo.GetPosition_x(1)))
	{
		return FALSE;	// 動けない
	}
	return TRUE;		// 動ける
}

//--------------------------------//
// フィールドにプヨプヨを保存する //
//--------------------------------//
void CField::SetFieldPuyo(const CPuyoPuyo& pPuyoPuyo)
{
	cuchar puyo_x0 = pPuyoPuyo.GetPosition_x(0);
	cuchar puyo_y0 = pPuyoPuyo.GetPosition_y(0);
	cuchar puyo_x1 = pPuyoPuyo.GetPosition_x(1);
	cuchar puyo_y1 = pPuyoPuyo.GetPosition_y(1);
	
	// プヨ1
	m_PuyoMass[puyo_x0][puyo_y0].m_Attr
	= pPuyoPuyo.GetAttr(0);
	// プヨ2
	m_PuyoMass[puyo_x1][puyo_y1].m_Attr 
	= pPuyoPuyo.GetAttr(1);
}

//------------------------//
// x軸のプヨを落とす処理  //
//------------------------//	
BOOL CField::DropField(const uchar x)
{
	BOOL bFlg = FALSE;

	// 一番下は見ないため-2
	uchar y = FIELD_HEIGHT - 2;

	//yを0まで回すためにカウンタ
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