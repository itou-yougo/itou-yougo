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
	m_pfData = NULL;
	m_frontCol = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
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
CGauge * CGauge::Create(float * pData, D3DXVECTOR3 leftPos, float fBarWidht, float fBarHeight, float fMaxNum, D3DXCOLOR frontCol)
{
	// メモリの確保
	CGauge *pGage;
	pGage = new CGauge;

	// 引数の代入
	pGage->m_pos = leftPos;             // 左端
	pGage->m_fBarWidht = fBarWidht;     // 幅
	pGage->m_fBarHeight = fBarHeight;   // 高さ
	pGage->m_fMaxNum = fMaxNum;         // 最大数
	pGage->m_pfData = pData;            // ゲージと紐づける数値のポインタ
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

	// 頂点座標の設定
	D3DXVECTOR3 vtxPos[NUM_VERTEX];

	vtxPos[0] = D3DXVECTOR3(m_pos.x - m_fBarWidht / 2.0f, m_pos.y - *m_pfData, 0.0f);
	vtxPos[1] = D3DXVECTOR3(m_pos.x + m_fBarWidht / 2.0f, m_pos.y - *m_pfData, 0.0f);
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
	// 幅の計算
	float fHeight = 0.0f;
	// 幅の計算
	fHeight = m_fBarHeight * *m_pfData / m_fMaxNum;

	// 頂点座標の設定
	D3DXVECTOR3 vtxPos[NUM_VERTEX];

	vtxPos[0] = D3DXVECTOR3(m_pos.x - m_fBarWidht / 2.0f, m_pos.y - fHeight, 0.0f);
	vtxPos[1] = D3DXVECTOR3(m_pos.x + m_fBarWidht / 2.0f, m_pos.y - fHeight, 0.0f);
	vtxPos[2] = D3DXVECTOR3(m_pos.x - m_fBarWidht / 2.0f, m_pos.y          , 0.0f);
	vtxPos[3] = D3DXVECTOR3(m_pos.x + m_fBarWidht / 2.0f, m_pos.y          , 0.0f);

	m_pPolygon->SetVertexPos(vtxPos);

	// ポリゴンの最大数分更新処理
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