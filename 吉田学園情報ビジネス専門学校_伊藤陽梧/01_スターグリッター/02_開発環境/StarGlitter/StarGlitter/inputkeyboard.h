////=============================================================================
////
//// ポリゴンの描画の処理 [inputkeyboard.h]
//// Author : 伊藤陽梧
////
////=============================================================================
//#ifndef _INPUTKEYBOARD_H_
//#define _INPUTKEYBOARD_H_
//
////=============================================================================
////インクルードファイル
////=============================================================================
//#include "main.h"
//#include"input.h"
//
////=============================================================================
//// キーボードクラス
////=============================================================================
//class CInputKeyboard : public CInput
//{
//public:
//	CInputKeyboard();
//	~CInputKeyboard();
//
//	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
//	void Uninit(void);
//	void Update(void);
//	bool GetKeyboardPress(int nKey);
//	bool GetKeyboardTrigger(int nKey);
//	bool GetKeyboardRelease(int nKey);
//private:
//	BYTE m_aKeyState[MAX_KEY_NUM];	//キーボードのトリガー入力情報ワーク
//	BYTE m_aKeyState2[MAX_KEY_NUM];	//キーボードのリリース入力情報ワーク
//	BYTE m_aKeyStateTrigger[MAX_KEY_NUM];	//キーボードのトリガー情報
//	BYTE m_aKeyStateRelease[MAX_KEY_NUM];	//キーボードのリリース情報
//};
//
//#endif
