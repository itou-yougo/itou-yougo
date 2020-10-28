//=============================================================================
//
// ライフポリゴンの処理 [lifepolygon.cpp]
// Author : 伊藤陽梧
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "lifepolygon.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CLifepolygon::m_pTexture = NULL;

//=============================================================================
// ライフポリゴンクラスのコンストラクタ
//=============================================================================
CLifepolygon::CLifepolygon()
{
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fSizeX = 0.0f;
	m_fSizeY = 0.0f;
}

//=============================================================================
// ライフポリゴンクラスのデストラクタ
//=============================================================================
CLifepolygon::~CLifepolygon()
{

}

//=============================================================================
// ライフポリゴンクラスのテクスチャ読み込み
//=============================================================================
HRESULT CLifepolygon::Load(void)
{
	// インスタンス生成したものを受け取る
	CRenderer *pRenderer = CManager::GetRenderer();

	// デバイスを受け取る
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの読み込み
	HRESULT hr = D3DXCreateTextureFromFile(pDevice, TEXTURE_LIFE, &m_pTexture);

	return S_OK;
}

//=============================================================================
// ライフポリゴンクラスのテクスチャ破棄
//=============================================================================
void CLifepolygon::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// ライフポリゴンクラスのインスタンス生成
//=============================================================================
CLifepolygon * CLifepolygon::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nDivide, int nCount)
{
	// CLifepolygonのポインタ
	CLifepolygon *pLifepolygon = NULL;

	// メモリの確保
	pLifepolygon = new CLifepolygon;

	// pLifepolygonがNULLじゃないとき
	if (pLifepolygon != NULL)
	{
		// 初期化処理
		pLifepolygon->Init();

		// ライフポリゴンのセット
		pLifepolygon->SetLifePolygon(nDivide, nCount);
		pLifepolygon->SetPosition(pos);
		pLifepolygon->SetSize(fSizeX, fSizeY);
	}

	// pLifepolygonを返す
	return pLifepolygon;
}

//=============================================================================
// ライフポリゴンクラスの初期化処理
//=============================================================================
HRESULT CLifepolygon::Init()
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


	return S_OK;
}

//=============================================================================
// ライフポリゴンクラスの終了処理
//=============================================================================
void CLifepolygon::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
// ライフポリゴンクラスの更新処理
//=============================================================================
void CLifepolygon::Update(void)
{
	// VERTEX_2Dのポインタ
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - (m_fSizeX / 2), m_pos.y - (m_fSizeY / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_fSizeX / 2), m_pos.y - (m_fSizeY / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (m_fSizeX / 2), m_pos.y + (m_fSizeY / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_fSizeX / 2), m_pos.y + (m_fSizeY / 2), 0.0f);

	//頂点データをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
// ライフポリゴンクラスの描画処理
//=============================================================================
void CLifepolygon::Draw(void)
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
// ライフポリゴンクラスのテクスチャの処理
//=============================================================================
void CLifepolygon::SetLifePolygon(int nDivide, int nCount)
{
	// VERTEX_2Dのポインタ
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0); // この書式は変えないこと

	// テクスチャの座標
	pVtx[0].tex = D3DXVECTOR2((float)(1.0f / nDivide)* nCount, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((float)(1.0f / nDivide)* (nCount + 1), 0.0f);
	pVtx[2].tex = D3DXVECTOR2((float)(1.0f / nDivide)* nCount, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((float)(1.0f / nDivide)* (nCount + 1), 1.0f);

	// 頂点データアンロック
	m_pVtxBuff->Unlock();
}
