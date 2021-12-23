//=============================================================================
//
// effect_explosionヘッダ [effect_explosion.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _EFFECT_EXPLOSION_H_
#define _EFFECT_EXPLOSION_H_

//*****************************
// インクルード
//*****************************
#include "scene.h"
#include "resource_map.h"
#include "stage_select.h"

//*****************************
// 前方宣言
//*****************************
class CScene2d;

//=============================
// マクロ定義
//=============================
#define EFFECT_EXPLOSION_TEX_NUM 1
#define EFFECT_EXPLOSION_DEFAULT_SIZE D3DXVECTOR3(700.0f,700.0f,0.0f)
//*****************************
//クラス定義
//*****************************

//ゲージクラス
class CResultExplosion : public CScene
{
public:

	//============
	// メンバ関数
	//============
	CResultExplosion();
	~CResultExplosion();

	// static
	static CResultExplosion *Create(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 size = EFFECT_EXPLOSION_DEFAULT_SIZE); // クラス生成

	HRESULT Init(void); // 初期化
	void Uninit(void);  // 終了
	void Update(void);  // 更新
	void Draw(void);    // 描画

private:
	// メンバ変数
	CScene2d * m_apPolygon[EFFECT_EXPLOSION_TEX_NUM]; // 名前ポリゴン
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
	bool m_bReCreate;
	int m_nCntAnim; // テクスチャアニメーションカウント
	int m_nTexU;    // テクスチャ分割U

};

#endif