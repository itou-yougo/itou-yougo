//=============================================================================
//
// リバースアイテムの処理 [reverse_item.cpp]
// Author : 吉田悠人
//
//=============================================================================

//******************************
// インクルード
//******************************
#include "reverse_item.h"
#include "player.h"

//******************************
// コンストラクタ
//******************************
CReverseItem::CReverseItem()
{
}

//******************************
// デストラクタ
//******************************
CReverseItem::~CReverseItem()
{
}

//******************************
// クラス生成
//******************************
CReverseItem * CReverseItem::Create(D3DXVECTOR3 pos)
{
	//メモリの確保
	CReverseItem *pItem = nullptr;
	pItem = new CReverseItem;

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
HRESULT CReverseItem::Init(void)
{
	// アイテムの初期化処理
	CItem::Init();
	// モデルの割り当て
	BindModel(CResourceModel::GetModel(CResourceModel::MODEL_ITEM_REVERSE));

	return S_OK;
}

//******************************
// アイテム効果処理
//******************************
void CReverseItem::ItemEffect(CPlayer*pPlayer)
{
	//他のプレイヤー用のポインタ
	CPlayer * pOthersPlayer = (CPlayer*)GetTop(OBJTYPE_PLAYER);

	while (pOthersPlayer != NULL)
	{
		//自分以外
		if (pOthersPlayer != pPlayer)
		{
			//他プレイヤーが死亡状態じゃないか
			if (pOthersPlayer->GetState() != CPlayer::PLAYER_STATE_DEATH)
			{
				//リバース状態にする
				pOthersPlayer->SetItemState(CPlayer::ITEM_STATE_REVERSE);
			}
		}
		pOthersPlayer = (CPlayer*)pOthersPlayer->GetNext();
	}
}
