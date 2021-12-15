////////////////////////////////////////////////////
//
//    アイテムクラスの処理[item.cpp]
//    Author:西潟栞那汰
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "item.h"
#include "dash_item.h"
#include "reverse_item.h"
#include "manager.h"
#include "player.h"
#include "collision.h"
#include "shadow.h"

//*****************************
// マクロ定義
//*****************************
#define MODEL_SIZE		(D3DXVECTOR3( 0.6f, 0.6f, 0.6f))
#define ITEM_ONE_SIDE	(10.0f)

//******************************
// コンストラクタ
//******************************
CItem::CItem() : CModel(OBJTYPE_ITEM)
{
	m_rot = D3DXVECTOR3(0.0f, 0.05f, 0.0f);//角度
	m_move = D3DXVECTOR3(0.0f, 0.1f, 0.0f);//移動

	m_pCollision = NULL;	//コリジョンのポインタ
	m_pPlayer = NULL;		//プレイヤーのポインタ
	m_pShadow = NULL;		//影のポインタ

	m_bUp = false;			//上限判定
	m_bDeath = false;		//死亡フラグ
}

//******************************
// デストラクタ
//******************************
CItem::~CItem()
{
}

//******************************
// クラス生成
//******************************
CItem * CItem::Create(D3DXVECTOR3 pos,ITEM_EFFECT effect)
{
	//メモリの確保
	CItem *pItem;
	switch (effect)
	{
	case ITEM_EFFECT_DASH:
		pItem = CDashItem::Create(pos);
		break;
	case ITEM_EFFECT_REVERSE:
		pItem = CReverseItem::Create(pos);
		break;
	}

	//影生成
	pItem->m_pShadow = CShadow::Create(D3DXVECTOR3(pos.x, 0.2f, pos.z), D3DXVECTOR3(8.0f, 0.0f, 8.0f));

	return pItem;
}

//******************************
// 初期化処理
//******************************
HRESULT CItem::Init(void)
{
	//モデル初期化
	CModel::Init();
	
	// モデルのサイズの設定
	SetSize(MODEL_SIZE);

	return E_NOTIMPL;
}

//******************************
// 終了処理
//******************************
void CItem::Uninit(void)
{
	//コリジョンの終了処理
	if (m_pCollision != NULL)
	{
		m_pCollision->OutList();
		m_pCollision->Uninit();
		delete m_pCollision;
		m_pCollision = NULL;
	}

	//モデルの終了処理
	CModel::Uninit();
}

//******************************
// 更新処理
//******************************
void CItem::Update(void)
{
	//位置の取得
	D3DXVECTOR3 ItemPos = GetPos();

	if (m_pCollision == NULL)
	{
		m_pCollision = CCollision::CreateSphere(D3DXVECTOR3(ItemPos.x, ItemPos.y + ITEM_ONE_SIDE / 2, ItemPos.z), ITEM_ONE_SIDE / 2);
	}
	else
	{
		m_pCollision->SetPos(D3DXVECTOR3(ItemPos.x, ItemPos.y + ITEM_ONE_SIDE / 2, ItemPos.z));
	}
	// プレイヤーとの当たり判定
	CollisionItem();

	//上下の移動
	MoveUpdate();
	//回転
	RotUpdate();

	if (m_bDeath == true)
	{
		CItem::Uninit();
	}
}

//******************************
// 描画処理
//******************************
void CItem::Draw(void)
{
	CModel::Draw();
}

//******************************
// 移動の更新処理
//******************************
void CItem::MoveUpdate(void)
{
	//位置の取得
	D3DXVECTOR3 ItemPos = GetPos();

	if (m_bUp == false)//上限に到達していないなら
	{
		//位置に移動量を加算
		ItemPos += m_move;
	}
	else
	{
		//位置に移動量を減算
		ItemPos -= m_move;
	}

	//位置の再設定
	SetPos(ItemPos);

	//上限到達
	if (ItemPos.y >= 10.0f)
	{
		m_bUp = true;
	}
	//下限到達
	else if (ItemPos.y <= 3.0f)
	{
		m_bUp = false;
	}
}

//******************************
// 回転の更新処理
//******************************
void CItem::RotUpdate(void)
{
	//角度の取得
	D3DXVECTOR3 ItemRot = GetRot();

	//角度の加算
	ItemRot += m_rot;

	//角度の設定
	SetRot(ItemRot);
}

//******************************
// アイテム当たり判定処理
//******************************
void CItem::CollisionItem(void)
{
	CPlayer * pPlayer = (CPlayer*)GetTop(OBJTYPE_PLAYER);

	while (pPlayer != NULL)
	{
		if (pPlayer->GetPlayerNumber() != m_nPlayerNum)
		{
			if (CCollision::CollisionSphere(m_pCollision, pPlayer->GetCollision()))
			{
				//消滅フラグ
				m_bDeath = true;
				//アイテム効果処理
				ItemEffect(pPlayer);
				//影の終了処理
				if (m_pShadow != NULL)
				{
					m_pShadow->Uninit();
					m_pShadow = NULL;
				}
				return;
			}
		}
		pPlayer = (CPlayer*)pPlayer->GetNext();
	}
}

//******************************
// アイテム効果処理
// Akuthor: 吉田悠人
//******************************
void CItem::ItemEffect(CPlayer*pPlayer)
{

}
