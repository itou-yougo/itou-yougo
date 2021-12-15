////////////////////////////////////////////////////
//
//    リザルトクラスの処理[result.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////


//=============================
// インクルード
//=============================
#include "result.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "mouse.h"
#include "joypad.h"
#include "fade.h"
#include "result_graph.h"

//**********************************
// マクロ定義
//**********************************
#define PLAYER_SPACE (150.0f) //　プレイヤー位置の間隔
#define PLAYER_POS_Z (100.0f) // プレイヤーのZ位置
#define PLAYER_FALL_COUNT (300) // プレイヤーがこけるカウント数
#define RANK_UI_HEGHT (-50) // ランキングのUIプレイヤーからの位置
#define RESULT_BOARD_SPACE (320.0f)

#define LOGO_POS (D3DXVECTOR3(SCREEN_WIDTH/2, 100.0f, 0.0f))
#define LOGO_SIZE (D3DXVECTOR3(300.0f,75.0f,0.0f))
#define OBJ_BASE_POS_Y (2000.0f)

//**********************************
// 静的メンバ変数宣言
//**********************************


//=============================
// コンストラクタ
//=============================
CResult::CResult()
{
	m_fFloat = 0.0f;
}

//=============================
// デストラクタ
//=============================
CResult::~CResult()
{
}

//=============================
// クリエイト
//=============================
CResult * CResult::Create(void)
{
	// メモリの確保
	CResult *pResult = new CResult;
	// 初期化
	pResult->Init();
	return pResult;
}

//=============================
// 初期化処理
//=============================
HRESULT CResult::Init(void)
{
	//　グラフの生成
	CResultGraph::Create();

	return S_OK;
}

//=============================
// 終了処理
//=============================
void CResult::Uninit(void)
{
	// 開放処理
	Release();
}


//=============================
// 更新処理
//=============================
void CResult::Update(void)
{
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_RETURN) ||
		CManager::GetMouse()->GetMouseTrigger(0) /*||
		CManager::GetJoypad()->GetJoystickTrigger(3, 0) ||
		CManager::GetJoypad()->GetJoystickTrigger(11, 0)*/)
	{
		// デバッグ用画面遷移コマンド
		CManager::GetFade()->SetFade(CManager::MODE_TOTAL_RESULT);
	}
}

//=============================
// 描画処理
//=============================
void CResult::Draw(void)
{

}