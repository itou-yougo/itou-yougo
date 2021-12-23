//=============================================================================
//
// ワープ床ヘッダー [warp_tile.cpp]
// Author : 吉田 悠人
//
//=============================================================================

//*****************************
// インクルード
//*****************************
#include "warp_tile.h"
#include "player.h"
#include "collision.h"
#include <vector>
#include <time.h>

//******************************
// 静的メンバ変数宣言
//******************************
int CWarpTile::m_nTotalWarpTile = 0;
std::vector<std::vector<CWarpTile*>> CWarpTile::m_pWarpTile(WARP_TILE_TYPE_MAX, std::vector<CWarpTile*>(0));
//******************************
// コンストラクタ
//******************************
CWarpTile::CWarpTile()
{
	m_nLyncTile = 0;
	m_WarpType = WARP_TILE_TYPE_NONE;
	m_WarpState = WARP_TILE_NORMAL;
}

//******************************
// デストラクタ
//******************************
CWarpTile::~CWarpTile()
{
}

//******************************
// 生成処理(タイプ1)
//******************************
void CWarpTile::Create_1(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	//動的配列にメモリ確保
	m_pWarpTile.at(WARP_TILE_TYPE_1).emplace_back(new CWarpTile);

	//NULLチェック
	if (m_pWarpTile.at(WARP_TILE_TYPE_1).at(m_pWarpTile.at(WARP_TILE_TYPE_1).size() - 1) != NULL)
	{
		m_pWarpTile.at(WARP_TILE_TYPE_1).at(m_pWarpTile.at(WARP_TILE_TYPE_1).size() - 1)->m_WarpType = WARP_TILE_TYPE_1;
		//初期化処理
		m_pWarpTile.at(WARP_TILE_TYPE_1).at(m_pWarpTile.at(WARP_TILE_TYPE_1).size() - 1)->Init();
		//位置設定
		m_pWarpTile.at(WARP_TILE_TYPE_1).at(m_pWarpTile.at(WARP_TILE_TYPE_1).size() - 1)->SetPos(pos);
		//ワープタイルの総数追加
		m_nTotalWarpTile++;
	}
}

//******************************
// 生成処理(タイプ2)
//******************************
void CWarpTile::Create_2(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	//動的配列にメモリ確保
	m_pWarpTile.at(WARP_TILE_TYPE_2).emplace_back(new CWarpTile);

	//NULLチェック
	if (m_pWarpTile.at(WARP_TILE_TYPE_2).at(m_pWarpTile.at(WARP_TILE_TYPE_2).size() - 1) != NULL)
	{
		m_pWarpTile.at(WARP_TILE_TYPE_2).at(m_pWarpTile.at(WARP_TILE_TYPE_2).size() - 1)->m_WarpType = WARP_TILE_TYPE_2;
		//初期化処理
		m_pWarpTile.at(WARP_TILE_TYPE_2).at(m_pWarpTile.at(WARP_TILE_TYPE_2).size() - 1)->Init();
		//位置設定
		m_pWarpTile.at(WARP_TILE_TYPE_2).at(m_pWarpTile.at(WARP_TILE_TYPE_2).size() - 1)->SetPos(pos);
		//ワープタイルの総数追加
		m_nTotalWarpTile++;
	}
}



//******************************
// 初期化処理
//******************************
HRESULT CWarpTile::Init(void)
{
	//タイル初期化処理
	CTile::Init();
	//タイプごとの見た目変化
	switch (m_WarpType)
	{
	case WARP_TILE_TYPE_1:
		//テクスチャの設定

		//カラーの設定
		SetColor(D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
		break;
	case WARP_TILE_TYPE_2:
		//テクスチャの設定

		//カラーの設定
		SetColor(D3DXCOLOR(1.0f,0.0f,1.0f,1.0f));
		break;
	}
	return S_OK;
}

//******************************
// 終了処理
//******************************
void CWarpTile::Uninit(void)
{
	//動的配列の削除
	for (int nWarpType=0; nWarpType<WARP_TILE_TYPE_MAX; nWarpType++)
	{
		//配列の最大数取得
		int nMaxArray = m_pWarpTile.at(nWarpType).size();

		//配列分回す
		for (int nWarpCount = 0; nWarpCount<nMaxArray; nWarpCount++)
		{
			if (m_pWarpTile.at(nWarpType).at(nWarpCount) == this)
			{
				m_pWarpTile.at(nWarpType).erase(m_pWarpTile.at(nWarpType).begin() + (nWarpCount));
				break;
			}
		}
	}

	//終了処理
	CTile::Uninit();
}

//******************************
// 更新処理
//******************************
void CWarpTile::Update(void)
{
	switch (m_WarpState)
	{
		//通常状態
	case WARP_TILE_NORMAL:

		break;
		//ワープ状態
	case WARP_TILE_WARP:
		break;
		//機能停止状態
	case WARP_TILE_STOP:
		break;

	}

	// タイル更新処理
	CTile::Update();
}

//******************************
// プレイヤーが乗っているか
//******************************
void CWarpTile::HitPlayerAction(CPlayer * pPlayer)
{
	switch (m_WarpState)
	{
	case WARP_TILE_NORMAL:	//通常状態
		{
		//配列の最大数取得
		int nMaxArray = m_pWarpTile.at(m_WarpType).size();

		for (int nWarpCount = 0; nWarpCount < nMaxArray; nWarpCount++)
		{
			//タイルに乗ないフラグを立てる
			m_pWarpTile.at(m_WarpType).at(nWarpCount)->SetRide(true);

		}
			//ワープ状態の変更
			m_WarpState = WARP_TILE_WARP;
			break;
		}
	case WARP_TILE_WARP:	//ワープ状態
		{
		//プレイヤーの状況確認
		if (pPlayer->GetState() != CPlayer::PLAYER_STATE_STOP
			&&pPlayer->GetState() != CPlayer::PLAYER_STATE_DEATH)
		{
			//プレイヤーが動いてないときにステートを停止状態に変更
			if (pPlayer->GetMoveFlag())
			{
				pPlayer->SetState(CPlayer::PLAYER_STATE_STOP);
			}

		}
		else if (pPlayer->GetState() == CPlayer::PLAYER_STATE_STOP)
		{
			bool bLync = false;
			//ランダムの最大値
			int nMaxRand = m_pWarpTile.at(m_WarpType).size();
			//ランダム関数の初期化
			srand((unsigned int)time(NULL));
			//同じタイルを選ばないように設定
			while (!bLync)
			{
				//ランダムに飛ばすタイル
				m_nLyncTile = rand() % nMaxRand;
				if (m_pWarpTile.at(m_WarpType).at(m_nLyncTile) != this)
				{
					//ループを抜ける
					bLync = true;
				}
			}
			//ランダムに跳ぶタイル位置取得
			D3DXVECTOR3 Tile = m_pWarpTile.at(m_WarpType).at(m_nLyncTile)->GetPos();
	
			//配列の最大数取得
			int nMaxArray = m_pWarpTile.at(m_WarpType).size();
			//タイプ設定
			for (int nWarpCount = 0; nWarpCount < nMaxArray; nWarpCount++)
			{
				if (m_nLyncTile != nWarpCount)
				{
					m_pWarpTile.at(m_WarpType).at(nWarpCount)->m_WarpState = WARP_TILE_STOP;
				}
				else
				{
					m_pWarpTile.at(m_WarpType).at(nWarpCount)->m_WarpState = WARP_TILE_WARP_AFTER;
				}
			}

			//プレイヤーの位置設定
			pPlayer->SetPos(D3DXVECTOR3(Tile.x, pPlayer->GetPos().y, Tile.z));
			pPlayer->GetCollision()->SetPos(D3DXVECTOR3(Tile.x, pPlayer->GetPos().y, Tile.z));
		}
			break;
		}
	case WARP_TILE_WARP_AFTER:	//ワープ先状態
	{
		//プレイヤーをノーマル状態に変更
		pPlayer->SetState(CPlayer::PLAYER_STATE_NORMAL);
		break;
	}

	case WARP_TILE_STOP:	//停止状態
		{
			break;
		}
	}
}

//******************************
// プレイヤーが降りた処理
//******************************
void CWarpTile::HitPlayerActionRelease(void)
{
	if (m_WarpState == WARP_TILE_WARP_AFTER)
	{
		//配列の最大数取得
		int nMaxArray = m_pWarpTile.at(m_WarpType).size();

		for (int nWarpCount = 0; nWarpCount < nMaxArray; nWarpCount++)
		{
			//タイルのステートを変化
			m_pWarpTile.at(m_WarpType).at(nWarpCount)->m_WarpState = WARP_TILE_NORMAL;

			//タイルに乗れるフラグを立てる
			m_pWarpTile.at(m_WarpType).at(nWarpCount)->SetRide(false);

		}
	}
}
