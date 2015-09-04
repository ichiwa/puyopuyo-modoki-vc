// Game.cpp: CGame �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "puyo1.h"
#include "Game.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

CGame::CGame()
:m_GameStatus(GameStandby)
,m_ChainCount(0)
{
	m_Rect.SetRectEmpty();

	m_pOutDC = new CDC;	
	m_pBitmap = new CBitmap;

	// ���A�A�ԁA�΁A���F�u���V�̍쐬
	m_Brush[puyoNONE]	= new CBrush(NONE_BRUSH);
	m_Brush[puyoBLUE]	= new CBrush(BLUE_BRUSH);
	m_Brush[puyoRED]	= new CBrush(RED_BRUSH);
	m_Brush[puyoGREEN]	= new CBrush(GREEN_BRUSH);
	m_Brush[puyoYELLOW]	= new CBrush(YELLOW_BRUSH);
	
	// �����̎�܂�
	srand(time(NULL));

	// �����e�[�u���̍쐬
	for (int i = 0; i < RANDOM_MAX; i ++)
	{
		m_RanDomTable[i] = static_cast<uchar>(GetRandom(1, 4));
	}
}

CGame::~CGame()
{
	for (int i = 0; i < MAX_BRUSH; i++)
	{
		delete m_Brush[i];	// �u���V�j��
	}
	delete m_pOutDC;		// �o�b�NDC�j��
	delete m_pBitmap;		// �o�b�NBMP�j��
}
//--------------------//
// �Q�[���N���X�̍\�z //
//--------------------//
void CGame::Create(CDC* pDC, const CRect* rect)
{
	// �o�b�N�o�b�t�@�̍쐬
	m_Rect = rect;
	m_pOutDC->CreateCompatibleDC(pDC);
	m_pBitmap->CreateCompatibleBitmap(pDC, m_Rect.Width(), m_Rect.Height());
	m_pOutDC->SelectObject(m_pBitmap);
	m_pInDC = CDC::FromHandle(pDC->GetSafeHdc());		// ����

	// �t�H���g�쐬
	m_Font.CreateFont(26, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, SHIFTJIS_CHARSET, 
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_ROMAN, NULL);	

	// �t�H���g�ݒ�
	m_pOutDC->SelectObject(&m_Font);

	// �e�L�X�g�J���[�ݒ�
	m_pOutDC->SetTextColor(INFO_BRUSH);

	// �w�i����
	m_pOutDC->SetBkMode(TRANSPARENT);
	
	// �t�B�[���h�N���X�̍\�z
	m_Field.Create();

	// �v���N���X�̍\�z
	m_PuyoPuyo.Create(m_RanDomTable);

	// �Q�[���X�^�[�g
	m_GameStatus = GameIdle;
}
//---------//
// ���`��  //
//---------//
void CGame::BackForeDrawScreen()
{
	BackDrawScreen();
	ForeDrawScreen();
}
//-----------//
// �\�`��	 //
//-----------//
void CGame::ForeDrawScreen()
{
	// ���b�N
	m_Section.Lock();

	// �t�H�A�o�b�t�@�Ƀo�b�N�o�b�t�@�ɕ`�� ����i��ɕ`�悳����(-PUYO_SIZE)
	m_pInDC->BitBlt(0, -PUYO_SIZE, m_Rect.Width(), m_Rect.Height(), m_pOutDC, 0, 0, SRCCOPY);

	// �A�����b�N
	m_Section.Unlock();
}
//-----------//
// ���`��	 //
//-----------//
void CGame::BackDrawScreen()
{
	// ���b�N
	m_Section.Lock();

	// ��ʃN���A
	m_pOutDC->FillSolidRect(0, 0, m_Rect.Width(), m_Rect.Height(), NONE_BRUSH);
	
	// �t�B�[���h���C���`��
	DrawFieldLine();

	// �t�B�[���h�`��
	DrawFieldMass();

	// �A�C�h����
	if (m_GameStatus == GameIdle)
	{ 
		// ���쒆�v���v���`��
		DrawPuyoPuyo();
	}

	// �A��������`��
	DrawInfoString();
	
	// �A�����b�N
	m_Section.Unlock();
}
//------------------//
// �u���V�̎擾		//
//------------------//
CBrush* CGame::GetBrushColor(puyoAttr attr)
{
	// ������
	switch(attr)
	{
	  case puyoNONE:
		break;
	  case puyoBLUE:
		return m_Brush[puyoBLUE];
	  case puyoRED:
		return m_Brush[puyoRED];
	  case puyoGREEN:
		return m_Brush[puyoGREEN];
	  case puyoYELLOW:
		return m_Brush[puyoYELLOW];
	  default:
		break;
	}
	ASSERT(0);
	return NULL;
}
//---------------------//
//  ���쒆�v���v���`�� //
//---------------------//
void CGame::DrawPuyoPuyo()
{
	// �v���v������
	for (uint i = 0; i < 2; i ++)
	{
		CBrush* brs;		// �v���F
		CRect rect;			// �~
		uchar x, y;			// �ʒu
		
		// �ʒu�擾
		x = m_PuyoPuyo.GetPosition_x(i);
		y = m_PuyoPuyo.GetPosition_y(i);
		
		// �F�擾
		brs = GetBrushColor(m_PuyoPuyo.GetAttr(i));
		
		m_pOutDC->SelectObject(brs);
		
		rect.SetRect(m_Field.m_PuyoMass[x][y].m_Posi.x, m_Field.m_PuyoMass[x][y].m_Posi.y,
			m_Field.m_PuyoMass[x][y].m_Posi.x + PUYO_SIZE, m_Field.m_PuyoMass[x][y].m_Posi.y + PUYO_SIZE);
		rect.InflateRect(1, 1, 1, 1);
		m_pOutDC->Ellipse(&rect);
	}
}
//---------------//
// �S�}�X�ڕ`��  //
//---------------//
void CGame::DrawFieldMass()
{
	// �}�X��񂩂炷�ׂĂ�`�悷��
	for (uint i = 0; i < FIELD_WIDTH; i ++)
	{
		// ��ԏ�͖���
		for (uint j = 1; j < FIELD_HEIGHT; j ++)	
		{
			CBrush* brs;		// �`��u���V

			// �}�X�F�Ȃ��͕`�悵�Ȃ�
			if (m_Field.m_PuyoMass[i][j].m_Attr == puyoNONE)
			{
				// ���}�X��
				continue;
			}
			// �}�X�F����̓u���V���擾����
			brs = GetBrushColor(m_Field.m_PuyoMass[i][j].m_Attr); // �F�擾

			m_pOutDC->SelectObject(brs);

			CRect rect;	// �~
			rect.SetRect(m_Field.m_PuyoMass[i][j].m_Posi.x, m_Field.m_PuyoMass[i][j].m_Posi.y,
				m_Field.m_PuyoMass[i][j].m_Posi.x + PUYO_SIZE, m_Field.m_PuyoMass[i][j].m_Posi.y + PUYO_SIZE);
			rect.InflateRect(1, 1, 1, 1);
			m_pOutDC->Ellipse(&rect);
		}
	}	
}
//-----------------//
// �A��������`��  //
//-----------------//
void CGame::DrawInfoString()
{
	// �A���Ȃ�
	if (m_ChainCount == 0)
	{
		return;
	}

	TRACE("count = %d\n", m_ChainCount);
	CString str;		// �����o�t
	
	// 5�A���ȏ�
	if (m_ChainCount > 4)
	{
		str.Format("%d�A���I�I�I", m_ChainCount);
	}
	// 3�A���ȏ�
	else if (m_ChainCount > 2)
	{
		str.Format("%d�A���I�I", m_ChainCount);
	}
	// ���̑�
	else
	{	
		str.Format("%d�A���I", m_ChainCount);
	}
	// �^�񒆕ӂ�ɕ`��
	m_pOutDC->TextOut(m_Field.m_PuyoMass[2][5].m_Posi.x, m_Field.m_PuyoMass[2][5].m_Posi.y, str);
}
//----------------------//
// �t�B�[���h���C���`�� //
//----------------------//
void CGame::DrawFieldLine()
{
	CPen pen;			// ���C���p�y��
	pen.CreatePen(PS_DASH, 1, GRAY__BRUSH);
	
	m_pOutDC->SelectObject(pen);
	
	// ����
	for (uint i = 0; i <= (uint)m_Rect.Height(); i += PUYO_SIZE)
	{
		m_pOutDC->MoveTo(0, i);
		m_pOutDC->LineTo(m_Rect.Width(), i);
	}
	// �c��
	for (uint j = 0; j <= (uint)m_Rect.Width(); j += PUYO_SIZE)
	{
		m_pOutDC->MoveTo(j, 0);
		m_pOutDC->LineTo(j, m_Rect.Height());
	}
	// ���ɖ߂�
	m_pOutDC->SelectStockObject(BLACK_PEN);
}
//------------------//
// �L�[�R���g���[�� //
//------------------//
BOOL CGame::KeyControl(const puyoCtrl key)
{
	CPuyoPuyo Temp;		// ���v���v��
	Temp = m_PuyoPuyo;	// �R�s�[

	// �ړ��������̂����
	Temp.CtrlPuyo(key);

	// �t�B�[���h�ړ��s�\
	if (!m_Field.CanMovedPuyo(Temp, key))
	{
		// �ړ��s�\�ŃL�[�����ȊO
		if (key != puyoDOWN)
		{
			// �ړ��s�\
			return FALSE;
		}

		// �G�t�F�N�g�ɂ���
		m_GameStatus = GameEffect;

		// �t�B�[���h�Ƀ����o�̃v���v����ۑ�����
		m_Field.SetFieldPuyo(m_PuyoPuyo);
		
		// �A������
		MainChain();
	
		// �t�B�[���h���`�F�b�N����
		CheckField();

		// �Q�[���I�[�o�[��?
		if (m_GameStatus == GameOver)
		{
			// �Q�[���I�[�o�[����
			GameOverEffect();
			
			// ���߂ɑ҂�����
			Sleep(EffectSleep*2);
		}
		// �V�����v���̍쐬
		m_PuyoPuyo.Create(m_RanDomTable);
		
		MSG dummy;		// �_�~�[

		// �L�[���b�Z�[�W���N���A���� �����b�Z�[�W������ƐV�����v���������Ă��܂���
		while(::PeekMessage(&dummy, m_hwnd, WM_KEYFIRST, WM_KEYLAST, PM_REMOVE));
		
		// �A�C�h���ɖ߂�
		m_GameStatus = GameIdle;
	}
	// �t�B�[���h�ړ��\
	else
	{
		// �{���ɉ����R�s�[����
		m_PuyoPuyo = Temp;
	}

	// �ĕ`��
	return TRUE;
}
//----------------------//
// ���C���̃v���v������ //
//----------------------//
void CGame::MainChain()
{
	BOOL ChainFlg = FALSE;		// �A���t���O
	
	while (1)
	{
		// �v����������
		DropPuyo();

		// �t�B�[���h�̑S����
		for (uchar i = 0; i <= FIELD_WIDTH-1; i ++)
		{
			for (uchar j = 0; j <= FIELD_HEIGHT; j ++)
			{
				uint Count = 0;	// �A����
				
				// �F�Ȃ��͐����Ȃ�
				if (m_Field.m_PuyoMass[i][j].m_Attr != puyoNONE)
				{
					CountPuyo(i, j, Count);

					// 4�ȏ�q�����Ă���v������
					if (Count > 3)
					{
						ChainFlg = TRUE;	// �A���t���OTRUE

						// �v������
						VanishPuyo(i, j);
					}
				}
			}
		}// for �t�B�[���h�̑S����
		
		// �ҋ@
		Sleep(EffectSleep);
		
		// �A���Ȃ�
		if (!ChainFlg)
		{
			break;
		}
		
		// �A����
		m_ChainCount++;

		// �`��
		BackForeDrawScreen();

		// �ҋ@
		Sleep(EffectSleep);

		// �A���t���O�߂�
		ChainFlg = FALSE;

		// �Č���
	}

	// �A���I���㏉����
	m_ChainCount = 0;
}
//---------------//
// �v����������	 //
//---------------//
void CGame::DropPuyo()
{
	// ���ʃt���O
	BOOL bDownFlg[FIELD_WIDTH] ={FALSE, FALSE, FALSE, FALSE, FALSE, FALSE};

	while (1)
	{
		// 1�s���Ƃɏ������s��
		for (uchar x = 0; x <= FIELD_WIDTH-1; x ++)
		{
			bDownFlg[x] = m_Field.DropField(x);
		}
		// �t���O������ꍇ
		if (GetDownFlg(bDownFlg))
		{
			Sleep(EffectSleep);
			
			BackDrawScreen();
		}
		// �t���O�Ȃ�
		else 
		{
			Sleep(EffectSleep);
			
			BackDrawScreen();

			break;
		}
	}
}
//--------------------//
// �_�E���t���O�̔��� //
//--------------------//
BOOL CGame::GetDownFlg(const BOOL* downFlg)
{
	for (int i = 0; i <= FIELD_WIDTH - 1; i ++)
	{
		if (downFlg[i] == TRUE)
			return TRUE;
	}
	return FALSE;
}
//-----------------//
// �v����������  //
//-----------------//
void CGame::CountPuyo(uchar x, uchar y, uint& count)
{
	// �F�̎擾
	puyoAttr attr = m_Field.m_PuyoMass[x][y].m_Attr;
	m_Field.m_PuyoMass[x][y].m_Attr = puyoNONE;

	count++;

	// �E
    if(x + 1 <= FIELD_WIDTH && m_Field.m_PuyoMass[x + 1][y].m_Attr == attr)
	{
		CountPuyo(static_cast<uchar>(x + 1), y, count);
	}
	// ��
    if(y + 1 <= FIELD_HEIGHT && m_Field.m_PuyoMass[x][y + 1].m_Attr == attr)
	{
		CountPuyo(x, static_cast<uchar>(y + 1), count);
	}
	// ��
    if(x - 1 >= 0 && m_Field.m_PuyoMass[x - 1][y].m_Attr == attr)
	{
		CountPuyo(static_cast<uchar>(x - 1), y, count);
	}
	// ��
    if(y - 1 >= 0 && m_Field.m_PuyoMass[x][y - 1].m_Attr == attr)
	{
		CountPuyo(x, static_cast<uchar>(y - 1), count);
	}
	
	// �������Ƃ���͌��ɖ߂�
	m_Field.m_PuyoMass[x][y].m_Attr = attr;
}
//------------------------------------//
// �n���ꂽ�v���Ɨאڂ���Ƃ�������� //
//------------------------------------//
void CGame::VanishPuyo(uchar x, uchar y)
{
	// �F�̎擾
	puyoAttr attr = m_Field.m_PuyoMass[x][y].m_Attr;
	m_Field.m_PuyoMass[x][y].m_Attr = puyoNONE;
	
	// �E
	if(x + 1 <= FIELD_WIDTH && m_Field.m_PuyoMass[x + 1][y].m_Attr == attr)
	{
		VanishPuyo(static_cast<uchar>(x + 1), y);
	}
	// ��
    if(y + 1 <= FIELD_HEIGHT && m_Field.m_PuyoMass[x][y + 1].m_Attr == attr)
	{
		VanishPuyo(x, static_cast<uchar>(y + 1));
	}
	// ��
    if(x - 1 >= 0 && m_Field.m_PuyoMass[x - 1][y].m_Attr == attr)
	{
		VanishPuyo(static_cast<uchar>(x - 1), y);
	}
	// ��
    if(y - 1 >= 0 && m_Field.m_PuyoMass[x][y - 1].m_Attr == attr)
	{
		VanishPuyo(x, static_cast<uchar>(y - 1));
	}
}

//----------------------------//
// �t�B�[���h�̃`�F�b�N���s�� //
//----------------------------//
void CGame::CheckField()
{
	// �ŏ��̈ʒu�����܂��Ă�����Q�[���I�[�o�[
	if ((m_Field.m_PuyoMass[FIRST_PUYO_X][FIRST_PUYO_Y].m_Attr != puyoNONE)
	||	(m_Field.m_PuyoMass[FIRST_PUYO_X][FIRST_PUYO_Y + 1].m_Attr != puyoNONE))
	{
		m_GameStatus = GameOver;
	}
}
//---------------------//
// �Q�[���I�[�o�[����  //
//---------------------//
void CGame::GameOverEffect()
{
	uint nCount = 0;

	// �S�񕪗��Ƃ�
	while (nCount < FIELD_HEIGHT)
	{
		// �������񂸂��炷
		for (int x = 0; x < FIELD_WIDTH; x ++)
		{
			for (int y = FIELD_HEIGHT - 2; y >= 0; y --)
			{
				m_Field.m_PuyoMass[x][y + 1].m_Attr = m_Field.m_PuyoMass[x][y].m_Attr;
				m_Field.m_PuyoMass[x][y].m_Attr = puyoNONE;
			}
		}
		Sleep(80);
		BackForeDrawScreen();
		nCount ++;
	}
}
//------------------//
// �G�t�F�N�g��Ԃ� //
//------------------//
BOOL CGame::IsEffect()
{
	return m_GameStatus == GameEffect;
}
//----------------------//
// �Q�[���I�[�o�[��Ԃ� //
//----------------------//
BOOL CGame::IsGameOver()
{
	return m_GameStatus == GameOver;
}
//----------------//
// �Q�[���ҋ@���� //
//----------------//
BOOL CGame::IsGameStandby()
{
	return m_GameStatus == GameStandby;
}
// Sub Function
int GetRandom(int min, int max)
{
	return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}
