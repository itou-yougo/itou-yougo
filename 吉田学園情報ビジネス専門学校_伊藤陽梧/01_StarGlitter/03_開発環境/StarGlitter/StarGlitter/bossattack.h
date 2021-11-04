//=============================================================================
//
// ボスアタックの処理 [bossattack.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _BOSSATTACK_H_
#define _BOSSATTACK_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"
#include "bullet.h"
#include "player.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define BOSS_SIZE_X (300.0f)			// ボスの横の長さ
#define BOSS_SIZE_Y (300.0f)			// ボスの縦の長さ
#define MAX_BOSS_TEXTURE (2)			// ボスのテクスチャの最大数

//=============================================================================
// ボスアタッククラス
//=============================================================================
class CBossattck :public CScene2D
{
public:
	typedef enum
	{
		BOSSATTCK_PLAYER_NONE = 0,
		BOSSATTCK_PLAYER1, // プレイヤー1のボスアタック
		BOSSATTCK_PLAYER2, // プレイヤー2のボスアタック
		BOSSATTCK_PLAYER_MAX,
	}PLAYER;

	typedef enum
	{
		BOSSATTACK_BEAM,   // ビームを撃つボスアタック
		BOSSATTACK_BULLET, // たまを撃つボスアタック
		BOSSATTACK_MAX,
	}BOSSATTACK;

	CBossattck();   // コンストラク
	~CBossattck(); 	// デストラクタ
	
	static HRESULT Load(void); // ロード
	static void Unload(void);  // アンロード
	static CBossattck *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife,
		PLAYER Player, BOSSATTACK BossAttack, OBJTYPE objType); // クリエイト

	HRESULT Init();    // 初期化処理
	void Uninit(void); // 終了処理
	void Update(void); // 更新処理
	void Draw(void);   // 描画処理

	void BossAttackDamage(int nDamage); // ダメージを受けた時の処理

	void SetBossAttack(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife,
		PLAYER Player, BOSSATTACK BossAttack, OBJTYPE objType) { // ボスアタックの設定
		SetPosition(pos); m_pos = pos; m_move = move;
		m_nLife = nLife; m_Player = Player;
		m_BossAttack = BossAttack; SetObjType(objType);
	}

	void BossBeam(void); // ビームを撃つボスの処理
	void BossBullet(void); // 弾を撃つボスの処理
	void BossAttackBeam(void); // ビームを撃つ処理
	void BossAttackBullet(CPlayer::PLAYERNUM PlayerNum); // 弾を撃つ処理

	void Hit(void); // 当たる処理
	void HitDamage(void); // 当たるときのダメージの処理
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BOSS_TEXTURE];  // テクスチャへのポインタ
	D3DXVECTOR3	m_pos;						   // 座標
	D3DXVECTOR3	m_move;						   // 速さ
	D3DXVECTOR3 m_size;						   // 大きさ
	float		m_fAngle;					   // 角度
	int			m_nCount;					   // カウント
	int			m_nInvincibleTime;			   // 無敵時間
	int			m_nCountBullet;				   // 弾を撃つカウント
	int			m_nCountStop;				   // 止まるときのカウント
	int			m_nLife;					   // 体力
	bool		m_bStop;					   // 止まったかの判別
	PLAYER		m_Player;					   // プレイヤーの種類
	BOSSATTACK  m_BossAttack;				   // ボスアタックの種類
};
#endif