////////////////////////////////////////////////////
//
//    ゲームクラスの処理[game.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//=============================
// インクルード
//=============================
#include "game.h"
#include "number.h"
#include "mouse.h"
#include "camera_tps.h"
#include "light.h"
#include "fade.h"
#include "keyboard.h"
#include "particle.h"
#include "time.h"
#include "joypad.h"
#include "result.h"
#include "bg.h"
#include "player.h"
#include "map.h"
#include "tile.h"
#include "debug_log.h"
#include "color_manager.h"
#include "color_tile.h"
#include "kill_count.h"
#include "paintnum.h"
#include "player_model.h"

//=============================
// マクロ定義
//=============================

//=============================
// 静的メンバ変数宣言
//=============================
CRuleManager* CGame::m_pRuleManager = NULL;                       // ルールマネージャークラス
CMap* CGame::m_pMap = NULL;			                              // ステージクラスポインタ
CMapManager::MAP_TYPE CGame::m_MapType = CMapManager::MAP_TYPE_1; // マップタイプ

//=============================
// コンストラクタ
//=============================
CGame::CGame()
{
	// 変数のクリア
}

//=============================
// デストラクタ
//=============================
CGame::~CGame()
{
}

//=============================
// クリエイト
//=============================
CGame * CGame::Create(void)
{
	// メモリの確保
	CGame *pGame = new CGame;
	// 初期化
	pGame->Init();
	return pGame;
}

//=============================
// 初期化処理
//=============================
HRESULT CGame::Init(void)
{
	// ポーズの初期化
	CManager::SetActivePause(false);

	// マネージャーの番号のリセット
	GET_COLORMANAGER->UseNumReset();

	CManager::SetCamera(CCamera::Create());

	// 背景の生成
	CBg::Create();
	CModel::Create(D3DXVECTOR3(0.0f, -13.0f, 0.0f), CResourceModel::MODEL_DESK,D3DXVECTOR3(0.4f, 0.4f, 0.4f));
	//ステージ生成
	m_pMap = CMap::Create(m_MapType);
	
	// プレイヤーごとの色の割合の表示
	CPaintnum::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 25.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, 50.0f, 0.0f));

	// 制限時間クラス
	CTime::Create();

	// ライトの向きの設定
	CManager::GetLight()->SetDir(LIGHT_DIR_BASE);
	return S_OK;
}

//=============================
// 終了処理
//=============================
void CGame::Uninit(void)
{
	// カメラクラスの解放処理
	CCamera * pCamera = CManager::GetCamera();
	if (pCamera != NULL)
	{
		CManager::SetCamera(NULL);
	}

	// 開放処理
	Release();
}

//=============================
// 更新処理
//=============================
void CGame::Update(void)
{
	// カメラクラス更新処理
	CCamera * pCamera = CManager::GetCamera();
	if (pCamera != NULL)
	{
		pCamera->Update();
	}

#ifdef _DEBUG
	// デバッグ用画面遷移コマンド
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_F1))
	{
		CManager::GetFade()->SetFade(CManager::MODE_RESULT);
	}
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_F2))
	{
		CManager::SetCamera(CTpsCamera::Create());
	}
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_F3))
	{
		CManager::SetCamera(CCamera::Create());
	}
	CKillCount::AddTotalKill();
	CColorTile::CountColorTile();

	CDebugLog::Init();
	CDebugLog::Print("1P:Kill:%d\n", CKillCount::GetTotalKill(0));
	CDebugLog::Print("2P:Kill:%d\n", CKillCount::GetTotalKill(1));
	CDebugLog::Print("3P:Kill:%d\n", CKillCount::GetTotalKill(2));
	CDebugLog::Print("4P:Kill:%d\n", CKillCount::GetTotalKill(3));

	CDebugLog::Print("赤:%d(一:%d,二:%d,三:%d)\n", CColorTile::GetTileNum(0), CColorTile::GetTileNum(0, 1), CColorTile::GetTileNum(0, 2), CColorTile::GetTileNum(0, 3));
	CDebugLog::Print("青:%d(一:%d,二:%d,三:%d)\n", CColorTile::GetTileNum(1), CColorTile::GetTileNum(1, 1), CColorTile::GetTileNum(1, 2), CColorTile::GetTileNum(1, 3));
	CDebugLog::Print("緑:%d(一:%d,二:%d,三:%d)\n", CColorTile::GetTileNum(2), CColorTile::GetTileNum(2, 1), CColorTile::GetTileNum(2, 2), CColorTile::GetTileNum(2, 3));
	CDebugLog::Print("橙:%d(一:%d,二:%d,三:%d)\n", CColorTile::GetTileNum(3), CColorTile::GetTileNum(3, 1), CColorTile::GetTileNum(3, 2), CColorTile::GetTileNum(3, 3));
#endif // _DEBUG

}

//=============================
// 描画処理
//=============================
void CGame::Draw(void)
{
	CCamera * pCamera = CManager::GetCamera();
    // カメラのセット
    if (pCamera != NULL)
    {
		pCamera->SetCamera();
    }
}