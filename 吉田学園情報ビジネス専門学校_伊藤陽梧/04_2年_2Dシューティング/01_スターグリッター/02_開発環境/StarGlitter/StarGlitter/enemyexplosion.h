//=============================================================================
//
// 敵の爆発の処理 [enemyexplosion.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _ENEMYEXPLOSION_H_
#define _ENEMYEXPLOSION_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_ENEMYEXPLOSION_TEXTURE (2)

//=============================================================================
// 前方宣言
//=============================================================================
class CSound;

//=============================================================================
// 敵の爆発クラス
//=============================================================================
class CEnemyexplosion :public CScene2D
{
public:
	typedef enum
	{
		EXPLOSIONTYPE_NONE = 0,
		EXPLOSIONTYPE_PLAYER,  // PLAYER1の爆発
		EXPLOSIONTYPE_PLAYER2, // PLAYER2の爆発
		EXPLOSIONTYPE_MAX,
	}EXPLOSIONTYPE;

	typedef enum
	{
		EXPLOSIONTEXTURE_1 = 0, // 弾に当たって倒されたときのテクスチャ
		EXPLOSIONTEXTURE_2,		// 爆発に当たって倒されたときのテクスチャ
	}EXPLOSIONTEXTURE;

	CEnemyexplosion();
	~CEnemyexplosion();

	static HRESULT Load(void);
	static void Unload(void);
	static CEnemyexplosion *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, EXPLOSIONTYPE ExplosionType, EXPLOSIONTEXTURE ExplosionTexture, OBJTYPE objType);
	void SetExplosion(D3DXVECTOR3 pos, float fSizeX, float fSizeY, EXPLOSIONTYPE ExplosionType, EXPLOSIONTEXTURE ExplosionTexture, OBJTYPE objType) {
		m_pos = pos; m_fSizeX = fSizeX; m_fSizeY = fSizeY;
		m_ExplosionType = ExplosionType; m_ExplosionTexture = ExplosionTexture;
		SetPosition(pos); SetSize(fSizeX, fSizeY);
		SetObjType(objType);
	}

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	EXPLOSIONTYPE GetExplosionType(void);
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_ENEMYEXPLOSION_TEXTURE]; // テクスチャへのポインタ
	D3DXVECTOR3		  m_pos;			  // 座標
	D3DXVECTOR3		  m_Getpos;			  // 受け取った座標
	float			  m_fSizeX;			  // 横の大きさ
	float			  m_fSizeY;			  // 縦の大きさ
	int				  m_nCounterAnim;	  // アニメーションのカウント
	int				  m_nPatternAnim;	  // アニメーションのパターン
	int				  m_nTimeAnim;		  // アニメーションの時間
	EXPLOSIONTYPE	  m_ExplosionType;	  // 爆発のタイプ
	EXPLOSIONTEXTURE  m_ExplosionTexture; // 爆発のテクスチャ
};
#endif