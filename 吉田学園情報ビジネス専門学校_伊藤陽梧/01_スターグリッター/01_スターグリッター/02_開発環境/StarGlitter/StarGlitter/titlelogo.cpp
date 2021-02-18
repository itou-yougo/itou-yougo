//=============================================================================
//
// タイトルロゴの処理 [titlelogo.cpp]
// Author : 伊藤陽梧
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "titlelogo.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "gattyann.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TITLE_POS (350.0f)
#define START_COUNT (40)

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CTitleLogo::m_pTexture[MAX_LOGO_TEXTURE] = {};

//=============================================================================
// タイトルロゴクラスのコンストラクタ
//=============================================================================
CTitleLogo::CTitleLogo()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCount = 0;
	m_nAlpha = 0;
	m_bUse = true;
	m_LogoType = LOGOTYPE_SIROHAIKEI;
}

//=============================================================================
// タイトルロゴクラスのデストラクタ
//=============================================================================
CTitleLogo::~CTitleLogo()
{

}

//=============================================================================
// タイトルロゴクラスのテクスチャ読み込み
//=============================================================================
HRESULT CTitleLogo::Load(void)
{
	// インスタンス生成したものを受け取る
	CRenderer *pRenderer = CManager::GetRenderer();

	// デバイスを受け取る
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_SIROHAIKEI, &m_pTexture[LOGOTYPE_NONE]);		  // なし
	D3DXCreateTextureFromFile(pDevice, TEXTURE_SIROHAIKEI, &m_pTexture[LOGOTYPE_SIROHAIKEI]); // 白い背景
	D3DXCreateTextureFromFile(pDevice, TEXTURE_TITLELOGO, &m_pTexture[LOGOTYPE_TITLE]);		  // タイトル
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PRESSENTER, &m_pTexture[LOGOTYPE_PRESSENTER]); // プレスエンター

	return S_OK;
}

//=============================================================================
// タイトルロゴクラスのテクスチャ破棄
//=============================================================================
void CTitleLogo::Unload(void)
{
	for (int nCount = 0; nCount < MAX_LOGO_TEXTURE; nCount++)
	{
		// テクスチャの破棄
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
// タイトルロゴクラスのインスタンス生成
//=============================================================================
CTitleLogo * CTitleLogo::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, LOGOTYPE logoType)
{
	// CTitleLogoのポインタ
	CTitleLogo *pText = NULL;

	// メモリの確保
	pText = new CTitleLogo;

	// pTextがNULLじゃないとき
	if (pText != NULL)
	{
		// 座標やサイズのセット
		pText->SetTitleLogo(pos, size, logoType);

		// 初期化処理
		pText->Init();
	}

	// pNumberを返す
	return pText;
}

//=============================================================================
// タイトルロゴクラスの初期化処理
//=============================================================================
HRESULT CTitleLogo::Init()
{
	// CScene2Dの初期化処理
	CScene2D::Init();

	// m_pTextureがNULLじゃないとき
	if (m_pTexture[m_LogoType] != NULL)
	{
		//　テクスチャの設定
		BindTexture(m_pTexture[m_LogoType]);
	}

	// プレスエンター
	if (m_LogoType == LOGOTYPE_PRESSENTER)
	{
		// 色の設定
		SetColor(255, 255, 255, m_nAlpha);
	}

	return S_OK;
}

//=============================================================================
// タイトルロゴクラスの終了処理
//=============================================================================
void CTitleLogo::Uninit(void)
{
	// CScene2Dの終了処理
	CScene2D::Uninit();
}

//=============================================================================
// タイトルロゴクラスの更新処理
//=============================================================================
void CTitleLogo::Update(void)
{
	// CScene2Dの更新処理
	CScene2D::Update();

	// 座標の受け取り
	m_pos = GetPosition();

	switch (m_LogoType)
	{
		// タイトル
	case LOGOTYPE_TITLE:
		TitleLogo();
		break;

		// プレスエンター
	case LOGOTYPE_PRESSENTER:
		PlessEnter();
		break;

	default:
		break;
	}

	// 座標のセット
	SetPosition(m_pos);
}

//=============================================================================
// タイトルロゴクラスの描画処理
//=============================================================================
void CTitleLogo::Draw(void)
{
	// CScene2Dの描画処理
	CScene2D::Draw();
}

//=============================================================================
// タイトルロゴクラスのタイトルロゴを動かす処理
//=============================================================================
void CTitleLogo::TitleLogo(void)
{
	// CInputのポインタのインスタンス生成の受け取り
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	CInputJoypad *pInputJoypad = CManager::GetInputJoypad();

	m_pos.y += 3.0f;

	// 座標がTITLE_POSより大きいとき
	if (m_pos.y > TITLE_POS)
	{
		m_pos.y = TITLE_POS;
	}

	//エンターキー押されたかどうか
	if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN))
	{
		m_pos.y = TITLE_POS;
	}
	//startが押されたかどうか
	else if (pInputJoypad->GetJoypadTrigger(PLAYER_1, CInputJoypad::BUTTON_START))
	{
		m_pos.y = TITLE_POS;
	}

	// m_bUseが使用状態の時
	if (m_bUse == true)
	{
		// 座標がTITLE_POSと同じとき
		if (m_pos.y == TITLE_POS)
		{
			// プレスエンターの生成
			CTitleLogo::Create(D3DXVECTOR3(SCREEN_CENTER_X, 800.0f, 0.0f), D3DXVECTOR3(1220.0f, 166.0f, 0.0f), CTitleLogo::LOGOTYPE_PRESSENTER);

			// m_bUseを使用しない状態にする
			m_bUse = false;
		}
	}
}

//=============================================================================
// タイトルロゴクラスのプレスエンターの文字を動かす処理
//=============================================================================
void CTitleLogo::PlessEnter(void)
{
	// CInputのポインタのインスタンス生成の受け取り
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	CInputJoypad *pInputJoypad = CManager::GetInputJoypad();

	// m_bUseが使用状態の時
	if (m_bUse == true)
	{
		m_nAlpha += 3;

		// 色のセット
		SetColor(255, 255, 255, m_nAlpha);

		//m_nAlphaが255以上になったら
		if (m_nAlpha >= 255)
		{
			// m_bUseを使用しない状態にする
			m_bUse = false;
		}
	}
	// m_bUseが使用しない状態の時
	else if (m_bUse == false)
	{
		m_nAlpha -= 3;

		// 色のセット
		SetColor(255, 255, 255, m_nAlpha);

		//m_nAlphaが0以下になったら
		if (m_nAlpha <= 0)
		{
			// m_bUseを使用する状態にする
			m_bUse = true;
		}
	}

	m_nCount++;

	// カウントがSTART_COUNT以上になったら
	if (m_nCount >= START_COUNT)
	{
		//エンターキー押されたかどうか
		if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) && CManager::GetFade()->GetFade() == CFade::FADE_NOME)
		{
			if (CManager::GetFade() != NULL)
			{
				// モードをチュートリアルにする
				CManager::GetFade()->SetFade(CManager::MODE_TUTORIAL);

				// サウンドの再生
				CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_PRESSENTER);
			}
		}
		//STARTが押されたかどうか
		else if (pInputJoypad->GetJoypadTrigger(PLAYER_1, CInputJoypad::BUTTON_START) && CManager::GetFade()->GetFade() == CFade::FADE_NOME)
		{
			if (CManager::GetFade() != NULL)
			{
				// モードをチュートリアルにする
				CManager::GetFade()->SetFade(CManager::MODE_TUTORIAL);

				// サウンドの再生
				CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_PRESSENTER);
			}
		}
	}
}
