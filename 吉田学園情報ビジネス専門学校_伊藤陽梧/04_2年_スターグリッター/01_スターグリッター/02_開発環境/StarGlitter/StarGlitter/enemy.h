//=============================================================================
//
// ポリゴンの描画の処理 [enemy.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_


//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"
#include "bullet.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CSound;
class CScore;
class CGauge;

//=============================================================================
// エネミークラス
//=============================================================================
class CEnemy :public CScene2D
{
public:
	typedef enum
	{
		DAMAGE_TYPE_NONE = 0,
		DAMAGE_TYPE_BULLET,    // 弾のダメージ
		DAMAGE_TYPE_EXPLOSION, // 爆発のダメージ
		DAMAGE_TYPE_MAX,
	}DAMAGETYPE;

	CEnemy();
	~CEnemy();

	static HRESULT Load(void);
	static void Unload(void);
	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fSizeX, float fSizeY, int nLife, OBJTYPE objType);

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fSizeX, float fSizeY, int nLife, OBJTYPE objType) {
		SetPosition(pos); SetSize(fSizeX, fSizeY); m_pos = pos;
		m_move = move; m_fSizeX = fSizeX; m_fSizeY = fSizeY;
		m_nLife = nLife; SetObjType(objType);
	}

	void EnemyDamage(int nDamage, DAMAGETYPE DamageType, CBullet::BULLETTYPE BulletType);
private:
	CGauge* m_pGauge; // ゲージのポインタ
	static LPDIRECT3DTEXTURE9 m_pTexture; // テクスチャへのポインタ
	D3DXVECTOR3			m_pos;		   // 位置
	D3DXVECTOR3			m_move;		   // 速度
	float				m_fSizeX;	   // 横の大きさ
	float				m_fSizeY;	   // 縦の大きさ
	int					m_nLife;	   // 敵の体力
	int					m_nOjamaCount; // おじゃまのカウント
	DAMAGETYPE			m_DamageType;  // ダメージのタイプ
	CBullet::BULLETTYPE m_BulletType;  // 誰の弾なのか
};
#endif