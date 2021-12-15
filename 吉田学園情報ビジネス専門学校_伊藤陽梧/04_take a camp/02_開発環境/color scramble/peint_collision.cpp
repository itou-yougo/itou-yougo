//=============================================================================
//
// 塗り処理 [peint_collision.cpp]
// Author : 吉田 悠人
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "peint_collision.h"
#include "collision.h"
#include "player.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_LIFE (2)	//マックスライフ

//=============================================================================
// コンストラクタ
//=============================================================================
CPeintCollision::CPeintCollision()
{
	m_nPlayerNum	= 0;
	m_nColorNumber  = 0;
	m_bDeath		= false;
	m_pCollision	= NULL;
	m_nLife			= 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CPeintCollision::~CPeintCollision()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CPeintCollision * CPeintCollision::Create(D3DXVECTOR3 pos, int nPlayerNum)
{
	//メモリ確保
	CPeintCollision * pPeintCollision = NULL;
	pPeintCollision = new CPeintCollision;

	//NULLチェック
	if (pPeintCollision != NULL)
	{
		//初期化処理
		pPeintCollision->Init();
		//位置設定
		pPeintCollision->m_pos = (pos);
		//サイズ設定
		pPeintCollision->m_size = (D3DXVECTOR3(0.5f, 0.5f, 0.5f));
		//プレイヤーナンバー取得
		pPeintCollision->m_nPlayerNum = nPlayerNum;
		//カラー番号取得(ナンバーを取得後にする)
		pPeintCollision->ColorLoad();
		//ライフ
		pPeintCollision->m_nLife = MAX_LIFE;

		// オブジェクトタイプ
		pPeintCollision->SetPriority(OBJTYPE_PEINT);
	}
	return pPeintCollision;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPeintCollision::Init(void)
{	
	// 初期化処理
	//CScene::Init();

	//// モデル割り当て
	//BindModel(CResourceModel::GetModel(CResourceModel::MODEL_BULLET01));

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPeintCollision::Uninit(void)
{
	if (m_pCollision != NULL)
	{
		m_pCollision->OutList();
		m_pCollision->Uninit();
		delete m_pCollision;
		m_pCollision = NULL;
	}
	// 終了処理
	Release();

}

//=============================================================================
// 更新処理
//=============================================================================
void CPeintCollision::Update(void)
{
	// 位置の取得
	//D3DXVECTOR3 Pos = GetPos();

	if (m_pCollision == NULL)
	{
		m_pCollision = CCollision::CreateSphere(D3DXVECTOR3(m_pos.x, m_pos.y + 20.0f / 2, m_pos.z), 10 / 2);
	}
	else
	{
		m_pCollision->SetPos(D3DXVECTOR3(m_pos.x, m_pos.y + 20.0f / 2, m_pos.z));
	}

	//ライフDOWN
	m_nLife--;
	//ライフがゼロ以下になると
	if (m_nLife<=0)
	{
		//死亡フラグ
		Death();

		m_nLife = 0;
	}

	//死亡フラグ
	if (m_bDeath)
	{
		Uninit();
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void CPeintCollision::Draw(void)
{
	// 描画処理
	//CScene3d::Draw();
}

//=============================================================================
// カラー番号読み込み
//=============================================================================
void CPeintCollision::ColorLoad(void)
{
	CPlayer * pPlayer = (CPlayer*)GetTop(OBJTYPE_PLAYER);

	while (pPlayer != NULL)
	{
		if (m_nPlayerNum == pPlayer->GetPlayerNumber())
		{
			//プレイヤーのカラー取得
			m_nColorNumber = pPlayer->GetColorNumber();
			return;
		}
		pPlayer = (CPlayer*)pPlayer->GetNext();
	}
}

//=============================================================================
// 死亡フラグオン
//=============================================================================
void CPeintCollision::Death()
{
	m_bDeath = true;
}

