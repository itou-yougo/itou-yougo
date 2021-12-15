//=============================================================================
//
// attack_areaヘッダ [attack_area.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _ATTACK_AREA_H_
#define _ATTACK_AREA_H_

//*****************************
//インクルード
//*****************************
#include "scene3d.h"

//*****************************
//クラス定義
//*****************************

//攻撃範囲の可視化
class CAttackArea : public CScene3d
{
public:
	// メンバ関数
	CAttackArea();
	~CAttackArea();
	static CAttackArea *Create(void);
	HRESULT Init(void);
	void Update(void);
	void Draw(void);

	bool GetDrawFlag(void) { return m_bDraw; }
	void SetDrawFlag(bool bFlag) { m_bDraw = bFlag; }
private:
	// メンバ変数
	bool m_bDraw;// 描画フラグ
	bool m_bExpansion; // 拡大フラグ
};


#endif