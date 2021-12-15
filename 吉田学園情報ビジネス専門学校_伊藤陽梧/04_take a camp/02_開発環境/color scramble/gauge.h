//=============================================================================
//
// gaugeヘッダ [gauge.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _GAUGE_H_
#define _GAUGE_H_

//*****************************
//インクルード
//*****************************
#include "main.h"
#include "scene.h"

//*****************************
//前方宣言
//*****************************
class CPolygon;

//*****************************
// マクロ定義
//*****************************

//*****************************
//クラス定義
//*****************************

//ゲージクラス
class CGauge : public CScene
{
public:

	//============
	// 列挙定義
	//============

	//============
	// メンバ関数
	//============

	CGauge();
	~CGauge();

	// static
	static CGauge *Create(float* pData, D3DXVECTOR3 leftPos, float fBarWidht, float fBarHeight, float fMaxNum, D3DXCOLOR frontCol); // クラス生成

	HRESULT Init(void); // 初期化
	void Uninit(void);  // 終了
	void Update(void);  // 更新
	void Draw(void);    // 描画

private:
	// メンバ変数
	CPolygon*   m_pPolygon;  // ライフ描画用のポリゴン
	D3DXVECTOR3 m_pos;       // ゲージの位置(底)
	float       m_fBarWidht; // 幅
	float       m_fBarHeight; // 高さ
	float       m_fMaxNum;   // 最大数
	float *     m_pfData;    // ゲージと紐づける数値のポインタ
	D3DXCOLOR   m_frontCol;  // フロントのカラー
};

#endif