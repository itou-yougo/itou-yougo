////////////////////////////////////////////////////
//
//    spawn_tileクラスの処理[spawn_tile.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "spawn_tile.h"
#include "scene3d.h"
#include "resource_texture.h"
#include "bullet.h"

//*****************************
// マクロ定義

//*****************************
// 静的メンバ変数宣言
//*****************************

//******************************
// コンストラクタ
//******************************
CSpawnTile::CSpawnTile()
{
	m_pCrossPolygon = NULL;

}

//******************************
// デストラクタ
//******************************
CSpawnTile::~CSpawnTile()
{
}

//******************************
// クラス生成
//******************************
void CSpawnTile::Create(D3DXVECTOR3 pos , D3DXCOLOR col )
{
	// メモリの確保
	CSpawnTile *pTile;
	pTile = new CSpawnTile;

	// 初期化
	pTile->Init();

	// 各値の代入・セット
	pTile->SetPos(pos);
	pTile->SetPriority(OBJTYPE_TILE); // オブジェクトタイプ
	pTile->SetRide(true);			  // 載れないようにフラグを立てる
	 // ×マークの生成
	pTile->m_pCrossPolygon = CScene3d::Create(D3DXVECTOR3(pos.x, pos.y + (TILE_SIZE_Y / 2) + 1.0f, pos.z), D3DXVECTOR3(TILE_ONE_SIDE - 2, 0.0f, TILE_ONE_SIDE - 2));
	pTile->m_pCrossPolygon->SetColor(col);
	pTile->m_pCrossPolygon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_CROSS_MARK));
	pTile->m_pCrossPolygon->SetPriority(OBJTYPE_MAP);

}

//******************************
// 初期化処理
//******************************
HRESULT CSpawnTile::Init(void)
{
	if (FAILED(CTile::Init()))
	{
		return E_FAIL;
	}



	SetColor(TILE_DEFAULT_COLOR);

	return S_OK;
}

//******************************
// 終了処理
//******************************
void CSpawnTile::Uninit(void)
{
	CTile::Uninit();
}