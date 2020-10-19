//=============================================================================
//
// マネージャーの処理 [manager.cpp]
// Author : 伊藤陽梧
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "scene2d.h"
#include "input.h"
#include "player.h"
#include "player2.h"
#include "explosion.h"
#include "sound.h"
#include "bg.h"
#include "enemy.h"
#include "bullet.h"
#include "lifepolygon.h"
#include "effect.h"
#include "gauge.h"
#include "ojamaplayer.h"
#include "ojamaplayer2.h"
#include "title.h"
#include "game.h"
#include "enemyexplosion.h"
#include "fade.h"
#include "charge.h"
#include "gauge.h"
#include "chargeshot.h"
#include "input.h"
#include "extraattack.h"
#include "bomb.h"
#include "bombexplosion.h"
#include "bossattack.h"
#include "titlelogo.h"
#include "tutorial.h"
#include "gattyann.h"
#include "text.h"
#include "select.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CTitle *CManager::m_pTitle = NULL;
CTutorial *CManager::m_pTutorial = NULL;
CGame *CManager::m_pGame = NULL;
CResult *CManager::m_pResult = NULL;
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputkeyboard = NULL;
CInputJoypad *CManager::m_pInputJoypad = NULL;
CSound *CManager::m_pSound = NULL;
CFade *CManager::m_pFade = NULL;
CManager::MODE CManager::m_mode = MODE_TITLE;

//=============================================================================
// マネージャークラスのコンストラクタ
//=============================================================================
CManager::CManager()
{
	m_nCountFPS = 0;
}

//=============================================================================
// マネージャークラスのデストラクタ
//=============================================================================
CManager::~CManager()
{

}

//=============================================================================
// マネージャークラスの初期化処理
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	if (m_pRenderer == NULL)
	{
		// レンダラーのメモリの確保
		m_pRenderer = new CRenderer;
	}
	// レンダラーの初期化処理
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{
		return -1;
	}

	if (m_pInputkeyboard == NULL)
	{
		// キーボードのメモリ確保
		m_pInputkeyboard = new CInputKeyboard;
	}
	// キーボードの初期化処理
	if (FAILED(m_pInputkeyboard->Init(hInstance, hWnd)))
	{
		return -1;
	}

	if (m_pInputJoypad == NULL)
	{
		// キーボードのメモリ確保
		m_pInputJoypad = new CInputJoypad;
	}
	// キーボードの初期化処理
	if (FAILED(m_pInputJoypad->Init(hInstance, hWnd)))
	{
		return -1;
	}

	if (m_pSound == NULL)
	{
		// サウンドのメモリ確保
		m_pSound = new CSound;
	}
	// サウンドの初期化処理
	if (FAILED(m_pSound->Init(hWnd)))
	{
		return -1;
	}
	
	// テクスチャのロード
	CBg::Load();
	CPlayer::Load();
	CPlayer2::Load();
	CEnemy::Load();
	CBullet::Load();
	CExplosion::Load();
	CLifepolygon::Load();
	CEffect::Load();
	COjamaplayer::Load();
	COjamaplayer2::Load();
	CEnemyexplosion::Load();
	CCharge::Load();
	CGauge::Load();
	CChargeshot::Load();
	CExtraattck::Load();
	CBomb::Load();
	CBombexplosion::Load();
	CBossattck::Load();
	CTitleLogo::Load();
	CGattyann::Load();
	CText::Load();
	CSelect::Load();


	SetMode(MODE_TITLE);
	m_pFade = CFade::Create();

	return S_OK;
}

//=============================================================================
// マネージャークラスの終了処理
//=============================================================================
void CManager::Uninit(void)
{
	// m_pSoundがNULLじゃないとき
	if (m_pSound != NULL)
	{
		// サウンドの終了処理
		m_pSound->Uninit();

		// メモリの開放(サウンドのクラス)
		delete m_pSound;
		m_pSound = NULL;
	}

	// m_pInputkeyboardがNULLじゃないとき
	if (m_pInputkeyboard != NULL)
	{
		// キーボードの終了処理
		m_pInputkeyboard->Uninit();

		// メモリの開放(キーボードクラス)
		delete m_pInputkeyboard;
		m_pInputkeyboard = NULL;
	}

	// m_pInputJoypadがNULLじゃないとき
	if (m_pInputJoypad != NULL)
	{
		// ジョイパッドの終了処理
		m_pInputJoypad->Uninit();

		// メモリの開放(ジョイパッドクラス)
		delete m_pInputJoypad;
		m_pInputJoypad = NULL;
	}

	// テクスチャのアンロード
	CBg::Unload();
	CPlayer::Unload();
	CPlayer2::Unload();
	CEnemy::Unload();
	CBullet::Unload();
	CExplosion::Unload();
	CLifepolygon::Unload();
	CEffect::Unload();
	COjamaplayer::Unload();
	COjamaplayer2::Unload();
	CEnemyexplosion::Unload();
	CCharge::Unload();
	CGauge::Unload();
	CChargeshot::Unload();
	CExtraattck::Unload();
	CBomb::Unload();
	CBombexplosion::Unload();
	CBossattck::Unload();
	CTitleLogo::Unload();
	CGattyann::Unload();
	CText::Unload();
	CSelect::Unload();

	// オブジェクトの終了処理とメモリの開放
	CScene::ReleaseAll();

	// m_pRendererがNULLじゃないとき
	if (m_pRenderer != NULL)
	{
		// レンダラーの終了処理
		m_pRenderer->Uninit();

		// メモリの開放(レンダリングクラス)
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

//=============================================================================
// マネージャークラスの更新処理
//=============================================================================
void CManager::Update(void)
{
	// CInputのポインタのインスタンス生成の受け取り
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	CInputJoypad *pInputJoypad = CManager::GetInputJoypad();

	switch (m_mode)
	{
	case MODE_TITLE:
		// m_pTitleがNULLじゃないとき
		if (m_pTitle != NULL)
		{
			// 初期化処理
			m_pTitle->Update();
		}
		break;

	case MODE_TUTORIAL:
		// m_pTutorialがNULLじゃないとき
		if (m_pTutorial != NULL)
		{
			// 初期化処理
			m_pTutorial->Update();
		}
		break;

	case MODE_GAME:
		// m_pGameがNULLじゃないとき
		if (m_pGame != NULL)
		{
			// 初期化処理
			m_pGame->Update();
		}
		break;
	}

	// m_pInputkeyboardがNULLじゃないとき
	if (m_pInputkeyboard != NULL)
	{
		m_pInputkeyboard->Update();
	}

	// m_pInputJoypadがNULLじゃないとき
	if (m_pInputJoypad != NULL)
	{
		m_pInputJoypad->Update();
	}

	// m_pRendererがNULLじゃないとき
	if (m_pRenderer != NULL)
	{
		// FPSのセット
		m_pRenderer->SetNumFPS(m_nCountFPS);

		// 更新処理
		m_pRenderer->Update();
	}

}

//=============================================================================
// マネージャークラスの描画処理
//=============================================================================
void CManager::Draw(void)
{
	if (m_pRenderer != NULL)
	{
		// 描画処理
		m_pRenderer->Draw();
	}

	switch (m_mode)
	{
	case MODE_TITLE:
		// m_pTitleがNULLじゃないとき
		if (m_pTitle != NULL)
		{
			// 初期化処理
			m_pTitle->Draw();
		}
		break;

	case MODE_GAME:
		// m_pGameがNULLじゃないとき
		if (m_pGame != NULL)
		{
			// 初期化処理
			m_pGame->Draw();
		}
		break;

		break;
	}
}


//=============================================================================
// マネージャークラスのモードを設定する処理
//=============================================================================
void CManager::SetMode(MODE mode)
{
	m_mode = mode;

	if (m_pTitle != NULL)
	{
		m_pTitle->Uninit();

		delete m_pTitle;
		m_pTitle = NULL;
	}

	if (m_pTutorial != NULL)
	{
		m_pTutorial->Uninit();

		delete m_pTutorial;
		m_pTutorial = NULL;
	}

	if (m_pGame != NULL)
	{
		m_pGame->Uninit();

		delete m_pGame;
		m_pGame = NULL;
	}

	switch (m_mode)
	{
	case MODE_TITLE:
		if (m_pTitle == NULL)
		{
			// タイトルのクリエイト
			m_pTitle = CTitle::Create();
		}
		break;

	case MODE_TUTORIAL:
		if (m_pTutorial == NULL)
		{
			// チュートリアルのクリエイト
			m_pTutorial = CTutorial::Create();
		}
		break;

	case MODE_GAME:
		if (m_pGame == NULL)
		{
			// ゲームのクリエイト
			m_pGame = CGame::Create();
		}
		break;
	}
}

//=============================================================================
// マネージャークラスのモードを設定する処理
//=============================================================================
CManager::MODE CManager::GetMode(void)
{
	return m_mode;
}

//=============================================================================
// マネージャークラスのレンダラーのポインタを渡す処理
//=============================================================================
CRenderer* CManager::GetRenderer(void)
{
	// m_pRendererを返す
	return m_pRenderer;
}

//=============================================================================
// マネージャークラスのキーボードのポインタを渡す処理
//=============================================================================
CInputKeyboard* CManager::GetInputKeyboard(void)
{
	// m_pInputkeyboardを返す
	return m_pInputkeyboard;
}

//=============================================================================
// マネージャークラスのジョイパッドのポインタを渡す処理
//=============================================================================
CInputJoypad * CManager::GetInputJoypad(void)
{
	// m_pInputJoypadを返す
	return m_pInputJoypad;
}

//=============================================================================
// マネージャークラスのサウンドのポインタを渡す処理
//=============================================================================
CSound * CManager::GetSound(void)
{
	// m_pSoundを返す
	return m_pSound;
}

//=============================================================================
// マネージャークラスのフェードのポインタを渡す処理
//=============================================================================
CFade * CManager::GetFade(void)
{
	// m_pFadeを返す
	return m_pFade;
}
