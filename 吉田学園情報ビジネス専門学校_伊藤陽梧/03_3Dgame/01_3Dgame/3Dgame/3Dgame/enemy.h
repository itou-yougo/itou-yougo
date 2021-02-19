//=============================================================================
//
// 敵の処理 [enemy.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "character.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MOTION_ENEMY_TEXT ("data/MODEL/ENEMY/MOTION/motion.txt")	// モーションのテキスト
#define LOAD_ENEMY_TEXT ("data/MODEL/ENEMY/MOTION/enemy.txt")		// 各モデルパーツの初期値

#define ENEMY_SIZE (D3DXVECTOR3(20.0f,50.0f,20.0f)) // 当たり判定サイズ
#define ENEMY_LIFE (10)								// 体力
#define ENEMY_MOVE_SPEED (1.0f)						// 移動量
#define ENEMY_DISTANCE_PLAYER (30.0f)				// プレイヤーとの距離
#define ENEMY_CREATE_NUM (10)						// 敵を生成する数
#define ENEMY_CREATE_ANGLE (360)					// 敵を生成する角度
#define ENEMY_CREATE_DISTANCE (D3DXVECTOR3(1000.0f, 0.0f, 1000.0f))	// 敵を生成する距離
#define ENEMY_CREATE_TIME (20)						// 敵を生成する時間

//=============================================================================
// 前方宣言
//=============================================================================
class CMotion;
class CModel;

//=============================================================================
// エネミークラス
//=============================================================================
class CEnemy :public CCharacter
{
public:
	typedef enum
	{
		ENEMYSTATE_NOMAL = 0,
	}ENEMYSTATE;

	CEnemy(int nPriority = CScene::OBJTYPE_ENEMY);//コンストラクタ
	~CEnemy();//デストラクタ

	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, ENEMYSTATE EnemyState);//生成処理

	HRESULT Init(void);//初期化処理
	void Uninit(void);//終了処理
	void Update(void);//更新処理
	void Draw(void);//描画処理
	void HitDamage(int nDamage);
	void EnemyCollision(void);
	static void SetChase(bool bChase);
	void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, ENEMYSTATE EnemyState);

private:
	bool m_bChase;						// チェイス判定
	bool m_bHit;						// ダメージを受けている判定
	bool m_bAttack;						// 攻撃判定
	int m_nCntAttack;					// 攻撃速度
	int m_nCntFrame;					// フレームカウント
	ENEMYSTATE m_EnemyState;			// 敵の状態
};

#endif