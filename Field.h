// Field.h: CField �N���X�̃C���^�[�t�F�C�X
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIELD_H__1D01BA79_574E_4B8D_8C81_64D9D812217B__INCLUDED_)
#define AFX_FIELD_H__1D01BA79_574E_4B8D_8C81_64D9D812217B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PuyoMass.h"

class CPuyoPuyo;

// �t�B�[���h�N���X
class CField  
{
public:
	CPuyoMass		m_PuyoMass[FIELD_WIDTH][FIELD_HEIGHT];	// �t�B�[���h
public:
	CField();
	virtual ~CField();
	void	Create();										// �\�z
	BOOL	CanMovedPuyo(const CPuyoPuyo& pPuyoPuyo,		// �v���������邩�ǂ���?
		const puyoCtrl key) const;									
	void	SetFieldPuyo(const CPuyoPuyo& pPuyoPuyo);		// �t�B�[���h�ɑ�����ۑ�����
	BOOL	DropField(const uchar x);						// x�̒l���������ė��Ƃ�����
};

#endif // !defined(AFX_FIELD_H__1D01BA79_574E_4B8D_8C81_64D9D812217B__INCLUDED_)
