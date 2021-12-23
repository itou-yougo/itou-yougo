////////////////////////////////////////////////////
//
//    キャラ選択クラスの処理[chara_select.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//=============================
// インクルード
//=============================
#include "stage_select.h"
#include "keyboard.h"
#include "joypad.h"
#include "manager.h"
#include "fade.h"
#include "stage_name_ui.h"
#include "chara_select.h"
#include "player.h"
#include "camera_base.h"
#include "light.h"
#include "bg.h"
#include "map.h"
#include "resource_map.h"
#include "stage_select_polygon.h"

//=============================
// マクロ定義
//=============================
#define WAIT_TIME 20

//=============================
// 静的メンバ変数宣言
//=============================
CMapManager::MAP_TYPE CStageSelect::m_selectStageType = CMapManager::MAP_TYPE_1;

//=============================
// コンストラクタ
//=============================
CStageSelect::CStageSelect()
{
	m_pStageName = NULL;
	m_pStagePolygon = NULL;
	m_selectStageType = CMapManager::MAP_TYPE_1;
	m_nWaitCnt = 0;
}

//=============================
// デストラクタ
//=============================
CStageSelect::~CStageSelect()
{
}

//=============================
// クリエイト
//=============================
CStageSelect * CStageSelect::Create(void)
{
	// メモリの確保
	CStageSelect *pMode = new CStageSelect;
	// 初期化
	pMode->Init();

	return pMode;
}

//=============================
// 初期化処理
//=============================
HRESULT CStageSelect::Init(void)
{
	// カメラクラスの生成
	CManager::SetCamera(CCamera::Create());

	// ステージ名ポリゴンの生成
	m_pStageName = CStageNameUi::Create(m_selectStageType);

	SetObject();

	return S_OK;
}

//=============================
// 終了処理
//=============================
void CStageSelect::Uninit(void)
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
void CStageSelect::Update(void)
{
	SelectStageType();

	if (m_pStageName != NULL) m_pStageName->SetSelectNum(m_selectStageType);

	if (m_nWaitCnt > 0) m_nWaitCnt--;

	// カメラクラス更新処理
	CCamera * pCamera = CManager::GetCamera();
	if (pCamera != NULL)
	{
		pCamera->Update();
	}

#ifdef _DEBUG

	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_F1) || CManager::GetKeyboard()->GetKeyTrigger(DIK_RETURN))
	{
		CGame::SetMapType(m_selectStageType);
		CManager::GetFade()->SetFade(CManager::MODE_GAME);
	}

#endif
}

//=============================
// 描画処理
//=============================
void CStageSelect::Draw(void)
{
	CCamera * pCamera = CManager::GetCamera();
	// カメラのセット
	if (pCamera != NULL)
	{
		pCamera->SetCamera();
	}
}

//=============================
// オブジェクトの設置
//=============================
void CStageSelect::SetObject(void)
{
	// 退避
	OutList();

	m_pStageName->OutList();

	// 退避したもの以外全オブジェクトの削除
	ReleaseAll();

	// ステージセレクトの生成
	m_pStagePolygon = CStageSelectPolygon::Create();
	// プライオリティの再設定
	SetPriority(OBJTYPE_NONE);
	m_pStageName->SetPriority(OBJTYPE_UI_2);

	// 背景の生成
	CBg::Create();
	CModel::Create(D3DXVECTOR3(0.0f, -13.0f, 0.0f), CResourceModel::MODEL_DESK, D3DXVECTOR3(0.4f, 0.4f, 0.4f))->SetPriority(OBJTYPE_MAP);

	CCharaSelect::Entry_Data noneData = {};
	CCharaSelect::Entry_Data aSaveData[MAX_PLAYER] = {};
	// キャラデータの無効化
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		aSaveData[nCnt] = CCharaSelect::GetEntryData(nCnt);
		CCharaSelect::SetEntryData(nCnt, noneData);
	}

	// マップの生成
	CMap::Create(m_selectStageType);

	// キャラデータを戻す
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++) CCharaSelect::SetEntryData(nCnt, aSaveData[nCnt]);
}

//=============================
// ステージタイプの選択処理
//=============================
void CStageSelect::SelectStageType(void)
{
	if (m_nWaitCnt > 0) return;

	CCharaSelect::Entry_Data entryData = {};
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		entryData = CCharaSelect::GetEntryData(nCntPlayer);
		// エントリーしているプレイヤー(1P)データの取得
		if (entryData.bEntry) break;
		else if (nCntPlayer == (MAX_PLAYER - 1))
		{
			CManager::GetFade()->SetFade(CManager::MODE_GAME); 
			return;
		}
	}

	CInputJoypad * pJoy = CManager::GetJoypad();
	CInputKeyboard *pKey = CManager::GetKeyboard();
	// スティックの座標
	D3DXVECTOR2 StickPos = pJoy->GetStickState(pJoy->PAD_LEFT_STICK, entryData.nControllNum);

	int nStageType = m_selectStageType;
	// キャラの選択処理
	if (!entryData.bController && pKey->GetKeyPress(CPlayer::GetPlayerControllKey(entryData.nControllNum, CPlayer::KEY_LEFT))
		|| entryData.bController && ((StickPos.x < 0.0f && StickPos.y < STICK_DECISION_RANGE && StickPos.y > -STICK_DECISION_RANGE)
			|| pJoy->GetButtonState(XINPUT_GAMEPAD_DPAD_LEFT, pJoy->BUTTON_PRESS, entryData.nControllNum)))
	{// 進む
		nStageType--;
		if (nStageType < 0) nStageType = SELECT_STAGE_NUM - 1;
		m_selectStageType = (CMapManager::MAP_TYPE)nStageType;

		SetObject();

		m_nWaitCnt = WAIT_TIME;
		return;
	}
	if (!entryData.bController && pKey->GetKeyPress(CPlayer::GetPlayerControllKey(entryData.nControllNum, CPlayer::KEY_RIGHT))
		|| entryData.bController && ((StickPos.x > 0.0f && StickPos.y < STICK_DECISION_RANGE && StickPos.y > -STICK_DECISION_RANGE)
			|| pJoy->GetButtonState(XINPUT_GAMEPAD_DPAD_RIGHT, pJoy->BUTTON_PRESS, entryData.nControllNum)))
	{// 戻り

		nStageType++;
		if (nStageType >= SELECT_STAGE_NUM) nStageType = 0;
		m_selectStageType = (CMapManager::MAP_TYPE)nStageType;

		SetObject();

		m_nWaitCnt = WAIT_TIME;

		return;
	}

	m_nWaitCnt = 0;

	// 決定キー
	if (!entryData.bController && pKey->GetKeyTrigger(CPlayer::GetPlayerControllKey(entryData.nControllNum, CPlayer::KEY_RECESSION))
		|| entryData.bController && pJoy->GetButtonState(XINPUT_GAMEPAD_A, pJoy->BUTTON_TRIGGER, entryData.nControllNum))
	{
		CGame::SetMapType(m_selectStageType);
		CManager::GetFade()->SetFade(CManager::MODE_GAME);
	}
}
