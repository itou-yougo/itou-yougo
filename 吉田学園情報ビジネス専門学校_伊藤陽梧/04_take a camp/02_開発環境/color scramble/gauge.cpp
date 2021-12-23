//===================================================
//
//    ゲージクラスの処理[gage.cpp]
//    Author:増澤 未来
//
//====================================================

//**********************************
// インクルード
//**********************************
#include "gauge.h"
#include "manager.h"
#include "renderer.h"
#include "polygon.h"
#include "player.h"
#include "game.h"

//**********************************
// マクロ定義
//**********************************

//**********************************
// 静的メンバ変数宣言
//**********************************

//==================================
// コンストラクタ
//==================================
CGauge::CGauge() :CScene(OBJTYPE_UI_2)
{
	// 変数のクリア
	m_pPolygon = NULL;
	m_fBarWidht = 0.0f;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fValue = 0.0f;
	m_frontCol = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	m_mode = MODE_VALUE_AUTO;
	m_fHeightDist = 0.0f;
	m_fHeight = 0.0f;
}

//==================================
// デストラクタ
//==================================
CGauge::~CGauge()
{
}

//==================================
// クリエイト
//==================================
CGauge * CGauge::Create( D3DXVECTOR3 leftPos, float fBarWidht, float fBarHeight, float fMaxNum, D3DXCOLOR frontCol)
{
	// メモリの確保
	CGauge *pGage;
	pGage = new CGauge;

	// 引数の代入
	pGage->m_pos = leftPos;             // 左端
	pGage->m_fBarWidht = fBarWidht;     // 幅
	pGage->m_fBarHeight = fBarHeight;   // 高さ
	pGage->m_fMaxNum = fMaxNum;         // 最大数
	pGage->m_frontCol = frontCol;       // フロントカラー

	// 初期化
	pGage->Init();
	// オブジェクトタイプの設定
	pGage->SetPriority(OBJTYPE_UI_2);

	return pGage;
}

//==================================
// 初期化処理
//==================================
HRESULT CGauge::Init(void)
{
	// ポリゴンの生成
	m_pPolygon = CPolygon::Create(
		m_pos,
		D3DXVECTOR3(m_fBarWidht, 0.0f, 0.0f),
		m_frontCol);

	// 値の初期化
	m_fValue = 0.0f;
	m_fValueDist = 0.0f;
	m_fGaugeRate = DEFAULT_GAUGE_RATE;
	m_mode = MODE_VALUE_AUTO;
	m_fHeightDist = 0.0f;
	m_fHeight = 0.0f;

	// 頂点座標の設定
	D3DXVECTOR3 vtxPos[NUM_VERTEX];

	vtxPos[0] = D3DXVECTOR3(m_pos.x - m_fBarWidht / 2.0f, m_pos.y - m_fHeight, 0.0f);
	vtxPos[1] = D3DXVECTOR3(m_pos.x + m_fBarWidht / 2.0f, m_pos.y - m_fHeight, 0.0f);
	vtxPos[2] = D3DXVECTOR3(m_pos.x - m_fBarWidht / 2.0f, m_pos.y            , 0.0f);
	vtxPos[3] = D3DXVECTOR3(m_pos.x + m_fBarWidht / 2.0f, m_pos.y            , 0.0f);

	m_pPolygon->SetVertexPos(vtxPos);
	
	return S_OK;
}

//==================================
// 終了処理
//==================================
void CGauge::Uninit(void)
{
	// ライフの最大数分ポリゴンの終了処理
	if (m_pPolygon != NULL)
	{
		// 終了処理
		m_pPolygon->Uninit();
		// メモリの解放
		delete m_pPolygon;
		m_pPolygon = NULL;
	}

	// 開放処理
	Release();
}

//==================================
// 更新処理
//==================================
void CGauge::Update(void)
{
	// ゲージ高さの計算
	UpdateValue();

	// 頂点座標の設定
	D3DXVECTOR3 vtxPos[NUM_VERTEX];

	vtxPos[0] = D3DXVECTOR3(m_pos.x - m_fBarWidht / 2.0f, m_pos.y - m_fHeight, 0.0f);
	vtxPos[1] = D3DXVECTOR3(m_pos.x + m_fBarWidht / 2.0f, m_pos.y - m_fHeight, 0.0f);
	vtxPos[2] = D3DXVECTOR3(m_pos.x - m_fBarWidht / 2.0f, m_pos.y          , 0.0f);
	vtxPos[3] = D3DXVECTOR3(m_pos.x + m_fBarWidht / 2.0f, m_pos.y          , 0.0f);

	m_pPolygon->SetVertexPos(vtxPos);

	// ポリゴンの更新処理
	if (m_pPolygon != NULL)
	{
		m_pPolygon->Update();
	}
}

//==================================
// 描画処理
//==================================
void CGauge::Draw(void)
{
	// 前パーツ分描画
	if (m_pPolygon != NULL)
	{
		m_pPolygon->Draw();
	}
}

//==================================
// モードのセット
//==================================
void CGauge::SetMode(MODE mode)
{
	if (m_mode == mode) return;

	switch (m_mode)
	{
	case CGauge::MODE_VALUE_AUTO:

		if (mode == MODE_HEIGHT_AUTO)
		{
			// 最大値からの割合
			m_fHeight = m_fBarHeight*(m_fValue / m_fMaxNum);
		}
		break;
	case CGauge::MODE_HEIGHT_AUTO:

		if (mode == MODE_VALUE_AUTO)
		{
			// 最大値からの割合
			m_fValue = m_fMaxNum*(m_fHeight / m_fBarHeight);
		}
		break;
	default:
		break;
	}

	m_mode = mode;
}

//==================================
// ゲージ高さの計算
//==================================
void CGauge::UpdateValue(void)
{
	switch (m_mode)
	{
	case CGauge::MODE_VALUE_AUTO:
		m_fValue += (m_fValueDist - m_fValue)*m_fGaugeRate;
	case CGauge::MODE_VALUE_SELF:
		// 幅の計算
		m_fHeight = m_fBarHeight * (m_fValue) / m_fMaxNum;
	break;

	case CGauge::MODE_HEIGHT_AUTO:
		m_fHeight += (m_fHeightDist - m_fHeight)*m_fGaugeRate;
		break;
	default:
		break;
	}
}
