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
#include "polygon.h"
#include "stage_texture.h"

//**********************************
// マクロ定義
//**********************************
#define BG_COLOR D3DXCOLOR(0.4f,0.4f,0.4f,0.6f)

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
	m_pBg->SetSize(D3DXVECTOR3(SCREEN_WIDTH - 15.0f, SCREEN_HEIGHT - 20.0f, 0.0f));
	m_pBg->SetColor(BG_COLOR);
	m_pBg->SetPriority(OBJTYPE_BG);

	// カメラ生成
	CManager::SetCamera(CCharaSelectCamera::Create());

	//スコア生成
	CTotalScore::Create();

	m_pBackGroundPolygon = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	m_pBackGroundPolygon->BindTexture(CStageTexture::GetStateTexturePointa()->GetTexture());
	return S_OK;
}

//=============================
// 終了処理
//=============================
void CTotalResult::Uninit(void)
{
	if (m_pBackGroundPolygon != NULL)
	{
		m_pBackGroundPolygon->Uninit();
		delete m_pBackGroundPolygon;
		m_pBackGroundPolygon = NULL;
	}

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

	m_pBackGroundPolygon->Draw();
}

