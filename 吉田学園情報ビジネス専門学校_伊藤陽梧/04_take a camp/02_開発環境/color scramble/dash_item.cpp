//=============================================================================
//
// ダッシュアイテムの処理 [dash_item.cpp]
// Author : 吉田悠人
//
//=============================================================================

//******************************
// インクルード
//******************************
#include "dash_item.h"
#include "player.h"

//******************************
// コンストラクタ
//******************************
CDashItem::CDashItem()
{
}

//******************************
// デストラクタ
//******************************
CDashItem::~CDashItem()
{
}

//******************************
// クラス生成
//******************************
CDashItem * CDashItem::Create(D3DXVECTOR3 pos)
{
	//メモリの確保
	CDashItem *pItem = nullptr;
	pItem = new CDashItem;

	if (pItem != nullptr)
	{
		//初期化処理
		pItem->Init();
		//位置セット
		pItem->SetPos(pos);

	}
	return pItem;
}

//******************************
// 初期化処理
//******************************
HRESULT CDashItem::Init(void)
{
	// アイテムの初期化処理
	CItem::Init();
	// モデルの割り当て
	BindModel(CResourceModel::GetModel(CResourceModel::MODEL_ITEM_DASH));

	return S_OK;
}

//******************************
// アイテム効果処理
//******************************
void CDashItem::ItemEffect(CPlayer*pPlayer)
{
	// プレイヤーのアイテムステート変化
	pPlayer->SetItemState(CPlayer::ITEM_STATE_DASH);
}
