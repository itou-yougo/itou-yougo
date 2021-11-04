//=============================================================================
//
// 弾の処理 [bullet.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"
#include "player.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_BULLET_TEXTURE (5) // 弾のテクスチャの最大数

//=============================================================================
// バレットクラス
//=============================================================================
class CBullet :public CScene2D
{
public:
	typedef enum
	{
		BULLET_TYPE_NONE = 0,
		BULLET_TYPE_1P,   // PLAYER1の弾
		BULLET_TYPE_2P,   // PLAYER2の弾
		BULLET_TYPE_BOSS, // ボスの弾
		BULLET_TYPE_MAX,
	}BULLETTYPE;

	typedef enum
	{
		CHARGEBULLET_TYPE_NONE = 0,
		CHARGEBULLET_TYPE_NOMAL,	 // 普通の弾
		CHARGEBULLET_TYPE_CHARGE,	 // チャージした弾
		CHARGEBULLET_TYPE_LASER,	 // レーザー弾
		CHARGEBULLET_TYPE_BOSSLASER, // ボスのレーザー弾
		CHARGEBULLET_TYPE_MAX,
	}CHARGEBULLETTYPE;

	CBullet();  // コンストラク
	~CBullet();	// デストラクタ

	static HRESULT Load(void); // ロード
	static void Unload(void);  // アンロード
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size,
		int nLife, int nDamage, BULLETTYPE BulletType, CHARGEBULLETTYPE ChargeBulletType, OBJTYPE objType); // クリエイト

	HRESULT Init();    // 初期化処理
	void Uninit(void); // 終了処理
	void Update(void); // 更新処理
	void Draw(void);   // 描画処理

	void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size,
		int nLife, int nDamage, BULLETTYPE BulletType, CHARGEBULLETTYPE ChargeBulletType, OBJTYPE objType) { // 弾の設定
		SetPosition(pos); SetSize(size);
		m_pos = pos; m_move = move; m_size = size;
		m_nLife = nLife; m_nDamage = nDamage;
		m_BulletType = BulletType; m_ChargeBulletType = ChargeBulletType;
		SetObjType(objType);
	}

	void Move(void); // 動く処理
	void BulletNomal(BULLETTYPE BulletType); // 弾の処理
	void BulletCharge(BULLETTYPE BulletType); // チャージ弾の処理
	void BulletLaser(CPlayer::PLAYERNUM PlayerNum, BULLETTYPE BulletType); // レーザー弾の処理
	void BulletBossLaser(void); // レーザー弾の処理
	BULLETTYPE GetBulletType(void); // 弾のタイプを返す
	CHARGEBULLETTYPE GetChargeBulletType(void); // チャージ弾のタイプを返す
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BULLET_TEXTURE]; // テクスチャへのポインタ
	D3DXVECTOR3	m_pos;					 // 球の位置
	D3DXVECTOR3	m_move;					 // 球の速さ
	D3DXVECTOR3 m_size;					 // 大きさ
	int     m_nLife;					 // 弾の体力
	int     m_nGetLife;					 // 受け取った体力
	int		m_nDamage;					 // 弾のダメージ
	BULLETTYPE m_BulletType;			 // 弾のタイプ
	CHARGEBULLETTYPE m_ChargeBulletType; // チャージ弾のタイプ
};
#endif