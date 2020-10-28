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
		BULLET_TYPE_PLAYER,  // PLAYER1の弾
		BULLET_TYPE_PLAYER2, // PLAYER2の弾
		BULLET_TYPE_BOSS,	 // ボスの弾
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

	CBullet();
	~CBullet();

	static HRESULT Load(void);
	static void Unload(void);
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fSizeX, float fSizeY, int nLife, int nDamage, BULLETTYPE BulletType, CHARGEBULLETTYPE ChargeBulletType, OBJTYPE objType);

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fSizeX, float fSizeY, int nLife, int nDamage, BULLETTYPE BulletType, CHARGEBULLETTYPE ChargeBulletType, OBJTYPE objType) {
		SetPosition(pos); SetSize(fSizeX, fSizeY);
		m_pos = pos; m_move = move;
		m_fSizeX = fSizeX; m_fSizeY = fSizeY;
		m_nLife = nLife; m_nDamage = nDamage;
		m_BulletType = BulletType; m_ChargeBulletType = ChargeBulletType;
		SetObjType(objType);
	}

	BULLETTYPE GetBulletType(void);
	CHARGEBULLETTYPE GetChargeBulletType(void);
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BULLET_TEXTURE]; // テクスチャへのポインタ
	D3DXVECTOR3	m_pos;					 // 球の位置
	D3DXVECTOR3	m_move;					 // 球の速さ
	D3DXVECTOR3 m_Getpos;				 // 受け取った座標
	float	m_fSizeX;					 // ポリゴンの横の大きさ
	float	m_fSizeY;					 // ポリゴンの縦の大きさ
	float	m_fGetSizeX;				 // ポリゴンの横の大きさ
	float	m_fGetSizeY;				 // ポリゴンの縦の大きさ
	int     m_nLife;					 // 弾の体力
	int     m_nGetLife;					 // 受け取った体力
	int		m_nDamage;					 // 弾のダメージ
	BULLETTYPE m_BulletType;			 // 弾のタイプ
	CHARGEBULLETTYPE m_ChargeBulletType; // チャージ弾のタイプ
};
#endif