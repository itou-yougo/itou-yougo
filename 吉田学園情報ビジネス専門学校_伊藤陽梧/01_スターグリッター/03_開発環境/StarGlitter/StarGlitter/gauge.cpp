//=============================================================================
//
// ゲージの処理 [gauge.cpp]
// Author : 伊藤陽梧
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "gauge.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CGauge::m_pTexture = NULL;

//=============================================================================
// ゲージクラスのコンストラクタ
//=============================================================================
CGauge::CGauge()
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fExtendX = 0.0f;
	m_fExtendY = 0.0f;
	m_fMaxExtendX = MAX_GAUGE_EXTEND;
	m_fMaxExtendY = 0.0f;
}

//=============================================================================
// ゲージクラスのデストラクタ
//=============================================================================
CGauge::~CGauge()
{

}

//=============================================================================
// ゲージクラスのテクスチャの読み込み
//=============================================================================
HRESULT CGauge::Load(void)
{
	// インスタンス生成したものを受け取る
	CRenderer *pRenderer = CManager::GetRenderer();

	// デバイスを受け取る
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "", &m_pTexture);

	return S_OK;
}

//=============================================================================
// ゲージクラスのテクスチャの破棄
//=============================================================================
void CGauge::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// ゲージクラスのインスタンス生成
//=============================================================================
CGauge* CGauge::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CGaugeのポインタ
	CGauge *pGauge = NULL;

	// メモリの確保
	pGauge = new CGauge;

	// pGaugeがNULLじゃないとき
	if (pGauge != NULL)
	{
		pGauge->SetGauge(pos, size);

		// 初期化処理
		pGauge->Init();
	}

	// pGaugeを返す
	return pGauge;
}

//=============================================================================
// ゲージクラスの初期化処理
//=============================================================================
HRESULT CGauge::Init()
{
	// VERTEX_2Dのポインタ
	VERTEX_2D *pVtx;

	// インスタンス生成したものを受け取る
	CRenderer *pRenderer = CManager::GetRenderer();

	// デバイスを受け取る
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 頂点バッファ生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);

	// rhwの設定(値は1.0で固定)
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定(0～255の範囲で設定)
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点データをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// ゲージクラスの終了処理
//=============================================================================
void CGauge::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
// ゲージクラスの更新処理
//=============================================================================
void CGauge::Update(void)
{
	// m_fExtendXがm_fMaxExtendXより大きくならないようにする
	if (m_fExtendX > m_fMaxExtendX)
	{
		m_fExtendX = m_fMaxExtendX;
	}

	// m_fMaxExtendXがMAX_GAUGE_EXTENDより大きくならないようにする
	if (m_fMaxExtendX > MAX_GAUGE_EXTEND)
	{
		m_fMaxExtendX = MAX_GAUGE_EXTEND;
	}

	// VERTEX_2Dのポインタ
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y - (m_size.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fMaxExtendX, m_pos.y - (m_size.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y + (m_size.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fMaxExtendX, m_pos.y + (m_size.y / 2), 0.0f);

	// 頂点カラーの設定(0～255の範囲で設定)
	pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	//頂点データをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
// ゲージクラスの描画処理
//=============================================================================
void CGauge::Draw(void)
{
	// インスタンス生成したものを受け取る
	CRenderer *pRenderer = CManager::GetRenderer();

	// デバイスを受け取る
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// ゲージクラスのゲージの最大値を返す処理
//=============================================================================
float CGauge::GetMaxExtend(void)
{
	return m_fMaxExtendX;
}

