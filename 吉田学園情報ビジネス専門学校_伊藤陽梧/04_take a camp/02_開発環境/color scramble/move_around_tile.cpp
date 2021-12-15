////////////////////////////////////////////////////
//
//    前後に動くタイルの処理[move_around_tile.cpp]
//    Author:吉田 悠人
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "move_around_tile.h"

//******************************
// コンストラクタ
//******************************
CAroundTile::CAroundTile()
{

}

//******************************
// デストラクタ
//******************************
CAroundTile::~CAroundTile()
{
}

//******************************
// クラス生成
//******************************
void CAroundTile::Create(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	// メモリの確保
	CAroundTile *pTile;
	pTile = new CAroundTile;

	//NULLチェック
	if (pTile != NULL)
	{
		// 初期化
		pTile->Init();

		// 各値の代入・セット
		pTile->SetPos(pos);					// 位置
		pTile->SetMove(pos);				// 移動量
		pTile->SetPriority(OBJTYPE_TILE); 	// オブジェクトタイプ
	}
}

//******************************
// 移動方向処理
//******************************
void CAroundTile::MoveRot(bool bReversal)
{
	//現在位置
	D3DXVECTOR3 pos = GetPos();
	//移動量
	D3DXVECTOR3 move = GetMove();

	//反転しているか
	if (!bReversal)
	{
		//移動量計算
		move.z += TILE_ONE_SIDE;
	}
	else
	{
		move.z -= TILE_ONE_SIDE;
	}

	//移動量セット
	SetMove(move);
}

//******************************
// 周囲のブロック確認処理
//******************************
void CAroundTile::TileCheck(void)
{
	//現在位置
	D3DXVECTOR3 pos = GetPos();

	if (CTile::GetHitTile(D3DXVECTOR3(pos.x , pos.y, pos.z + TILE_ONE_SIDE)) != nullptr)
	{
		//移動方向反転
		SetReversal(false);
	}
	else
	{
		//移動方向反転
		SetReversal(true);
	}
}
