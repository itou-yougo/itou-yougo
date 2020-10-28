//=============================================================================
//
// チャージの処理 [charge.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _CHARGE_H_
#define _CHARGE_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// チャージクラス
//=============================================================================
class CCharge
{
public:
	typedef enum
	{
		CHARGETYPE_NONE = 0,
		CHARGETYPE_1, // チャージの1段階目
		CHARGETYPE_2, // チャージの2段階目
		CHARGETYPE_3, // チャージの3段階目
		CHARGETYPE_MAX,
	}CHARGETYPE;

	CCharge();
	~CCharge();

	static HRESULT Load(void);
	static void Unload(void);

	static CCharge *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY);
	void SetCharge(D3DXVECTOR3 pos, float fSizeX, float fSizeY) {
		m_pos = pos; m_fSizeX = fSizeX; m_fSizeY = fSizeY;
	}

	void SetExtend(float fExtendX, float fMaxExtendX, float fExtendY, float fMaxExtendY) {
		m_fExtendX += fExtendX; m_fMaxExtendX = fMaxExtendX;
		m_fExtendY += fExtendY; m_fMaxExtendY = fMaxExtendY;
	}

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	CHARGETYPE GetChargeType(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;  // テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	   // 頂点バッファへのポインタ
	D3DXVECTOR3				m_pos;		   // 座標
	int						m_nCountColor; // 色を変えるカウント
	float					m_fSizeX;	   // 横の大きさ
	float					m_fSizeY;	   // 縦の大きさ
	float					m_fExtendX;	   // テクスチャを横に伸ばす
	float					m_fExtendY;	   // テクスチャを縦に伸ばす
	float					m_fMaxExtendX; // テクスチャを横に伸ばす最大値
	float					m_fMaxExtendY; // テクスチャを縦に伸ばす最大値
	CHARGETYPE				m_chargetye;   // チャージの段階
};
#endif