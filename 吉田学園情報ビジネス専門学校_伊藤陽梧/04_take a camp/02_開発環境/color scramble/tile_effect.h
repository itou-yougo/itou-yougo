//=============================================================================
//
// tile_effect_chargeヘッダ [tile_effect_charge.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _TILE_EFFECT_H_
#define _TILE_EFFECT_H_

//*****************************
//インクルード
//*****************************
#include "scene.h"

//*****************************
//クラス定義
//*****************************

//攻撃範囲の可視化
class CTileEffect : public CScene
{
public:
	// メンバ関数
	CTileEffect();
	~CTileEffect();

	HRESULT Init(void);
	void Uninit(void);
	virtual void Update(void);
	void Draw(void) = 0;

	bool GetDrawFlag(void) { return m_bDraw; }
	void SetDrawFlag(bool bFlag) { m_bDraw = bFlag; }

	float GetAlpha(void) { return m_fAlpha; }
private:
	// メンバ変数
	bool m_bDraw;
	float m_fAlpha;
};


#endif