//=============================================================================
//
// チャージの処理 [charge.cpp]
// Author : 伊藤陽梧
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "charge.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CCharge::m_pTexture = NULL;

//=============================================================================
// チャージクラスのコンストラクタ
//=============================================================================
CCharge::CCharge()
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCountColor = 0;
	m_fSizeX = 0.0f;
	m_fSizeY = 0.0f;
	m_fExtendX = 0.0f;
	m_fExtendY = 0.0f;
	m_fMaxExtendX = 0.0f;
	m_fMaxExtendY = 0.0f;
	m_chargetye = CHARGETYPE_NONE;
}

//=============================================================================
// チャージクラスのデストラクタ
//=============================================================================
CCharge::~CCharge()
{

}

//=============================================================================
// チャージクラスのチャージのテクスチャの読み込み
//=============================================================================
HRESULT CCharge::Load(void)
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
// チャージクラスのチャージのテクスチャの破棄
//=============================================================================
void CCharge::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// チャージクラスのインスタンス生成
//=============================================================================
CCharge* CCharge::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	// CChargeのポインタ
	CCharge *pGauge = NULL;

	// メモリの確保
	pGauge = new CCharge;

	// pGaugeがNULLじゃないとき
	if (pGauge != NULL)
	{
		pGauge->SetCharge(pos, fSizeX, fSizeY);

		// 初期化処理
		pGauge->Init();
	}

	// pGaugeを返す
	return pGauge;
}

//=============================================================================
// チャージクラスの初期化処理
//=============================================================================
HRESULT CCharge::Init()
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
// チャージクラスの終了処理
//=============================================================================
void CCharge::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
// チャージクラスの更新処理
//=============================================================================
void CCharge::Update(void)
{
	// m_fExtendXがm_fMaxExtendXより大きくなったら
	if (m_fExtendX > m_fMaxExtendX)
	{
		m_fExtendX = m_fMaxExtendX;
	}
	// m_fExtendXが0.0fより小さくなったら
	if (m_fExtendX < 0.0f)
	{
		m_fExtendX = 0.0f;
	}

	// VERTEX_2Dのポインタ
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y - (m_fSizeY / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_fExtendX / m_fMaxExtendX) * m_fMaxExtendX, m_pos.y - (m_fSizeY / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y + (m_fSizeY / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_fExtendX / m_fMaxExtendX) * m_fMaxExtendX, m_pos.y + (m_fSizeY / 2), 0.0f);

	// m_fExtendXが0.0f以上92.0fより小さかったら
	if (m_fExtendX >= 0.0f && m_fExtendX < 92.0f)
	{
		pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

		// m_chargetyeの設定
		m_chargetye = CHARGETYPE_NONE;
	}
	// m_fExtendXが92.0f以上184.0fより小さかったら
	if (m_fExtendX >= 92.0f && m_fExtendX < 184.0f)
	{
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

		// m_chargetyeの設定
		m_chargetye = CHARGETYPE_1;
	}
	// m_fExtendXが184.0f以上276.0fより小さかったら
	if (m_fExtendX >= 184.0f && m_fExtendX < 276.0f)
	{
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);

		// m_chargetyeの設定
		m_chargetye = CHARGETYPE_2;
	}
	// m_fExtendXが276.0fだったら
	if (m_fExtendX == 276.0f)
	{
		// m_nCountColorが0の時
		if (m_nCountColor == 0)
		{
			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

			// m_nCountColorの加算
			m_nCountColor++;
		}
		// m_nCountColorが1の時
		else if (m_nCountColor == 1)
		{
			pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

			// m_nCountColorの加算
			m_nCountColor++;
		}
		// m_nCountColorが2の時
		else if (m_nCountColor == 2)
		{
			pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);

			// m_nCountColorの加算
			m_nCountColor++;
		}
		// m_nCountColorが3の時
		else if (m_nCountColor == 3)
		{
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			m_nCountColor = 0;
		}

		// m_chargetyeの設定
		m_chargetye = CHARGETYPE_3;
	}

	//頂点データをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
// チャージクラスの描画処理
//=============================================================================
void CCharge::Draw(void)
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
// チャージクラスのチャージの段階の渡す処理
//=============================================================================
CCharge::CHARGETYPE CCharge::GetChargeType(void)
{
	return m_chargetye;
}

