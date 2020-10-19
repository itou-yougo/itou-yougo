//=============================================================================
//
// ボムの処理 [bomb.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _BOMB_H_
#define _BOMB_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// ボムクラス
//=============================================================================
class CBomb :public CScene2D
{
public:
	typedef enum
	{
		BOMB_TYPE_NONE = 0,
		BOMB_TYPE_PLAYER,  // プレイヤー1のボム
		BOMB_TYPE_PLAYER2, // プレイヤー2のボム
		BOMB_TYPE_MAX,
	}BOMBTTYPE;

	CBomb();
	~CBomb();

	static HRESULT Load(void);
	static void Unload(void);
	static CBomb *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, BOMBTTYPE BombType, OBJTYPE objType);

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetBomb(D3DXVECTOR3 pos, float fSizeX, float fSizeY, BOMBTTYPE BombType, OBJTYPE objType) {
		SetPosition(pos); SetSize(fSizeX, fSizeY);
		m_pos = pos; m_BombType = BombType;
		SetObjType(objType);
	}

	void UseBomb(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;  // テクスチャへのポインタ
	D3DXVECTOR3	m_pos;					   // ボムの座標
	D3DXVECTOR3 m_Getpos;				   // 受けっとった座標
	bool	m_bUse;						   // ボムを使ったかどうか
	BOMBTTYPE m_BombType;				   // ボムのタイプ
};
#endif