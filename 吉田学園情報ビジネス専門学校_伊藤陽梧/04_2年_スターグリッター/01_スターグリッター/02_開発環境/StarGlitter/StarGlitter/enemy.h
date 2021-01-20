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
#include "enemyexplosion.h"

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

	CEnemy();  // コンストラク
	~CEnemy(); // デストラクタ

	static HRESULT Load(void); // ロード
	static void Unload(void);  // アンロード
	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,
		D3DXVECTOR3 size, int nLife, OBJTYPE objType); // クリエイト

	HRESULT Init();    // 初期化処理
	void Uninit(void); // 終了処理
	void Update(void); // 更新処理
	void Draw(void);   // 描画処理

	void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, 
		D3DXVECTOR3 size, int nLife, OBJTYPE objType) { // 敵のセット
		SetPosition(pos); SetSize(size); m_pos = pos;
		m_move = move; m_size = size;
		m_nLife = nLife; SetObjType(objType);
	}

	void Death(void); // 倒されたときの処理
	void OjamanCreate(void); // おじゃまを作る処理
	void EnemyExplosionCreate(CEnemyexplosion::EXPLOSIONTEXTURE ExplosionTexture); // 敵の爆発を出す処理
	void GaugeUp(void); // ゲージの最大値を伸ばす処理
	void EnemyDamage(int nDamage, DAMAGETYPE DamageType, CBullet::BULLETTYPE BulletType); // ダメージの処理
private:
	CGauge* m_pGauge; // ゲージのポインタ
	static LPDIRECT3DTEXTURE9 m_pTexture; // テクスチャへのポインタ
	D3DXVECTOR3			m_pos;		   // 位置
	D3DXVECTOR3			m_move;		   // 速度
	D3DXVECTOR3			m_size;		   // 大きさ
	int					m_nLife;	   // 敵の体力
	int					m_nOjamaCount; // おじゃまのカウント
	DAMAGETYPE			m_DamageType;  // ダメージのタイプ
	CBullet::BULLETTYPE m_BulletType;  // 誰の弾なのか
};
#endif