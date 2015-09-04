// Field.h: CField クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIELD_H__1D01BA79_574E_4B8D_8C81_64D9D812217B__INCLUDED_)
#define AFX_FIELD_H__1D01BA79_574E_4B8D_8C81_64D9D812217B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PuyoMass.h"

class CPuyoPuyo;

// フィールドクラス
class CField  
{
public:
	CPuyoMass		m_PuyoMass[FIELD_WIDTH][FIELD_HEIGHT];	// フィールド
public:
	CField();
	virtual ~CField();
	void	Create();										// 構築
	BOOL	CanMovedPuyo(const CPuyoPuyo& pPuyoPuyo,		// プヨが動けるかどうか?
		const puyoCtrl key) const;									
	void	SetFieldPuyo(const CPuyoPuyo& pPuyoPuyo);		// フィールドに属性を保存する
	BOOL	DropField(const uchar x);						// xの値をちぎって落とす処理
};

#endif // !defined(AFX_FIELD_H__1D01BA79_574E_4B8D_8C81_64D9D812217B__INCLUDED_)
