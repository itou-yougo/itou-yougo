//====================================================
//
// ジョイパッドクラスの処理[joypad.cpp]
// Author:伊藤陽梧
//
//====================================================

//====================================================
// インクルード
//====================================================
#include "joypad.h"

//====================================================
// コンストラクタ
//====================================================
CInputJoypad::CInputJoypad()
{
	// 初期化
	memset(m_aJoyState, 0, sizeof(m_aJoyState));
	memset(m_aJoyStateTrigger, 0, sizeof(m_aJoyStateTrigger));
	memset(m_aJoyStateRelease, 0, sizeof(m_aJoyStateRelease));

	memset(m_aJoyStateLTRT, 0, sizeof(m_aJoyStateLTRT));
	memset(m_aJoyStateTriggerLTRT, 0, sizeof(m_aJoyStateTriggerLTRT));
	memset(m_aJoyStateReleaseLTRT, 0, sizeof(m_aJoyStateReleaseLTRT));
}

//====================================================
// デストラクタ
//====================================================
CInputJoypad::~CInputJoypad()
{
}

//====================================================
// 初期化処理
//====================================================
HRESULT CInputJoypad::Init(HINSTANCE hInstance, HWND hWnd)
{
	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CInputJoypad::Uninit(void)
{
	// 終了した後にバイブレーションが続かないようにする
	XInputEnable(false);

	CInput::Uninit();
}

//====================================================
// 更新処理
//====================================================
void CInputJoypad::Update(void)
{
	// コントローラの情報
	XINPUT_STATE state;

	// 更新する前に初期化
	memset(m_aJoyStateTrigger, 0, sizeof(m_aJoyStateTrigger));
	memset(m_aJoyStateRelease, 0, sizeof(m_aJoyStateRelease));
	memset(m_aJoyStateTriggerLTRT, 0, sizeof(m_aJoyStateTriggerLTRT));
	memset(m_aJoyStateReleaseLTRT, 0, sizeof(m_aJoyStateReleaseLTRT));

	for (int nCountJoystick = 0; nCountJoystick < MAX_JOYSTICK_NUM; nCountJoystick++)
	{
		// ジョイパッドの情報の取得
		if (GetPadState(state, nCountJoystick) == ERROR_SUCCESS)
		{
			// ボタンの更新
			UpdateButton(state, nCountJoystick);
			// LTRTの更新
			UpdateTrigger(state, nCountJoystick);
			// 振動の更新
			UpdateVibration(nCountJoystick);
		}
	}
}

//====================================================
// Xinputのボタンを返す処理
// Pad_Button_State:コントローラのボタン
//====================================================
WORD CInputJoypad::Return_XInput(const PAD_BUTTON_STATE Pad_Button_State)
{
	switch (Pad_Button_State)
	{
	case PAD_A:
		return XINPUT_GAMEPAD_A;
		break;

	case PAD_B:
		return XINPUT_GAMEPAD_B;
		break;

	case PAD_X:
		return XINPUT_GAMEPAD_X;
		break;

	case PAD_Y:
		return XINPUT_GAMEPAD_Y;
		break;
	case PAD_LB:
		return XINPUT_GAMEPAD_LEFT_SHOULDER;
		break;

	case PAD_RB:
		return XINPUT_GAMEPAD_RIGHT_SHOULDER;
		break;

	case PAD_BACK:
		return XINPUT_GAMEPAD_BACK;
		break;

	case PAD_START:
		return XINPUT_GAMEPAD_START;
		break;

	case PAD_UP:
		return XINPUT_GAMEPAD_DPAD_UP;
		break;

	case PAD_DOWN:
		return XINPUT_GAMEPAD_DPAD_DOWN;
		break;

	case PAD_LEFT:
		return XINPUT_GAMEPAD_DPAD_LEFT;
		break;

	case PAD_RIGHT:
		return XINPUT_GAMEPAD_DPAD_RIGHT;
		break;

	case PAD_LEFT_THUMB:
		return XINPUT_GAMEPAD_LEFT_THUMB;
		break;

	case PAD_RIGHT_THUMB:
		return XINPUT_GAMEPAD_RIGHT_THUMB;
		break;

	default:
		break;
	}
	return 0;
}

//====================================================
// 列挙型のボタンを返す処理
// Xinput_Gamepad:コントローラのボタン
//====================================================
int CInputJoypad::Return_Button(const WORD Xinput_Gamepad)
{
	switch (Xinput_Gamepad)
	{
	case XINPUT_GAMEPAD_A:
		return PAD_A;
		break;

	case XINPUT_GAMEPAD_B:
		return PAD_B;
		break;

	case XINPUT_GAMEPAD_X:
		return PAD_X;
		break;

	case XINPUT_GAMEPAD_Y:
		return PAD_Y;
		break;
	case XINPUT_GAMEPAD_LEFT_SHOULDER:
		return PAD_LB;
		break;

	case XINPUT_GAMEPAD_RIGHT_SHOULDER:
		return PAD_RB;
		break;

	case XINPUT_GAMEPAD_BACK:
		return PAD_BACK;
		break;

	case XINPUT_GAMEPAD_START:
		return PAD_START;
		break;

	case XINPUT_GAMEPAD_DPAD_UP:
		return PAD_UP;
		break;

	case XINPUT_GAMEPAD_DPAD_DOWN:
		return PAD_DOWN;
		break;

	case XINPUT_GAMEPAD_DPAD_LEFT:
		return PAD_LEFT;
		break;

	case XINPUT_GAMEPAD_DPAD_RIGHT:
		return PAD_RIGHT;
		break;

	case XINPUT_GAMEPAD_LEFT_THUMB:
		return PAD_LEFT_THUMB;
		break;

	case XINPUT_GAMEPAD_RIGHT_THUMB:
		return PAD_RIGHT_THUMB;
		break;

	default:
		break;
	}
	return 0;
}

//====================================================
// バイブレーションの開始
// L_magnification:左のバイブレーションの倍率(0.0f～1.0f)
// R_magnification:右のバイブレーションの倍率(0.0f～1.0f)
// fVibTime       :振動する時間
// nJoystickNum   :コントローラの番号
//====================================================
void CInputJoypad::EnableVibration(const float L_magnification, const float R_magnification, const float fVibTime, const int nJoystickNum)
{
	// 振動値を出す
	float fL_vib = 65535 * L_magnification;
	float fR_vib = 65535 * R_magnification;

	// 振動する時間
	m_fVibrationTime[nJoystickNum] = fVibTime;

	// 振動用の構造体
	XINPUT_VIBRATION vibration;

	// 初期化
	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));

	// 振動値代入
	vibration.wLeftMotorSpeed = (WORD)fL_vib;
	vibration.wRightMotorSpeed = (WORD)fR_vib;

	// 振動させる
	XInputSetState(nJoystickNum, &vibration);
}

//====================================================
// バイブレーションの終了
// nJoystickNum:コントローラの番号
//====================================================
void CInputJoypad::DisableVibration(int nJoystickNum)
{
	// 振動用の構造体
	XINPUT_VIBRATION vibration;

	// 初期化
	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));

	// 振動値代入
	vibration.wLeftMotorSpeed = 0;
	vibration.wRightMotorSpeed = 0;

	// 振動を止める
	XInputSetState(nJoystickNum, &vibration);
}

//====================================================
// ボタンの更新処理
//====================================================
void CInputJoypad::UpdateButton(const XINPUT_STATE state, const int nJoystickNum)
{
	for (int nCntButton = 0; nCntButton < MAX_PAD_BUTTON; nCntButton++)
	{
		//キーリリース
		m_aJoyStateRelease[nJoystickNum][nCntButton] = (m_aJoyState[nJoystickNum][nCntButton] ^ state.Gamepad.wButtons) & ~state.Gamepad.wButtons;

		// 押してるときにキーの情報を入れる
		if (state.Gamepad.wButtons & Return_XInput((PAD_BUTTON_STATE)nCntButton))
		{
			//キートリガー
			m_aJoyStateTrigger[nJoystickNum][nCntButton] = (m_aJoyState[nJoystickNum][nCntButton] ^ state.Gamepad.wButtons) & state.Gamepad.wButtons;

			//キープレス情報を保存
			m_aJoyState[nJoystickNum][nCntButton] = state.Gamepad.wButtons;
		}
		else
		{
			//キープレス情報を保存
			m_aJoyState[nJoystickNum][nCntButton] = 0;
		}
	}
}

//====================================================
// トリガーの更新処理
//====================================================
void CInputJoypad::UpdateTrigger(const XINPUT_STATE state, const int nJoystickNum)
{
	for (int nCntTrigger = 0; nCntTrigger < MAX_PAD_TRIGGER; nCntTrigger++)
	{
		switch ((PAD_TRRIGER_STATE)nCntTrigger)
		{
		case PAD_LT: // 左トリガー
			UpdateTriggerState(state.Gamepad.bLeftTrigger, nCntTrigger, nJoystickNum);
			break;

		case PAD_RT: // 右トリガー
			UpdateTriggerState(state.Gamepad.bRightTrigger, nCntTrigger, nJoystickNum);
			break;

		default:
			break;
		}
	}
}

//====================================================
// トリガーの情報更新処理
// nTriggerPush:トリガーの押し込んだ量
// nPadTrigger:スティックの座標
// nJoystickNum:コントローラの番号
//====================================================
void CInputJoypad::UpdateTriggerState(const int nTriggerPush, const int nPadTrigger, int nJoystickNum)
{
	if (nTriggerPush > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
	{
		//キートリガー
		m_aJoyStateTriggerLTRT[nJoystickNum][nPadTrigger] = (m_aJoyStateLTRT[nJoystickNum][nPadTrigger] ^ true) & true;

		//キーリリース
		m_aJoyStateReleaseLTRT[nJoystickNum][nPadTrigger] = false;

		//キープレス情報を保存
		m_aJoyStateLTRT[nJoystickNum][nPadTrigger] = true;
	}
	else
	{
		if (nTriggerPush == 0 && m_aJoyStateLTRT[nJoystickNum][nPadTrigger] == true)
		{
			//キーリリース
			m_aJoyStateReleaseLTRT[nJoystickNum][nPadTrigger] = true;
		}

		//キープレス情報を保存
		m_aJoyStateLTRT[nJoystickNum][nPadTrigger] = false;
	}
}

//====================================================
// 振動の更新処理
//====================================================
void CInputJoypad::UpdateVibration(const int nJoystickNum)
{
	// 振動の時間が指定されたら減算
	if (m_fVibrationTime[nJoystickNum] > 0.0f)
	{
		m_fVibrationTime[nJoystickNum]--;
	}
	else
	{
		// 初期値に戻して振動を停止
		m_fVibrationTime[nJoystickNum] = 0.0f;
		DisableVibration(nJoystickNum);
	}
}

//====================================================
// ボタンの取得
// wButton_State:どのボタンか
// Push_State:押し込み方
// nJoystickNum:コントローラの番号
// 返り値:押されているかの判定
//====================================================
bool CInputJoypad::GetButtonState(const WORD wButton_State, const BUTTON_PUSH_STATE Push_State, int nJoystickNum)
{
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(state));	// 初期化

										// ジョイパッドの情報の取得
	if (GetPadState(state, nJoystickNum) == ERROR_SUCCESS)
	{
		// 押し方によって渡すものを変える
		switch (Push_State)
		{
		case BUTTON_PRESS:
			return GetJoystickPress(wButton_State, Return_Button(wButton_State), nJoystickNum);
			break;

		case BUTTON_TRIGGER:
			return GetJoystickTrigger(wButton_State, Return_Button(wButton_State), nJoystickNum);
			break;

		case BUTTON_RELEASE:
			return GetJoystickRelease(wButton_State, Return_Button(wButton_State), nJoystickNum);
			break;
		default:
			break;
		}
	}
	return false;
}

//====================================================
// LT、RTの押し込みの取得
// Pad_Trigger_State:LT、RTどっちか
// Push_State:押し込み方
// nJoystickNum:コントローラの番号
// 返り値:押されているかの判定
//====================================================
bool CInputJoypad::GetTriggerState(const PAD_TRRIGER_STATE Pad_Trigger_State, const BUTTON_PUSH_STATE Push_State, int nJoystickNum)
{
	XINPUT_STATE state;

	// トリガーのデッドゾーン
	int Trigger_Dedzone = XINPUT_GAMEPAD_TRIGGER_THRESHOLD;

	// ジョイパッドの情報の取得
	if (GetPadState(state, nJoystickNum) == ERROR_SUCCESS)
	{
		// 押し方によって渡すものを変える
		switch (Push_State)
		{
		case BUTTON_PRESS:
			return GetJoystickPressLTRT(Pad_Trigger_State, nJoystickNum);
			break;

		case BUTTON_TRIGGER:
			return GetJoystickTriggerLTRT(Pad_Trigger_State, nJoystickNum);
			break;

		case BUTTON_RELEASE:
			return GetJoystickReleaseLTRT(Pad_Trigger_State, nJoystickNum);
			break;
		default:
			break;
		}
	}
	return false;
}

//====================================================
// LT、RTの押し込み具合の取得
// Pad_Trigger_State:LT、RTどっちか
// nJoystickNum:コントローラの番号
// 返り値:トリガーの押し込み具合
//====================================================
int CInputJoypad::GetTriggerPushCondition(const PAD_TRRIGER_STATE Pad_Trigger_State, int nJoystickNum)
{
	XINPUT_STATE state;

	// トリガーのデッドゾーン
	int Trigger_Dedzone = XINPUT_GAMEPAD_TRIGGER_THRESHOLD;

	// ジョイパッドの情報の取得
	if (GetPadState(state, nJoystickNum) == ERROR_SUCCESS)
	{
		switch (Pad_Trigger_State)
		{
		case PAD_LT: // 左トリガー
			if (state.Gamepad.bLeftTrigger > Trigger_Dedzone)
			{
				// 入力されているなら値を返す
				return state.Gamepad.bLeftTrigger;
			}
			break;

		case PAD_RT: // 右トリガー
			if (state.Gamepad.bRightTrigger > Trigger_Dedzone)
			{
				// 入力されているなら値を返す
				return state.Gamepad.bRightTrigger;
			}
			break;

		default:
			break;
		}
	}
	return 0;
}

//====================================================
// スティックの取得
// Pad_Stick_State:スティックの番号
// nJoystickNum:コントローラの番号
// 返り値:スティックの座標
//====================================================
D3DXVECTOR2 CInputJoypad::GetStickState(const PAD_STICK_STATE Pad_Stick_State, int nJoystickNum)
{
	XINPUT_STATE state;

	// 右、左スティックのデッドゾーン
	int Left_Thumb_Dedzone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
	int Right_Thumb_Dedzone = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;

	// ジョイパッドの情報の取得
	if (GetPadState(state, nJoystickNum) == ERROR_SUCCESS)
	{
		switch (Pad_Stick_State)
		{
		case PAD_LEFT_STICK:
			// 左スティック
			if (state.Gamepad.sThumbLX > Left_Thumb_Dedzone ||
				state.Gamepad.sThumbLX < -Left_Thumb_Dedzone ||
				state.Gamepad.sThumbLY > Left_Thumb_Dedzone ||
				state.Gamepad.sThumbLY < -Left_Thumb_Dedzone)
			{
				// 入力されているなら値を返す
				return D3DXVECTOR2(state.Gamepad.sThumbLX, state.Gamepad.sThumbLY);
			}
			break;

		case PAD_RIGHT_STICK:
			// 右スティック
			if (state.Gamepad.sThumbRX > Right_Thumb_Dedzone ||
				state.Gamepad.sThumbRX < -Right_Thumb_Dedzone ||
				state.Gamepad.sThumbRY > Right_Thumb_Dedzone ||
				state.Gamepad.sThumbRY < -Right_Thumb_Dedzone)
			{
				// 入力されているなら値を返す
				return D3DXVECTOR2(state.Gamepad.sThumbRX, state.Gamepad.sThumbRY);
			}
			break;

		default:
			break;
		}
	}

	// 入力されてないなら0.0fを返す
	return D3DXVECTOR2(0.0f, 0.0f);
}

//====================================================
// ジョイパッドの情報の取得
// state:コントローラの情報
// nJoystickNum:コントローラの番号
// 返り値:コントローラが接続されているかどうか
//====================================================
DWORD CInputJoypad::GetPadState(XINPUT_STATE& state, int nJoystickNum)
{
	ZeroMemory(&state, sizeof(state));						// 初期化
	DWORD dwResult = XInputGetState(nJoystickNum, &state);	// 情報取得

	return dwResult;
}

//====================================================
// プレス情報の取得
// wPad_State:ボタンの値
// nPad_Bottan:コントローラのボタン
// nJoystickNum:コントローラの番号
//====================================================
bool CInputJoypad::GetJoystickPress(const WORD wPad_State, const int nPad_Bottan, int nJoystickNum)
{
	return m_aJoyState[nJoystickNum][nPad_Bottan] & wPad_State ? true : false;
}

//====================================================
// トリガー情報の取得
// wPad_State:ボタンの値
// nPad_Bottan:コントローラのボタン
// nJoystickNum:コントローラの番号
//====================================================
bool CInputJoypad::GetJoystickTrigger(const WORD wPad_State, const int nPad_Bottan, int nJoystickNum)
{
	return m_aJoyStateTrigger[nJoystickNum][nPad_Bottan] & wPad_State ? true : false;
}

//====================================================
// リリース情報の取得
// wPad_State:ボタンの値
// nPad_Bottan:コントローラのボタン
// nJoystickNum:コントローラの番号
//====================================================
bool CInputJoypad::GetJoystickRelease(const WORD wPad_State, const int nPad_Bottan, int nJoystickNum)
{
	return m_aJoyStateRelease[nJoystickNum][nPad_Bottan] & wPad_State ? true : false;
}

//====================================================
// プレス情報の取得
// nPad_Trigger:トリガーの番号
// nJoystickNum:コントローラの番号
//====================================================
bool CInputJoypad::GetJoystickPressLTRT(const int nPad_Trigger, const int nJoystickNum)
{
	return m_aJoyStateLTRT[nJoystickNum][nPad_Trigger];
}

//====================================================
// トリガー情報の取得
// nPad_Trigger:トリガーの番号
// nJoystickNum:コントローラの番号
//====================================================
bool CInputJoypad::GetJoystickTriggerLTRT(const int nPad_Trigger, const int nJoystickNum)
{
	return m_aJoyStateTriggerLTRT[nJoystickNum][nPad_Trigger];
}

//====================================================
// リリース情報の取得
// nPad_Trigger:トリガーの番号
// nJoystickNum:コントローラの番号
//====================================================
bool CInputJoypad::GetJoystickReleaseLTRT(const int nPad_Trigger, const int nJoystickNum)
{
	return m_aJoyStateReleaseLTRT[nJoystickNum][nPad_Trigger];
}