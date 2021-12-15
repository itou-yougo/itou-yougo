//=============================================================================
//
// スキルサークル処理 [skill_circle.cpp]
// Author : 齋藤大行
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "base_Cylinder.h"
#include "manager.h"
#include "renderer.h"
#include "resource_texture.h"
#include "particle.h"
//=============================================================================
//静的メンバー変数
//=============================================================================

//=============================================================================
//コンストラクタ
//=============================================================================
Cbase_Cylinder::Cbase_Cylinder(int nPriority) :CScene(nPriority)
{
	m_apTexture = NULL;
	m_pVtxBuff = NULL;									  
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				  
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				  
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				  
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			  
	m_nLife = 500;										  
	m_fRotAngle = 0.0f;									  
	m_fFadeout = 0.0f;									  
	m_bFadeoutFlag = true;								  
	m_col = { 1.0f,0.0f,0.0f,1.0f };				  
	m_mtxWorld = {};									  
	m_bAddMode = false;
	m_fHighRot = 0.0f;
	m_fRowRot = 0.0f;
}


//=============================================================================
//デストラクタ
//=============================================================================
Cbase_Cylinder::~Cbase_Cylinder()
{
}

//=============================================================================
//生成処理関数
//=============================================================================
Cbase_Cylinder * Cbase_Cylinder::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXCOLOR col)
{
	// メモリの確保
	Cbase_Cylinder *pbase_Cylinder;
	pbase_Cylinder = new Cbase_Cylinder;
	

	// 引数の代入
	pbase_Cylinder->m_pos = D3DXVECTOR3(pos.x,pos.y + size.y,pos.z);
	pbase_Cylinder->m_size = size;
	pbase_Cylinder->m_col = col;
	// 初期化
	pbase_Cylinder->Init();
	
	return pbase_Cylinder;
}


//=============================================================================
//初期化処理関数
//=============================================================================
HRESULT Cbase_Cylinder::Init(void)
{
	VERTEX_3D *pVtx;// 頂点情報ポインタ

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*NUM_CYL_VERTEX * 2, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	// メンバ変数の初期化

	m_rot = { 0.0f,0.0f,0.0f };

	//ロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < NUM_CYL_VERTEX; nCnt++)
	{	// 頂点座標の設定
		FLOAT theta = (2 * D3DX_PI * nCnt) / (NUM_CYL_VERTEX - 1);
		
		pVtx[2 * nCnt + 0].pos = D3DXVECTOR3(sinf(theta), -1.0f, cosf(theta));
		pVtx[2 * nCnt + 1].pos = D3DXVECTOR3(sinf(theta),  1.0f, cosf(theta));
		// テクスチャUV座標の設定
		pVtx[2 * nCnt + 0].tex = D3DXVECTOR2(((FLOAT)nCnt) / (NUM_CYL_VERTEX - 1), 0.0f);
		pVtx[2 * nCnt + 1].tex = D3DXVECTOR2(((FLOAT)nCnt) / (NUM_CYL_VERTEX - 1), 1.0f);
	}

	for (int nCnt = 0; nCnt < NUM_CYL_VERTEX * 2; nCnt++)
	{
		// 色の設定
		pVtx[nCnt].col = m_col;
		// 法線
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}

	// アンロック
	m_pVtxBuff->Unlock();

	

	return S_OK;
}


//=============================================================================
//終了処理関数
//=============================================================================
void Cbase_Cylinder::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	Release();
}

//=============================================================================
//更新処理関数
//=============================================================================
void Cbase_Cylinder::Update(void)
{
}

//=============================================================================
//描画処理関数
//=============================================================================
void Cbase_Cylinder::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans, mtxScail;//行列計算用マトリクス
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);// カリング

	//アルファテスト基準値の設定
	pDevice->SetRenderState(D3DRS_ALPHAREF, 20);

	// 加算モードの時
	if (m_bAddMode)
	{
		// 加算合成
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}

	// マトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixIdentity(&mtxRot);
	D3DXMatrixIdentity(&mtxTrans);
	D3DXMatrixIdentity(&mtxScail);

	////サイズ
	D3DXMatrixScaling(&mtxScail, 1.0f, 1.0f, 1.0f);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScail);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x , m_pos.y , m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetTexture(0, m_apTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0,  2 * NUM_CYL_VERTEX - 2);
	
	// テクスチャの初期化
	pDevice->SetTexture(0, 0);

	//アルファテスト基準値の設定
	pDevice->SetRenderState(D3DRS_ALPHAREF, 1);

	// 加算モードの時
	if (m_bAddMode)
	{
		// 通常合成に戻す
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);           // カリング
  
}

//=============================================================================
// 座標のセット
//=============================================================================
void Cbase_Cylinder::SetPos(const D3DXVECTOR3 pos)
{

	VERTEX_3D *pVtx;// 頂点情報ポインタ

	//posの代入
	m_pos = pos;

	// ロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < NUM_CYL_VERTEX; nCnt++)
	{	// 頂点座標の設定
		FLOAT theta = (2 * D3DX_PI * nCnt) / (NUM_CYL_VERTEX - 2);

		pVtx[2 * nCnt + 0].pos = D3DXVECTOR3(sinf(theta) * (float)+(m_size.x / 2.0f) * (m_fHighRot + m_fRotAngle), + m_size.y , cosf(theta) * ((float)m_size.z / 2.0f)* (m_fHighRot + m_fRotAngle));
		pVtx[2 * nCnt + 1].pos = D3DXVECTOR3(sinf(theta) * (float)+(m_size.x / 2.0f) *  m_fRowRot, - m_size.y , cosf(theta) * ((float)m_size.z / 2.0f)* m_fRowRot);
    }

	// アンロック
	m_pVtxBuff->Unlock();
}

//=============================================================================
// サイズのセット
//=============================================================================
void Cbase_Cylinder::SetSize(const D3DXVECTOR3 size)
{
	m_size = size;

	// 頂点座標の再設定
	SetPos(m_pos);
}
//=============================================================================
// 色のセット
//=============================================================================
void Cbase_Cylinder::SetColor(const D3DXCOLOR col)
{
	VERTEX_3D *pVtx;// 頂点情報ポインタ

	//色の代入
	m_col = col;

	// ロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < NUM_CYL_VERTEX * 2; nCnt++)
	{	// 色の設定
		pVtx[nCnt].col = m_col;
	}
	// アンロック
	m_pVtxBuff->Unlock();
}
//=============================================================================
// 座標のセット
//=============================================================================
void Cbase_Cylinder::SetTextureUV(const float pos)
{
	VERTEX_3D *pVtx;// 頂点情報ポインタ

	// ロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < NUM_CYL_VERTEX * 2; nCnt++)
	{
		pVtx[2 * nCnt + 0].tex = D3DXVECTOR2(((FLOAT)nCnt) / (NUM_CYL_VERTEX - 1) + pos, 0.0f);
		pVtx[2 * nCnt + 1].tex = D3DXVECTOR2(((FLOAT)nCnt) / (NUM_CYL_VERTEX - 1) + pos, 1.0f);
	}
	// アンロック
	m_pVtxBuff->Unlock();

}










