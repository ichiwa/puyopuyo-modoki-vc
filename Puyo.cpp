// Puyo.cpp: CPuyo クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "puyo1.h"
#include "Puyo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CPuyo::CPuyo()
:m_Attr(puyoNONE)
{
	m_Pos.x = 0;
	m_Pos.y = 0;
}

CPuyo::~CPuyo()
{

}

