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

	CBossattck();
	~CBossattck();

	static HRESULT Load(void);
	static void Unload(void);
	static CBossattck *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, PLAYER Player, BOSSATTACK BossAttack, OBJTYPE objType);

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void BossAttackDamage(int nDamage);

	void SetExtraAttack(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, PLAYER Player, BOSSATTACK BossAttack, OBJTYPE objType) {
		SetPosition(pos); m_pos = pos; m_move = move;
		m_nLife = nLife; m_Player = Player;
		m_BossAttack = BossAttack; SetObjType(objType);
	}

private:
	CBullet::BULLETTYPE m_BulletType;		   // 弾のタイプ
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BOSS_TEXTURE];  // テクスチャへのポインタ
	D3DXVECTOR3	m_pos;						   // 座標
	D3DXVECTOR3	m_move;						   // 速さ
	D3DXVECTOR3 m_Getpos;					   // 受け取った座標
	float		m_fSizeX;					   // 横の大きさ
	float		m_fSizeY;					   // 縦の大きさ
	float		m_fGetSizeX;				   // 受け取った横の大きさ
	float		m_fGetSizeY;				   // 受け取った縦の大きさ
	float		m_fAngle;					   // 角度
	int			m_nCount;					   // カウント
	int			m_nCountBullet;				   // 弾を撃つカウント
	int			m_nCountStop;				   // 止まるときのカウント
	int			m_nLife;					   // 体力
	bool		m_bStop;					   // 止まったかの判別
	PLAYER		m_Player;					   // プレイヤーの種類
	BOSSATTACK  m_BossAttack;				   // ボスアタックの種類
};
#endif