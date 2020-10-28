//=============================================================================
//
// エクストラアタックの処理 [extraattack.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _EXTRAATTACK_H_
#define _EXTRAATTACK_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"
#include "bullet.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_EXTRAATTACK_TEXTURE (4) //テクスチャの最大数

//=============================================================================
// エクストラアタッククラス
//=============================================================================
class CExtraattck :public CScene2D
{
public:
	typedef enum
	{
		EXTRAATTCK_PLAYER_NONE = 0,
		EXTRAATTCK_PLAYER1,		    // プレイヤー1のエクストラアタック
		EXTRAATTCK_PLAYER2,		    // プレイヤー2のエクストラアタック
		EXTRAATTCK_PLAYER_MAX,
	}PLAYER;

	typedef enum
	{
		EXTRAATTACK_NONE = 0,
		EXTRAATTACK_TIKATIKA,  // チカチカしながら相手の方に行くエクストラアタック
		EXTRAATTACK_NERAU,	   // 相手を狙うエクストラアタック
		EXTRAATTACK_EXPLOSION, // 爆発するエクストラアタック
		EXTRAATTACK_LOCKET,	   // 上にあがるエクストラアタック
		EXTRAATTACK_MAX,
	}EXTRAATTACK;

	CExtraattck();
	~CExtraattck();

	static HRESULT Load(void);
	static void Unload(void);
	static CExtraattck *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fSizeX, float fSizeY, PLAYER Player, EXTRAATTACK Extraattack, OBJTYPE objType);

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetExtraAttack(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fSizeX, float fSizeY, PLAYER Player, EXTRAATTACK Extraattack, OBJTYPE objType) {
		SetPosition(pos); SetSize(fSizeX, fSizeY);
		m_pos = pos; m_move = move;
		m_fSizeX = fSizeX; m_fSizeY = fSizeY;
		m_Player = Player; m_ExtraAttack = Extraattack;
		SetObjType(objType);
	}

	EXTRAATTACK GetExtraAttack(void);
private:
	CBullet::BULLETTYPE m_BulletType;	   // 弾のタイプ
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_EXTRAATTACK_TEXTURE];  // テクスチャへのポインタ
	D3DXVECTOR3	m_pos;					   // 座標
	D3DXVECTOR3	m_move;					   // 速さ
	D3DXVECTOR3 m_Getpos;				   // 受け取った座標
	float	m_fSizeX;					   // 横の大きさ
	float	m_fSizeY;					   // 縦の大きさ
	float	m_fAngle;					   // 角度
	int		m_nCountColor;				   // 色のカウント
	PLAYER m_Player;					   // どのプレイヤーか
	EXTRAATTACK m_ExtraAttack;			   // エクストラアタックのタイプ
};
#endif