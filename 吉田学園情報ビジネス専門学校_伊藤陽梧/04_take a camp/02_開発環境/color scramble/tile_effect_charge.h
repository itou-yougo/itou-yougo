//=============================================================================
//
// tile_effect_chargeヘッダ [tile_effect_charge.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _TILE_EFFECT_CHARGE_H_
#define _TILE_EFFECT_CHARGE_H_

//*****************************
//インクルード
//*****************************
#include "tile_effect.h"

//*****************************
//前方宣言
//*****************************
class CScene3d;

//*****************************
//クラス定義
//*****************************

//攻撃範囲の可視化
class CTileEffectCharge : public CTileEffect
{
public:
	// メンバ関数
	CTileEffectCharge();
	~CTileEffectCharge();
	static CTileEffectCharge *Create(void);
	HRESULT Init(void);
	void Update(void);
	void Uninit(void);
	void Draw(void);

	void SetPos(D3DXVECTOR3 pos);
private:
	CScene3d* m_pPolygon;
};


#endif