//====================================================
//
// dummy_tileクラスの処理[dummy_tile.cpp]
// Author : 伊藤陽梧
//
//====================================================

//====================================================
// インクルード
//====================================================
#include "dummy_tile.h"
#include "scene3d.h"
#include "resource_texture.h"

//====================================================
// コンストラクタ
//====================================================
CDummyTile::CDummyTile()
{
	m_pCrossPolygon = NULL;
}

//====================================================
// デストラクタ
//====================================================
CDummyTile::~CDummyTile()
{
}

//====================================================
// クラス生成
//====================================================
void CDummyTile::Create(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	// メモリの確保
	CDummyTile *pTile;
	pTile = new CDummyTile;

	// 初期化
	pTile->Init();

	// 各値の代入・セット
	pTile->SetPos(pos);
	pTile->SetPriority(OBJTYPE_TILE); // オブジェクトタイプ
	pTile->SetRide(true);			  // 載れないようにフラグを立てる

	// ×マークの生成
	// テクスチャは今後変える
	pTile->m_pCrossPolygon = CScene3d::Create(D3DXVECTOR3(pos.x, pos.y + (TILE_SIZE_Y / 2) + 1.0f, pos.z), D3DXVECTOR3(TILE_ONE_SIDE - 2, 0.0f, TILE_ONE_SIDE - 2));
	pTile->m_pCrossPolygon->SetColor(col);
	pTile->m_pCrossPolygon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_CROSS_MARK));
	pTile->m_pCrossPolygon->SetPriority(OBJTYPE_MAP);
}

//====================================================
// 初期化処理
//====================================================
HRESULT CDummyTile::Init(void)
{
	if (FAILED(CTile::Init()))
	{
		return E_FAIL;
	}

	SetColor(TILE_DEFAULT_COLOR);

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CDummyTile::Uninit(void)
{
	CTile::Uninit();
}