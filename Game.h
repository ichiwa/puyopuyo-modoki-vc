// Game.h: CGame �N���X�̃C���^�[�t�F�C�X
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAME_H__4F56E4D9_D3CD_4D3A_B12E_7A0E45570D90__INCLUDED_)
#define AFX_GAME_H__4F56E4D9_D3CD_4D3A_B12E_7A0E45570D90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Field.h"
#include "PuyoPuyo.h"

class CGame  
{
private:
	CRect			m_Rect;							// �`��͈�
	CField			m_Field;						// �t�B�[���h�N���X
   CCriticalSection m_Section;						// ��������
#ifdef _DEBUG	// �f�o�b�O��
public:
#else			// �����[�X��
private:
#endif
	CPuyoPuyo		m_PuyoPuyo;						// ���쒆�v���v��
	CDC*			m_pInDC;						// �`��t�H�A�o�b�t�@
	uchar			m_RanDomTable[RANDOM_MAX];		// �����e�[�u��
	GameStatus		m_GameStatus;					// �Q�[�����
	CBrush*			m_Brush[MAX_BRUSH];				// �`��p�u���V
	CFont			m_Font;							// �`��p�t�H���g
	uint			m_ChainCount;					// �A����
private:
	CBrush*			GetBrushColor(puyoAttr attr);	// �u���V�̎擾
	BOOL			GetDownFlg(const BOOL* downFlg);// �_�E���t���O�̔���
	void			CheckField();					// �t�B�[���h�̃`�F�b�N
	void			GameOverEffect();				// �Q�[���I�[�o�[����
	void			CountPuyo(uchar x, uchar y, uint& count);// �v����������	
	void			VanishPuyo(uchar x, uchar y);	// �v������
	void			DropPuyo();						// �v����������
	void			MainChain();					// ���C���̃v���v������
	void			DrawPuyoPuyo();					// ���쒆�v���v���`��
	void			DrawFieldMass();				// �S�}�X�ڕ`��
	void			DrawInfoString();				// ��񕶎���`��
	void			DrawFieldLine();				// �t�B�[���h���`��
public:
	CGame();
	virtual ~CGame();
	void			Create(CDC* pDC, const CRect* rect);// ������
	void			BackDrawScreen();				// �o�b�N�o�b�t�@�`��
	void			ForeDrawScreen();				// �t�H�A�o�b�t�@�`��
	void			BackForeDrawScreen();			// ���o�b�t�@�̕`��
	BOOL			KeyControl(const puyoCtrl key);	// �L�[����
	BOOL			IsGameOver();					// �Q�[���I�[�o�[��
	BOOL			IsEffect();						// �G�t�F�N�g��
	BOOL			IsGameStandby();				// �Q�[���ҋ@����
public:
	HWND			m_hwnd;							// �r���[�n���h��
	CBitmap*		m_pBitmap;						// �o�b�N�o�b�t�@BMP
	CDC*			m_pOutDC;						// �`��o�b�N�o�b�t�@
};

// SubFunction
int GetRandom(int min, int max);

#endif // !defined(AFX_GAME_H__4F56E4D9_D3CD_4D3A_B12E_7A0E45570D90__INCLUDED_)
