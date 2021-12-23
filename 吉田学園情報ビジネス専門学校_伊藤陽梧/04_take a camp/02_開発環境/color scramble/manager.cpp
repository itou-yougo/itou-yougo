

//=============================
// インクルード
//=============================
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "game.h"
#include "scene.h"
#include "input.h"
#include "keyboard.h"
#include "joypad.h"
#include "mouse.h"
#include "title.h"
#include "result.h"
#include "fade.h"
#include "resource_texture.h"
#include "resource_model.h"
#include "resource_shader.h"
#include "resource_attack.h"
#include "resource_model_hierarchy.h"
#include "camera_base.h"
#include "debug_log.h"
#include "pause.h"
#include "tutorial.h"
#include "color_manager.h"
#include "collision.h"
#include "light.h"
#include "chara_select.h"
#include "total_result.h"
#include "tile_factory.h"
#include "resource_character.h"
#include "stage_select.h"
#include "stage_texture.h"
#include "resource_text.h"

//=============================
// 静的メンバ変数宣言
//=============================
CManager::MODE   CManager::m_mode = MODE_TITLE;      // ゲームモード
CManager::MODE   CManager::m_Decmode = MODE_TITLE;   // 判定用モード
CRenderer       *CManager::m_pRenderer = NULL;       // レンダラーポインタ
CInputKeyboard  *CManager::m_pInputKeyboard = NULL;  // キーボード
CInputJoypad    *CManager::m_pJoypad = NULL;         // ジョイパッド
CInputMouse     *CManager::m_pInputMouse = NULL;     // マウス
CSound          *CManager::m_pSound = NULL;          // サウンド
CGame           *CManager::m_pGame = NULL;           // ゲーム
CTitle          *CManager::m_pTitle = NULL;          // タイトル
CResult         *CManager::m_pResult = NULL;         // リザルト
CTotalResult	*CManager::m_TotalResult = NULL;	 // トータルリザルト
CFade           *CManager::m_pFade = NULL;           // フェード
CTutorial       *CManager::m_pTutorial = NULL;       // チュートリアル
CPause          *CManager::m_pPause = NULL;          // ポーズポインタ
CCamera         *CManager::m_pCamera = NULL;         // カメラクラス
CLight			*CManager::m_pLight = NULL;			 // ライトクラス
bool             CManager::m_bPause = false;         // ポーズフラグ
CCharaSelect    *CManager::m_pCharaSelectMode = NULL;// キャラ選択
CStageSelect    *CManager::m_pStageSelectMode = NULL;// ステージ選択
//=============================
// コンストラクタ
//=============================
CManager::CManager()
{
	
}

//=============================
// デストラクタ
//=============================
CManager::~CManager()
{
}

//=============================
// 初期化処理
//=============================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{

	// メモリの確保・初期化

	// キーボード
	m_pInputKeyboard = new CInputKeyboard;
	// キーボード初期化
	if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	// ジョイパッド
	m_pJoypad = new CInputJoypad;
	// ジョイパッドの初期化
	if (FAILED(m_pJoypad->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	// マウス
	m_pInputMouse = new CInputMouse;
	// マウス初期化
	if (FAILED(m_pInputMouse->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	// レンダラー
	m_pRenderer = new CRenderer;
	// レンダラークラスの初期化
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{
		return E_FAIL;
	}

	// サウンド
	m_pSound = new CSound;
	// サウンドクラスの初期化
	if (FAILED(m_pSound->Init(hWnd)))
	{
		return E_FAIL;
	}

	// ライトクラスの生成
	m_pLight = new CLight;
	// ライトクラスの初期化
	if (FAILED(m_pLight->Init()))
	{
		return E_FAIL;
	}

	// デバッグログ
	CDebugLog::Init();
	
	// フェードの生成
	m_pFade = CFade::Create();
	m_pFade->SetFade(m_mode);

	// テクスチャクラスの生成
	CResourceTexture::Create();
	// モデルリソースクラスの生成
	CResourceModel::Create();
	// シェーダーリソースクラスの生成
	CResourceShader::Create();
	// 階層構造リソースクラス
	CResourceModelHierarchy::Create();
	// キャラクターリソースの生成
	CResourceCharacter::Create();

	// テクスチャ・モデルの読み込み
	CPause::Load();    // ポーズ
	//ステージ読み込み
	CMapManager::Create();
	//攻撃範囲読み込み
	CAttackManager::Create();

	// カラーマネージャーの生成
	CColorManager::Create();

	// タイルファクトリーの生成
	CTileFactory::Create();

	//　ステージテクスチャクラス
	CStageTexture::Create(D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT));

	// チュートリアルに使うテキストの読み込み
	CResourceText::Create();

	// ポーズ状態の時
	return S_OK;
}

//=============================
// 終了処理
//=============================
void CManager::Uninit(void)
{
	// 開放処理
	CScene::ReleaseAll();
	//マップ管理クラスの破棄
	CMapManager::Release();
	//攻撃範囲読み込みクラスの破棄
	CAttackManager::Release();
	// テクスチャクラスの破棄
	CResourceTexture::Release();
	// モデルリソースクラスの破棄
	CResourceModel::Release();
	// シェーダーリソースクラスの破棄
	CResourceShader::Release();
	// 階層構造リソースクラス
	CResourceModelHierarchy::Release();
	// キャラクターリソースの破棄
	CResourceCharacter::Release();

	// カラーマーマネージャーの破棄
	CColorManager::Release();
	// タイルファクトリーの破棄
	CTileFactory::Release();
	// ステージテクスチャの
	CStageTexture::Release();
	// チュートリアルに使うテキストの破棄
	CResourceText::Release();

	// テクスチャのアンロード
	CPause::Unload();    // ポーズ

	if (m_pSound != NULL)
	{
		// 終了処理
		m_pSound->Uninit();
		// メモリの解放
		delete m_pSound;
		m_pSound = NULL;
	}

	if (m_pRenderer != NULL)
	{
		// 終了処理
		m_pRenderer->Uninit();
		// メモリの解放
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	if (m_pInputKeyboard != NULL)
	{
		// 終了処理
		m_pInputKeyboard->Uninit();
		// メモリの解放
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	if (m_pJoypad != NULL)
	{
		// 終了処理
		m_pJoypad->Uninit();
		// メモリの解放
		delete m_pJoypad;
		m_pJoypad = NULL;
	}

	if (m_pInputMouse != NULL)
	{
		// 終了処理
		m_pInputMouse->Uninit();
		// メモリの解放
		delete m_pInputMouse;
		m_pInputMouse = NULL;
	}

	if (m_pFade != NULL)
	{
		// 終了処理
		m_pFade->Uninit();
		// メモリの解放
		delete m_pFade;
		m_pFade = NULL;
	}

	if (m_pPause != NULL)
	{
		m_pPause->Uninit();
		delete m_pPause;
		m_pPause = NULL;
	}

	if (m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}
}


//=============================
// 更新処理
//=============================
void CManager::Update(void)
{
	// ジョイパッドクラスの更新処理
	if (m_pJoypad != NULL)
	{
		m_pJoypad->Update();
	}
	// キーボードクラスの更新処理
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}

	// マウスクラスの更新処理
	if (m_pInputMouse != NULL)
	{
		m_pInputMouse->Update();
	}

	// レンダラークラスの更新処理
	if (m_pRenderer != NULL)
	{
		if (m_mode == MODE_GAME)
		{// モードゲームのときポーズ画面の処理

			if (m_pInputKeyboard->GetKeyTrigger(DIK_TAB) /*|| m_pJoypad->GetJoystickTrigger(11, 0)*/)
			{// TAB

				if (m_pPause == NULL)
				{
					// 生成
					m_pPause = CPause::Create();
				}
				// ポーズの切り替え
				m_bPause ^= true;
			}
			if (!m_bPause)
			{// ポーズじゃないとき

				if (m_pPause != NULL)
				{
					m_pPause->Uninit();
					delete m_pPause;
					m_pPause = NULL;
				}

				m_pRenderer->Update();
			}
			else
			{// ポーズ状態
				if (m_pPause != NULL)
				{
					// ポーズの更新処理
					m_pPause->Update();
				}
			}
		}
		else
		{
			m_pRenderer->Update();
		}
		
	}

	// フェードクラスの更新処理
	if (m_pFade != NULL)
	{
		m_pFade->Update();
	}

#ifdef _DEBUG
	if (m_pInputKeyboard != NULL)
	{
		if (m_pInputKeyboard->GetKeyTrigger(DIK_NUMPAD0))
		{
			CCollision::SetDrawFlag(true^ CCollision::GetDrawFlag());
		}
	}
#endif

}

//=============================
// 描画処理
//=============================
void CManager::Draw(void)
{
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}

//=============================
// セットモード
//=============================
void CManager::SetMode(MODE mode)
{

	switch (m_mode)
	{
	case MODE_TITLE:
		// NULLクリア
		m_pTitle = NULL;
		// タイトルBGM停止
		m_pSound->Stop(CSound::LABEL_BGM_TITLE);
		break;
	case MODE_TUTORIAL:
		// NULLクリア
		m_pTutorial = NULL;
		// タイトルBGM停止
		m_pSound->Stop(CSound::LABEL_BGM_TUTORIAL);
		break;
	case MODE_CHARA_SELECT:
		m_pCharaSelectMode = NULL;

		break;
	case MODE_STAGE_SELECT:
		m_pStageSelectMode = NULL;

		break;
	case MODE_GAME:
		// NULLクリア
		m_pGame = NULL;
		// ゲームBGM停止
		//m_pSound->Stop(CSound::LABEL_BGM_GAME);
		break;

	case MODE_RESULT:
		// NULLクリア
		m_pResult = NULL;
		// リザルトBGM停止
		m_pSound->Stop(CSound::LABEL_BGM_RESULT);
		break;
	case MODE_TOTAL_RESULT:
		// NULLクリア
		m_TotalResult = NULL;
		// トータルリザルトBGM停止
		//m_pSound->Stop(CSound::LABEL_BGM_RESULT);
		break;

	default:
		break;
	}

	m_mode = mode;
	// 開放処理
	CScene::ReleaseAll();

	switch (m_mode)
	{
	case MODE_TITLE:
		// タイトル生成
		m_pTitle = CTitle::Create();
		// タイトルBGM再生
		//m_pSound->Play(CSound::LABEL_BGM_TITLE);
		break;
	case MODE_TUTORIAL:
		// チュートリアル生成
		m_pTutorial = CTutorial::Create();
		//　チュートリアルBGM再生
		//m_pSound->Play(CSound::LABEL_BGM_TUTORIAL);
		break;
	case MODE_CHARA_SELECT:
		m_pCharaSelectMode = CCharaSelect::Create();

		break;
	case MODE_STAGE_SELECT:
		m_pStageSelectMode = CStageSelect::Create();

		break;
	case MODE_GAME:
		// ゲーム生成
		m_pGame = CGame::Create();
		//// ゲームBGM再生
		//m_pSound->Play(CSound::LABEL_BGM_GAME);
		break;

	case MODE_RESULT:
		// リザルト生成
		m_pResult = CResult::Create();
		// リザルトBGM再生
		//m_pSound->Play(CSound::LABEL_BGM_RESULT);
		break;
	case MODE_TOTAL_RESULT:
		// トータルリザルト生成
		m_TotalResult = CTotalResult::Create();
		break;
	default:
		break;
	}
}

//=============================
// 判定用モードセット
//=============================
void CManager::SetDecMode(MODE mode)
{
	m_Decmode = mode;
}

//=============================
// カメラクラスのセット処理
//=============================
void CManager::SetCamera(CCamera * pCamera)
{
	// カメラクラスの解放処理
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();
		m_pCamera = NULL;
	}

	// セット
	m_pCamera = pCamera;
}