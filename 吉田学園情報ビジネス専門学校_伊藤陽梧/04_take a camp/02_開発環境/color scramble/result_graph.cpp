//===================================================
//
//    ゲージクラスの処理[gage.cpp]
//    Author:増澤 未来
//
//====================================================

//**********************************
// インクルード
//**********************************
#include "result_graph.h"
#include "gauge.h"
#include "scene2d.h"
#include "color_tile.h"
#include "color_manager.h"
#include "chara_select.h"

//**********************************
// マクロ定義
//**********************************
#define GAUGE_WIDTH  (50.0f)   // ゲージの幅
#define GAUGE_HEIGHT (500.0f)  // ゲージの高さ*最大値
#define GAUGE_SPACE  (150.0f)  // 各ゲージの間隔
#define BG_SIZE		(D3DXVECTOR3(SCREEN_WIDTH-15,SCREEN_HEIGHT-20,0.0f))
#define BG_COLOR	(D3DXCOLOR(0.0f,0.0f,0.0f,0.6f))
#define GAUGE_RATE	(0.03f)
#define BACK_GAUGE_SIZE (16)
#define BACK_GAUGE_COLOR (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))
#define GAUGE_POS_Y (710.0f)

//**********************************
// 静的メンバ変数宣言
//**********************************

//==================================
// コンストラクタ
//==================================
CResultGraph::CResultGraph() :CScene(OBJTYPE_UI_2)
{
	// 変数のクリア
	m_pBg = NULL;                // 背景ポリゴン
	ZeroMemory(&m_aGauge,sizeof(m_aGauge));  // ゲージクラス
}

//==================================
// デストラクタ
//==================================
CResultGraph::~CResultGraph()
{
}

//==================================
// クリエイト
//==================================
CResultGraph * CResultGraph::Create(void)
{
	// メモリの確保
	CResultGraph *pGraph;
	pGraph = new CResultGraph;
	pGraph->Init();

	return pGraph;
}

//==================================
// 初期化処理
//==================================
HRESULT CResultGraph::Init(void)
{
	// グラフ背景の生成
	m_pBg = CScene2d::Create();
	m_pBg->SetSize(BG_SIZE);
	m_pBg->SetColor(BG_COLOR);
	m_pBg->SetPriority(OBJTYPE_BG);

	float fMaxNum = 0.0f; // 前回のゲーム中一番高いスコア

	for (int nCntColor = 0; nCntColor < GET_COLORMANAGER->GetColorNum(); nCntColor++)
	{
		int nPlayerNum = GET_COLORMANAGER->GetUsePlayerNum(nCntColor);
		if (nPlayerNum != -1)
		{
			for (int nCntGauge = 0; nCntGauge < GAUGE_NUM; nCntGauge++)
			{
				// [プレイヤー番号]が使っているカラー番号の保管
				m_aGauge[nPlayerNum][nCntGauge].m_nColorNum = nCntColor;
			}
			// 最大数の保管
			if (fMaxNum < CColorTile::GetTileNum(nPlayerNum))
			{
				fMaxNum = (float)CColorTile::GetTileNum(nPlayerNum);
			}
		}
	}
	
	// プレイヤー数の取得
	int nEntryPlayerNum = CCharaSelect::GetEntryPlayerNum();

	// 生成位置X軸の調整
	float posX = (SCREEN_WIDTH/2) - ((float)(nEntryPlayerNum - 1) * GAUGE_SPACE) / 2;

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++ )
	{
		if (CCharaSelect::GetEntryData(nCntPlayer).bEntry)
		{
			
			for (int nCntGauge = 0; nCntGauge < GAUGE_NUM; nCntGauge++)
			{
				if (nCntGauge == 0)
				{
					m_aGauge[nCntPlayer][nCntGauge].pGauge = CGauge::Create(&m_aGauge[nCntPlayer][nCntGauge].fGraphData,
						D3DXVECTOR3(posX, GAUGE_POS_Y, 0.0f),
						GAUGE_WIDTH + BACK_GAUGE_SIZE,
						GAUGE_HEIGHT + BACK_GAUGE_SIZE / 2,
						fMaxNum,
						BACK_GAUGE_COLOR);

				}
				else
				{
					m_aGauge[nCntPlayer][nCntGauge].pGauge = CGauge::Create(&m_aGauge[nCntPlayer][nCntGauge].fGraphData,
						D3DXVECTOR3(posX, GAUGE_POS_Y, 0.0f),
						GAUGE_WIDTH,
						GAUGE_HEIGHT,
						fMaxNum,
						GET_COLORMANAGER->GetIconColor(m_aGauge[nCntPlayer][nCntGauge].m_nColorNum));
				}

				m_aGauge[nCntPlayer][nCntGauge].fGraphData = 0;
			}
			posX += GAUGE_SPACE;
		}
	}

	return S_OK;
}

//==================================
// 終了処理
//==================================
void CResultGraph::Uninit(void)
{

	// 開放処理
	Release();
}

//==================================
// 更新処理
//==================================
void CResultGraph::Update(void)
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		for (int nCntGauge = 0; nCntGauge < GAUGE_NUM; nCntGauge++)
		{
			m_aGauge[nCntPlayer][nCntGauge].fGraphData += ((CColorTile::GetTileNum(m_aGauge[nCntPlayer][nCntGauge].m_nColorNum)) - m_aGauge[nCntPlayer][nCntGauge].fGraphData)*GAUGE_RATE;
		}
	}
}

//==================================
// 描画処理
//==================================
void CResultGraph::Draw(void)
{

}