////////////////////////////////////////////////////
//
//    dynamic_tectureの処理[dynamic_tecture.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "dynamic_texture.h"
#include "manager.h"
#include "renderer.h"

//******************************
// マクロ定義
//******************************

//******************************
// コンストラクタ
//******************************
CDynamicTexture::CDynamicTexture()
{
	// 変数のクリア
	m_pTexture = NULL;		//テクスチャ
	m_pTexz = NULL;			//テクスチャの深度バッファ
	m_pTexSurface = NULL;	//テクスチャへアクセスする為のインターフェース
	m_pBackz = NULL;		//バックバッファの深度バッファ
	m_pBackSurface = NULL;	//バックバッファへアクセスする為の
	ZeroMemory( &m_proj, sizeof(m_proj));		// 射影行列
	ZeroMemory( &m_view, sizeof(m_view));		// ビュー行列
	ZeroMemory(&m_saveViewport, sizeof(m_saveViewport)); // 保存用ビューポート
	m_size = { 0.0f,0.0f };
}

//******************************
// デストラクタ
//******************************
CDynamicTexture::~CDynamicTexture()
{
}

//******************************
// クリエイト
//******************************
CDynamicTexture * CDynamicTexture::Create(D3DXVECTOR2 size)
{

	CDynamicTexture *pMulltipath = new CDynamicTexture;
	pMulltipath->Init(size);

	return pMulltipath;
}


//******************************
// 初期化処理
//******************************
HRESULT CDynamicTexture::Init(D3DXVECTOR2 size)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	m_size = size;
	//新規テクスチャ作成*****************************
	pDevice->CreateTexture((UINT)m_size.x, (UINT)m_size.y,
		8,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&m_pTexture,
		NULL);

	//新規テクスチャの深度バッファ作成***************
	pDevice->CreateDepthStencilSurface(
        (UINT)m_size.x, (UINT)m_size.y,
		D3DFMT_D16,
		D3DMULTISAMPLE_NONE,
		0,
		TRUE,
		&m_pTexz,
		NULL);

	//新規テクスチャへのインターフェース取得*********
	m_pTexture->GetSurfaceLevel(0, &m_pTexSurface);

	//バックバッファの情報を保存*********************
	pDevice->GetViewport(&m_saveViewport);
	pDevice->GetRenderTarget(0, &m_pBackSurface);
	pDevice->GetDepthStencilSurface(&m_pBackz);

	//レンダリングターゲット変更*******************************
	pDevice->SetRenderTarget(0, m_pTexSurface);
	pDevice->GetDepthStencilSurface(&m_pTexz);

	//変更したレンダリングターゲットのバッファなどをクリア*****
	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_RGBA(255, 255, 255, 0), 1.0f, 0);


	//レンダリングターゲットを元（バックバッファ）に戻す****
	pDevice->SetRenderTarget(0, m_pBackSurface);
	pDevice->SetDepthStencilSurface(m_pBackz);

	return S_OK;
}

//******************************
// 終了処理
//******************************
void CDynamicTexture::Uninit(void)
{
	if (m_pBackSurface != NULL)
	{
		m_pBackSurface->Release();
		m_pBackSurface = NULL;
	}
	if (m_pBackz != NULL)
	{
		m_pBackz->Release();
		m_pBackz = NULL;
	}
	if (m_pTexSurface != NULL)
	{
		m_pTexSurface->Release();
		m_pTexSurface = NULL;
	}
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
	if (m_pTexz != NULL)
	{
		m_pTexz->Release();
		m_pTexz = NULL;
	}
}

//******************************
// テクスチャに描画開始
//******************************
void CDynamicTexture::Begin(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//バックバッファの情報を保存*******************************
	pDevice->GetRenderTarget(0, &m_pBackSurface);
	pDevice->GetDepthStencilSurface(&m_pBackz);

	//ビューポートを保存***************************************
	pDevice->GetViewport(&m_saveViewport);

	// ビュー、プロジェクションマトリックスの保存**************
	pDevice->GetTransform(D3DTS_PROJECTION, &m_proj);
	pDevice->GetTransform(D3DTS_VIEW, &m_view);

	//レンダリングターゲット変更*******************************
	pDevice->SetRenderTarget(0, m_pTexSurface);
	pDevice->SetDepthStencilSurface(m_pTexz);

	//変更したレンダリングターゲットのバッファなどをクリア*****
	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_RGBA(255, 255, 255, 0), 1.0f, 0);

	//ビューポートをセット*************************************
	D3DVIEWPORT9 viewport2 = { 0, 0, (DWORD)m_size.x, (DWORD)m_size.y, 0.0f, 1.0f };
	pDevice->SetViewport(&viewport2);
}

//******************************
// テクスチャに描画終了
//******************************
void CDynamicTexture::End(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//レンダリングターゲットを元（バックバッファ）に戻す*******
	pDevice->SetRenderTarget(0, m_pBackSurface);
	pDevice->SetDepthStencilSurface(m_pBackz);

	//ビューポートを戻す***************************************
	pDevice->SetViewport(&m_saveViewport);

	// ビュー、プロジェクションマトリックスを戻す**************
	pDevice->SetTransform(D3DTS_PROJECTION, &m_proj);
	pDevice->SetTransform(D3DTS_VIEW, &m_view);
}
