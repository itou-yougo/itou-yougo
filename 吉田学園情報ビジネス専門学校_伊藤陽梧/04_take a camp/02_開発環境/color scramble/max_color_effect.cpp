////////////////////////////////////////////////////
//
//    max_color_effectの処理[max_color_effect.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//=============================
// インクルード
//=============================
#include "max_color_effect.h"
#include "scene3d.h"
#include "tile.h"
#include "manager.h"
#include "renderer.h"
#include "resource_texture.h"

//=============================
// マクロ定義
//=============================

//=============================
// 静的メンバ変数宣言
//=============================
#define LIFE_FRAME 60
#define ALPHA_RATE 0.05f

//=============================
// コンストラクタ
//=============================
CMaxColorEffect::CMaxColorEffect() : CScene(OBJTYPE_EFFECT)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_polygonColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	ZeroMemory(&m_apPolygon, sizeof(m_apPolygon));
	m_nCntLife = 0;
	m_fTexV = -1.0f;
	m_distColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

//=============================
// デストラクタ
//=============================
CMaxColorEffect::~CMaxColorEffect()
{
}

//=============================
// クリエイト
//=============================
CMaxColorEffect * CMaxColorEffect::Create(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	// メモリの確保
	CMaxColorEffect *pEffect = new CMaxColorEffect;
	// 座標
	pEffect->m_pos = pos;
	// カラー
	pEffect->m_polygonColor = col;
	// 初期化
	pEffect->Init();

	return pEffect;
}

//=============================
// 初期化処理
//=============================
HRESULT CMaxColorEffect::Init(void)
{
	// 寿命の初期化
	m_nCntLife = 0;
	m_polygonColor.a = 0.0f;
	m_fTexV = -1.0f;

	const D3DXVECTOR3 polygonPos[MAX_COLOR_EFFECT_POLYGON_NUM] =
	{
		D3DXVECTOR3(m_pos.x                    ,m_pos.y + TILE_SIZE_Y*1.5f,m_pos.z - TILE_ONE_SIDE / 2),
		D3DXVECTOR3(m_pos.x - TILE_ONE_SIDE / 2,m_pos.y + TILE_SIZE_Y*1.5f,m_pos.z),
		D3DXVECTOR3(m_pos.x + TILE_ONE_SIDE / 2,m_pos.y + TILE_SIZE_Y*1.5f,m_pos.z),
		D3DXVECTOR3(m_pos.x                    ,m_pos.y + TILE_SIZE_Y*1.5f,m_pos.z + TILE_ONE_SIDE / 2),
	};
	const D3DXVECTOR3 polygonSize[MAX_COLOR_EFFECT_POLYGON_NUM] =
	{
		D3DXVECTOR3(TILE_ONE_SIDE ,TILE_ONE_SIDE, 0.0f),
		D3DXVECTOR3(0.0f          ,TILE_ONE_SIDE, TILE_ONE_SIDE),
		D3DXVECTOR3(0.0f          ,TILE_ONE_SIDE, TILE_ONE_SIDE),
		D3DXVECTOR3(TILE_ONE_SIDE ,TILE_ONE_SIDE, 0.0f) ,
	};

	D3DXVECTOR2 uv[4];
	// テクスチャUV座標の設定
	uv[0] = D3DXVECTOR2(0.0f, m_fTexV + 0.0f);
	uv[1] = D3DXVECTOR2(1.0f, m_fTexV + 0.0f);
	uv[2] = D3DXVECTOR2(0.0f, m_fTexV + 1.0f);
	uv[3] = D3DXVECTOR2(1.0f, m_fTexV + 1.0f);

	for (int nCntPolygon = 0; nCntPolygon < MAX_COLOR_EFFECT_POLYGON_NUM; nCntPolygon++)
	{
		m_apPolygon[nCntPolygon] = CScene3d::Create(polygonPos[nCntPolygon] ,D3DXVECTOR3(TILE_ONE_SIDE, TILE_ONE_SIDE, 0.0f));
		if (nCntPolygon == 1 ||nCntPolygon  == 2)
		{
			m_apPolygon[nCntPolygon]->SetRot(D3DXVECTOR3(0.0f, D3DXToRadian(90.0f), 0.0f));
		}
		m_apPolygon[nCntPolygon]->SetColor(m_polygonColor);
		m_apPolygon[nCntPolygon]->OutList();
		m_apPolygon[nCntPolygon]->SetTextureUV(uv);
		m_apPolygon[nCntPolygon]->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_MAX_COLOR_EFFECT));
	}

	

	return S_OK;
}

//=============================
// 終了処理
//=============================
void CMaxColorEffect::Uninit(void)
{
	for (int nCntPolygon = 0; nCntPolygon < MAX_COLOR_EFFECT_POLYGON_NUM; nCntPolygon++)
	{
		if (m_apPolygon[nCntPolygon] != NULL)
		{
			m_apPolygon[nCntPolygon]->Uninit();
			delete m_apPolygon[nCntPolygon];
			m_apPolygon[nCntPolygon] = NULL;
		}
	}

	// 開放処理
	Release();
}

//=============================
// 更新処理
//=============================
void CMaxColorEffect::Update(void)
{
	// アルファ値の処理
	if (m_nCntLife < LIFE_FRAME / 2.0f)
	{// 目標値1.0f
		m_polygonColor.a += (1.0f - m_polygonColor.a)*ALPHA_RATE;
	}
	else
	{//目標値0.0f
		m_polygonColor.a += (0.0f - m_polygonColor.a)*ALPHA_RATE;
	}

	m_fTexV +=(0.0f - m_fTexV)*ALPHA_RATE;
	D3DXVECTOR2 uv[4];
	// テクスチャUV座標の設定
	uv[0] = D3DXVECTOR2(0.0f, m_fTexV + 0.0f);
	uv[1] = D3DXVECTOR2(1.0f, m_fTexV + 0.0f);
	uv[2] = D3DXVECTOR2(0.0f, m_fTexV + 1.0f);
	uv[3] = D3DXVECTOR2(1.0f, m_fTexV + 1.0f);

	// カラー・UVの設定
	for (int nCntPolygon = 0; nCntPolygon < MAX_COLOR_EFFECT_POLYGON_NUM; nCntPolygon++)
	{
		if (m_apPolygon[nCntPolygon] != NULL)
		{
			m_apPolygon[nCntPolygon]->SetColor(m_polygonColor);
			m_apPolygon[nCntPolygon]->SetTextureUV(uv);
		}
	}

	// 寿命の処理
	m_nCntLife++;
	if (m_nCntLife > LIFE_FRAME)
	{
		Uninit();
	}
}

//=============================
// 描画処理
//=============================
void CMaxColorEffect::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	DWORD save;
	pDevice->GetRenderState(D3DRS_CULLMODE, &save); // カリングの保存
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); // カリング オフ
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_BORDER); // テクスチャV値の繰り返し設定

	for (int nCntPolygon = 0; nCntPolygon < MAX_COLOR_EFFECT_POLYGON_NUM; nCntPolygon++)
	{
		if (m_apPolygon[nCntPolygon] != NULL)
		{
			m_apPolygon[nCntPolygon]->Draw();
		}
	}

	pDevice->SetRenderState(D3DRS_CULLMODE, save); // カリング戻す
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP); // テクスチャV値の繰り返し設定
}