//=============================================================================
//
// ポリゴンの描画の処理 [scene2d.h]
// Author : 伊藤陽梧
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include"main.h"
#include"scene.h"
#include"scene2d.h"
#include"renderer.h"
#include"manager.h"
#include"input.h"

//=============================================================================
// オブジェクトクラスのコンストラクタ
//=============================================================================
CScene2D::CScene2D(int nPriority) :CScene(nPriority)
{
	m_pTexture = NULL;					   // テクスチャへのポインタ
	m_pVtxBuff = NULL;					   // 頂点バッファへのポインタ
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); // ポリゴンの位置
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	m_nGetCounterAnim = 0;
	m_nGetPatternAnim = 0;
	m_nTimeAnim = 0;
	m_nTimeCount = 0;
	m_nRed = 0;
	m_nGreen = 0;
	m_nBrue = 0;
	m_nAlpha = 0;
	m_bTransparency = false;
	m_bTransparencyUse = false;
	m_fScrollX = 0.0f;
	m_fScrollY = 0.0f;
	m_fGetScrollMoveX = 0.0f;
	m_fGetScrollMoveY = 0.0f;
	m_AnimationType = TYPE_NONE;
}

//=============================================================================
// オブジェクトクラスのデストラクタ
//=============================================================================
CScene2D::~CScene2D()
{

}

//=============================================================================
// オブジェクトクラスのインスタンス生成
//=============================================================================
CScene2D *CScene2D::Create()
{
	// CScene2Dのポインタ
	CScene2D *pScene2D = NULL;

	// メモリの確保
	pScene2D = new CScene2D;

	// pScene2DがNULLじゃないとき
	if (pScene2D != NULL)
	{
		// 初期化処理
		pScene2D->Init();
	}

	// pScene2Dを返す
	return pScene2D;
}

//=============================================================================
// オブジェクトクラスのテクスチャの受け取り
//=============================================================================
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 Texture)
{
	m_pTexture = Texture;
}

//=============================================================================
// オブジェクトクラスの初期化処理
//=============================================================================
HRESULT CScene2D::Init()
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
// オブジェクトクラスの終了処理
//=============================================================================
void CScene2D::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//オブジェクトの破棄
	Release();
}

//=============================================================================
// オブジェクトクラスの更新処理
//=============================================================================
void CScene2D::Update(void)
{
	//// VERTEX_2Dのポインタ
	//VERTEX_2D *pVtx;

	//// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
 //	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//// 頂点情報を設定
	//pVtx[0].pos = D3DXVECTOR3(m_pos.x - (m_fSizeX / 2), m_pos.y - (m_fSizeY / 2), 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_fSizeX / 2), m_pos.y - (m_fSizeY / 2), 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(m_pos.x - (m_fSizeX / 2), m_pos.y + (m_fSizeY / 2), 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_fSizeX / 2), m_pos.y + (m_fSizeY / 2), 0.0f);

	////頂点データをアンロックする
	//m_pVtxBuff->Unlock();

	switch (m_AnimationType)
	{
	case TYPE_ANIMATION:
		UpdateAnimation();
		break;

	case TYPE_ANIMATIONSELECT:
		UpdateAnimationSelect();
		break;

	case TYPE_SCROLL:
		UpdateScroll();
		break;

	case TYPE_TRANSPARENCY:
		UpdateTransparency();
		break;

	case TYPE_COLOR:
		UpdateColor();
		break;

	default:
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
		break;
	}

}

//=============================================================================
// オブジェクトクラスの描画処理
//=============================================================================
void CScene2D::Draw(void)
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

	pDevice->SetTexture(0, NULL);
}

//=============================================================================
// オブジェクトクラスの座標の受け渡し
//=============================================================================
D3DXVECTOR3 CScene2D::GetPosition(void)
{
	// m_posを返す
	return m_pos;
}

//=============================================================================
// オブジェクトクラスのサイズの受け渡し
//=============================================================================
D3DXVECTOR3 CScene2D::GetSize(void)
{
	// m_sizeを返す
	return m_size;
}

//=============================================================================
// オブジェクトクラスのアニメーションの設定
//=============================================================================
void CScene2D::UpdateAnimation()
{
	// VERTEX_2Dのポインタ
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

  	if (m_nTimeCount == m_nTimeAnim)
	{
		m_nCounterAnim++;

		if (m_nCounterAnim % m_nGetCounterAnim == 0)
		{
			m_nCounterAnim = 0;
			m_nPatternAnim++;
			if (m_nPatternAnim % m_nGetPatternAnim == 0)
			{
				m_nPatternAnim = 0;
			}
		}

		// 頂点情報を設定
		pVtx[0].tex = D3DXVECTOR2((float)(1.0f / m_nGetCounterAnim)* m_nCounterAnim, (float)(1.0f / m_nGetPatternAnim)* m_nPatternAnim);
		pVtx[1].tex = D3DXVECTOR2((float)(1.0f / m_nGetCounterAnim)* (m_nCounterAnim + 1), (float)(1.0f / m_nGetPatternAnim)* m_nPatternAnim);
		pVtx[2].tex = D3DXVECTOR2((float)(1.0f / m_nGetCounterAnim)* m_nCounterAnim, (float)(1.0f / m_nGetPatternAnim)* (m_nPatternAnim + 1));
		pVtx[3].tex = D3DXVECTOR2((float)(1.0f / m_nGetCounterAnim)* (m_nCounterAnim + 1), (float)(1.0f / m_nGetPatternAnim)* (m_nPatternAnim + 1));

		m_nTimeCount = 0;
	}
	m_nTimeCount++;

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2), m_pos.y - (m_size.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y - (m_size.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);

	//頂点データをアンロックする
	m_pVtxBuff->Unlock();

	//頂点データをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
// オブジェクトクラスの任意で変えられるアニメーションの設定
//=============================================================================
void CScene2D::UpdateAnimationSelect()
{
	// VERTEX_2Dのポインタ
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (m_nTimeCount == m_nTimeAnim)
	{
		m_nCounterAnim++;

		if (m_nCounterAnim % m_nGetCounterAnim == 0)
		{
			m_nCounterAnim = 0;
		}

		// 頂点情報を設定
		pVtx[0].tex = D3DXVECTOR2((float)(1.0f / m_nGetCounterAnim)* m_nCounterAnim, (float)(1.0f / m_nGetPatternAnim)* m_nPatternAnim);
		pVtx[1].tex = D3DXVECTOR2((float)(1.0f / m_nGetCounterAnim)* (m_nCounterAnim + 1), (float)(1.0f / m_nGetPatternAnim)* m_nPatternAnim);
		pVtx[2].tex = D3DXVECTOR2((float)(1.0f / m_nGetCounterAnim)* m_nCounterAnim, (float)(1.0f / m_nGetPatternAnim)* (m_nPatternAnim + 1));
		pVtx[3].tex = D3DXVECTOR2((float)(1.0f / m_nGetCounterAnim)* (m_nCounterAnim + 1), (float)(1.0f / m_nGetPatternAnim)* (m_nPatternAnim + 1));
		
		m_nTimeCount = 0;
	}
	m_nTimeCount++;

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2), m_pos.y - (m_size.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y - (m_size.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);

	//頂点データをアンロックする
	m_pVtxBuff->Unlock();

	//頂点データをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
// オブジェクトクラスのスクロールの設定
//=============================================================================
void CScene2D::UpdateScroll()
{
	// VERTEX_2Dのポインタ
	VERTEX_2D *pVtx;

	// 受け取った速さ分加算
	m_fScrollX += m_fGetScrollMoveX;
	m_fScrollY += m_fGetScrollMoveY;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2), m_pos.y - (m_size.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y - (m_size.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);

	// 頂点情報を設定
	pVtx[0].tex = D3DXVECTOR2(m_fScrollX, m_fScrollY);
	pVtx[1].tex = D3DXVECTOR2(m_fScrollX + 1.0f, m_fScrollY);
	pVtx[2].tex = D3DXVECTOR2(m_fScrollX, m_fScrollY + 0.5f);
	pVtx[3].tex = D3DXVECTOR2(m_fScrollX + 1.0f, m_fScrollY + 0.5f);

	//頂点データをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
// オブジェクトクラスの透明化の設定
//=============================================================================
void CScene2D::UpdateTransparency()
{
	// VERTEX_2Dのポインタ
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2), m_pos.y - (m_size.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y - (m_size.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);

	// 透明にするのを使うかどうか
	if (m_bTransparencyUse)
	{
		// 透明にする
		if (!m_bTransparency)
		{
			// 頂点カラーの設定(0～255の範囲で設定)
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			m_bTransparency = true;
		}
		else if (m_bTransparency)
		{
			// 頂点カラーの設定(0～255の範囲で設定)
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 0);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 0);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 0);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 0);
			m_bTransparency = false;
		}
	}
	else if (!m_bTransparencyUse)
	{
		// 頂点カラーの設定(0～255の範囲で設定)
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	//頂点データをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
// オブジェクトクラスの色の設定
//=============================================================================
void CScene2D::UpdateColor()
{
	// VERTEX_2Dのポインタ
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2), m_pos.y - (m_size.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y - (m_size.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);

	// 頂点カラーの設定(0～255の範囲で設定)
	pVtx[0].col = D3DCOLOR_RGBA(m_nRed, m_nGreen, m_nBrue, m_nAlpha);
	pVtx[1].col = D3DCOLOR_RGBA(m_nRed, m_nGreen, m_nBrue, m_nAlpha);
	pVtx[2].col = D3DCOLOR_RGBA(m_nRed, m_nGreen, m_nBrue, m_nAlpha);
	pVtx[3].col = D3DCOLOR_RGBA(m_nRed, m_nGreen, m_nBrue, m_nAlpha);

	//頂点データをアンロックする
	m_pVtxBuff->Unlock();
}

