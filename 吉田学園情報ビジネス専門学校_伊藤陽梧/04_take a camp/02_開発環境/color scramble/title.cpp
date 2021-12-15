////////////////////////////////////////////////////
//
//    タイトルクラスの処理[title.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////


//=============================
// インクルード
//=============================
#include "title.h"
#include "manager.h"
#include "renderer.h"
#include "polygon.h"
#include "keyboard.h"
#include "mouse.h"
#include "joypad.h"
#include "fade.h"
#include "sound.h"
#include "resource_texture.h"
#include "camera_base.h"
#include "bg.h"
#include "light.h"
#include "map.h"
#include "button_title.h"
#include "chara_select.h"

//**********************************
// 静的メンバ変数宣言
//**********************************
CMap* CTitle::m_pMap = NULL;	// ステージクラスのポインタ
CMapManager::MAP_TYPE CTitle::m_MapType = CMapManager::MAP_TYPE_1;	// マップタイプ
CButton_Title* CTitle::m_pButton = NULL; // ボタンクラスのポインタ
//**********************************
// マクロ定義
//**********************************
#define OBJ_BACE_POS_Y 2000.0f
#define STAGE_SPACE 150.0f

//=============================
// コンストラクタ
//=============================
CTitle::CTitle()
{
	m_pPolygon = NULL;
}

//=============================
// デストラクタ
//=============================
CTitle::~CTitle()
{
}

//=============================
// クリエイト
//=============================
CTitle * CTitle::Create(void)
{
	// メモリの確保
	CTitle *pTitle = new CTitle;
	// 初期化
	pTitle->Init();
	return pTitle;
}

//=============================
// 初期化処理
//=============================
HRESULT CTitle::Init(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	m_pPolygon = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 200.0f, 0.0f),
		D3DXVECTOR3(1200.0f, 318.0f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	m_pPolygon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_TITLE));
	
	// カメラ生成
	CManager::SetCamera(CCamera::Create());

	// 背景の設定
	CBg::Create();

	// エントリー人数の初期化
	CCharaSelect::ResetEntryPlayer();
	
	// ステージ生成
	m_pMap = CMap::Create(m_MapType);

	// ボタンの生成
	m_pButton = CButton_Title::Create(D3DXVECTOR3(SCREEN_WIDTH/2, 500.0f, 0.0f), CButton_Title::BUTTON_START);
	m_pButton = CButton_Title::Create(D3DXVECTOR3(SCREEN_WIDTH/2, 630.0f, 0.0f), CButton_Title::BUTTON_TUTORIAL);

	return S_OK;
}

//=============================
// 終了処理
//=============================
void CTitle::Uninit(void)
{
	// カメラクラスの解放処理
	CCamera * pCamera = CManager::GetCamera();
	if (pCamera != NULL)
	{
		CManager::SetCamera(NULL);
		pCamera = NULL;
	}

	if (m_pPolygon != NULL)
	{
		// ポリゴンの終了処理
		m_pPolygon->Uninit();

		// メモリの解放
		delete m_pPolygon;
		m_pPolygon = NULL;
	}

	// 開放処理
	Release();
}


//=============================
// 更新処理
//=============================
void CTitle::Update(void)
{
	// カメラクラス更新処理
	CCamera * pCamera = CManager::GetCamera();
	if (pCamera != NULL)
	{
		pCamera->Update();
	}

	// ポリゴンの更新処理
	m_pPolygon->Update();

	//if( CManager::GetKeyboard()->GetKeyTrigger(DIK_RETURN) || 
	//	CManager::GetMouse()->GetMouseTrigger(0) /*|| 
	//	CManager::GetJoypad()->GetJoystickTrigger(3, 0)||
	//	CManager::GetJoypad()->GetJoystickTrigger(11, 0)*/)
	//{
	//	CManager::GetFade()->SetFade(CManager::MODE_TUTORIAL);
	//}
}


//=============================
// 描画処理
//=============================
void CTitle::Draw(void)
{
	// カメラクラス更新処理
	CCamera * pCamera = CManager::GetCamera();
	if (pCamera != NULL)
	{
		pCamera->SetCamera();
	}

	// ポリゴンの描画処理
	m_pPolygon->Draw();
}
