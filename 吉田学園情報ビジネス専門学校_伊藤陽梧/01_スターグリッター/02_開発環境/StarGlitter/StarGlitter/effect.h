//=============================================================================
//
// エフェクトの処理 [effect.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_EFFECT_TEXTURE (2)

//=============================================================================
// エフェクトクラス
//=============================================================================
class CEffect :public CScene2D
{
public:
	typedef enum
	{
		EFFECTTYPE_BULLET = 0,  // 弾のエフェクト
		EFFECTTYPE_CHARGESTATE, // チャージのエフェクト
	}EFFECTTYPE;     
	CEffect();
	~CEffect();

	static HRESULT Load(void);
	static void Unload(void);
	static CEffect *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nLife, int nRed, int nGreen, int nBrue, int nAlpha, EFFECTTYPE EffectType, OBJTYPE objType);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetEffect(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nLife, int nRed, int nGreen, int nBrue, int nAlpha, EFFECTTYPE EffectType, OBJTYPE objType) {
		m_pos = pos; m_fSizeX = fSizeX; m_fSizeY = fSizeY;
		m_nLife = nLife; m_nRed = nRed; m_nGreen = nGreen;
		m_nBrue = nBrue; m_nAlpha = nAlpha;
		m_EffectType = EffectType;
		SetPosition(pos); SetSize(fSizeX, fSizeY);
		SetObjType(objType);
	}

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_EFFECT_TEXTURE]; // テクスチャへのポインタ
	D3DXVECTOR3				  m_pos;	  // 座標
	int						  m_nLife;	  // 体力
	int						  m_nRed;	  // 赤
	int						  m_nGreen;	  // 緑
	int						  m_nBrue;	  // 青
	int						  m_nAlpha;	  // 透明度
	float					  m_fSizeX;	  // 横の大きさ
	float					  m_fSizeY;	  // 縦の大きさ
	EFFECTTYPE m_EffectType;
};
#endif