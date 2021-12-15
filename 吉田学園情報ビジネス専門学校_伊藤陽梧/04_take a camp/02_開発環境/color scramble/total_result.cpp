////////////////////////////////////////////////////
//
//    トータルリザルトクラスの処理[total_result.cpp]
//    Author : 吉田 悠人
//
////////////////////////////////////////////////////


//=============================
// インクルード
//=============================
#include "manager.h"
#include "total_result.h"
#include "total_score.h"
#include "keyboard.h"
#include "mouse.h"
#include "fade.h"
#include "scene2d.h"
#include "camera_charaselect.h"

//**********************************
// マクロ定義
//**********************************

//**********************************
// 静的メンバ変数宣言
//**********************************


//=============================
// コンストラクタ
//=============================
CTotalResult::CTotalResult()
{
	m_pBg			= NULL;
	m_pScoreKill	= NULL;
}

//=============================
// デストラクタ
//=============================
CTotalResult::~CTotalResult()
{
}

//=============================
// クリエイト
//=============================
CTotalResult * CTotalResult::Create(void)
{
	// メモリの確保
	CTotalResult *pTotalResult = NULL;
	pTotalResult = new CTotalResult;
	
	//NULLチェック
	if (pTotalResult != NULL)
	{
		// 初期化
		pTotalResult->Init();

	}
	return pTotalResult;
}

//=============================
// 初期化処理
//=============================
HRESULT CTotalResult::Init(void)
{
	// 背景の生成
	m_pBg = CScene2d::Create();
	m_pBg->SetSize(D3DXVECTOR3(SCREEN_WIDTH - 15, SCREEN_HEIGHT - 20, 0.0f));
	m_pBg->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f));
	m_pBg->SetPriority(OBJTYPE_BG);

	// カメラ生成
	CManager::SetCamera(CCharaSelectCamera::Create());

	//スコア生成
	CTotalScore::Create();
	return S_OK;
}

//=============================
// 終了処理
//=============================
void CTotalResult::Uninit(void)
{
	// カメラクラスの解放処理
	CCamera * pCamera = CManager::GetCamera();
	if (pCamera != NULL)
	{
		CManager::SetCamera(NULL);
		pCamera = NULL;
	}

	// 開放処理
	Release();
}


//=============================
// 更新処理
//=============================
void CTotalResult::Update(void)
{
	// カメラクラス更新処理
	CCamera * pCamera = CManager::GetCamera();
	if (pCamera != NULL)
	{
		pCamera->Update();
	}

	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_RETURN) ||
		CManager::GetMouse()->GetMouseTrigger(0) /*||
												 CManager::GetJoypad()->GetJoystickTrigger(3, 0) ||
												 CManager::GetJoypad()->GetJoystickTrigger(11, 0)*/)
	{
		// デバッグ用画面遷移コマンド
		CManager::GetFade()->SetFade(CManager::MODE_TITLE);
	}

}

//=============================
// 描画処理
//=============================
void CTotalResult::Draw(void)
{
	// カメラクラス更新処理
	CCamera * pCamera = CManager::GetCamera();
	if (pCamera != NULL)
	{
		pCamera->SetCamera();
	}
}

