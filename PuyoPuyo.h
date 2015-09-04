// PuyoPuyo.h: CPuyoPuyo �N���X�̃C���^�[�t�F�C�X
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PUYOPUYO_H__27182CBB_91E8_4A5C_9B5D_98ECB0CB9562__INCLUDED_)
#define AFX_PUYOPUYO_H__27182CBB_91E8_4A5C_9B5D_98ECB0CB9562__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Puyo.h"

// �v���v���N���X
class CPuyoPuyo  
{
public:
	CPuyoPuyo();
	virtual ~CPuyoPuyo();

	void			Create(const uchar* randomTable);		// �v���v���쐬
	void			CtrlPuyo(const puyoCtrl CtrlKey);		// �L�[����
	const uchar		GetPosition_x(const int arrayNum) const // �ʒu�擾x
	{
		return m_Puyo[arrayNum].GetPos_x();
	}														
	const uchar		GetPosition_y(const int arrayNum) const	// �ʒu�擾y
	{
		return m_Puyo[arrayNum].GetPos_y();
	}	
	const puyoAttr	GetAttr(const int arrayNum) const		// �����擾
	{
		return m_Puyo[arrayNum].GetAttr();
	}
	const puyoState GetpuyoState() const					// �v����Ԏ擾
	{
		return m_puyoState;
	}				

private:
	void			RollPuyo(const puyoCtrl roll);			// ��]����
private:
	CPuyo			m_Puyo[2];								// �v���v��
	puyoState		m_puyoState;							// �v���̏��
};


#endif // !defined(AFX_PUYOPUYO_H__27182CBB_91E8_4A5C_9B5D_98ECB0CB9562__INCLUDED_)
