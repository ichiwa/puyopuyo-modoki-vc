// PuyoPuyo.h: CPuyoPuyo クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PUYOPUYO_H__27182CBB_91E8_4A5C_9B5D_98ECB0CB9562__INCLUDED_)
#define AFX_PUYOPUYO_H__27182CBB_91E8_4A5C_9B5D_98ECB0CB9562__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Puyo.h"

// プヨプヨクラス
class CPuyoPuyo  
{
public:
	CPuyoPuyo();
	virtual ~CPuyoPuyo();

	void			Create(const uchar* randomTable);		// プヨプヨ作成
	void			CtrlPuyo(const puyoCtrl CtrlKey);		// キー操作
	const uchar		GetPosition_x(const int arrayNum) const // 位置取得x
	{
		return m_Puyo[arrayNum].GetPos_x();
	}														
	const uchar		GetPosition_y(const int arrayNum) const	// 位置取得y
	{
		return m_Puyo[arrayNum].GetPos_y();
	}	
	const puyoAttr	GetAttr(const int arrayNum) const		// 属性取得
	{
		return m_Puyo[arrayNum].GetAttr();
	}
	const puyoState GetpuyoState() const					// プヨ状態取得
	{
		return m_puyoState;
	}				

private:
	void			RollPuyo(const puyoCtrl roll);			// 回転操作
private:
	CPuyo			m_Puyo[2];								// プヨプヨ
	puyoState		m_puyoState;							// プヨの状態
};


#endif // !defined(AFX_PUYOPUYO_H__27182CBB_91E8_4A5C_9B5D_98ECB0CB9562__INCLUDED_)
