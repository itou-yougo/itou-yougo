////////////////////////////////////////////////////
//
//    塗時間クラスの処理[paint_time.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "tile_effect_charge.h"
#include "scene3d.h"
#include "tile.h"
#include "resource_texture.h"
//******************************
// マクロ定義
//******************************
#define COLOR D3DXCOLOR(0.0f,0.0f,0.0f,GetAlpha())

//******************************
// コンストラクタ
//******************************
CTileEffectCharge::CTileEffectCharge()
{
	m_pPolygon = NULL;
}

//******************************
// デストラクタ
//******************************
CTileEffectCharge::~CTileEffectCharge()
{
}

//******************************
// クラス生成
//******************************
CTileEffectCharge * CTileEffectCharge::Create(void)
{
	// クラス生成
	CTileEffectCharge * pInstace = new CTileEffectCharge;

	// 初期化処理
	pInstace->Init();

	return pInstace;
}

//******************************
// 初期化処理
//******************************
HRESULT CTileEffectCharge::Init(void)
{
	CTileEffect::Init();

	// 初期化
	m_pPolygon = CScene3d::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(TILE_ONE_SIDE - 5.0f, 0.0, TILE_ONE_SIDE - 5.0f));
	m_pPolygon->SetColor(COLOR);
	m_pPolygon->OutList();
	
	// テクスチャの割り当て
	m_pPolygon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_TILE_CHARGE));

	return S_OK;
}


//******************************
// 更新処理
//******************************
void CTileEffectCharge::Update(void)
{
	m_pPolygon->SetColor(COLOR);
	CTileEffect::Update();
}

//******************************
// 終了処理
//******************************
void CTileEffectCharge::Uninit(void)
{
	if (m_pPolygon != NULL)
	{
		m_pPolygon->Uninit();
		delete m_pPolygon;
		m_pPolygon = NULL;
	}

	CTileEffect::Uninit();
}

//******************************
// 描画処理
//******************************
void CTileEffectCharge::Draw(void)
{
	// 描画
	if (m_pPolygon != NULL)
	{
		m_pPolygon->Draw();
	}
}

//******************************
// 座標のセット
//******************************
void CTileEffectCharge::SetPos(D3DXVECTOR3 pos)
{
	m_pPolygon->SetPos(pos);
}
