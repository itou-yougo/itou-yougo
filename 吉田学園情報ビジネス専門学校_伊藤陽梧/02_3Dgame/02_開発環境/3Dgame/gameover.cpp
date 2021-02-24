//=============================================================================
//
// ゲームオーバー処理 [gameover.cpp]
// Author : 伊藤陽梧
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "gameover.h"
#include "renderer.h"
#include "manager.h"
#include "keyboard.h"
#include "joystick.h"
#include "time.h"
#include "sound.h"
#include "ui.h"
#include "mode.h"
#include "fade.h"

//=============================================================================
// 静的メンバ変数初期化
//=============================================================================
LPDIRECT3DTEXTURE9 CGameover::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CGameover::CGameover()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CGameover::~CGameover()
{
}

//=============================================================================
// テクスチャロード
//=============================================================================
HRESULT CGameover::Load(void)
{
	CRenderer * pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, TEXTURE_GAMEOVER, &m_pTexture);
	return S_OK;
}

//=============================================================================
// テクスチャアンロード
//=============================================================================
void CGameover::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGameover::Init()
{
	//サウンドの再生
	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_RESULT);

	//ゲームタイトルのUIの生成
	CUi::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CUi::TYPE_GAMEOVER);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CGameover::Uninit(void)
{
	//サウンドの停止
	CManager::GetSound()->StopSound(CSound::SOUND_LABEL_BGM_RESULT);

	//指定したオブジェクト以外のメモリの開放処理
	CScene::DesignationReleaseAll(CScene::OBJTYPE_FADE);
}

//=============================================================================
// 更新処理
//=============================================================================
void CGameover::Update(void)
{
	if (CManager::GetFade()->GetFadeState() == CFade::FADE_NONE)
	{
		if (CManager::GetInputKeyboard()->GetKeyTrigger(DIK_RETURN) || CManager::GetInputJoystick()->GetJoystickTrigger(CInputJoystick::BUTTON_B))
		{ //EnterキーまたはBボタンを押したとき
			//サウンドの再生
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_DECISION);

			//フェードの生成
			CManager::GetFade()->SetFade(CManager::MODE_TITLE);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CGameover::Draw(void)
{
}