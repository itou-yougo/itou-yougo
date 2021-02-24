//=============================================================================
//
// ゲーム処理 [game.cpp]
// Author : 伊藤陽梧
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "game.h"
#include "manager.h"
#include "keyboard.h"
#include "joystick.h"
#include "fade.h"
#include "sound.h"
#include "ui.h"
#include "mode.h"
#include "player.h"
#include "enemy.h"
#include "camera.h"
#include "light.h"
#include "scene.h"
#include "map.h"
#include "skybox.h"
#include "fire.h"
#include "number.h"
#include "enemyremainder.h"
#include "magiccircle.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
CPlayer *CGame::m_pPlayer = NULL;
int CGame::m_nEnemyNum = 0;
int CGame::m_nEnemyDeathTotal = 0;

//=============================================================================
// コンストラクタ
//=============================================================================
CGame::CGame()
{
	m_bEnemyCreate = true;
	m_nEnemyCreateTime = ENEMY_CREATE_TIME;
}

//=============================================================================
// デストラクタ
//=============================================================================
CGame::~CGame()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGame::Init(void)
{
	//randの初期化
	srand((unsigned)time(NULL));

	//サウンドの再生
	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_GAME);

	//カメラ
	CManager::CreateCamera();

	//ライト
	CManager::CreateLight();
	m_pPlayer = CPlayer::Create(PLAYER_DEFAULT_POS, PLAYER_DEFAULT_ROT, PLAYER_DEFAULT_SIZE);
	CSkyBox::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 1000.0f, 2000.0f));
	CMap::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 200.0f));	

	// HPのUI
	CUi::Create(D3DXVECTOR3(150.0f, 600.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), CUi::TYPE_HP);
	CUi::Create(D3DXVECTOR3(400.0f, 600.0f, 0.0f), D3DXVECTOR3(450.0f, 50.0f, 0.0f), CUi::TYPE_HPSPBACK);
	CUi::Create(D3DXVECTOR3(400.0f, 600.0f, 0.0f), D3DXVECTOR3(450.0f, 50.0f, 0.0f), CUi::TYPE_PLAYER_LIFE);
	CUi::Create(D3DXVECTOR3(400.0f, 600.0f, 0.0f), D3DXVECTOR3(450.0f, 50.0f, 0.0f), CUi::TYPE_HPFLAME);

	// SPのUI
	CUi::Create(D3DXVECTOR3(750.0f, 600.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), CUi::TYPE_SP);
	CUi::Create(D3DXVECTOR3(1000.0f, 600.0f, 0.0f), D3DXVECTOR3(450.0f, 50.0f, 0.0f), CUi::TYPE_HPSPBACK);
	CUi::Create(D3DXVECTOR3(1000.0f, 600.0f, 0.0f), D3DXVECTOR3(450.0f, 50.0f, 0.0f), CUi::TYPE_PLAYER_SP);
	CUi::Create(D3DXVECTOR3(1000.0f, 600.0f, 0.0f), D3DXVECTOR3(450.0f, 50.0f, 0.0f), CUi::TYPE_SPFLAME);

	CEnemyremainder::Create(D3DXVECTOR3(1000.0f, 100.0f, 0.0f));
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CGame::Uninit(void)
{
	//サウンドの停止
	CManager::GetSound()->StopSound(CSound::SOUND_LABEL_BGM_GAME);

	//指定したオブジェクト以外のメモリの開放処理
	CScene::DesignationReleaseAll(CScene::OBJTYPE_FADE);

	m_pPlayer = NULL;
	m_nEnemyNum = 0;
	m_nEnemyDeathTotal = 0;

	m_bEnemyCreate = false;
	m_nEnemyCreateTime = 0;
}

//=============================================================================
// 更新処理
//=============================================================================
void CGame::Update(void)
{
	// 生成するフラグが立っているなら
	if (m_bEnemyCreate == true)
	{
		// 敵を生成する時間の加算
		m_nEnemyCreateTime++;
		if (m_nEnemyCreateTime >= ENEMY_CREATE_TIME)
		{
			// 生成する角度
			float fCreateAngle = D3DXToRadian((rand() % ENEMY_CREATE_ANGLE));
			float fDivide = (float)(rand() % 3 + 1);

			// 敵を生成するときの魔法陣の生成
			CMagiccercle::Create(D3DXVECTOR3((ENEMY_CREATE_DISTANCE.x / fDivide) * sinf(fCreateAngle), 0.0f, (ENEMY_CREATE_DISTANCE.z / fDivide) * cosf(fCreateAngle)),
				MAGICCERCLE_DEFAULT_ROT, MAGICCERCLE_ENEMY_DEFAULT_SIZE, MAGICCERCLE_DEFAULT_COLOR,
				MAGICCERCLE_ENEMY_COUNTANIM * MAGICCERCLE_ENEMY_PATTERNANIM * MAGICCERCLE_ENEMY_TIMEANIM, CMagiccercle::MAGICCIRCLETYPE_ENEMY);

			// 敵の数の加算
			m_nEnemyNum++;
			m_nEnemyCreateTime = 0;

			// 敵の総数が超えたら
			if (m_nEnemyNum >= ENEMY_CREATE_NUM)
			{
				m_bEnemyCreate = false;
			}
		}
	}

	// 敵の数が0になったら
	if (m_nEnemyNum == 0)
	{
		m_bEnemyCreate = true;
	}

	if (m_nEnemyDeathTotal >= MAX_ENEMY_NUM)
	{
		if (CScene::GetUpdateStop() == false)
		{
			//サウンドの停止
			CManager::GetSound()->StopSound(CSound::SOUND_LABEL_BGM_GAME);
			CManager::GetSound()->StopSound(CSound::SOUND_LABEL_SE_DASH);

			//フェードの生成
			CManager::CreateFade(CManager::MODE_RESULT);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CGame::Draw(void)
{
}

//=============================================================================
// プレイヤーの取得
//=============================================================================
CPlayer *CGame::GetPlayer(void)
{
	return m_pPlayer;
}