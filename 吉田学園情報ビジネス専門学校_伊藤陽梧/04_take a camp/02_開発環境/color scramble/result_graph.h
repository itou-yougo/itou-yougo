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
class CCharacterPolygon;

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
	enum
	{
		GAUGE_BACK = 0,
		GAUGE_FRONT,
	};

	//============
	// 構造体定義
	//============
	struct GraphParts
	{
		CGauge   * pGauge;    // ゲージ
		int      m_nColorNum; // カラー番号
	};

	struct Rank
	{
		int nPlayerNum; // プレイヤー番号
		int nPaintNum;  // 塗数
		int nKillNum;   // キル数
		int nRank;      // 順位
	};

	struct CharaPolygonData
	{
		CCharacterPolygon* pCharaPolygon;
		float fMoveY;
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

	bool GetEndFlag(void) { return m_bEnd; }
private:
	void SetMaxNum(void);
	void CreatePolygon(void);
	void ManageGraph(void);
	void ManageCharacterHeight(void);
	// メンバ変数
	CScene2d * m_pBg;                  // 背景ポリゴン
	GraphParts m_aGauge[MAX_PLAYER][GAUGE_NUM];  // ゲージ
    float m_fMaxNum; // ゲージ内部数値最大値
	std::vector<Rank> m_aRankData;
	int m_nActionRank; // アクションを起こす順位
	int m_nActionCnt;
	std::vector<CCharacterPolygon*> m_apCharaPolygon;
	bool m_bEnd;
};

#endif