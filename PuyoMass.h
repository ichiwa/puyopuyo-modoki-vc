// PuyoMass.h: CPuyoMass クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PUYOMASS_H__2110B62D_0C9F_4E49_B4D9_EAE7A4AA6C11__INCLUDED_)
#define AFX_PUYOMASS_H__2110B62D_0C9F_4E49_B4D9_EAE7A4AA6C11__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// マスクラス
class CPuyoMass  
{
public:
	CPuyoMass();
	virtual ~CPuyoMass();
	void Create(int x, int y);			// プヨマスの初期化

public:
	puyoAttr	m_Attr;					// プヨ属性
	CPoint		m_Posi;					// 位置情報
};

#endif // !defined(AFX_PUYOMASS_H__2110B62D_0C9F_4E49_B4D9_EAE7A4AA6C11__INCLUDED_)
