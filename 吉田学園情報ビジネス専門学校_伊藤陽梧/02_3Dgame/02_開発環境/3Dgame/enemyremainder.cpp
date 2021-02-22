//=============================================================================
//
// 倒す敵の数の処理 [enemyremainder.cpp]
// Author : 伊藤陽梧
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "enemyremainder.h"
#include "number.h"
#include "game.h"
#include "ui.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CEnemyremainder::CEnemyremainder(int nPriority)
{
	memset(m_apNumber, 0, sizeof(m_apNumber));
}

//=============================================================================
// デストラクタ
//=============================================================================
CEnemyremainder::~CEnemyremainder()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CEnemyremainder * CEnemyremainder::Create(D3DXVECTOR3 pos)
{
	CEnemyremainder *pEnemyremainder;
	pEnemyremainder = new CEnemyremainder;
	pEnemyremainder->m_pos = pos;
	pEnemyremainder->Init();
	return pEnemyremainder;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CEnemyremainder::Init(void)
{
	// あと何体の配置
	CUi::Create(m_pos, D3DXVECTOR3(422.5f, 65.5f, 0.0f), CUi::TYPE_ENEMYREMAINDER);

	// 数字の配置
	m_apNumber[0] = CNumber::Create(m_pos - D3DXVECTOR3(30.0f, 0.0f, 0.0f), D3DXVECTOR3(70.0f, 95.5f, 0.0f));
	m_apNumber[1] = CNumber::Create(m_pos + D3DXVECTOR3(30.0f, 0.0f, 0.0f), D3DXVECTOR3(70.0f, 95.5f, 0.0f));
	return E_NOTIMPL;
}

//=============================================================================
// 終了処理
//=============================================================================
void CEnemyremainder::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER_CREATE; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			// 終了処理
			m_apNumber[nCount]->Uninit();

			// 消してNULLにする
			delete m_apNumber[nCount];
			m_apNumber[nCount] = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CEnemyremainder::Update(void)
{
	// 数字の設定
	for (int nCount = 0; nCount < MAX_NUMBER_CREATE; nCount++)
	{
		int nScore = (int)pow(10.0f, MAX_NUMBER_CREATE - nCount);
		int nScore2 = (int)pow(10.0f, MAX_NUMBER_CREATE - nCount - 1);
		int nAnswer = (MAX_ENEMY_NUM - CGame::GetEnemyDeathTotal()) % nScore / nScore2;

		m_apNumber[nCount]->SetNumber(nAnswer);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CEnemyremainder::Draw(void)
{
	// 描画処理
	for (int nCount = 0; nCount < MAX_NUMBER_CREATE; nCount++)
	{
		m_apNumber[nCount]->Draw();
	}
}