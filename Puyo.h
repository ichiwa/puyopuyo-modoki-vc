// Puyo.h: CPuyo �N���X�̃C���^�[�t�F�C�X
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PUYO_H__601472D0_9145_4CA1_8DA3_781187331D2E__INCLUDED_)
#define AFX_PUYO_H__601472D0_9145_4CA1_8DA3_781187331D2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// �v���N���X
class CPuyo  
{
public:
	CPuyo();
	virtual ~CPuyo();
	void SetAttr(puyoAttr attr)				// �����ݒ�
	{
		m_Attr = attr;
	}									
	void SetPos(uchar x, uchar y)			// �ʒu�ݒ�
	{
		m_Pos.x = x;
		m_Pos.y = y;
	}										
	void Set_x(uchar x)						// �ʒu�ݒ�x
	{
		if (x >= 0 && x < FIELD_WIDTH)
		{
			m_Pos.x = x;
		}
	}										
	void Set_y(uchar y)						// �ʒu�ݒ�y
	{
		if (y >= 0 && y < FIELD_HEIGHT)
		{
			m_Pos.y = y;
		}
	}											
	void Add_x(uchar num)					// ���݈ʒux�Ƀv���X
	{
		m_Pos.x = static_cast<uchar>(m_Pos.x + num);
	}										
	void Subtrc_x(uchar num)				// ���݈ʒux�Ƀ}�C�i�X
	{
		// 0���傫��
		if (m_Pos.x > 0)
		{
			m_Pos.x = static_cast<uchar>(m_Pos.x - num);
		}
	}										
	void Add_y(uchar num)					// ���݈ʒuy�Ƀv���X
	{
		m_Pos.y = static_cast<uchar>(m_Pos.y + num);
	}										
	void Subtrc_y(uchar num)				// ���݈ʒuy�Ƀ}�C�i�X
	{
		// 0���傫��
		if (m_Pos.y > 0)
		{
			m_Pos.y = static_cast<uchar>(m_Pos.y - num);
		}
	}										
	const uchar GetPos_x() const			// ���݈ʒu�擾x
	{
		return m_Pos.x;	
	}
	const uchar GetPos_y() const			// ���݈ʒu�擾y
	{	
		return m_Pos.y;
	}										
	const puyoAttr GetAttr() const			// �����擾
	{
		return m_Attr;
	}
	bool operator ==(const CPuyo &puyo)const
	{
		if (m_Pos.x == puyo.GetPos_x() && m_Pos.y == puyo.GetPos_y())
		{
			return true;
		}
		return false;
	}										
private:
	puyoAttr m_Attr;						// �v������
	puyoPos  m_Pos;							// �v���ʒu
};

#endif // !defined(AFX_PUYO_H__601472D0_9145_4CA1_8DA3_781187331D2E__INCLUDED_)
