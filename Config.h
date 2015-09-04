#ifndef _CONFIG_H

typedef unsigned char uchar;	// 符号なしchar
typedef unsigned int  uint;		// 符号なしint
typedef const uchar   cuchar;	// const

#define VK_Z		 0x5A		// 仮想キー z
#define VK_X		 0x58		// 仮想キー x
#define MOVE_TIMERID 0x03dd		// 移動タイマーID
#define BUTTONID	 0x23ff		// ボタンID

#define TITLE_TEXT	 "プヨプヨもどき"
#define STRAT_TEXT	 "開始ボタンを押してください"
#define KEY_TEXT1	 "z : 左回転  x : 右回転"
#define KEY_TEXT2	 "←: →: ↓: プヨ移動"

const uint  EffectSleep	= 140;	// エフェクト中スリープ間隔
const uint  TIMER_INVAL	= 500;	// タイマー間隔
const uint  RANDOM_MAX	= 1000;	// ランダム最大
const uchar FIELD_WIDTH = 6;	// ゲームフィールドの最大横マス
const uchar FIELD_HEIGHT= 13;	// ゲームフィールドの最大縦マス
const uchar FIRST_PUYO_X= 2;	// 初期位置x
const uchar FIRST_PUYO_Y= 0;	// 初期位置y
const uchar MAX_BRUSH	= 5;	// ブラシの種類
const int PUYO_SIZE		= 42;	// プヨサイズ
const int FPS			= 35;	// フレームレート

// 色
const COLORREF NONE_BRUSH	= RGB(0, 0, 0);		// なし
const COLORREF BLUE_BRUSH	= RGB(0, 0, 255);	// 青
const COLORREF RED_BRUSH	= RGB(255, 0, 80);	// 赤
const COLORREF GREEN_BRUSH	= RGB(0, 255, 80);	// 緑
const COLORREF YELLOW_BRUSH = RGB(255, 212, 0);	// 黄色
const COLORREF GRAY__BRUSH	= RGB(128, 128, 128);// 灰色
const COLORREF BACK_BRUSH	= RGB(75, 75, 75);	// 背景色
const COLORREF INFO_BRUSH	= RGB(195, 145, 67);// 情報色
const COLORREF TITLE_BRUSH  = RGB(255, 122, 23);// タイトル色

// プヨ属性
typedef enum
{
	puyoNONE = 0,		// なし
	puyoBLUE,			// 青
	puyoRED,			// 赤
	puyoGREEN,			// 緑
	puyoYELLOW			// 黄色
}puyoAttr;

// 操作用キー
typedef enum 
{
	puyoDisregard = 0,	// 無視
	puyoDOWN,			// 下 
	puyoLEFT,			// 左
	puyoRIGHT,			// 右
	puyoLEFT_ROLL,		// 左回転
	puyoRIGHT_ROLL		// 右回転
}puyoCtrl;

// プヨ状態
typedef enum
{
	puyoLowSide = 0,	// 下向き
	puyoUpperSide,		// 上向き(通常)
	puyoLeftSide,		// 左向き
	puyoRightSide		// 右向き
}puyoState;

// プヨますめ
struct puyoPos
{
	uchar x;			// x
	uchar y;			// y
};

// ゲーム状態
typedef enum
{
	GameStandby,		// ゲーム待機中
	GameIdle,			// アイドル
	GameEffect,			// エフェクト
	GameOver,			// ゲーム終了
}GameStatus;


#endif // _CONFIG_H

