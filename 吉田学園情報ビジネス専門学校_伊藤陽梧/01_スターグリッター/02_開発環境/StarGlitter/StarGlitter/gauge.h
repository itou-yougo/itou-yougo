//=============================================================================
//
// ゲージの処理 [gauge.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _GAUGE_H_
#define _GAUGE_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_GAUGE_TEXTURE (3)
#define MAX_GAUGE_EXTEND (276.0f)

//=============================================================================
// ゲージクラス
//=============================================================================
class CGauge
{
public:
	CGauge();
	~CGauge();

	static HRESULT Load(void);
	static void Unload(void);

	static CGauge *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY);
	void SetGauge(D3DXVECTOR3 pos, float fSizeX, float fSizeY) {
		m_pos = pos; m_fSizeX = fSizeX; m_fSizeY = fSizeY;
	}

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetExtend(float fExtendX, float fExtendY) {
		m_fMaxExtendX += fExtendX; m_fMaxExtendY += fExtendY;
	}
	float GetMaxExtend(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;  // テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	   // 頂点バッファへのポインタ
	D3DXVECTOR3				m_pos;		   // 座標
	float					m_fSizeX;	   // 横の大きさ
	float					m_fSizeY;	   // 縦の大きさ
	float					m_fExtendX;	   // テクスチャを横に伸ばす
	float					m_fExtendY;	   // テクスチャを縦に伸ばす
	float					m_fMaxExtendX; // テクスチャを横に伸ばす最大値
	float					m_fMaxExtendY; // テクスチャを縦に伸ばす最大値
};
#endif