// PuyoMass.h: CPuyoMass �N���X�̃C���^�[�t�F�C�X
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PUYOMASS_H__2110B62D_0C9F_4E49_B4D9_EAE7A4AA6C11__INCLUDED_)
#define AFX_PUYOMASS_H__2110B62D_0C9F_4E49_B4D9_EAE7A4AA6C11__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// �}�X�N���X
class CPuyoMass  
{
public:
	CPuyoMass();
	virtual ~CPuyoMass();
	void Create(int x, int y);			// �v���}�X�̏�����

public:
	puyoAttr	m_Attr;					// �v������
	CPoint		m_Posi;					// �ʒu���
};

#endif // !defined(AFX_PUYOMASS_H__2110B62D_0C9F_4E49_B4D9_EAE7A4AA6C11__INCLUDED_)
