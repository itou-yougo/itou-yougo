//=============================================================================
//
// ゲームの処理 [game.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_SELECT (2) // 選択の最大値

//=============================================================================
// 前方宣言
//=============================================================================
class CScene2D;
class CGauge;
class CSelect;

//=============================================================================
// ゲームクラス
//=============================================================================
class CGame
{
public:
	typedef enum
	{
		GAMESTATE_NONE = 0,
		GAMESTATE_NORMAL,   // ノーマルの状態
		GAMESTATE_START,	// ゲームが始まった状態
		GAMESTATE_END,		// ゲームが終わった状態
		GAMESTATE_MAX,
	}GAMESTATE;

	CGame();
	~CGame();

	static CGame *Create();

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static void SetGameState(GAMESTATE gamestate);
	static GAMESTATE GetGameState(void);
private:
	static GAMESTATE	  m_gamestate;			  // ゲームの状態
	static CSelect		  *m_pSelect[MAX_SELECT]; // セレクトクラスのポインタ
	int					  m_nCountCreate;		  // 生成するカウント
	int					  m_nSelectCount;		  // 選んだ時のカウント
	int					  m_nCountText;			  // テキストのカウント
	bool				  m_bPause;				  // ポーズ状態かどうか
	bool				  m_bGameStart;			  // ゲームが始まったかどうか
};
#endif