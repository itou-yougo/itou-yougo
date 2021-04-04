//=============================================================================
//
// 必殺技のエフェクトの処理 [spesialattackeffect.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _SPESIALATTACKEFFECT_H_
#define _SPESIALATTACKEFFECT_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include"particle.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define SPESIALATTACKEFFECT_COUNTANIM (10)	// テクスチャの横の分割
#define SPESIALATTACKEFFECT_PATTERNANIM (1) // テクスチャの縦の分割
#define SPESIALATTACKEFFECT_TIMEANIM (4)	// アニメーションの時間

#define SPESIALATTACKEFFECT_SIZE (D3DXVECTOR3(300.0f, 300.0f, 0.0f))	// サイズ
#define SPESIALATTACKEFFECT_COLOR (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))	// 色

//=============================================================================
// スペシャルアタックエフェクトクラス
//=============================================================================
class CSpesialattackeffect : public CParticle
{
public:
	CSpesialattackeffect();
	~CSpesialattackeffect();

	static CSpesialattackeffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, int Life);
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
};
#endif