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
#include "keyboard.h"
#include "manager.h"
#include "effect_result_explosion.h"
#include "character_polygon.h"
#include "confetti_factory.h"
#include "kill_count.h"
#include "player_model.h"
#include "motion.h"

//**********************************
// マクロ定義
//**********************************
#define GAUGE_WIDTH  (180.0f)   // ゲージの幅
#define GAUGE_HEIGHT (575.0f)  // ゲージの高さ*最大値
#define GAUGE_SPACE  (275.0f)  // 各ゲージの間隔
#define BG_SIZE		(D3DXVECTOR3(SCREEN_WIDTH-15,SCREEN_HEIGHT-20,0.0f)) // 背景サイズ
#define BG_COLOR	(D3DXCOLOR(0.4f,0.4f,0.4f,0.6f))                     // 背景色
#define BACK_GAUGE_SIZE (40)                                             // バックゲージサイズ
#define BACK_GAUGE_COLOR (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))                // バックゲージカラー
#define GAUGE_POS_Y (710.0f)                                             // ゲージ座標Y
#define MIN_POINT 1.0f                                                   // 0点でもゲージを出すため最低値の加算
#define START_RATE 0.0008f                                                // スタート時のゲージ係数
#define ANNOUNCEMENT_RATE 0.1f                                           // 順位発表時のゲージ係数
#define RANK_ANNOUNCEMENT_COUNT 100                                      // 順位発表カウント
#define EXPLOSION_POS_1 D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f)
#define EXPLOSION_POS_2 D3DXVECTOR3(0.0f,SCREEN_HEIGHT,0.0f)
#define CHARACTER_POLYGON_SIZE (DEFAULT_CHARACTER_POLYGON_SIZE*0.7f)
#define CHARACTER_HEIGHT_DIST ((SCREEN_HEIGHT - CHARACTER_POLYGON_SIZE.y / 2.0f)-20.0f/2.0f)
#define CHARACTER_HEIGHT_ADD 15.0f
#define CHARACTER_CREATE_ADD_HEIGHT -202 //キャラクターを生成する位置を変える
#define CONFETTI_TIME (120)

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
    m_fMaxNum = 0.0f;
	m_nActionRank = 0;
	m_nActionCnt = 0;
	m_bEnd = false;
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

	// グラフ内部数値最大数のセット
	SetMaxNum();

	// ポリゴンの生成
	CreatePolygon();

	// ランクソート処理
	// キル数
	std::sort(m_aRankData.begin(), m_aRankData.end(), [](Rank const& rank1, Rank const& rank2) {return (rank1.nKillNum > rank2.nKillNum); });
	// 塗数
	std::sort(m_aRankData.begin(), m_aRankData.end(), [](Rank const& rank1, Rank const& rank2) {return (rank1.nPaintNum > rank2.nPaintNum); });

	for (int nCnt = 0; nCnt < (int)m_aRankData.size(); nCnt++)
	{
		m_aRankData[nCnt].nRank = nCnt;

		if (nCnt > 0)
		{
			if (m_aRankData[nCnt].nPaintNum == m_aRankData[nCnt - 1].nPaintNum&&
				m_aRankData[nCnt].nKillNum == m_aRankData[nCnt - 1].nKillNum)
			{
				m_aRankData[nCnt].nRank = m_aRankData[nCnt - 1].nRank;
			}
		}
	}

	// アクション順位の初期化
	if (m_aRankData.size() >= 1) m_nActionRank = m_aRankData[m_aRankData.size() - 1].nRank;
	
	// アクションカウントの初期化
	m_nActionCnt = -RANK_ANNOUNCEMENT_COUNT;
	
	// エンドフラグの初期化
	m_bEnd = false;

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
	// グラフ
	ManageGraph();

	// キャラの座標Yの管理
	ManageCharacterHeight();
}

//==================================
// 描画処理
//==================================
void CResultGraph::Draw(void)
{
}

//==================================
// グラフ最大数のセット
//==================================
void CResultGraph::SetMaxNum(void)
{
	m_fMaxNum = 0.0f; // 前回のゲーム中一番高いスコア

	for (int nCntColor = 0; nCntColor < GET_COLORMANAGER->GetColorNum(); nCntColor++)
	{
		// プレイヤー番号の取得
		int nPlayerNum = GET_COLORMANAGER->GetUsePlayerNum(nCntColor);
		if (nPlayerNum == -1) continue;

		for (int nCntGauge = 0; nCntGauge < GAUGE_NUM; nCntGauge++)
		{
			// [プレイヤー番号]が使っているカラー番号の保管
			m_aGauge[nPlayerNum][nCntGauge].m_nColorNum = nCntColor;
		}

		int nTileNum = CColorTile::GetTileNum(nPlayerNum) + (int)MIN_POINT;
		Rank rank = { nPlayerNum ,nTileNum ,CKillCount::GetTotalKill(nPlayerNum) };
		m_aRankData.push_back(rank);

		// 最大数の保管
		if (m_fMaxNum < nTileNum)
		{
			m_fMaxNum = (float)nTileNum;
		}
	}
}

//==================================
// ポリゴンの生成処理
//==================================
void CResultGraph::CreatePolygon(void)
{
	// プレイヤー数の取得
	int nEntryPlayerNum = CCharaSelect::GetEntryPlayerNum();

	// 生成位置X軸の調整
	float posX = (SCREEN_WIDTH / 2.0f) - ((float)(nEntryPlayerNum - 1) * GAUGE_SPACE) / 2.0f;

	float fCreateCharaHeight = CHARACTER_CREATE_ADD_HEIGHT;
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (!CCharaSelect::GetEntryData(nCntPlayer).bEntry) continue;

		for (int nCntGauge = 0; nCntGauge < GAUGE_NUM; nCntGauge++)
		{
			// ゲージで使う値の設定
			float fWight = GAUGE_WIDTH;
			float fHeight = GAUGE_HEIGHT;
			D3DXCOLOR col = GET_COLORMANAGER->GetIconColor(m_aGauge[nCntPlayer][nCntGauge].m_nColorNum);

			if (nCntGauge == 0)
			{
				fWight = GAUGE_WIDTH + BACK_GAUGE_SIZE;
				fHeight = GAUGE_HEIGHT + BACK_GAUGE_SIZE / 2.0f;
				col = BACK_GAUGE_COLOR;
			}
			// ゲージの生成
			m_aGauge[nCntPlayer][nCntGauge].pGauge = CGauge::Create(D3DXVECTOR3(posX, GAUGE_POS_Y, 0.0f), fWight, fHeight, m_fMaxNum, col);
			// 目標値の設定
			m_aGauge[nCntPlayer][nCntGauge].pGauge->SetValueDist(CColorTile::GetTileNum(m_aGauge[nCntPlayer][nCntGauge].m_nColorNum) + MIN_POINT);

		}

		// キャラクターポリゴンの生成
		CCharacterPolygon * pCharaPolygon = CCharacterPolygon::Create(D3DXVECTOR3(posX, fCreateCharaHeight, 0.0f));
		pCharaPolygon->SetSize(CHARACTER_POLYGON_SIZE);
		pCharaPolygon->SetCharaType(CCharaSelect::GetEntryData(nCntPlayer).charaType);
		pCharaPolygon->SetRimColor(GET_COLORMANAGER->GetStepColor(CCharaSelect::GetEntryData(nCntPlayer).nColorNum, 1));
		pCharaPolygon->SetTexColor(GET_COLORMANAGER->GetIconColor(CCharaSelect::GetEntryData(nCntPlayer).nColorNum));

		// キャラクターデータの保存
		m_apCharaPolygon.push_back(pCharaPolygon);
		
		fCreateCharaHeight += CHARACTER_CREATE_ADD_HEIGHT;

		// ゲージの設定
		m_aGauge[nCntPlayer][GAUGE_BACK].pGauge->SetMode(CGauge::MODE_HEIGHT_SELF);
		m_aGauge[nCntPlayer][GAUGE_FRONT].pGauge->SetMode(CGauge::MODE_HEIGHT_AUTO);
		m_aGauge[nCntPlayer][GAUGE_FRONT].pGauge->SetHeightDist(GAUGE_HEIGHT / 2.0f);
		m_aGauge[nCntPlayer][GAUGE_FRONT].pGauge->SetRate(START_RATE);
		posX += GAUGE_SPACE;
	}
}

//==================================
// グラフ管理
//==================================
void CResultGraph::ManageGraph(void)
{
	m_nActionCnt++;
	if (m_nActionCnt >= RANK_ANNOUNCEMENT_COUNT && (int)m_aRankData.size() == m_nActionRank)
	{
		m_nActionCnt = 0;
		m_nActionRank--;
	}

	if (m_nActionRank >= 0)
	{
		if (m_nActionCnt > RANK_ANNOUNCEMENT_COUNT)
		{
			bool bAnnouncement = false;
			for (int nCntRankData = 0; nCntRankData < (int)m_aRankData.size(); nCntRankData++)
			{
				// アクションを起こす順位の比較
				if (m_aRankData[nCntRankData].nRank != m_nActionRank)    continue;

				// プレイヤー番号
				int nPlayerNum = m_aRankData[nCntRankData].nPlayerNum;
				// ゲージのモードを切り替える
				m_aGauge[nPlayerNum][GAUGE_FRONT].pGauge->SetMode(CGauge::MODE_VALUE_AUTO);
				m_aGauge[nPlayerNum][GAUGE_FRONT].pGauge->SetRate(ANNOUNCEMENT_RATE);

				// 爆発エフェクトの生成
				D3DXCOLOR iconCol = GET_COLORMANAGER->GetIconColor(m_aGauge[nPlayerNum][GAUGE_FRONT].m_nColorNum);
				CResultExplosion::Create(EXPLOSION_POS_1, iconCol);
				CResultExplosion::Create(EXPLOSION_POS_2, iconCol);

				if (m_nActionRank == 0)
				{// 一位発表時
					CConfettiFactory::Create(iconCol, CONFETTI_TIME);
					m_bEnd = true;
				}
				bAnnouncement = true;

				// 次の順位が一位の時はディレイなく発表する
				if (nCntRankData > 0 && m_aRankData[nCntRankData - 1].nRank == 0)
				{
					bAnnouncement = false;
				}
			}
			// アクションランクを次のランクにする
			m_nActionRank--;
			// カウントの初期化*順位が中抜けだったときはカウントを初期化しない
			m_nActionCnt = 0;
			if (!bAnnouncement) m_nActionCnt = RANK_ANNOUNCEMENT_COUNT;
		}
	}

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		// NULLチェック
		if (m_aGauge[nCntPlayer][GAUGE_BACK].pGauge == NULL || m_aGauge[nCntPlayer][1].pGauge == NULL) continue;

		// バックゲージの値の設定
		m_aGauge[nCntPlayer][GAUGE_BACK].pGauge->SetHeight(m_aGauge[nCntPlayer][1].pGauge->GetHeight() + (BACK_GAUGE_SIZE / 2.0f));
	}

}

//==================================
// キャラの座標Yの管理
//==================================
void CResultGraph::ManageCharacterHeight(void)
{
	for (int nCnt = 0; nCnt < (int)m_apCharaPolygon.size(); nCnt++)
	{
		// 座標の取得
		D3DXVECTOR3 pos = m_apCharaPolygon[nCnt]->GetPos();
		if (pos.y < CHARACTER_HEIGHT_DIST)
		{
			// 高さの加算
			pos.y += CHARACTER_HEIGHT_ADD;
			if (pos.y > CHARACTER_HEIGHT_DIST)
			{// 行き過ぎないよう調整
				pos.y = CHARACTER_HEIGHT_DIST;
				m_apCharaPolygon[nCnt]->GetCharaModel()->GetMotion(CResourceCharacter::MOTION_ROLL)->SetActiveMotion(true);
			}
			// 座標のセット
			m_apCharaPolygon[nCnt]->SetPos(pos);
		}
	}
}
