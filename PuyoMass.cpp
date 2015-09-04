// PuyoMass.cpp: CPuyoMass クラスのインプリメンテーション
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
// 構築/消滅
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
// 構築 //
//------//
void CPuyoMass::Create(int x, int y)
{
	m_Posi.x = x;					// マス位置x
	m_Posi.y = y;					// マス位置y
}