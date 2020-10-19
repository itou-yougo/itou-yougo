////=============================================================================
////
//// PLASTIC TROOPERSの処理[controller.h](コントローラーでの操作）
//// Author : 後藤慎之助
////
////=============================================================================
//#ifndef _CONTROLLER_H_
//#define _CONTROLLER_H_
//#define _CRT_SECURE_NO_WARNINGS_
//
////=============================================================================
//// インクルードファイル
////=============================================================================
//#include"main.h"
//
////=============================================================================
//// 外部変数
////=============================================================================
//extern LPDIRECTINPUT8		pDInput;
//extern LPDIRECTINPUTDEVICE8	pDIKeyboard;
//extern BYTE					diKeyState[256];
//extern LPDIRECTINPUTDEVICE8	pDIJoypad;
//extern DWORD				diJoyState;
//extern LPDIRECTINPUTDEVICE8	pDIMouse;
//extern DIMOUSESTATE			diMouseState;
//
////=============================================================================
////マクロ定義
////=============================================================================
//#define BUTTON_UP     (0)	    //十字キー上
//#define BUTTON_DOWN   (18000)	//十字キー下
//#define BUTTON_LEFT   (27000)	//十字キー左
//#define BUTTON_RIGHT  (9000)	//十字キー右
//#define CROSSZONE (4500)        //十字キーの許容範囲
//#define	MAX_CONTROLLER	(4)				//つなぐコントローラーの最大数 
//
////プレイヤーの番号
//#define PLAYER_1 (0)     //プレイヤーのコントローラー番号 (1P)
//#define PLAYER_2 (1)     //プレイヤーのコントローラー番号 (2P)
//#define PLAYER_3 (2)     //プレイヤーのコントローラー番号 (3P)
//#define PLAYER_4 (3)     //プレイヤーのコントローラー番号 (4P)
//
////=============================================================================
//// コントローラークラス
////=============================================================================
//class CController
//{
//public:
//	typedef enum
//	{
//		BUTTON_X = 0,
//		BUTTON_Y,
//		BUTTON_A,
//		BUTTON_B,
//		BUTTON_L1,
//		BUTTON_R1,
//		BUTTON_L2,
//		BUTTON_R2,
//		BUTTON_SELECT,	//
//		BUTTON_START,
//		BUTTON_L3,		//
//		BUTTON_R3,		//
//		BUTTON_M,
//		MAX_BUTTON
//	}BUTTON;//ボタンの数
//
//	typedef struct
//	{
//		LPDIRECTINPUTDEVICE8	pDIJoypad;	// コントローラーデバイス
//		DIJOYSTATE2 State;							//コントローラーのプレス情報
//		DIJOYSTATE2 Trigger;						//コントローラーのトリガー情報
//		DIJOYSTATE2 Release;						//コントローラーのプレス情報
//	}CONTROLLER;
//
//
//	CController();
//	~CController();
//
//	BOOL CALLBACK GetJoystickCallback(LPDIDEVICEINSTANCE lpddi, LPVOID);
//	HRESULT InitJoypad(HINSTANCE hInstance, HWND hWnd);
//	void UpdateJoypad(void);
//	void ReleaseDInput(void);
//	bool GetJoypadPress(int nContllre, int nButton);
//	bool GetJoypadTrigger(int nContllre, int nButton);
//	bool GetJoypadRelease(int nContllre, int nButton);
//	DIJOYSTATE2 GetController(int nContllre);
//
//private:
//	LPDIRECTINPUTDEVICE8	m_DIJoypad;	// コントローラーデバイス
//	DIJOYSTATE2 m_ControllerState;				//コントローラーのプレス情報
//	DIJOYSTATE2 m_ControllerStateTrigger;		//コントローラーのトリガー情報
//	DIJOYSTATE2 m_ControllerStateRelease;		//コントローラーのプレス情報
//	CONTROLLER m_Controller[MAX_CONTROLLER];
//	static int m_nCntContoroller;
//};
//
//#endif