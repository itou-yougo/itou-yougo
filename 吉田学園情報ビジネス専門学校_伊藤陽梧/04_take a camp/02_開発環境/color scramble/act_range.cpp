//=============================================================================
//
// 行動範囲ヘッダ [act_range.h]
// Author : 吉田 悠人
//
//=============================================================================
//*****************************
// インクルード
//*****************************
#include "act_range.h"
#include "player.h"
#include "tile.h"
#include "map.h"
#include "game.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CActRange::CActRange()
{
	//変数初期化
	m_pPlayer = nullptr;
	m_bDeath = false;
	memset(&m_MapData, 0, sizeof(m_MapData));
	memset(&m_ActPos, 0, sizeof(m_ActPos));
	memset(&m_bPlayerMove, true, sizeof(m_bPlayerMove));
	memset(&m_OtherAct, 0, sizeof(m_OtherAct));
	memset(&m_NewActPos, 0, sizeof(m_NewActPos));
}

//=============================================================================
// デストラクタ
//=============================================================================
CActRange::~CActRange()
{
}

//=============================================================================
// プレイヤーがどの位置にいるか
//=============================================================================
void CActRange::PlayerPos(void)
{
	//マップデータがあるか
	if (&m_MapData != NULL)
	{
		//プレイヤー位置取得
		D3DXVECTOR3 PlayerPos = m_pPlayer->GetPos();

		for (int nBlockY = 0; nBlockY < m_MapData.nStageSizeY; nBlockY++)
		{
			for (int nBlockX = 0; nBlockX < m_MapData.BlockData[nBlockY].nStageSizeX; nBlockX++)
			{
				D3DXVECTOR3 BlockPos = D3DXVECTOR3(TILE_ONE_SIDE * -nBlockX, -TILE_SIZE_Y / 2, TILE_ONE_SIDE * nBlockY) + m_MapData.m_pos;
				if (PlayerPos.x>BlockPos.x - TILE_ONE_SIDE / 2
					&& PlayerPos.x<BlockPos.x + TILE_ONE_SIDE / 2
					&& PlayerPos.z>BlockPos.z - TILE_ONE_SIDE / 2
					&& PlayerPos.z<BlockPos.z + TILE_ONE_SIDE / 2)
				{
					//位置取得
					m_ActPos.x = (float)nBlockX;
					m_ActPos.z = (float)nBlockY;

				}
			}
		}
	}

}

//=============================================================================
// マップ上のプレイヤーの移動判定関数
//=============================================================================
bool CActRange::ActMove(int nMoveX, int nMoveZ)
{
	//移動方向取得
	m_NewActPos.x = nMoveX + m_ActPos.x;
	m_NewActPos.z = nMoveZ + m_ActPos.z;
	if (nMoveX<0)
	{
		return m_bPlayerMove[PLAYER_MOVE_RIGHT];
	}
	if (nMoveX>0)
	{
		return m_bPlayerMove[PLAYER_MOVE_LEFT];
	}
	if (nMoveZ<0)
	{
		return m_bPlayerMove[PLAYER_MOVE_UP];
	}
	if (nMoveZ>0)
	{
		return m_bPlayerMove[PLAYER_MOVE_DOWN];
	}

	return false;
}

//=============================================================================
// 他のプレイヤーにぶつかり止まる判定
//=============================================================================
void CActRange::OtherPlayer(void)
{

	//リストのトップ取得
	CActRange* pActRange = (CActRange*)GetTop(OBJTYPE_ACT_RANGE);
	//他プレイヤー
	int nOtherPlayer = 0;

	//NULLチェック
	while (pActRange != NULL)
	{
		//自分以外
		if (pActRange != this)
		{
			//プレイヤーのマップ位置取得
			m_OtherAct[nOtherPlayer].OtherActPos = pActRange->GetActPos();
			//プレイヤーのマップ移動位置取得
			m_OtherAct[nOtherPlayer].OtherNewActPos = pActRange->GetNewActPos();
			//プレイヤーが死んでいるか
			m_OtherAct[nOtherPlayer].bDeath = pActRange->GetDeath();
			//プレイヤーが移動しているか
			m_OtherAct[nOtherPlayer].bMove = pActRange->GetMove();
			//次のプレイヤーへ
			nOtherPlayer++;
		}
		//次のポインタへ
		pActRange = (CActRange*)pActRange->GetNext();
	}
}

//=============================================================================
// プレイヤーの移動範囲
//=============================================================================
void CActRange::ActRange(void)
{
	D3DXVECTOR3 Range[PLAYER_MOVE_MAX] =
	{
		D3DXVECTOR3(0,0,-1),
		D3DXVECTOR3(0,0,1),
		D3DXVECTOR3(1,0,0),
		D3DXVECTOR3(-1,0,0)
	};

	//上下左右にプレイヤーが移動できるか
	for (int nMove = 0; nMove<PLAYER_MOVE_MAX; nMove++)
	{		
		//タイルポインタ取得
		CTile * pTile = CTile::GetHitTile(D3DXVECTOR3(-(m_ActPos.x + Range[nMove].x)*TILE_ONE_SIDE, -TILE_POS_Y, (m_ActPos.z + Range[nMove].z)*TILE_ONE_SIDE)+ m_MapData.m_pos);
		
		//NULLチェック
		if (pTile != NULL)
		{
			//タイルが乗れる状態か
			if (!pTile->GetRide())
			{
				if (pTile->GetType() == CScene::OBJTYPE_COLOR_TILE
					|| pTile->GetType() == CScene::OBJTYPE_TILE)
				{
					//プレイヤーの確認
					for (int nPlayer = 0; nPlayer<MAX_PLAYER - 1; nPlayer++)
					{
						if ((m_ActPos + Range[nMove]) == m_OtherAct[nPlayer].OtherActPos && !m_OtherAct[nPlayer].bDeath)
						{
							//移動できないためfalse
							m_bPlayerMove[nMove] = false;
							break;
						}
						else if ((m_ActPos + Range[nMove]) == m_OtherAct[nPlayer].OtherNewActPos
							&& !m_OtherAct[nPlayer].bDeath
							&& !m_OtherAct[nPlayer].bMove)
						{
							//移動できないためfalse
							m_bPlayerMove[nMove] = false;
							break;
						}
						else
						{
							//移動できるためtrue
							m_bPlayerMove[nMove] = true;

						}
					}
				}
				else
				{
					//移動できないためfalse
					m_bPlayerMove[nMove] = false;
				}
			}
			else
			{
				//移動できないためfalse
				m_bPlayerMove[nMove] = false;
			}
		}
		else
		{
			//移動できないためfalse
			m_bPlayerMove[nMove] = false;
		}
	}


}

//=============================================================================
// 生成処理関数
//=============================================================================
CActRange * CActRange::Create(CPlayer * pPlayer)
{
	//メモリ確保
	CActRange *pActRange = nullptr;
	pActRange = new CActRange;

	//NULLチェック
	if (pActRange != NULL)
	{
		pActRange->SetPriority(OBJTYPE_ACT_RANGE); // オブジェクトタイプ
		pActRange->m_pPlayer = pPlayer;	//プレイヤーのポインター
		pActRange->Init();				//初期化処理
	}

	return pActRange;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CActRange::Init(void)
{
	//マップ情報取得
	m_MapData = CMapManager::GetMapData(CGame::GetMapType());

	//最初の位置取得
	PlayerPos();

	m_NewActPos = m_ActPos;
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CActRange::Uninit(void)
{
	//オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新関数
//=============================================================================
void CActRange::Update(void)
{

	// 他のプレイヤーのマップ位置
	OtherPlayer();
	// プレイヤーの移動範囲
	ActRange();
	// プレイヤーの位置取得
	PlayerPos();

}

//=============================================================================
// 描画関数
//=============================================================================
void CActRange::Draw(void)
{
}
