//=============================================================================
//
// チャージショットの処理 [chargeshot.cpp]
// Author : 伊藤陽梧
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "chargeshot.h"
#include "charge.h"
#include "gauge.h"
#include "manager.h"
#include "input.h"
#include "renderer.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CChargeshot::m_pTexture = NULL;

//=============================================================================
// チャージショットクラスのコンストラクタ
//=============================================================================
CChargeshot::CChargeshot() :CScene(OBJTYPE_GAUGE)
{
	pGauge = NULL;
	pCharge = NULL;
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// チャージショットクラスのデストラクタ
//=============================================================================
CChargeshot::~CChargeshot()
{

}

//=============================================================================
// チャージショットクラスのテクスチャの読み込み
//=============================================================================
HRESULT CChargeshot::Load(void)
{
	// インスタンス生成したものを受け取る
	CRenderer *pRenderer = CManager::GetRenderer();

	// デバイスを受け取る
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_GAUGE, &m_pTexture);

	return S_OK;
}

//=============================================================================
// チャージショットクラスのテクスチャの破棄
//=============================================================================
void CChargeshot::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// チャージショットクラスのインスタンス生成
//=============================================================================
CChargeshot * CChargeshot::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CHARGESHOTTYPE chargeshottype, OBJTYPE objType)
{
	// CChargeshotのポインタ
	CChargeshot *pChargeshot = NULL;

	// メモリの確保
	pChargeshot = new CChargeshot;

	// pChargeshotがNULLじゃないとき
	if (pChargeshot != NULL)
	{
		// チャージショットのセット
		pChargeshot->SetChargeShot(pos, size, chargeshottype, objType);

		// 初期化処理
		pChargeshot->Init();
	}

	// pChargeshotを返す
	return pChargeshot;
}

//=============================================================================
// チャージショットクラスのデストラクタ
//=============================================================================
HRESULT CChargeshot::Init()
{
	SetObjType(OBJTYPE_GAUGE);

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
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点データをアンロックする
	m_pVtxBuff->Unlock();

	// ゲージとチャージの生成
	pGauge = CGauge::Create(D3DXVECTOR3(m_pos.x - 136.0f, m_pos.y, 0.0f), D3DXVECTOR3(0.0f, m_size.y, 0.0f));
	pCharge = CCharge::Create(D3DXVECTOR3(m_pos.x - 136.0f, m_pos.y, 0.0f), D3DXVECTOR3(100.0f, m_size.y, 0.0f));

	return S_OK;
}

//=============================================================================
// チャージショットクラスのデストラクタ
//=============================================================================
void CChargeshot::Uninit(void)
{
	// pGaugeがNULLじゃないとき
	if (pGauge != NULL)
	{
		// pGaugeの終了処理
		pGauge->Uninit();
	}

	// pChargeがNULLじゃないとき
	if (pCharge != NULL)
	{
		// pChargeの終了処理
		pCharge->Uninit();
	}

	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	Release();
}

//=============================================================================
// チャージショットクラスのデストラクタ
//=============================================================================
void CChargeshot::Update(void)
{
	// CInputのポインタのインスタンス生成の受け取り
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	CInputJoypad *pInputJoypad = CManager::GetInputJoypad();

	// VERTEX_2Dのポインタ
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2), m_pos.y - (m_size.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y - (m_size.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);

	//頂点データをアンロックする
	m_pVtxBuff->Unlock();

	// pGaugeがNULLじゃないとき
	if (pGauge != NULL)
	{
		// pGaugeの更新処理
		pGauge->Update();
	}

	// pChargeがNULLじゃないとき
	if (pCharge != NULL)
	{
		// pChargeの更新処理
		pCharge->Update();
	}
}

//=============================================================================
// チャージショットクラスのデストラクタ
//=============================================================================
void CChargeshot::Draw(void)
{
	// pGaugeがNULLじゃないとき
	if (pGauge != NULL)
	{
		// pGaugeの描画処理
		pGauge->Draw();
	}

	// pChargeがNULLじゃないとき
	if (pCharge != NULL)
	{
		// pChargeの描画処理
		pCharge->Draw();
	}

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
// チャージショットクラスのゲージのポインタを返す処理
//=============================================================================
CGauge* CChargeshot::GetGauge(void)
{
	return pGauge;
}

//=============================================================================
// チャージショットクラスのチャージのポインタを返す処理
//=============================================================================
CCharge * CChargeshot::GetCharge(void)
{
	return pCharge;
}
