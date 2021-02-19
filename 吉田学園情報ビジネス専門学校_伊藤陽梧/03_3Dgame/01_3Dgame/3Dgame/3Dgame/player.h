//=============================================================================
//
// プレイヤーの処理 [player.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "character.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_PLAYER_PARTS (15) // プレイヤーのモデルのパーツの最大数
#define MOTION_PLAYER_TEXT ("data/MODEL/PLAYER/MOTION/motion.txt") // モーションのテキスト
#define LOAD_PLAYER_TEXT ("data/MODEL/PLAYER/MOTION/player.txt") // 各モデルパーツの初期値4
#define PLAYER_LIFE (100)

#define SWORD_COLISION_SIZE (D3DXVECTOR3(5.0f, 5.0f, 5.0f)) // 剣の当たり判定の大きさ

#define MOVE_SPEED (2.0f)	  // 歩く速度
#define SUBTRACT_FLAME (1.0f) // 減らすフレームの量

//=============================================================================
// 前方宣言
//=============================================================================
class CMotion;
class CModel;
class CReticle;
class CEnemy;

//=============================================================================
// プレイヤークラス
//=============================================================================
class CPlayer :public CCharacter
{
public:

	typedef enum
	{
		MOTION_IDLE = 0,
		MOTION_RUN,
		MOTION_SLASH,
		MOTION_N,
		MOTION_L
	}MOTION;

	typedef enum
	{
		PLAYERSTATE_NOMAL = 0,
		PLAYERSTATE_ATTACK,
		PLAYERSTATE_DAMAGE
	}PLAYERSTATE;

	CPlayer(int nPriority = CScene::OBJTYPE_PLAYER);//コンストラクタ
	~CPlayer();//デストラクタ

	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);//生成処理

	HRESULT Init(void);//初期化処理
	void Uninit(void);//終了処理
	void Update(void);//更新処理
	void Draw(void);//描画処理

	void SetPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);//各種設定

	void GamePad(void);//ゲームパッド処理
	void Attack(D3DXVECTOR3 Distance); // 攻撃の処理
	void Swordeffect(D3DXVECTOR3 Distance); // 剣のエフェクト

	void HitDamage(int nDamage);	//ダメージ処理
	static void DeathFlag(void);	//死亡フラグ


	bool GetDeath(void) { return m_bDeath; }//死亡フラグ

private:
	float m_fNotControl;	// 操作できない時間
	bool m_bAttackHit;		// 攻撃が当たっているか

	int m_nDamageMotionCnt;				// ダメージモーションのカウント
	bool m_bDamageMotion;				// ダメージモーションの判定

	int m_nDeathMotionCnt;				// 死亡モーションのカウント
	bool m_bDeathMotion;				// 死亡モーションの判定
	static bool m_bDeath;				// 死亡フラグ

	int m_nSwordEffectTime; // 剣のエフェクトの出す時間

	CEnemy *m_pEnemy;					// 敵クラスのポインタ
	PLAYERSTATE m_Playerstate;			// プレイヤーの状態

};

#endif