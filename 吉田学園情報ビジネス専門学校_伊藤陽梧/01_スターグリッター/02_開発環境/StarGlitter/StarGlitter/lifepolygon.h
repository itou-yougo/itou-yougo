//=============================================================================
//
// ライフポリゴンの処理 [lifepolygon.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _LIFEPOLYGON_H_
#define _LIFEPOLYGON_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// ライフポリゴンクラス
//=============================================================================
class CLifepolygon
{
public:

	CLifepolygon();
	~CLifepolygon();

	static HRESULT Load(void);
	static void Unload(void);
	static CLifepolygon *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nDivide, int nCount);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetLifePolygon(int nDivide, int nCount);

	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetSize(float fSizeX, float fSizeY) {
		m_fSizeX = fSizeX; m_fSizeY = fSizeY;
	}

private:
	static LPDIRECT3DTEXTURE9 m_pTexture; // テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	  // 頂点バッファへのポインタ
	D3DXVECTOR3				m_pos;		  // 座標
	float					m_fSizeX;	  // 横の大きさ
	float					m_fSizeY;	  // 縦の大きさ
};
#endif