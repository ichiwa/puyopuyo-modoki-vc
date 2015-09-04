// Puyo.h: CPuyo クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PUYO_H__601472D0_9145_4CA1_8DA3_781187331D2E__INCLUDED_)
#define AFX_PUYO_H__601472D0_9145_4CA1_8DA3_781187331D2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// プヨクラス
class CPuyo  
{
public:
	CPuyo();
	virtual ~CPuyo();
	void SetAttr(puyoAttr attr)				// 属性設定
	{
		m_Attr = attr;
	}									
	void SetPos(uchar x, uchar y)			// 位置設定
	{
		m_Pos.x = x;
		m_Pos.y = y;
	}										
	void Set_x(uchar x)						// 位置設定x
	{
		if (x >= 0 && x < FIELD_WIDTH)
		{
			m_Pos.x = x;
		}
	}										
	void Set_y(uchar y)						// 位置設定y
	{
		if (y >= 0 && y < FIELD_HEIGHT)
		{
			m_Pos.y = y;
		}
	}											
	void Add_x(uchar num)					// 現在位置xにプラス
	{
		m_Pos.x = static_cast<uchar>(m_Pos.x + num);
	}										
	void Subtrc_x(uchar num)				// 現在位置xにマイナス
	{
		// 0より大きい
		if (m_Pos.x > 0)
		{
			m_Pos.x = static_cast<uchar>(m_Pos.x - num);
		}
	}										
	void Add_y(uchar num)					// 現在位置yにプラス
	{
		m_Pos.y = static_cast<uchar>(m_Pos.y + num);
	}										
	void Subtrc_y(uchar num)				// 現在位置yにマイナス
	{
		// 0より大きい
		if (m_Pos.y > 0)
		{
			m_Pos.y = static_cast<uchar>(m_Pos.y - num);
		}
	}										
	const uchar GetPos_x() const			// 現在位置取得x
	{
		return m_Pos.x;	
	}
	const uchar GetPos_y() const			// 現在位置取得y
	{	
		return m_Pos.y;
	}										
	const puyoAttr GetAttr() const			// 属性取得
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
	puyoAttr m_Attr;						// プヨ属性
	puyoPos  m_Pos;							// プヨ位置
};

#endif // !defined(AFX_PUYO_H__601472D0_9145_4CA1_8DA3_781187331D2E__INCLUDED_)
