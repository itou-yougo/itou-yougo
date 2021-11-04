//=============================================================================
//
// セレクトの処理 [select.cpp]
// Author : 伊藤陽梧
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "select.h"
#include "renderer.h"
#include "manager.h"
#include "text.h"
#include "input.h"
#include "fade.h"
#include "gattyann.h"
#include "sound.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CSelect::m_apTexture[MAX_SELECT_TEXTURE] = {};

//=============================================================================
// セレクトクラスのコンストラクタ
//=============================================================================
CSelect::CSelect() :CScene2D(OBJTYPE_TEXT)
{
	m_pVtxBuff = NULL;
	m_pText[0] = NULL;
	m_pText[1] = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCount = 0;
	m_nCountSelect = 0;
	m_bButtonPress = false;
	m_pSelectType = SELECTTYPE_KUROHAIKEI;
}

//=============================================================================
// セレクトクラスのデストラクタ
//=============================================================================
CSelect::~CSelect()
{

}

//=============================================================================
// セレクトクラスのテクスチャ読み込み
//=============================================================================
HRESULT CSelect::Load(void)
{
	// インスタンス生成したものを受け取る
	CRenderer *pRenderer = CManager::GetRenderer();

	// デバイスを受け取る
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_MENUHAIKEI, &m_apTexture[SELECTTYPE_KUROHAIKEI]); // 黒い背景
	D3DXCreateTextureFromFile(pDevice, TEXTURE_MENU, &m_apTexture[SELECTTYPE_MENU]);			 // メニュー

	return S_OK;
}

//=============================================================================
// セレクトクラスのテクスチャ破棄
//=============================================================================
void CSelect::Unload(void)
{
	for (int nCount = 0; nCount < MAX_SELECT_TEXTURE; nCount++)
	{
		// テクスチャの破棄
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
// セレクトクラスのインスタンス生成
//=============================================================================
CSelect * CSelect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, SELECTTYPE SelectType)
{
	// CTextのポインタ
	CSelect *pText = NULL;

	// メモリの確保
	pText = new CSelect;

	// pTextがNULLじゃないとき
	if (pText != NULL)
	{
		// 座標やサイズのセット
		pText->SetSelect(pos, size, SelectType);

		// 初期化処理
		pText->Init();
	}

	// pNumberを返す
	return pText;
}

//=============================================================================
// セレクトクラスの初期化処理
//=============================================================================
HRESULT CSelect::Init()
{
	// CScene2Dの初期化処理
	CScene2D::Init();

	//　テクスチャの設定
	BindTexture(m_apTexture[m_pSelectType]);

	// m_pSelectTypeがメニューの時
	if (m_pSelectType == SELECTTYPE_MENU)
	{
		// テキストクラスのクリエイトと色のセット
		m_pText[0] = m_pText[0]->Create(D3DXVECTOR3(m_pos.x, m_pos.y - 100.0f, m_pos.z), D3DXVECTOR3(662.0f, 150.0f, 0.0f), CText::TEXTTYPE_RESTART);
		m_pText[0]->SetColor(255, 255, 255, 255);
		m_pText[1] = m_pText[1]->Create(D3DXVECTOR3(m_pos.x, m_pos.y + 100.0f, m_pos.z), D3DXVECTOR3(695.0f, 132.0f, 0.0f), CText::TEXTTYPE_MODORU);
		m_pText[1]->SetColor(255, 255, 255, 100);
	}

	SetObjType(OBJTYPE_TEXT);
	return S_OK;
}

//=============================================================================
// セレクトクラスの終了処理
//=============================================================================
void CSelect::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_TEXT; nCount++)
	{
		// m_pTextがNULLじゃないとき
		if (m_pText[nCount] != NULL)
		{
			// m_pTextの終了処理
			m_pText[nCount]->Uninit();
			m_pText[nCount] = NULL;
		}
	}

	// CScene2Dの終了処理
	CScene2D::Uninit();
}

//=============================================================================
// セレクトクラスの更新処理
//=============================================================================
void CSelect::Update(void)
{
	// CScene2Dの更新処理
	CScene2D::Update();

	Menu();
}

//=============================================================================
// セレクトクラスの描画処理
//=============================================================================
void CSelect::Draw(void)
{
	// CScene2Dの描画処理
	CScene2D::Draw();
}

//=============================================================================
// セレクトクラスのメニューの処理
//=============================================================================
void CSelect::Menu(void)
{
	CInputJoypad *pInputJoypad = CManager::GetInputJoypad();

	// m_pSelectTypeがメニューの時
	if (m_pSelectType == SELECTTYPE_MENU)
	{
		// 選ぶ処理
		Select();

		// 決める処理
		Decision();
	}
}

//=============================================================================
// セレクトクラスの選ぶ処理
//=============================================================================
void CSelect::Select(void)
{
	CInputJoypad *pInputJoypad = CManager::GetInputJoypad();

	//コントローラーの情報を取得する
	DIJOYSTATE2 Controller = pInputJoypad->GetController(PLAYER_1);
	// 下
	if (Controller.lY > 0)
	{
		m_nCount++;
	}
	// 上
	if (Controller.lY < 0)
	{
		m_nCount--;
	}

	Controller = pInputJoypad->GetController(PLAYER_2);
	// 下
	if (Controller.lY > 0)
	{
		// m_nCountの減算
		m_nCount++;
	}
	// 上
	if (Controller.lY < 0)
	{
		// m_nCountの加算
		m_nCount--;
	}

	// 選んだ時のカウントの減算
	m_nCountSelect--;

	// ボタンを押してないとき
	if (m_bButtonPress == false)
	{
		// 選んだ時のカウントが0より小さいとき
		if (m_nCountSelect < 0)
		{
			// m_nCountが0より小さいとき
			if (m_nCount < 0)
			{
				m_nCount = 0;

				// テキストの色の設定
				m_pText[m_nCount]->SetColor(255, 255, 255, 255);
				m_pText[m_nCount + 1]->SetColor(255, 255, 255, 100);

				// サウンドの再生
				CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_MENUKIRIKAE);

				// 選んだ時のカウントに代入する
				m_nCountSelect = 50;
			}

			// m_nCountが1より大きいとき
			if (m_nCount > 1)
			{
				m_nCount = 1;

				// テキストの色の設定
				m_pText[m_nCount]->SetColor(255, 255, 255, 255);
				m_pText[m_nCount - 1]->SetColor(255, 255, 255, 100);

				// サウンドの再生
				CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_MENUKIRIKAE);

				// 選んだ時のカウントに代入する
				m_nCountSelect = 50;
			}
		}
	}
}

//=============================================================================
// セレクトクラスの決める処理
//=============================================================================
void CSelect::Decision(void)
{
	CInputJoypad *pInputJoypad = CManager::GetInputJoypad();

	// カウントが0になったら
	if (m_nCount == 0)
	{
		// ボタンを押してないとき
		if (m_bButtonPress == false)
		{
			// Aボタンを押したら
			if (pInputJoypad->GetJoypadTrigger(PLAYER_1, CInputJoypad::BUTTON_A))
			{
				// ガッチャンのクリエイト
				CGattyann::Create(D3DXVECTOR3(SCREEN_CENTER_X / 4, SCREEN_HEIGHT + SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(432.0f, 1080.0f, 0.0f), CGattyann::GATTYANN_5);
				CGattyann::Create(D3DXVECTOR3(SCREEN_CENTER_X - SCREEN_CENTER_X / 4, -SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(432.0f, 1080.0f, 0.0f), CGattyann::GATTYANN_6);
				CGattyann::Create(D3DXVECTOR3(SCREEN_CENTER_X + SCREEN_CENTER_X / 4, SCREEN_HEIGHT + SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(432.0f, 1080.0f, 0.0f), CGattyann::GATTYANN_7);
				CGattyann::Create(D3DXVECTOR3(SCREEN_WIDTH - SCREEN_CENTER_X / 4, -SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(432.0f, 1080.0f, 0.0f), CGattyann::GATTYANN_8);

				// ポーズ状態の解除
				CScene::SetPause(false);

				// サウンドの再生
				CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_MENUKETTEI);

				//ボタンを押した状態にする
				m_bButtonPress = true;
			}
			else if (pInputJoypad->GetJoypadTrigger(PLAYER_2, CInputJoypad::BUTTON_A))
			{
				// ガッチャンのクリエイト
				CGattyann::Create(D3DXVECTOR3(SCREEN_CENTER_X / 4, SCREEN_HEIGHT + SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(432.0f, 1080.0f, 0.0f), CGattyann::GATTYANN_5);
				CGattyann::Create(D3DXVECTOR3(SCREEN_CENTER_X - SCREEN_CENTER_X / 4, -SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(432.0f, 1080.0f, 0.0f), CGattyann::GATTYANN_6);
				CGattyann::Create(D3DXVECTOR3(SCREEN_CENTER_X + SCREEN_CENTER_X / 4, SCREEN_HEIGHT + SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(432.0f, 1080.0f, 0.0f), CGattyann::GATTYANN_7);
				CGattyann::Create(D3DXVECTOR3(SCREEN_WIDTH - SCREEN_CENTER_X / 4, -SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(432.0f, 1080.0f, 0.0f), CGattyann::GATTYANN_8);

				// ポーズ状態の解除
				CScene::SetPause(false);

				// サウンドの再生
				CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_MENUKETTEI);

				//ボタンを押した状態にする
				m_bButtonPress = true;
			}
		}
	}
	// カウントが1になったら
	else if (m_nCount == 1)
	{
		// ボタンを押してないとき
		if (m_bButtonPress == false)
		{
			// Aボタンを押したら
			if (pInputJoypad->GetJoypadTrigger(PLAYER_1, CInputJoypad::BUTTON_A))
			{
				if (CManager::GetFade() != NULL)
				{
					// タイトルに戻る
					CManager::GetFade()->SetFade(CManager::MODE_TITLE);

					// ポーズ状態の解除
					CScene::SetPause(false);

					// サウンドの再生
					CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_MENUKETTEI);

					//ボタンを押した状態にする
					m_bButtonPress = true;
				}
			}
			else if (pInputJoypad->GetJoypadTrigger(PLAYER_2, CInputJoypad::BUTTON_A))
			{
				if (CManager::GetFade() != NULL)
				{
					// タイトルに戻る
					CManager::GetFade()->SetFade(CManager::MODE_TITLE);

					// ポーズ状態の解除
					CScene::SetPause(false);

					// サウンドの再生
					CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_MENUKETTEI);

					//ボタンを押した状態にする
					m_bButtonPress = true;
				}
			}
		}
	}
}
