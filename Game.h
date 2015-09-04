// Game.h: CGame クラスのインターフェイス
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
	CRect			m_Rect;							// 描画範囲
	CField			m_Field;						// フィールドクラス
   CCriticalSection m_Section;						// 同期制御
#ifdef _DEBUG	// デバッグ時
public:
#else			// リリース時
private:
#endif
	CPuyoPuyo		m_PuyoPuyo;						// 操作中プヨプヨ
	CDC*			m_pInDC;						// 描画フォアバッファ
	uchar			m_RanDomTable[RANDOM_MAX];		// 乱数テーブル
	GameStatus		m_GameStatus;					// ゲーム状態
	CBrush*			m_Brush[MAX_BRUSH];				// 描画用ブラシ
	CFont			m_Font;							// 描画用フォント
	uint			m_ChainCount;					// 連鎖回数
private:
	CBrush*			GetBrushColor(puyoAttr attr);	// ブラシの取得
	BOOL			GetDownFlg(const BOOL* downFlg);// ダウンフラグの判別
	void			CheckField();					// フィールドのチェック
	void			GameOverEffect();				// ゲームオーバー処理
	void			CountPuyo(uchar x, uchar y, uint& count);// プヨ個数数える	
	void			VanishPuyo(uchar x, uchar y);	// プヨ消す
	void			DropPuyo();						// プヨ落下処理
	void			MainChain();					// メインのプヨプヨ処理
	void			DrawPuyoPuyo();					// 操作中プヨプヨ描画
	void			DrawFieldMass();				// 全マス目描画
	void			DrawInfoString();				// 情報文字列描画
	void			DrawFieldLine();				// フィールド線描画
public:
	CGame();
	virtual ~CGame();
	void			Create(CDC* pDC, const CRect* rect);// 初期化
	void			BackDrawScreen();				// バックバッファ描画
	void			ForeDrawScreen();				// フォアバッファ描画
	void			BackForeDrawScreen();			// 両バッファの描画
	BOOL			KeyControl(const puyoCtrl key);	// キー制御
	BOOL			IsGameOver();					// ゲームオーバーか
	BOOL			IsEffect();						// エフェクトか
	BOOL			IsGameStandby();				// ゲーム待機中か
public:
	HWND			m_hwnd;							// ビューハンドル
	CBitmap*		m_pBitmap;						// バックバッファBMP
	CDC*			m_pOutDC;						// 描画バックバッファ
};

// SubFunction
int GetRandom(int min, int max);

#endif // !defined(AFX_GAME_H__4F56E4D9_D3CD_4D3A_B12E_7A0E45570D90__INCLUDED_)
