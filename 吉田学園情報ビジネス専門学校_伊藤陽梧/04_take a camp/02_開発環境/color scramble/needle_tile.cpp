////////////////////////////////////////////////////
//
//    トゲタイルの処理[needle_tile.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "needle_tile.h"
#include "model.h"
#include "resource_model.h"
#include "resource_texture.h"
#include "player.h"
#include "collision.h"
#include "scene3d.h"

//*****************************
// マクロ定義
//*****************************
#define NEEDLE_POS_Y	(0)					// とげDOWN時のY座標
#define NEEDLE_POS_Y_UP (TILE_SIZE_Y / 2)	// とげUP時のY座標
#define NEEDLE_POS_RATE	(0.2f)				// とげを上げるときの係数
#define DEATH_FRAME		(10.0f)				// 触れてから死ぬまでのフレーム数
#define UP_FRAME		(80)				// とげが上がっている間のカウント
#define DOWN_FRAME		(180)				// とげが下がっている間のカウント

//*****************************
// 静的メンバ変数宣言
//*****************************

//******************************
// コンストラクタ
//******************************
CNeedleTile::CNeedleTile()
{
	m_pNeedleModel = NULL;
	m_nCntHit = 0;
	m_bUp = false;
	m_nUpCnt = 0;
}

//******************************
// デストラクタ
//******************************
CNeedleTile::~CNeedleTile()
{
}

//******************************
// クラス生成
//******************************
void CNeedleTile::Create(D3DXVECTOR3 pos , D3DXCOLOR col )
{
	// メモリの確保
	CNeedleTile *pTile;
	pTile = new CNeedleTile;

	// 初期化
	pTile->Init();

	// 各値の代入・セット
	pTile->SetPos(pos);

	// とげブロックの生成
	pTile->m_pNeedleModel = CModel::Create(D3DXVECTOR3(pos.x, pos.y + (TILE_SIZE_Y / 4), pos.z), CResourceModel::MODEL_NEEDLE);
	pTile->m_pNeedleModel->SetPriority(OBJTYPE_MAP);
 
	// 穴
	pTile->m_pHole = CScene3d::Create(pTile->GetPos(), D3DXVECTOR3(TILE_ONE_SIDE-1, 0.0f, TILE_ONE_SIDE-1));
	pTile->m_pHole->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_NEEDLE));
	pTile->m_pHole->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	pTile->m_pHole->SetPriority(OBJTYPE_MAP);

}

//******************************
// 更新処理
//******************************
void CNeedleTile::Update(void)
{
	CColorTile::Update();

	ManageNeedle();

	// 穴位置の調整
	D3DXVECTOR3 pos = m_pHole->GetPos();
	if (pos != D3DXVECTOR3(GetPos().x, GetPos().y + (TILE_SIZE_Y / 2) + 0.2f, GetPos().z))
	{
		pos = D3DXVECTOR3(GetPos().x, GetPos().y + (TILE_SIZE_Y / 2) + 0.2f, GetPos().z);

		m_pHole->SetPos(pos);
	}

}

//******************************
// プレイヤーとヒット時の処理
//******************************
void CNeedleTile:: HitPlayerAction(CPlayer*pPlayer)
{
	if (m_bUp)
	{
		m_nCntHit++;
		if (m_nCntHit > DEATH_FRAME)
		{
			pPlayer->Death();
			m_nCntHit = 0;
		}
	}
}

//******************************
// とげの管理
//******************************
void CNeedleTile::ManageNeedle(void)
{
	// とげの高さの処理
	D3DXVECTOR3 needlePos = m_pNeedleModel->GetPos();
	float fDistPosY;

	if (m_bUp)
	{// とげを上げる
		fDistPosY = GetPos().y + NEEDLE_POS_Y_UP;

		m_nUpCnt++;
		if (m_nUpCnt > UP_FRAME)
		{
			m_bUp = false;
			m_nUpCnt = 0;
		}
	}
	else
	{// とげを下げる
		fDistPosY = GetPos().y + NEEDLE_POS_Y;

		// カウントの初期化
		m_nCntHit = 0;

		m_nUpCnt++;
		if (m_nUpCnt > DOWN_FRAME)
		{
			m_bUp = true;
			m_nUpCnt = 0;
		}
	}

	// Y座標の設定
	needlePos.y += (fDistPosY - needlePos.y)*NEEDLE_POS_RATE;
	m_pNeedleModel->SetPos(needlePos);
}