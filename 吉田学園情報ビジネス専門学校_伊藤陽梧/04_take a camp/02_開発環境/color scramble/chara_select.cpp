////////////////////////////////////////////////////
//
//    キャラ選択クラスの処理[chara_select.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//=============================
// インクルード
//=============================
#include "chara_select.h"
#include "joypad.h"
#include "manager.h"
#include "chara_select_ui.h"
#include "keyboard.h"
#include "manager.h"
#include "fade.h"
#include "player.h"
#include "camera_charaselect.h"
#include "bg.h"
#include "light.h"

//=============================
// マクロ定義
//=============================
#define WAIT_TIME 10
#define MIN_PLAYER_NUM 2

//=============================
// 静的メンバ変数宣言
//=============================
CCharaSelect::Entry_Data CCharaSelect::m_aEntryData[MAX_PLAYER] = {};
int CCharaSelect::m_nEntryPlayerNum = 0;

//=============================
// コンストラクタ
//=============================
CCharaSelect::CCharaSelect()
{
	// 変数のクリア
	ZeroMemory(&m_abUseJoy, sizeof(m_abUseJoy));
	ZeroMemory(&m_abUseKey, sizeof(m_abUseKey));
	ZeroMemory(&m_anWaitCnt, sizeof(m_anWaitCnt));
}

//=============================
// デストラクタ
//=============================
CCharaSelect::~CCharaSelect()
{
}

//=============================
// クリエイト
//=============================
CCharaSelect * CCharaSelect::Create(void)
{
	// メモリの確保
	CCharaSelect *pGame = new CCharaSelect;
	// 初期化
	pGame->Init();

	return pGame;
}

//=============================
// 初期化処理
//=============================
HRESULT CCharaSelect::Init(void)
{
	for (int nCntData = 0; nCntData < MAX_PLAYER; nCntData++)
	{
		m_abUseJoy[nCntData] = false;
		m_abUseKey[nCntData] = false;
	}

	// エントリー情報のリセット
	ResetEntryPlayer();
	// UIの生成
	CCharaSelectUi::Create();
	// カメラ生成
	CManager::SetCamera(CCharaSelectCamera::Create());
	// 背景の生成
	CBg::Create();

	// ライトの向きの設定
	CManager::GetLight()->SetDir(LIGHT_DIR_CHARA_FRONT);

	return S_OK;
}

//=============================
// 終了処理
//=============================
void CCharaSelect::Uninit(void)
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
void CCharaSelect::Update(void)
{
	// カメラクラス更新処理
	CCamera * pCamera = CManager::GetCamera();
	if (pCamera != NULL)
	{
		pCamera->Update();
	}

	// エントリー処理
	EntryPlayer();

	FadeGameScene();

#ifdef _DEBUG

	if(CManager::GetKeyboard()->GetKeyTrigger(DIK_F1)|| CManager::GetKeyboard()->GetKeyTrigger(DIK_RETURN))
	{
		switch (CManager::GetDecMode())
		{
		case CManager::MODE_TUTORIAL:
			CManager::GetFade()->SetFade(CManager::MODE_TUTORIAL);
			break;

		case CManager::MODE_GAME:
			CManager::GetFade()->SetFade(CManager::MODE_STAGE_SELECT);
			break;

		default:
			break;
		}
	}

	CountEntryPlayerNum();
#endif // _DEBUG

}

//=============================
// 描画処理
//=============================
void CCharaSelect::Draw(void)
{
	// カメラクラス更新処理
	CCamera * pCamera = CManager::GetCamera();
	if (pCamera != NULL)
	{
		pCamera->SetCamera();
	}
}

//=============================
// キャラクター数のリセット
//=============================
void CCharaSelect::ResetEntryPlayer(void)
{
	for (int nCntData = 0; nCntData < MAX_PLAYER; nCntData++)
	{
		m_aEntryData[nCntData].bController = false;
		m_aEntryData[nCntData].bEntry = false;
		m_aEntryData[nCntData].nColorNum = nCntData; // 仮
		m_aEntryData[nCntData].nControllNum = -1;
		m_aEntryData[nCntData].charaType = CResourceCharacter::CHARACTER_NONE;
		m_aEntryData[nCntData].bReady = false;
	}
	m_nEntryPlayerNum = 0;
}

//=============================
// ゲームシーンにフェード
//=============================
void CCharaSelect::FadeGameScene(void)
{
	int nReadyPlayerNum = 0;
	for (int nCntData = 0; nCntData < MAX_PLAYER; nCntData++)
	{
		if (m_aEntryData[nCntData].bEntry && !m_aEntryData[nCntData].bReady) return;
		else if (m_aEntryData[nCntData].bEntry && m_aEntryData[nCntData].bReady) nReadyPlayerNum++;
	}

	// プレイヤー数のカウント
	CountEntryPlayerNum();

	if (m_nEntryPlayerNum >= MIN_PLAYER_NUM&&nReadyPlayerNum == m_nEntryPlayerNum)
	{// エントリー数がMIN_PLAYER_NUM以上且つエントリー数と準備完了数が一緒の時

		CManager::GetFade()->SetFade(CManager::MODE_STAGE_SELECT);
	}
}

//=============================
// プレイヤーのエントリー処理
//=============================
void CCharaSelect::EntryPlayer(void)
{
	// エントリー
	auto EntryPlayer = [this](int nCntData, int nCntJoy, bool bController)
	{
		// エントリー状態にする
		m_aEntryData[nCntData].bEntry = true;
		// コントローラーフラグ
		m_aEntryData[nCntData].bController = bController;
		// コントローラー番号のセット
		m_aEntryData[nCntData].nControllNum = nCntJoy;
		// キャラタイプ
		m_aEntryData[nCntData].charaType = CResourceCharacter::CHARACTER_KNIGHT;
		// コントローラーを使用状態に
		if (bController) m_abUseJoy[nCntJoy] = true;
		// キーボードを使用状態に
		else m_abUseKey[nCntJoy] = true;
		// カウントの初期化
		m_anWaitCnt[nCntData] = 0;
	};

	// エントリー解除処理
	auto EntryCancelPlayer = [this](int nCntData)
	{
		// エントリー状態にする
		m_aEntryData[nCntData].bEntry = false;
		// コントローラー・キーボードを非使用状態に
		if (m_aEntryData[nCntData].bController) m_abUseJoy[m_aEntryData[nCntData].nControllNum] = false;
		else m_abUseKey[m_aEntryData[nCntData].nControllNum] = false;

		// コントローラーフラグ
		m_aEntryData[nCntData].bController = false;
		// コントローラー番号のセット
		m_aEntryData[nCntData].nControllNum = -1;
	};

	CInputJoypad * pJoy = CManager::GetJoypad();
	CInputKeyboard *pKey = CManager::GetKeyboard();

	for (int nCntData = 0; nCntData < MAX_PLAYER; nCntData++)
	{
		if (m_aEntryData[nCntData].bEntry)
		{
			// エントリー解除処理
			if (   m_aEntryData[nCntData].bController && pJoy->GetButtonState(XINPUT_GAMEPAD_START, CInputJoypad::BUTTON_TRIGGER, m_aEntryData[nCntData].nControllNum)
				||!m_aEntryData[nCntData].bController && pKey->GetKeyTrigger(CPlayer::GetPlayerControllKey(m_aEntryData[nCntData].nControllNum, CPlayer::KEY_PROGRESS)))
			{
				// エントリーのキャンセル
				EntryCancelPlayer(nCntData);
				break;
			}
			if (m_anWaitCnt[nCntData] > 0) m_anWaitCnt[nCntData]--;
			CharacterSelect(nCntData);
		}

		for (int nCntJoy = 0; nCntJoy < MAX_PLAYER; nCntJoy++)
		{
			// エントリー処理
			if (!m_aEntryData[nCntData].bEntry)
			{// エントリー状態じゃないとき
				if (!m_abUseJoy[nCntJoy] && pJoy->GetButtonState(XINPUT_GAMEPAD_START, CInputJoypad::BUTTON_TRIGGER, nCntJoy))
				{// コントローラーでエントリー
					EntryPlayer(nCntData, nCntJoy, true);
					pJoy->EnableVibration(1.0f, 1.0f, 10.0f, nCntJoy);
					break;
				}

				// エントリーキーの取得*前進キー
				int nEntryKey = CPlayer::GetPlayerControllKey(nCntJoy, CPlayer::KEY_PROGRESS);
				if (!m_abUseKey[nCntJoy] && pKey->GetKeyTrigger(CPlayer::GetPlayerControllKey(nCntJoy, CPlayer::KEY_PROGRESS)))
				{// キーボードでエントリー
					EntryPlayer(nCntData, nCntJoy, false);
					break;
				}
				m_aEntryData[nCntData].charaType = CResourceCharacter::CHARACTER_NONE;
			}
		}
	}
}

//=============================
// エントリー人数のカウント
//=============================
void CCharaSelect::CountEntryPlayerNum(void)
{
	m_nEntryPlayerNum = 0;
	for (int nCntData = 0; nCntData < MAX_PLAYER; nCntData++)
	{
		if (m_aEntryData[nCntData].bEntry)
		{// エントリーフラグがtrueの時にカウントする
			m_nEntryPlayerNum++;
		}
	}
}

//=============================
// キャラセレクト
//=============================
void CCharaSelect::CharacterSelect(int nCntData)
{
	if (m_anWaitCnt[nCntData] > 0) return;

	// キーボード・ゲームパッドの情報の取得
	CInputKeyboard *pKey = CManager::GetKeyboard();
	CInputJoypad * pJoy = CManager::GetJoypad();

	// スティックの座標
	D3DXVECTOR2 StickPos = pJoy->GetStickState(pJoy->PAD_LEFT_STICK, m_aEntryData[nCntData].nControllNum);

	if (m_aEntryData[nCntData].bReady)
	{
		// 決定キー
		if (!m_aEntryData[nCntData].bController && pKey->GetKeyTrigger(CPlayer::GetPlayerControllKey(m_aEntryData[nCntData].nControllNum, CPlayer::KEY_RECESSION))
			|| m_aEntryData[nCntData].bController && pJoy->GetButtonState(XINPUT_GAMEPAD_A, pJoy->BUTTON_TRIGGER, m_aEntryData[nCntData].nControllNum))
		{
			m_aEntryData[nCntData].bReady = false;
		}
		return;
	}

	int nType = m_aEntryData[nCntData].charaType;
	// キャラの選択処理
	if (!m_aEntryData[nCntData].bController && pKey->GetKeyPress(CPlayer::GetPlayerControllKey(m_aEntryData[nCntData].nControllNum, CPlayer::KEY_LEFT))
		|| m_aEntryData[nCntData].bController && ((StickPos.x < 0.0f && StickPos.y < STICK_DECISION_RANGE && StickPos.y > -STICK_DECISION_RANGE)
			|| pJoy->GetButtonState(XINPUT_GAMEPAD_DPAD_LEFT, pJoy->BUTTON_PRESS, m_aEntryData[nCntData].nControllNum)))
	{
		
		// 進む
		nType--;
		if (nType < 0)
		{
			nType = CResourceCharacter::CHARACTER_MAX - 1;
		}
		m_aEntryData[nCntData].charaType = (CResourceCharacter::CHARACTER_TYPE)nType;

		m_anWaitCnt[nCntData] = WAIT_TIME;
		return;
	}
	if (!m_aEntryData[nCntData].bController && pKey->GetKeyPress(CPlayer::GetPlayerControllKey(m_aEntryData[nCntData].nControllNum, CPlayer::KEY_RIGHT))
		|| m_aEntryData[nCntData].bController && ((StickPos.x > 0.0f && StickPos.y < STICK_DECISION_RANGE && StickPos.y > -STICK_DECISION_RANGE)
			|| pJoy->GetButtonState(XINPUT_GAMEPAD_DPAD_RIGHT, pJoy->BUTTON_PRESS, m_aEntryData[nCntData].nControllNum)))
	{
		// 戻る
		nType++;
		if (nType >= CResourceCharacter::CHARACTER_MAX)
		{
			nType = 0;
		}
		m_aEntryData[nCntData].charaType = (CResourceCharacter::CHARACTER_TYPE)nType;
		m_anWaitCnt[nCntData] = WAIT_TIME;
		return;
	}

	// 決定キー
	if (!m_aEntryData[nCntData].bController && pKey->GetKeyTrigger(CPlayer::GetPlayerControllKey(m_aEntryData[nCntData].nControllNum, CPlayer::KEY_RECESSION))
		|| m_aEntryData[nCntData].bController && pJoy->GetButtonState(XINPUT_GAMEPAD_A, pJoy->BUTTON_TRIGGER, m_aEntryData[nCntData].nControllNum))
	{
		m_aEntryData[nCntData].bReady = true;
	}

	// カウントの初期化
	m_anWaitCnt[nCntData] = 0;
}
