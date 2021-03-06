//=============================================================================
//
// チュートリアル処理 [tutorial.cpp]
// Author : 伊藤陽梧
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "tutorial.h"
#include "manager.h"
#include "keyboard.h"
#include "joystick.h"
#include "sound.h"
#include "ui.h"
#include "fade.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CTutorial::CTutorial()
{
	m_pUi = NULL;
	m_nCountTexture = 1;
}

//=============================================================================
// デストラクタ
//=============================================================================
CTutorial::~CTutorial()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTutorial::Init(void)
{
	//チュートリアルのUIの生成
	m_pUi = CUi::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CUi::TYPE_TUTORIAL);
	m_pUi->SetTextureSelect(m_nCountTexture, 2);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTutorial::Uninit(void)
{
	//サウンドの停止
	CManager::GetSound()->StopSound(CSound::SOUND_LABEL_BGM_TITLE);

	//指定したオブジェクト以外のメモリの開放処理
	CScene::DesignationReleaseAll(CScene::OBJTYPE_FADE);
}

//=============================================================================
// 更新処理
//=============================================================================
void CTutorial::Update(void)
{
	if (CManager::GetFade()->GetFadeState() == CFade::FADE_NONE)
	{
		if (CManager::GetInputKeyboard()->GetKeyTrigger(DIK_RETURN) || CManager::GetInputJoystick()->GetJoystickTrigger(CInputJoystick::BUTTON_START))
		{
			if (m_nCountTexture == TEXTURE_END_NUM)
			{
				//フェードの生成
				CManager::GetFade()->SetFade(CManager::MODE_GAME);
			}

			// テクスチャをずらす数が小さかったら
			if (m_nCountTexture < TEXTURE_END_NUM)
			{
				m_nCountTexture++;
			}
		}
	}

	// テクスチャをずらす
	m_pUi->SetTextureSelect(m_nCountTexture, TEXTURE_END_NUM);
}

//=============================================================================
// 描画処理
//=============================================================================
void CTutorial::Draw(void)
{

}