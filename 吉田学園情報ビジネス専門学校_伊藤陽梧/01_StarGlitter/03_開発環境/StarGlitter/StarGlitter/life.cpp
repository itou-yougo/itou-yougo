//=============================================================================
//
// ライフの処理 [life.cpp]
// Author : 伊藤陽梧
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "life.h"
#include "lifepolygon.h"

//=============================================================================
// ライフクラスのコンストラクタ
//=============================================================================
CLife::CLife() :CScene(OBJTYPE_LIFE)
{
	for (int nCount = 0; nCount < MAX_LIFEPOLYGON; nCount++)
	{
		m_pLifepolygon[nCount] = NULL;
	}
	m_nLife = 0;
	m_LifeType = LIFE_TYPE_NONE;
}

//=============================================================================
// ライフクラスのデストラクタ
//=============================================================================
CLife::~CLife()
{

}

//=============================================================================
// ライフクラスのインスタンス生成
//=============================================================================
CLife * CLife::Create(int nLife, LIFETYPE LifeType, OBJTYPE objType)
{
	// pHpのポインタ
	CLife *pHp = NULL;

	// メモリの確保
	pHp = new CLife;

	// pHpがNULLじゃないとき
	if (pHp != NULL)
	{
		pHp->SetLife(nLife);
		pHp->SetType(LifeType, objType);

		// 初期化処理
		pHp->Init();
	}

	// pHpを返す
	return pHp;
}

//=============================================================================
// ライフクラスの初期化処理
//=============================================================================
HRESULT CLife::Init()
{
	switch (m_LifeType)
	{
		// PLAYER1の体力
	case LIFE_TYPE_PLAYER:
		for (int nCount = 0; nCount < m_nLife; nCount++)
		{
			// ライフポリゴンのクリエイト
			m_pLifepolygon[nCount] = m_pLifepolygon[nCount]->Create(
				D3DXVECTOR3((LIFEPOLYGON_SIZE_X * 2) + (50.0f * nCount), 50.0f, 0.0f), 
				D3DXVECTOR3(LIFEPOLYGON_SIZE_X, LIFEPOLYGON_SIZE_Y, 0.0f), 1, 0);
		}
		break;

		// PLAYER2の体力
	case LIFE_TYPE_PLAYER2:
		for (int nCount = 0; nCount < m_nLife; nCount++)
		{
			// ライフポリゴンのクリエイト
			m_pLifepolygon[nCount] = m_pLifepolygon[nCount]->Create(
				D3DXVECTOR3(SCREEN_WIDTH - (LIFEPOLYGON_SIZE_X * 2) - (50.0f * nCount), 50.0f, 0.0f), 
				D3DXVECTOR3(LIFEPOLYGON_SIZE_X, LIFEPOLYGON_SIZE_Y, 0.0f), 1, 0);
		}
		break;
	default:
		break;
	}

	return S_OK;
}

//=============================================================================
// ライフクラスの終了処理
//=============================================================================
void CLife::Uninit(void)
{
	switch (m_LifeType)
	{
		// PLAYER1の体力
	case LIFE_TYPE_PLAYER:
		for (int nCount = 0; nCount < m_nLife; nCount++)
		{
			// ライフポリゴンの終了処理
			m_pLifepolygon[nCount]->Uninit();

			delete m_pLifepolygon[nCount];
			m_pLifepolygon[nCount] = NULL;
		}
		break;
		
		// PLAYER2の体力
	case LIFE_TYPE_PLAYER2:
		for (int nCount = 0; nCount < m_nLife; nCount++)
		{
			// ライフポリゴンの終了処理
			m_pLifepolygon[nCount]->Uninit();

			delete m_pLifepolygon[nCount];
			m_pLifepolygon[nCount] = NULL;
		}
		break;

	default:
		break;
	}

	Release();
}

//=============================================================================
// ライフクラスの更新処理
//=============================================================================
void CLife::Update(void)
{
	switch (m_LifeType)
	{
		// PLAYER1の体力
	case LIFE_TYPE_PLAYER:
		for (int nCount = 0; nCount < m_nLife; nCount++)
		{
			// ライフポリゴンの更新処理
			m_pLifepolygon[nCount]->Update();
		}
		break;

		// PLAYER2の体力
	case LIFE_TYPE_PLAYER2:
		for (int nCount = 0; nCount < m_nLife; nCount++)
		{
			// ライフポリゴンの更新処理
			m_pLifepolygon[nCount]->Update();
		}
		break;

	default:
		break;
	}
}

//=============================================================================
// ライフクラスの描画処理
//=============================================================================
void CLife::Draw(void)
{
	switch (m_LifeType)
	{
		// PLAYER1の体力
	case LIFE_TYPE_PLAYER:
		for (int nCount = 0; nCount < m_nLife; nCount++)
		{
			// ライフポリゴンの描画処理
			m_pLifepolygon[nCount]->Draw();
		}
		break;

		// PLAYER2の体力
	case LIFE_TYPE_PLAYER2:
		for (int nCount = 0; nCount < m_nLife; nCount++)
		{
			// ライフポリゴンの描画処理
			m_pLifepolygon[nCount]->Draw();
		}
		break;

	default:
		break;
	}
}

//=============================================================================
// ライフクラスのライフを返す処理
//=============================================================================
int CLife::GetLife(void)
{
	return m_nLife;
}

//=============================================================================
// ライフクラスのダメージを受けた時の処理
//=============================================================================
void CLife::Damage()
{
	if (m_nLife < 0)
	{
		m_nLife = 0;
	}

	switch (m_LifeType)
	{
		// PLAYER1の体力
	case LIFE_TYPE_PLAYER:
		// m_pLifepolygonがNULLじゃないとき
		if (m_pLifepolygon[m_nLife] != NULL)
		{
			// ライフポリゴンの終了処理
			m_pLifepolygon[m_nLife]->Uninit();
			m_pLifepolygon[m_nLife] = NULL;
		}
		break;

		// PLAYER2の体力
	case LIFE_TYPE_PLAYER2:
		// m_pLifepolygonがNULLじゃないとき
		if (m_pLifepolygon[m_nLife] != NULL)
		{
			// ライフポリゴンの終了処理
			m_pLifepolygon[m_nLife]->Uninit();
			m_pLifepolygon[m_nLife] = NULL;
		}
		break;

	default:
		break;
	}
}

//=============================================================================
// ライフクラスの回復したときの処理
//=============================================================================
void CLife::Cure()
{
	switch (m_LifeType)
	{
	case LIFE_TYPE_PLAYER:
		if (m_nLife - 1 < PLAYER_LIFE)
		{
			// ライフポリゴンの生成
			m_pLifepolygon[m_nLife - 1] = m_pLifepolygon[m_nLife - 1]->Create(
				D3DXVECTOR3((LIFEPOLYGON_SIZE_X * 2) + (50.0f * (m_nLife - 1)), 50.0f, 0.0f), 
				D3DXVECTOR3(LIFEPOLYGON_SIZE_X, LIFEPOLYGON_SIZE_Y, 0.0f), 1, 0);
		}
		break;

	case LIFE_TYPE_PLAYER2:
		if (m_nLife < PLAYER_LIFE + 1)
		{
			// ライフポリゴンの生成
			m_pLifepolygon[m_nLife - 1] = m_pLifepolygon[m_nLife - 1]->Create(
				D3DXVECTOR3(SCREEN_WIDTH - (LIFEPOLYGON_SIZE_X * 2) - (50.0f * (m_nLife - 1)), 50.0f, 0.0f), 
				D3DXVECTOR3(LIFEPOLYGON_SIZE_X, LIFEPOLYGON_SIZE_Y, 0.0f), 1, 0);
		}
		break;

	default:
		break;
	}
}
