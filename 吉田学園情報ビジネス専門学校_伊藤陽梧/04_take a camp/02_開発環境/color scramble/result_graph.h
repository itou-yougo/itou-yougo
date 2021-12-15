//=============================================================================
//
// result_graphヘッダ [result_graph.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _RESULT_GRAPH_H_
#define _RESULT_GRAPH_H_

//*****************************
//インクルード
//*****************************
#include "main.h"
#include "scene.h"
#include "game.h"

//*****************************
//前方宣言
//*****************************
class CScene2d;
class CGauge;

//*****************************
// マクロ定義
//*****************************
#define GAUGE_NUM (2)
//*****************************
//クラス定義
//*****************************

//ゲージクラス
class CResultGraph : public CScene
{
public:

	//============
	// 列挙定義
	//============

	//============
	// 構造体定義
	//============
	struct GraphParts
	{
		CGauge   * pGauge;    // ゲージ
		float    fGraphData;  // ゲージ数値
		int      m_nColorNum; // カラー番号
	};

	//============
	// メンバ関数
	//============

	CResultGraph();
	~CResultGraph();

	// static
	static CResultGraph *Create(void); // クラス生成

	HRESULT Init(void); // 初期化
	void Uninit(void);  // 終了
	void Update(void);  // 更新
	void Draw(void);    // 描画
private:
	// メンバ変数
	CScene2d * m_pBg;                  // 背景ポリゴン
	GraphParts m_aGauge[MAX_PLAYER][GAUGE_NUM];  // ゲージ
};

#endif