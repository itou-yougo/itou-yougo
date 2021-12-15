//=============================================================================
//
// 弾の処理 [Bullet.cpp]
// Author : 佐藤颯紀
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "bullet.h"
#include "manager.h"
#include "player.h"
#include "collision.h"
#include "peint_collision.h"
#include "kill_count.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MODEL_SIZE D3DXVECTOR3(0.5f, 0.5f, 0.5f)	// サイズ
#define BULLET_LIFE		(20)	// 弾のライフ
#define COLLISION_SIZE (D3DXVECTOR3(10.0f,10.0f,10.0f))	// 当たり判定の大きさ
#define BULLET_COLOR D3DXCOLOR(0.0f,0.0f,0.0f,0.0f)
#define BULLET_ONE_SIDE 20.0f
#define BULLET_COLLISION_SIZE 10.0f
#define PEINT_SIDE (20.0f)	//塗る用の当たり判定の一辺の大きさ

//=============================================================================
// 静的メンバー変数宣言
//=============================================================================
D3DXVECTOR3 CBullet::m_PeintPos[MAX_PEINT] = 
{
	D3DXVECTOR3(0.0f,0.0f,0.0f),
	D3DXVECTOR3(-PEINT_SIDE,0.0f,0.0f),
	D3DXVECTOR3(PEINT_SIDE,0.0f,0.0f),
	D3DXVECTOR3(0.0f,0.0f,-PEINT_SIDE),
	D3DXVECTOR3(0.0f,0.0f,PEINT_SIDE),
};

//=============================================================================
// コンストラクタ
//=============================================================================
CBullet::CBullet() :CModel(OBJTYPE_BULLET)
{
	m_move = VEC3_ZERO;		// 移動量
	m_size = VEC3_ZERO;		// サイズ
	m_nLife = 0;			// ライフ
	m_fSpeed = 0.0f;		// 速さ
	m_pCollision = NULL;	// 当たり判定
	memset(&m_pPeintCollision, 0, sizeof(m_pPeintCollision));
	m_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}
//=============================================================================
// デストラクタ
//=============================================================================
CBullet::~CBullet()
{

}

//=============================================================================
// 生成処理
//=============================================================================
CBullet * CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nPlayerNum)
{
	CBullet *pBullet = NULL;

	// メモリの確保
	pBullet = new CBullet;

	// 初期化処理呼び出し
	pBullet->Init();

	pBullet->SetPos(pos);

	pBullet->m_move = move;

	pBullet->m_nPlayerNum = nPlayerNum;

	// オブジェクトタイプ
	pBullet->SetPriority(OBJTYPE_BULLET);

	return pBullet;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBullet::Init(void)
{
	// 初期化処理
	CModel::Init();

	// サイズの設定
	SetSize(MODEL_SIZE);

	// カラーの設定
	m_color = BULLET_COLOR;

	// モデル割り当て
	BindModel(CResourceModel::GetModel(CResourceModel::MODEL_BULLET01));
	
	// ライフ
	m_nLife = BULLET_LIFE;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBullet::Uninit()
{
	if (m_pCollision != NULL)
	{
		m_pCollision->OutList();
		m_pCollision->Uninit();
		delete m_pCollision;
		m_pCollision = NULL;
	}
	// 終了処理
	CModel::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CBullet::Update()
{
	// 位置の取得
	D3DXVECTOR3 BulletPos = GetPos();

	if (m_pCollision == NULL)
	{
		m_pCollision = CCollision::CreateSphere(D3DXVECTOR3(BulletPos.x, BulletPos.y + BULLET_ONE_SIDE / 2, BulletPos.z), BULLET_COLLISION_SIZE / 2);
	}
	else
	{
		m_pCollision->SetPos(D3DXVECTOR3(BulletPos.x, BulletPos.y + BULLET_ONE_SIDE / 2, BulletPos.z));
	}
	// プレイヤーとの当たり判定
	CollisionPlayer();

	// 位置に移動量を加算する
	BulletPos += m_move;

	// ライフを毎フレームごと減らしていく
	m_nLife--;

	// 位置の設定
	SetPos(BulletPos);

	// ライフが０になったら
	if (m_nLife == 0)
	{
		// 終了処理
		Uninit();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CBullet::Draw()
{
	// 色の設定
	D3DXMATERIAL* mat = (D3DXMATERIAL*)GetModelData()->pBuffMat->GetBufferPointer();
	mat->MatD3D.Ambient = m_color;
	mat->MatD3D.Diffuse = m_color;
	mat->MatD3D.Specular = m_color;
	mat->MatD3D.Emissive = m_color;

	// 描画処理
	CModel::Draw();
}

//=============================================================================
// 当たり判定の処理
//=============================================================================
void CBullet::CollisionPlayer(void)
{
	CPlayer * pPlayer = (CPlayer*)GetTop(OBJTYPE_PLAYER);

	while (pPlayer != NULL)
	{
		//自分以外のプレイヤーか＆そのプレイヤーが無敵フラグがオフ
		if (pPlayer->GetPlayerNumber() != m_nPlayerNum
			&&!pPlayer->GetInvincible())
		{
			//当たり判定処理
			if (CCollision::CollisionSphere(m_pCollision, pPlayer->GetCollision()))
			{
				// 死亡状態にする
				pPlayer->Death();
				//キル時のカウント
				KillCount();
				//タイルを塗る用の当たり判定生成
				for (int nPeint = 0; nPeint < MAX_PEINT; nPeint++)
				{
					m_pPeintCollision[nPeint] = CPeintCollision::Create(m_PeintPos[nPeint]+GetPos(),m_nPlayerNum);
				}

				return;
			}
		}
			pPlayer = (CPlayer*)pPlayer->GetNext();
	}
}

//=============================================================================
// キルカウント処理
//=============================================================================
void CBullet::KillCount(void)
{
	CPlayer * pPlayer = (CPlayer*)GetTop(OBJTYPE_PLAYER);

	while (pPlayer != NULL)
	{
		if (pPlayer->GetPlayerNumber() == m_nPlayerNum)
		{
			//キルカウントを進める
			pPlayer->GetKillCount()->AddKill();
			return;
		}
		pPlayer = (CPlayer*)pPlayer->GetNext();
	}

}
