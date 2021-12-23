////////////////////////////////////////////////////
//
//    ステージ名クラスの処理[chara_select.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//=============================
// インクルード
//=============================
#include "effect_result_explosion.h"
#include "scene2d.h"
#include "resource_texture.h"

//=============================
// マクロ定義
//=============================
#define TEX_ANIM_MAX_X 7           // テクスチャ分割数*横
#define TEX_ANIM_MAX_Y 1           // テクスチャ分割数*縦
#define ANIMATION_INTERVAL 3       // アニメーション間隔
#define RECREATE_ANIM_NUM 3 
#define RECREATE_SIZE_RATE 0.8f

//=============================
// コンストラクタ
//=============================
CResultExplosion::CResultExplosion() :CScene(OBJTYPE_SYSTEM)
{
	// 変数のクリア
	ZeroMemory(&m_apPolygon, sizeof(m_apPolygon));
	m_pos  = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_size = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_nCntAnim = 0;
	m_nTexU = 0;
	m_bReCreate = false;
}

//=============================
// デストラクタ
//=============================
CResultExplosion::~CResultExplosion()
{
}

//=============================
// クリエイト
//=============================
CResultExplosion * CResultExplosion::Create(D3DXVECTOR3 pos , D3DXCOLOR col, D3DXVECTOR3 size)
{
	// メモリの確保
	CResultExplosion *pPointa = new CResultExplosion;
	// 初期化
	pPointa->m_pos = pos;
	pPointa->m_size = size;
	pPointa->Init();
	pPointa->m_bReCreate = true;
	for (int nCnt = 0; nCnt < EFFECT_EXPLOSION_TEX_NUM; nCnt++)
	{
		if (pPointa->m_apPolygon[nCnt] == NULL) continue;
		// カラーの設定
		pPointa->m_apPolygon[nCnt]->SetColor(col);
		
	}
	return pPointa;
}

//=============================
// 初期化処理
//=============================
HRESULT CResultExplosion::Init(void)
{

	D3DXVECTOR2 uv[NUM_VERTEX];
	float fu = 1.0f / TEX_ANIM_MAX_X;
	float fv = 1.0f / TEX_ANIM_MAX_Y;

	uv[0] = D3DXVECTOR2(fu*0.0f      , 0.0f);
	uv[1] = D3DXVECTOR2(fu*0.0f + fu , 0.0f);
	uv[2] = D3DXVECTOR2(fu*0.0f      , 0.0f+ fv);
	uv[3] = D3DXVECTOR2(fu*0.0f + fu , 0.0f+ fv);

	for (int nCnt = 0; nCnt < EFFECT_EXPLOSION_TEX_NUM; nCnt++)
	{
		m_apPolygon[nCnt] = CScene2d::Create();
		m_apPolygon[nCnt]->SetPriority(OBJTYPE_EFFECT_2);
		m_apPolygon[nCnt]->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_RESULT_EXPLOSION));
		m_apPolygon[nCnt]->SetPos( m_pos);
		m_apPolygon[nCnt]->SetSize(m_size);
		m_apPolygon[nCnt]->SetTextureUV(uv);
	}

	m_nCntAnim = 0;
	m_nTexU = 0;
	return S_OK;
}

//=============================
// 終了処理
//=============================
void CResultExplosion::Uninit(void)
{
	// 開放処理
	Release();
}

//=============================
// 更新処理
//=============================
void CResultExplosion::Update(void)
{
	// アニメーション
	m_nCntAnim++;
	if (m_nCntAnim%ANIMATION_INTERVAL == 0)
	{
		m_nTexU++;

		if (m_bReCreate)
		{
			if (m_nTexU == RECREATE_ANIM_NUM)
			{
				CResultExplosion*pEnplosion = CResultExplosion::Create(m_pos, m_apPolygon[0]->GetColor(), m_size*RECREATE_SIZE_RATE);
				pEnplosion->m_bReCreate = false;
			}
		}
		
		if (m_nTexU >= TEX_ANIM_MAX_X)
		{// アニメーション最大時に消す
			Uninit();
			for (int nCnt = 0; nCnt < EFFECT_EXPLOSION_TEX_NUM; nCnt++)
			{
				if (m_apPolygon[nCnt] == NULL) continue;
				m_apPolygon[nCnt]->Uninit();
			}
			return;
		}
	}

	D3DXVECTOR2 uv[NUM_VERTEX];
	float fu = 1.0f / TEX_ANIM_MAX_X;
	float fv = 1.0f / TEX_ANIM_MAX_Y;

	uv[0] = D3DXVECTOR2(fu*m_nTexU     , 0.0f);
	uv[1] = D3DXVECTOR2(fu*m_nTexU + fu, 0.0f);
	uv[2] = D3DXVECTOR2(fu*m_nTexU     , 0.0f + fv);
	uv[3] = D3DXVECTOR2(fu*m_nTexU + fu, 0.0f + fv);

	for (int nCnt = 0; nCnt < EFFECT_EXPLOSION_TEX_NUM; nCnt++)
	{
		if (m_apPolygon[nCnt] == NULL) continue;
		m_apPolygon[nCnt]->SetTextureUV(uv);
	}

}

//=============================
// 描画処理
//=============================
void CResultExplosion::Draw(void)
{
}