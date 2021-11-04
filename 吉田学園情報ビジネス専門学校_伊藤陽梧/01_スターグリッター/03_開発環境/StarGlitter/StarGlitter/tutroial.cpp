//=============================================================================
//
// チュートリアルの処理 [tutroial.cpp]
// Author : 伊藤陽梧
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "tutorial.h"
#include "renderer.h"
#include "player.h"
#include "input.h"
#include "sound.h"
#include "bg.h"
#include "manager.h"
#include "fade.h"
#include "gattyann.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define GATTYAN1_POS (D3DXVECTOR3(SCREEN_CENTER_X / 4, SCREEN_HEIGHT + SCREEN_CENTER_Y, 0.0f))
#define GATTYAN2_POS (D3DXVECTOR3(SCREEN_CENTER_X - SCREEN_CENTER_X / 4, -SCREEN_CENTER_Y, 0.0f))
#define GATTYAN3_POS (D3DXVECTOR3(SCREEN_CENTER_X + SCREEN_CENTER_X / 4, SCREEN_HEIGHT + SCREEN_CENTER_Y, 0.0f))
#define GATTYAN4_POS (D3DXVECTOR3(SCREEN_WIDTH - SCREEN_CENTER_X / 4, -SCREEN_CENTER_Y, 0.0f))

#define GTTYANN_SIZE (D3DXVECTOR3(432.0f, 1080.0f, 0.0f))

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CTutorial::m_pTexture;

//=============================================================================
// チュートリアルクラスのコンストラクタ
//=============================================================================
CTutorial::CTutorial()
{
	m_bTrriger = false;
}

//=============================================================================
// チュートリアルクラスのデストラクタ
//=============================================================================
CTutorial::~CTutorial()
{

}

//=============================================================================
// 背景クラスのインスタンス生成
//=============================================================================
CTutorial *CTutorial::Create()
{
	// pTitleのポインタ
	CTutorial *pTutorial = NULL;

	// メモリの確保
	pTutorial = new CTutorial;

	// pTutorialがNULLじゃないとき
	if (pTutorial != NULL)
	{
		// 初期化処理
		pTutorial->Init();
	}

	// pTutorialを返す
	return pTutorial;
}

//=============================================================================
// チュートリアルクラスの初期化処理
//=============================================================================
HRESULT CTutorial::Init()
{
	// m_pBgメモリの確保
	CBg::Create(CBg::BGTYPE_TUTORIAL, CScene::OBJTYPE_BG);

	// サウンドの停止
	CManager::GetSound()->StopSound(CManager::GetSound()->SOUND_LABEL_TITLEBGM);
	return S_OK;
}

//=============================================================================
// チュートリアルクラスの終了処理
//=============================================================================
void CTutorial::Uninit(void)
{
	// オブジェクトの終了処理とメモリの開放
	CScene::NotFadeReleaseAll();
}

//=============================================================================
// チュートリアルクラスの更新処理
//=============================================================================
void CTutorial::Update(void)
{
	// CInputのポインタのインスタンス生成の受け取り
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	CInputJoypad *pInputJoypad = CManager::GetInputJoypad();

	// 押していないとき
	if (m_bTrriger == false)
	{
		if (pInput->GetKeyboardTrigger(DIK_RETURN) && CManager::GetFade()->GetFade() == CFade::FADE_NOME)
		{
			// ガッチャンの生成
			CGattyann::Create(GATTYAN1_POS, GTTYANN_SIZE, CGattyann::GATTYANN_5);
			CGattyann::Create(GATTYAN2_POS, GTTYANN_SIZE, CGattyann::GATTYANN_6);
			CGattyann::Create(GATTYAN3_POS, GTTYANN_SIZE, CGattyann::GATTYANN_7);
			CGattyann::Create(GATTYAN4_POS, GTTYANN_SIZE, CGattyann::GATTYANN_8);

			// 押していないとき
			m_bTrriger = true;
		}
		else if (pInputJoypad->GetJoypadTrigger(PLAYER_1, CInputJoypad::BUTTON_START) && CManager::GetFade()->GetFade() == CFade::FADE_NOME)
		{
			// ガッチャンの生成
			CGattyann::Create(GATTYAN1_POS, GTTYANN_SIZE, CGattyann::GATTYANN_5);
			CGattyann::Create(GATTYAN2_POS, GTTYANN_SIZE, CGattyann::GATTYANN_6);
			CGattyann::Create(GATTYAN3_POS, GTTYANN_SIZE, CGattyann::GATTYANN_7);
			CGattyann::Create(GATTYAN4_POS, GTTYANN_SIZE, CGattyann::GATTYANN_8);

			// 押していないとき
			m_bTrriger = true;
		}
	}
}

//=============================================================================
// チュートリアルクラスの描画処理
//=============================================================================
void CTutorial::Draw(void)
{

}