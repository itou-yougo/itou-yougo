//=============================================================================
//
// ゲーム処理 [game.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "mode.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_ENEMY_NUM (50) // 敵の最大数
#define MAX_NUMBER_CREATE (2) // ナンバーの生成する数

//=============================================================================
// 前方宣言
//=============================================================================
class CPlayer;
class CNumber;

//=============================================================================
// ゲームクラス
//=============================================================================
class CGame :public CMode
{
public:
	CGame();
	~CGame();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayer *GetPlayer(void);
	static void SubtractEnemy(void) { 
		m_nEnemyNum--; m_nEnemyDeathTotal++; }

	static int GetEnemyDeathTotal(void) { return m_nEnemyDeathTotal; }
private:
	static CPlayer *m_pPlayer;		// プレイヤー
	static int m_nEnemyNum;			// 敵の数
	static int m_nEnemyDeathTotal;	// 敵倒した総数
	bool m_bEnemyCreate;			// 敵を生成するかどうか
	int m_nEnemyCreateTime;			// 敵を生成する時間
};
#endif