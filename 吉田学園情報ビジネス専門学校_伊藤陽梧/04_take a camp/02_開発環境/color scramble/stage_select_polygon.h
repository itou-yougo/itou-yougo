//=============================================================================
//
// stage_select_polygonヘッダ [stage_select_polygon.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _STAGE_SELECT_POLYGON_H_
#define _STAGE_SELECT_POLYGON_H_

//*****************************
// インクルード
//*****************************
#include "scene.h"

//*****************************
// 前方宣言
//*****************************
class CScene2d;

//=============================
// マクロ定義
//=============================
#define STAGE_SELECT_POLYGON_NUM 3
#define WEIGHT_MUN  8	   // 重みを計算する個数

//*****************************
//クラス定義
//*****************************

//ゲージクラス
class CStageSelectPolygon : public CScene
{
public:

	//============
	// メンバ関数
	//============
	CStageSelectPolygon();
	~CStageSelectPolygon();

	// static
	static CStageSelectPolygon *Create(void); // クラス生成

	HRESULT Init(void); // 初期化
	void Uninit(void);  // 終了
	void Update(void);  // 更新
	void Draw(void);    // 描画

private:
	void DrawBlur(void);
	void UpdateWeight(float fDispersion);
	// メンバ変数
	CScene2d * m_apPolygon[STAGE_SELECT_POLYGON_NUM]; // 名前ポリゴン
	D3DXHANDLE	m_weightHandle;	// 重みの配列シェーダーに送るよう
	float		m_afWeight[WEIGHT_MUN];// 重みの配列
};

#endif