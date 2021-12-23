////////////////////////////////////////////////////
//
//    紙吹雪ファクトリークラスの処理[confetti_factory.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//=============================
// インクルード
//=============================
#include "confetti_factory.h"
#include "confetti.h"

//**********************************
// マクロ定義
//**********************************
#define CONFETTI_INTERVAL (2)

//=============================
// コンストラクタ
//=============================
CConfettiFactory::CConfettiFactory() : CScene(OBJTYPE_SYSTEM)
{
	m_nLife = 0;
	m_nCntConfetti = 0;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

//=============================
// デストラクタ
//=============================
CConfettiFactory::~CConfettiFactory()
{
}

//=============================
// クリエイト
//=============================
CConfettiFactory * CConfettiFactory::Create(D3DXCOLOR col, int nLife)
{
	// メモリの確保
	CConfettiFactory *pConfettiFactory = new CConfettiFactory;
	// 初期化
	pConfettiFactory->Init();
	pConfettiFactory->m_nLife = nLife;
	pConfettiFactory->m_col = col;

	return pConfettiFactory;
}

//=============================
// 初期化処理
//=============================
HRESULT CConfettiFactory::Init(void)
{
	
	m_nCntConfetti = 0;
	return S_OK;
}

//=============================
// 終了処理
//=============================
void CConfettiFactory::Uninit(void)
{
	// 開放処理
	Release();
}


//=============================
// 更新処理
//=============================
void CConfettiFactory::Update(void)
{
	m_nCntConfetti++;

	if (m_nCntConfetti % CONFETTI_INTERVAL == 0)
	{
		CConfetti::Create(D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f), m_col, D3DXToRadian(-60));
		CConfetti::Create(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), m_col, D3DXToRadian(-60 - 60));
	}

	if (m_nLife >= 0)
	{
		m_nLife--;
		if (m_nLife < 0)
		{
			Uninit();
		}
	}
}

//=============================
// 描画処理
//=============================
void CConfettiFactory::Draw(void)
{
}