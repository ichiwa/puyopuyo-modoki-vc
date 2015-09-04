#ifndef _CONFIG_H

typedef unsigned char uchar;	// �����Ȃ�char
typedef unsigned int  uint;		// �����Ȃ�int
typedef const uchar   cuchar;	// const

#define VK_Z		 0x5A		// ���z�L�[ z
#define VK_X		 0x58		// ���z�L�[ x
#define MOVE_TIMERID 0x03dd		// �ړ��^�C�}�[ID
#define BUTTONID	 0x23ff		// �{�^��ID

#define TITLE_TEXT	 "�v���v�����ǂ�"
#define STRAT_TEXT	 "�J�n�{�^���������Ă�������"
#define KEY_TEXT1	 "z : ����]  x : �E��]"
#define KEY_TEXT2	 "��: ��: ��: �v���ړ�"

const uint  EffectSleep	= 140;	// �G�t�F�N�g���X���[�v�Ԋu
const uint  TIMER_INVAL	= 500;	// �^�C�}�[�Ԋu
const uint  RANDOM_MAX	= 1000;	// �����_���ő�
const uchar FIELD_WIDTH = 6;	// �Q�[���t�B�[���h�̍ő剡�}�X
const uchar FIELD_HEIGHT= 13;	// �Q�[���t�B�[���h�̍ő�c�}�X
const uchar FIRST_PUYO_X= 2;	// �����ʒux
const uchar FIRST_PUYO_Y= 0;	// �����ʒuy
const uchar MAX_BRUSH	= 5;	// �u���V�̎��
const int PUYO_SIZE		= 42;	// �v���T�C�Y
const int FPS			= 35;	// �t���[�����[�g

// �F
const COLORREF NONE_BRUSH	= RGB(0, 0, 0);		// �Ȃ�
const COLORREF BLUE_BRUSH	= RGB(0, 0, 255);	// ��
const COLORREF RED_BRUSH	= RGB(255, 0, 80);	// ��
const COLORREF GREEN_BRUSH	= RGB(0, 255, 80);	// ��
const COLORREF YELLOW_BRUSH = RGB(255, 212, 0);	// ���F
const COLORREF GRAY__BRUSH	= RGB(128, 128, 128);// �D�F
const COLORREF BACK_BRUSH	= RGB(75, 75, 75);	// �w�i�F
const COLORREF INFO_BRUSH	= RGB(195, 145, 67);// ���F
const COLORREF TITLE_BRUSH  = RGB(255, 122, 23);// �^�C�g���F

// �v������
typedef enum
{
	puyoNONE = 0,		// �Ȃ�
	puyoBLUE,			// ��
	puyoRED,			// ��
	puyoGREEN,			// ��
	puyoYELLOW			// ���F
}puyoAttr;

// ����p�L�[
typedef enum 
{
	puyoDisregard = 0,	// ����
	puyoDOWN,			// �� 
	puyoLEFT,			// ��
	puyoRIGHT,			// �E
	puyoLEFT_ROLL,		// ����]
	puyoRIGHT_ROLL		// �E��]
}puyoCtrl;

// �v�����
typedef enum
{
	puyoLowSide = 0,	// ������
	puyoUpperSide,		// �����(�ʏ�)
	puyoLeftSide,		// ������
	puyoRightSide		// �E����
}puyoState;

// �v���܂���
struct puyoPos
{
	uchar x;			// x
	uchar y;			// y
};

// �Q�[�����
typedef enum
{
	GameStandby,		// �Q�[���ҋ@��
	GameIdle,			// �A�C�h��
	GameEffect,			// �G�t�F�N�g
	GameOver,			// �Q�[���I��
}GameStatus;


#endif // _CONFIG_H

