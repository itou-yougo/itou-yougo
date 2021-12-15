////////////////////////////////////////////////////
//
//    キルカウントヘッダー[kill_count.h]
//    Author : 吉田 悠人
//
////////////////////////////////////////////////////

//二重インクルード防止
#ifndef _KILL_COUNT_H_
#define _KILL_COUNT_H_

//=============================
// インクルード
//=============================
#include "main.h"
#include "scene.h"
#include "game.h"

//=============================
//マクロ定義
//=============================
#define MAX_KILL_NUMBER (3)

//=============================
// 前方宣言
//=============================
class CNumber;

//=============================
// クラス定義
//=============================

// マネージャークラス
class CKillCount : public CScene
{
public:
	//============
	// 状態列挙
	//============

	//============
	// メンバ関数
	//============
	CKillCount();
	~CKillCount();
	static CKillCount *Create(int nPlayer); //クラス生成
	HRESULT Init(void);		// 初期化
	void	Uninit(void);	// 終了
	void	Update(void);	// 更新
	void	Draw(void);		// 描画
	void	AddKill(void);	// キル数加算
	void	SetKill(int nKill) { m_nKillCount = nKill; }	// キル数セッター
	int 	GetKill(void) { return m_nKillCount; }			// キル数ゲッター
	void	SetPlayer(int nPlayer) { m_nPlayer = nPlayer; }	// プレイヤー番号セッター
	int		GetPlayer(void) { return m_nPlayer; }			// プレイヤー番号ゲッター

	static void	AddTotalKill(void);		// キル数加算
	static int GetTotalKill(int nPlayer) { return m_nTotalKill[nPlayer]; }	//トータルキル数のゲッター
private:
	//============
	// メンバ変数
	//============
	CNumber * pNumber[MAX_PLAYER][MAX_KILL_NUMBER];
	static int	m_nTotalKill[MAX_PLAYER];			// プレイヤー全体のキル数
	int m_nKillCount;								// キル数
	int m_nPlayer;									// プレイヤー番号
};


#endif