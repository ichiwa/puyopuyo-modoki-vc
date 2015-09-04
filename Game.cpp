// Game.cpp: CGame クラスのインプリメンテーション
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
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CGame::CGame()
:m_GameStatus(GameStandby)
,m_ChainCount(0)
{
	m_Rect.SetRectEmpty();

	m_pOutDC = new CDC;	
	m_pBitmap = new CBitmap;

	// 黒、青、赤、緑、黄色ブラシの作成
	m_Brush[puyoNONE]	= new CBrush(NONE_BRUSH);
	m_Brush[puyoBLUE]	= new CBrush(BLUE_BRUSH);
	m_Brush[puyoRED]	= new CBrush(RED_BRUSH);
	m_Brush[puyoGREEN]	= new CBrush(GREEN_BRUSH);
	m_Brush[puyoYELLOW]	= new CBrush(YELLOW_BRUSH);
	
	// 乱数の種まき
	srand(time(NULL));

	// 乱数テーブルの作成
	for (int i = 0; i < RANDOM_MAX; i ++)
	{
		m_RanDomTable[i] = static_cast<uchar>(GetRandom(1, 4));
	}
}

CGame::~CGame()
{
	for (int i = 0; i < MAX_BRUSH; i++)
	{
		delete m_Brush[i];	// ブラシ破棄
	}
	delete m_pOutDC;		// バックDC破棄
	delete m_pBitmap;		// バックBMP破棄
}
//--------------------//
// ゲームクラスの構築 //
//--------------------//
void CGame::Create(CDC* pDC, const CRect* rect)
{
	// バックバッファの作成
	m_Rect = rect;
	m_pOutDC->CreateCompatibleDC(pDC);
	m_pBitmap->CreateCompatibleBitmap(pDC, m_Rect.Width(), m_Rect.Height());
	m_pOutDC->SelectObject(m_pBitmap);
	m_pInDC = CDC::FromHandle(pDC->GetSafeHdc());		// 複製

	// フォント作成
	m_Font.CreateFont(26, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, SHIFTJIS_CHARSET, 
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_ROMAN, NULL);	

	// フォント設定
	m_pOutDC->SelectObject(&m_Font);

	// テキストカラー設定
	m_pOutDC->SetTextColor(INFO_BRUSH);

	// 背景透過
	m_pOutDC->SetBkMode(TRANSPARENT);
	
	// フィールドクラスの構築
	m_Field.Create();

	// プヨクラスの構築
	m_PuyoPuyo.Create(m_RanDomTable);

	// ゲームスタート
	m_GameStatus = GameIdle;
}
//---------//
// 両描画  //
//---------//
void CGame::BackForeDrawScreen()
{
	BackDrawScreen();
	ForeDrawScreen();
}
//-----------//
// 表描画	 //
//-----------//
void CGame::ForeDrawScreen()
{
	// ロック
	m_Section.Lock();

	// フォアバッファにバックバッファに描画 ※一段上に描画させる(-PUYO_SIZE)
	m_pInDC->BitBlt(0, -PUYO_SIZE, m_Rect.Width(), m_Rect.Height(), m_pOutDC, 0, 0, SRCCOPY);

	// アンロック
	m_Section.Unlock();
}
//-----------//
// 裏描画	 //
//-----------//
void CGame::BackDrawScreen()
{
	// ロック
	m_Section.Lock();

	// 画面クリア
	m_pOutDC->FillSolidRect(0, 0, m_Rect.Width(), m_Rect.Height(), NONE_BRUSH);
	
	// フィールドライン描画
	DrawFieldLine();

	// フィールド描画
	DrawFieldMass();

	// アイドル時
	if (m_GameStatus == GameIdle)
	{ 
		// 操作中プヨプヨ描画
		DrawPuyoPuyo();
	}

	// 連鎖文字列描画
	DrawInfoString();
	
	// アンロック
	m_Section.Unlock();
}
//------------------//
// ブラシの取得		//
//------------------//
CBrush* CGame::GetBrushColor(puyoAttr attr)
{
	// 属性別
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
//  操作中プヨプヨ描画 //
//---------------------//
void CGame::DrawPuyoPuyo()
{
	// プヨプヨ数分
	for (uint i = 0; i < 2; i ++)
	{
		CBrush* brs;		// プヨ色
		CRect rect;			// 円
		uchar x, y;			// 位置
		
		// 位置取得
		x = m_PuyoPuyo.GetPosition_x(i);
		y = m_PuyoPuyo.GetPosition_y(i);
		
		// 色取得
		brs = GetBrushColor(m_PuyoPuyo.GetAttr(i));
		
		m_pOutDC->SelectObject(brs);
		
		rect.SetRect(m_Field.m_PuyoMass[x][y].m_Posi.x, m_Field.m_PuyoMass[x][y].m_Posi.y,
			m_Field.m_PuyoMass[x][y].m_Posi.x + PUYO_SIZE, m_Field.m_PuyoMass[x][y].m_Posi.y + PUYO_SIZE);
		rect.InflateRect(1, 1, 1, 1);
		m_pOutDC->Ellipse(&rect);
	}
}
//---------------//
// 全マス目描画  //
//---------------//
void CGame::DrawFieldMass()
{
	// マス情報からすべてを描画する
	for (uint i = 0; i < FIELD_WIDTH; i ++)
	{
		// 一番上は無視
		for (uint j = 1; j < FIELD_HEIGHT; j ++)	
		{
			CBrush* brs;		// 描画ブラシ

			// マス色なしは描画しない
			if (m_Field.m_PuyoMass[i][j].m_Attr == puyoNONE)
			{
				// 次マスへ
				continue;
			}
			// マス色ありはブラシを取得する
			brs = GetBrushColor(m_Field.m_PuyoMass[i][j].m_Attr); // 色取得

			m_pOutDC->SelectObject(brs);

			CRect rect;	// 円
			rect.SetRect(m_Field.m_PuyoMass[i][j].m_Posi.x, m_Field.m_PuyoMass[i][j].m_Posi.y,
				m_Field.m_PuyoMass[i][j].m_Posi.x + PUYO_SIZE, m_Field.m_PuyoMass[i][j].m_Posi.y + PUYO_SIZE);
			rect.InflateRect(1, 1, 1, 1);
			m_pOutDC->Ellipse(&rect);
		}
	}	
}
//-----------------//
// 連鎖文字列描画  //
//-----------------//
void CGame::DrawInfoString()
{
	// 連鎖なし
	if (m_ChainCount == 0)
	{
		return;
	}

	TRACE("count = %d\n", m_ChainCount);
	CString str;		// 文字バフ
	
	// 5連鎖以上
	if (m_ChainCount > 4)
	{
		str.Format("%d連鎖！！！", m_ChainCount);
	}
	// 3連鎖以上
	else if (m_ChainCount > 2)
	{
		str.Format("%d連鎖！！", m_ChainCount);
	}
	// その他
	else
	{	
		str.Format("%d連鎖！", m_ChainCount);
	}
	// 真ん中辺りに描画
	m_pOutDC->TextOut(m_Field.m_PuyoMass[2][5].m_Posi.x, m_Field.m_PuyoMass[2][5].m_Posi.y, str);
}
//----------------------//
// フィールドライン描画 //
//----------------------//
void CGame::DrawFieldLine()
{
	CPen pen;			// ライン用ペン
	pen.CreatePen(PS_DASH, 1, GRAY__BRUSH);
	
	m_pOutDC->SelectObject(pen);
	
	// 横線
	for (uint i = 0; i <= (uint)m_Rect.Height(); i += PUYO_SIZE)
	{
		m_pOutDC->MoveTo(0, i);
		m_pOutDC->LineTo(m_Rect.Width(), i);
	}
	// 縦線
	for (uint j = 0; j <= (uint)m_Rect.Width(); j += PUYO_SIZE)
	{
		m_pOutDC->MoveTo(j, 0);
		m_pOutDC->LineTo(j, m_Rect.Height());
	}
	// 元に戻す
	m_pOutDC->SelectStockObject(BLACK_PEN);
}
//------------------//
// キーコントロール //
//------------------//
BOOL CGame::KeyControl(const puyoCtrl key)
{
	CPuyoPuyo Temp;		// 仮プヨプヨ
	Temp = m_PuyoPuyo;	// コピー

	// 移動したものを作る
	Temp.CtrlPuyo(key);

	// フィールド移動不可能
	if (!m_Field.CanMovedPuyo(Temp, key))
	{
		// 移動不可能でキーが下以外
		if (key != puyoDOWN)
		{
			// 移動不能
			return FALSE;
		}

		// エフェクトにする
		m_GameStatus = GameEffect;

		// フィールドにメンバのプヨプヨを保存する
		m_Field.SetFieldPuyo(m_PuyoPuyo);
		
		// 連鎖処理
		MainChain();
	
		// フィールドをチェックする
		CheckField();

		// ゲームオーバーか?
		if (m_GameStatus == GameOver)
		{
			// ゲームオーバー処理
			GameOverEffect();
			
			// 長めに待たせる
			Sleep(EffectSleep*2);
		}
		// 新しいプヨの作成
		m_PuyoPuyo.Create(m_RanDomTable);
		
		MSG dummy;		// ダミー

		// キーメッセージをクリアする ※メッセージがあると新しいプヨが動いてしまう為
		while(::PeekMessage(&dummy, m_hwnd, WM_KEYFIRST, WM_KEYLAST, PM_REMOVE));
		
		// アイドルに戻す
		m_GameStatus = GameIdle;
	}
	// フィールド移動可能
	else
	{
		// 本物に仮をコピーする
		m_PuyoPuyo = Temp;
	}

	// 再描画
	return TRUE;
}
//----------------------//
// メインのプヨプヨ処理 //
//----------------------//
void CGame::MainChain()
{
	BOOL ChainFlg = FALSE;		// 連鎖フラグ
	
	while (1)
	{
		// プヨ落下処理
		DropPuyo();

		// フィールドの全検索
		for (uchar i = 0; i <= FIELD_WIDTH-1; i ++)
		{
			for (uchar j = 0; j <= FIELD_HEIGHT; j ++)
			{
				uint Count = 0;	// 連結個数
				
				// 色なしは数えない
				if (m_Field.m_PuyoMass[i][j].m_Attr != puyoNONE)
				{
					CountPuyo(i, j, Count);

					// 4個以上繋がっているプヨあり
					if (Count > 3)
					{
						ChainFlg = TRUE;	// 連鎖フラグTRUE

						// プヨ消す
						VanishPuyo(i, j);
					}
				}
			}
		}// for フィールドの全検索
		
		// 待機
		Sleep(EffectSleep);
		
		// 連鎖なし
		if (!ChainFlg)
		{
			break;
		}
		
		// 連鎖回数
		m_ChainCount++;

		// 描画
		BackForeDrawScreen();

		// 待機
		Sleep(EffectSleep);

		// 連鎖フラグ戻す
		ChainFlg = FALSE;

		// 再検索
	}

	// 連鎖終了後初期化
	m_ChainCount = 0;
}
//---------------//
// プヨ落下処理	 //
//---------------//
void CGame::DropPuyo()
{
	// 判別フラグ
	BOOL bDownFlg[FIELD_WIDTH] ={FALSE, FALSE, FALSE, FALSE, FALSE, FALSE};

	while (1)
	{
		// 1行ごとに処理を行う
		for (uchar x = 0; x <= FIELD_WIDTH-1; x ++)
		{
			bDownFlg[x] = m_Field.DropField(x);
		}
		// フラグがある場合
		if (GetDownFlg(bDownFlg))
		{
			Sleep(EffectSleep);
			
			BackDrawScreen();
		}
		// フラグなし
		else 
		{
			Sleep(EffectSleep);
			
			BackDrawScreen();

			break;
		}
	}
}
//--------------------//
// ダウンフラグの判別 //
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
// プヨ個数数える  //
//-----------------//
void CGame::CountPuyo(uchar x, uchar y, uint& count)
{
	// 色の取得
	puyoAttr attr = m_Field.m_PuyoMass[x][y].m_Attr;
	m_Field.m_PuyoMass[x][y].m_Attr = puyoNONE;

	count++;

	// 右
    if(x + 1 <= FIELD_WIDTH && m_Field.m_PuyoMass[x + 1][y].m_Attr == attr)
	{
		CountPuyo(static_cast<uchar>(x + 1), y, count);
	}
	// 下
    if(y + 1 <= FIELD_HEIGHT && m_Field.m_PuyoMass[x][y + 1].m_Attr == attr)
	{
		CountPuyo(x, static_cast<uchar>(y + 1), count);
	}
	// 左
    if(x - 1 >= 0 && m_Field.m_PuyoMass[x - 1][y].m_Attr == attr)
	{
		CountPuyo(static_cast<uchar>(x - 1), y, count);
	}
	// 上
    if(y - 1 >= 0 && m_Field.m_PuyoMass[x][y - 1].m_Attr == attr)
	{
		CountPuyo(x, static_cast<uchar>(y - 1), count);
	}
	
	// 数えたところは元に戻す
	m_Field.m_PuyoMass[x][y].m_Attr = attr;
}
//------------------------------------//
// 渡されたプヨと隣接するところを消す //
//------------------------------------//
void CGame::VanishPuyo(uchar x, uchar y)
{
	// 色の取得
	puyoAttr attr = m_Field.m_PuyoMass[x][y].m_Attr;
	m_Field.m_PuyoMass[x][y].m_Attr = puyoNONE;
	
	// 右
	if(x + 1 <= FIELD_WIDTH && m_Field.m_PuyoMass[x + 1][y].m_Attr == attr)
	{
		VanishPuyo(static_cast<uchar>(x + 1), y);
	}
	// 下
    if(y + 1 <= FIELD_HEIGHT && m_Field.m_PuyoMass[x][y + 1].m_Attr == attr)
	{
		VanishPuyo(x, static_cast<uchar>(y + 1));
	}
	// 左
    if(x - 1 >= 0 && m_Field.m_PuyoMass[x - 1][y].m_Attr == attr)
	{
		VanishPuyo(static_cast<uchar>(x - 1), y);
	}
	// 上
    if(y - 1 >= 0 && m_Field.m_PuyoMass[x][y - 1].m_Attr == attr)
	{
		VanishPuyo(x, static_cast<uchar>(y - 1));
	}
}

//----------------------------//
// フィールドのチェックを行う //
//----------------------------//
void CGame::CheckField()
{
	// 最初の位置が埋まっていたらゲームオーバー
	if ((m_Field.m_PuyoMass[FIRST_PUYO_X][FIRST_PUYO_Y].m_Attr != puyoNONE)
	||	(m_Field.m_PuyoMass[FIRST_PUYO_X][FIRST_PUYO_Y + 1].m_Attr != puyoNONE))
	{
		m_GameStatus = GameOver;
	}
}
//---------------------//
// ゲームオーバー処理  //
//---------------------//
void CGame::GameOverEffect()
{
	uint nCount = 0;

	// 全列分落とす
	while (nCount < FIELD_HEIGHT)
	{
		// 下から一列ずつずらす
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
// エフェクト状態か //
//------------------//
BOOL CGame::IsEffect()
{
	return m_GameStatus == GameEffect;
}
//----------------------//
// ゲームオーバー状態か //
//----------------------//
BOOL CGame::IsGameOver()
{
	return m_GameStatus == GameOver;
}
//----------------//
// ゲーム待機中か //
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
