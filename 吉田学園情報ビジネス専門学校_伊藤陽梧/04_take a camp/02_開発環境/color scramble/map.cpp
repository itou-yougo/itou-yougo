//=============================================================================
//
// マップクラス [map.cpp]
// Author : 吉田悠人
//
//=============================================================================
//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "map.h"
#include "tile.h"
#include "color_tile.h"
#include "player.h"
#include "spawn_tile.h"
#include "color_manager.h"
#include "needle_tile.h"
#include "item.h"
#include <time.h>
#include "chara_select.h"
#include "tile_factory.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define COLOR_TILE_PLUS_HEIGHT 0.0f				// カラータイル生成時ひとつ生成するたびに生成位置を高くする
#define COLOR_TILE_INIT_HEIGHT -TILE_SIZE_Y/2	// カラータイル初めの高さ
//#define COLOR_TILE_PLUS_HEIGHT 50.0f // カラータイル生成時ひとつ生成するたびに生成位置を高くする
//#define COLOR_TILE_INIT_HEIGHT 500.0f // カラータイル初めの高さ
#define MAX_ITEM_SPAWN_COUNT (60*10)	// アイテムスポーンの最大カウント
#define MAX_ITEM (3)					// マップ上の最大個数

//=============================================================================
// 静的メンバー変数
//=============================================================================

//=============================================================================
// コンストラクタ
//=============================================================================
CMap::CMap() :CScene(OBJTYPE_SYSTEM)
{
	m_nItemSpawnCount = 0;
	memset(&m_MapData, 0, sizeof(m_MapData));
}

//=============================================================================
// デストラクタ
//=============================================================================
CMap::~CMap()
{
}

//=============================================================================
// 生成処理関数
//=============================================================================
CMap * CMap::Create(CMapManager::MAP_TYPE MapType)
{
	// メモリの確保
	CMap *pMap;
	pMap = new CMap;
	if (pMap != NULL)
	{
		//マップ情報取得
		pMap->SetMapData(CMapManager::GetMapData(MapType));
		//初期化処理
		pMap->Init();
	}

	return pMap;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CMap::Init(void)
{
	//マップ生成
	MapCreate();
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CMap::Uninit(void)
{
	//オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新関数
//=============================================================================
void CMap::Update(void)
{
	ItemSpawn();
}

//=============================================================================
// 描画関数
//=============================================================================
void CMap::Draw(void)
{

}
//=============================================================================
// マップ生成関数
//=============================================================================
void CMap::MapCreate(void)
{
	// タイルリストのリセット
	CTile::ResetTileList();

	//マップデータがあるか
	if (&m_MapData != NULL)
	{
		float ColorTileHeight = COLOR_TILE_INIT_HEIGHT;

		for (int nBlockY = 0; nBlockY < m_MapData.nStageSizeY; nBlockY++)
		{
			for (int nBlockX = 0; nBlockX < m_MapData.BlockData[nBlockY].nStageSizeX; nBlockX++)
			{
				CTileFactory* pTileFactory = CTileFactory::GetTileFactory();

				D3DXCOLOR tileCol = TILE_DEFAULT_COLOR;

				// プレイヤーの生成
				switch (m_MapData.BlockData[nBlockY].nBlockType[nBlockX])
				{
				case CMapManager::BLOCK_TYPE_1P_START:	//1Pスタート位置

					if (CCharaSelect::GetEntryData(0).bEntry)
					{
						CPlayer::Create(D3DXVECTOR3(TILE_ONE_SIDE * -nBlockX, 0.0f, TILE_ONE_SIDE * nBlockY) + m_MapData.m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
						tileCol = GET_COLORMANAGER->GetColorDataByPlayerNumber(0).iconColor;
					}

					break;
				case CMapManager::BLOCK_TYPE_2P_START:	//2Pスタート位置
					if (CCharaSelect::GetEntryData(1).bEntry)
					{
						CPlayer::Create(D3DXVECTOR3(TILE_ONE_SIDE * -nBlockX, 0.0f, TILE_ONE_SIDE * nBlockY) + m_MapData.m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);
						tileCol = GET_COLORMANAGER->GetColorDataByPlayerNumber(1).iconColor;
					}

					break;
				case CMapManager::BLOCK_TYPE_3P_START:	//3Pスタート位置
					if (CCharaSelect::GetEntryData(2).bEntry)
					{
						CPlayer::Create(D3DXVECTOR3(TILE_ONE_SIDE * -nBlockX, 0.0f, TILE_ONE_SIDE * nBlockY) + m_MapData.m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2);
						tileCol = GET_COLORMANAGER->GetColorDataByPlayerNumber(2).iconColor;
					}
					break;
				case CMapManager::BLOCK_TYPE_4P_START:	//4Pスタート位置
					if (CCharaSelect::GetEntryData(3).bEntry)
					{
						CPlayer::Create(D3DXVECTOR3(TILE_ONE_SIDE * -nBlockX, 0.0f, TILE_ONE_SIDE * nBlockY) + m_MapData.m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
						tileCol = GET_COLORMANAGER->GetColorDataByPlayerNumber(3).iconColor;
					}
					break;
				}

				// タイルの生成
				if (pTileFactory != NULL
					&&pTileFactory->GetCreateFunction(m_MapData.BlockData[nBlockY].nBlockType[nBlockX]) != NULL)
				{
					pTileFactory->GetCreateFunction(m_MapData.BlockData[nBlockY].nBlockType[nBlockX])(D3DXVECTOR3(TILE_ONE_SIDE * -nBlockX, ColorTileHeight, TILE_ONE_SIDE * nBlockY) + m_MapData.m_pos, tileCol);
				}
			}
		}
	}
}

//=============================================================================
// マップデータセッター関数
//=============================================================================
void CMap::SetMapData(CMapManager::MAP_DATA MapData)
{
	m_MapData = MapData;
}

//=============================================================================
// マップデータゲッター関数
//=============================================================================
CMapManager::MAP_DATA CMap::GetMapData(void)
{
	return m_MapData;
}

//=============================================================================
// アイテムスポーン処理関数
//=============================================================================
void CMap::ItemSpawn(void)
{
	//カウントアップ
	m_nItemSpawnCount++;
	//カウントが一定になったら
	if (m_nItemSpawnCount >= MAX_ITEM_SPAWN_COUNT)
	{
		//既存のアイテム位置
		D3DXVECTOR3 OtherItem[MAX_ITEM];
		memset(&OtherItem, 0, sizeof(OtherItem));
		//アイテムポインタ取得
		CItem * pItem = (CItem*)GetTop(OBJTYPE_ITEM);
		//アイテムの個数カウント変数
		int nItemCount = 0;
		
		//他のアイテムのポインタを取得
		while (pItem != NULL)
		{
			if (nItemCount<MAX_ITEM)
			{
				//他のアイテムの位置取得
				OtherItem[nItemCount] = pItem->GetPos();
				//アイテムカウント
				nItemCount++;
			}
			pItem = (CItem*)pItem->GetNext();
		}

		//マップ上のアイテムが限界を超えていないか
		if (nItemCount < MAX_ITEM)
		{
			//アイテムのスポーン位置
			D3DXVECTOR3 ItemPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			//位置決め用の変数
			int nPosY, nPosX;
			//生成できるかのフラグ変数
			bool bItem = false;
			//ランダム関数の初期化
			srand((unsigned int)time(NULL));

			while (!bItem)
			{
				//ループ用にフラグを立てる
				bItem = true;

				//ランダムにマップ上の位置を決める
				nPosY = rand() % m_MapData.nStageSizeY;
				nPosX = rand() % m_MapData.BlockData[nPosY].nStageSizeX;

				//ランダムに決めたマス目が生成できるマス目か
				if (m_MapData.BlockData[nPosY].nBlockType[nPosX] == CMapManager::BLOCK_TYPE_BLOCK)
				{
					//生成位置
					ItemPos = D3DXVECTOR3(TILE_ONE_SIDE*-nPosX, 3.0f, TILE_ONE_SIDE*nPosY) + m_MapData.m_pos;
					
					//他アイテムとかぶらないように
					for (int nOtherItem = 0; nOtherItem < nItemCount; nOtherItem++)
					{
						//同じ場所にアイテムがあるか
						if (ItemPos.x <= (OtherItem[nOtherItem].x + 5.0f)
							&& ItemPos.x >= (OtherItem[nOtherItem].x - 5.0f)
							&& ItemPos.z <= (OtherItem[nOtherItem].z + 5.0f)
							&& ItemPos.z >= (OtherItem[nOtherItem].z - 5.0f))
						{
							//ループを続ける
							bItem = false;
							break;
						}
					}
				}
				//ランダムに決めたマスが生成できない時
				else
				{
					//ループを続ける
					bItem = false;
				}
			}
			//アイテム生成
			CItem::Create(ItemPos, (CItem::ITEM_EFFECT)(rand() % CItem::ITEM_EFFECT_MAX));
		}
	
		//カウント初期化
		m_nItemSpawnCount = 0;
	}
}
