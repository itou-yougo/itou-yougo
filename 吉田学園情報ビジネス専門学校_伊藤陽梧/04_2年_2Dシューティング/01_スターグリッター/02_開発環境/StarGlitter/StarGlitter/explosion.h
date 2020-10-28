//=============================================================================
//
// ポリゴンの描画の処理 [explosion.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_EXPLOSION_TEXTUTE (2)

//=============================================================================
// 前方宣言
//=============================================================================
class CSound;

//=============================================================================
// エクスプロージョンクラス
//=============================================================================
class CExplosion :public CScene2D
{
public:
	typedef enum
	{
		EXPLOSIONTYPE_NOMAL = 0, // 弾の爆発
		EXPLOSIONTYPE_BOSS,		 // ボスアタックの爆発
	}EXPLOSIONTYPE;

	CExplosion();
	~CExplosion();

	static HRESULT Load(void);
	static void Unload(void);
	static CExplosion *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, EXPLOSIONTYPE ExplosionType, OBJTYPE objType);

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetExplosion(D3DXVECTOR3 pos, float fSizeX, float fSizeY, EXPLOSIONTYPE ExplosionType, OBJTYPE objType) {
		m_pos = pos; m_fSizeX = fSizeX; m_fSizeY = fSizeY;
		SetPosition(pos); SetSize(fSizeX, fSizeY);
		m_ExplosionType = ExplosionType; SetObjType(objType);
	}
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_EXPLOSION_TEXTUTE]; // テクスチャへのポインタ
	D3DXVECTOR3		  m_pos;		   // 座標
	float			  m_fSizeX;		   // 横の大きさ
	float			  m_fSizeY;		   // 縦の大きさ
	int				  m_nCounterAnim;  // アニメーションのカウント
	EXPLOSIONTYPE	  m_ExplosionType; // 爆発のタイプ
};
#endif