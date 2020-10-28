//=============================================================================
//
// ボムの爆発の処理 [bombexplosion.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _BOMBEXPLOSION_H_
#define _BOMBEXPLOSION_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define BOMBEXPLOSION_ANIMATION_COUNT (10)	// 爆発のアニメーションのカウント(横のテクスチャの分割数)
#define BOMBEXPLOSION_ANIMATION_PATTERN (2) // 爆発のアニメーションのパターン(縦のテクスチャの分割数)
#define BOMBEXPLOSION_SIZE_X (745.0f)			// 爆発の縦の長さ
#define BOMBEXPLOSION_SIZE_Y (1080.0f)			// 爆発の横の長さ

//=============================================================================
// 前方宣言
//=============================================================================
class CSound;

//=============================================================================
// ボムの爆発クラス
//=============================================================================
class CBombexplosion :public CScene2D
{
public:
	typedef enum
	{
		BOMBEXPLOSION_NONE = 0,
		BOMBEXPLOSION_PLAYER,  // プレイヤー1のボムの爆発
		BOMBEXPLOSION_PLAYER2, // プレイヤー2のボムの爆発
		BOMBEXPLOSION_MAX,
	}BOMBEXPLOSIONTYPE;

	CBombexplosion();
	~CBombexplosion();

	static HRESULT Load(void);
	static void Unload(void);
	static CBombexplosion *Create(D3DXVECTOR3 pos, int nLife, BOMBEXPLOSIONTYPE bombexplosiontype, OBJTYPE objType);

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetExplosion(D3DXVECTOR3 pos, int nLife, BOMBEXPLOSIONTYPE bombexplosiontype, OBJTYPE objType) {
		m_pos = pos; m_nLife = nLife; 
		SetPosition(pos); SetSize(BOMBEXPLOSION_SIZE_X, BOMBEXPLOSION_SIZE_Y);
		m_BombExplosionType = bombexplosiontype; SetObjType(objType);
	}
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;  // テクスチャのポインタ
	D3DXVECTOR3		  m_pos;			   // 爆発の座標
	D3DXVECTOR3		  m_Getpos;			   // 受け取った座標
	float			  m_fSizeX;			   // 横の大きさ
	float			  m_fSizeY;			   // 縦の大きさ
	float			  m_fGetSizeX;		   // 受け取った横のサイズ
	float			  m_fGetSizeY;		   // 受け取った縦のサイズ
	int				  m_nLife;			   // 体力
	BOMBEXPLOSIONTYPE m_BombExplosionType; // ボムの爆発のタイプ
};
#endif