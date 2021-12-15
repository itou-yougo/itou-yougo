//=============================================================================
//
// max_color_effectヘッダ [max_color_effect.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _MAX_EFFECT_COLOR_H_
#define _MAX_EFFECT_COLOR_H_

//*****************************
//インクルード
//*****************************
#include "scene.h"

//*****************************
// 前方宣言
//*****************************
class CScene3d;

//*****************************
//マクロ定義
//*****************************
#define MAX_COLOR_EFFECT_POLYGON_NUM 4 // エフェクトに使うタイルの数

//*****************************
//クラス定義
//*****************************

// 塗段階最大時のエフェクトクラス
class CMaxColorEffect : public CScene
{
public:
	//*****************************
	// 列挙定義
	//*****************************

	//*****************************
	// 構造体定義
	//*****************************

	//*****************************
	// メンバ関数
	//*****************************
	CMaxColorEffect();
	~CMaxColorEffect();

	static CMaxColorEffect *Create(D3DXVECTOR3 pos, D3DXCOLOR col); // クラス生成

	HRESULT Init(void); // 初期化
	void Uninit(void);  // 終了
	void Update(void);  // 更新
	void Draw(void);    // 描画

private:
	CScene3d *m_apPolygon[MAX_COLOR_EFFECT_POLYGON_NUM]; // ポリゴン
	D3DXCOLOR m_polygonColor; // ポリゴンカラー
	D3DXCOLOR m_distColor;    // 目標カラー
	D3DXVECTOR3 m_pos;        // 座標
	int m_nCntLife;           // 寿命カウント
	float m_fTexV;            // テクスチャV座標
};

#endif