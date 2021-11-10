//=============================================================================
//
// ポリゴンの描画の処理 [player.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"
#include "extraattack.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CSound;
class CLife;
class CChargeshot;
class CBomb;
class CEffect;

//=============================================================================
// マクロ定義
//=============================================================================
#define PLAYER_SPEED (10.0f)			  // 1Pの速さ
#define PLAYER_MOVABLE_RANGE_S (70.0f)	  // 1Pの移動できる範囲(短いほう)
#define PLAYER_MOVABLE_RANGE_L (815.0f)	  // 1Pの移動できる範囲(長いほう)
#define PLAYER2_SPEED (10.0f)			  // 2Pの速さ
#define PLAYER2_MOVABLE_RANGE_S (915.0f)  // 2Pの移動できる範囲(短いほう)
#define PLAYER2_MOVABLE_RANGE_L (1658.0f) // 2Pの移動できる範囲(長いほう)
#define PLAYER_BOMB_MAX (2)				  // 自機のボムの最大数
#define PLAYER_INVINCIBLE (180)			  // 無敵時間
#define PLAYER_RIGORE (80)			  // 無敵時間

//=============================================================================
// プレイヤークラス
//=============================================================================
class CPlayer :public CScene2D
{
public:
	typedef enum
	{
		PLAYERSTATE_NONE = 0,
		PLAYERSTATE_NOMAL,  // ノーマル状態
		PLAYERSTATE_DAMAGE, // ダメージを受けた状態
		PLAYERSTATE_LOSE,   // 負けた時の状態
		PLAYERSTATE_MAX,
	}PLAYERSTATE;

	typedef enum
	{
		PLAYER_1P,		 // 1P
		PLAYER_2P,		 // 2P
		PLAYER_MAX,
	}PLAYERNUM;

	CPlayer();  // コンストラク
	~CPlayer();	// デストラクタ

	static HRESULT Load(void); // ロード
	static void Unload(void);  // アンロード
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nLife, PLAYERNUM PlayerNum, OBJTYPE objType); // クリエイト

	HRESULT Init();    // 初期化処理
	void Uninit(void); // 終了処理
	void Update(void); // 更新処理
	void Draw(void);   // 描画処理

	void SetPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nLife, PLAYERNUM PlayerNum, OBJTYPE objType) { // プレイヤーの設定
		SetPosition(pos); m_pos = pos; m_move = move;
		m_size = m_size; SetSize(size);
		m_nLife = nLife; m_PlayerNum = PlayerNum;
		SetObjType(objType);
	}

	void PlayerDamage(int nDamage); // ダメージの処理
	void PlayerAddLife(int nLife);  // 回復の処理
	void GamePad(void); // ゲームパッドの処理
	void keyBoard(void); // キーボードの処理
	void Shot(void); // 弾を撃つ処理
	void ChargeShot(void); // チャージ弾を撃つ処理
	void ExtraAttack(void); // エクストラアタックの処理
	void BossAttack(void); // ボスアタックの処理
	void ExtraAttackInvocating(void); // エクストラアタックを発動する処理
	void HitEnemy(void); // 敵に当たった処理
	void HitOjama(void); // おじゃまに当たった処理
	void HitExtraAttack(CExtraattck::EXTRAATTCKPLAYERNUM ExtraAttackPlayerNum); // エクストラアタックに当たった処理
	void HitBossAttack(void); // ボスに当たった処理
	void DamageState(void); // ダメージの状態
	void Charging(void); // チャージ中の処理
	CChargeshot* GetChargeShot(void); // チャージショットのポインタを返す
	PLAYERSTATE GetPlayerState(void); // プレイヤーの状態を返す
	PLAYERNUM GetPlayerNum(void); // プレイヤーの番号を返す
private:
	CLife*					  m_pLife;					// 体力のポインタ
	CChargeshot*			  m_pChargeShot;			// チャージショットのポインタ
	CBomb*					  m_pBomb[PLAYER_BOMB_MAX]; // ボムのポインタ
	CEffect*				  m_pEffect;				// エフェクトのポインタ
	static LPDIRECT3DTEXTURE9 m_apTexture[PLAYER_MAX];				// テクスチャへのポインタ
	static int				  m_nDamage;				// 受けたダメージの値
	D3DXVECTOR3				  m_pos;					// 位置
	D3DXVECTOR3				  m_Getpos;					// 敵の位置
	D3DXVECTOR3				  m_move;					// 速さ
	D3DXVECTOR3				  m_size;					// 大きさ
	D3DXVECTOR3				  m_GetSize;				// 受け取った大きさ
	float					  m_fAngle;					// 角度
	int						  m_nLife;					// 自機の体力
	int						  m_nBulletShotCount;		// 弾を撃つ間隔
	int						  m_nInvincibleTime;		// 無敵時間
	int						  m_nRigorTime;				// 硬直時間
	int						  m_nExtraAttackCount;		// エクストラアタックのカウント
	int						  m_nPressTime;				// ボタンを押す時間
	bool					  m_bExtraAttack;			// エクストラアタックをするフラグ
	bool					  m_bEffectCreate;			// エフェクトを出すフラグ
	PLAYERSTATE				  m_PlayerState;			// プレイヤーの状態
	PLAYERNUM				  m_PlayerNum;				// プレイヤーの番号
};
#endif