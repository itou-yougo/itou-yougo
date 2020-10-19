////=============================================================================
////
//// PLASTIC TROOPERS�̏���[controller.h](�R���g���[���[�ł̑���j
//// Author : �㓡�T�V��
////
////=============================================================================
//#ifndef _CONTROLLER_H_
//#define _CONTROLLER_H_
//#define _CRT_SECURE_NO_WARNINGS_
//
////=============================================================================
//// �C���N���[�h�t�@�C��
////=============================================================================
//#include"main.h"
//
////=============================================================================
//// �O���ϐ�
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
////�}�N����`
////=============================================================================
//#define BUTTON_UP     (0)	    //�\���L�[��
//#define BUTTON_DOWN   (18000)	//�\���L�[��
//#define BUTTON_LEFT   (27000)	//�\���L�[��
//#define BUTTON_RIGHT  (9000)	//�\���L�[�E
//#define CROSSZONE (4500)        //�\���L�[�̋��e�͈�
//#define	MAX_CONTROLLER	(4)				//�Ȃ��R���g���[���[�̍ő吔 
//
////�v���C���[�̔ԍ�
//#define PLAYER_1 (0)     //�v���C���[�̃R���g���[���[�ԍ� (1P)
//#define PLAYER_2 (1)     //�v���C���[�̃R���g���[���[�ԍ� (2P)
//#define PLAYER_3 (2)     //�v���C���[�̃R���g���[���[�ԍ� (3P)
//#define PLAYER_4 (3)     //�v���C���[�̃R���g���[���[�ԍ� (4P)
//
////=============================================================================
//// �R���g���[���[�N���X
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
//	}BUTTON;//�{�^���̐�
//
//	typedef struct
//	{
//		LPDIRECTINPUTDEVICE8	pDIJoypad;	// �R���g���[���[�f�o�C�X
//		DIJOYSTATE2 State;							//�R���g���[���[�̃v���X���
//		DIJOYSTATE2 Trigger;						//�R���g���[���[�̃g���K�[���
//		DIJOYSTATE2 Release;						//�R���g���[���[�̃v���X���
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
//	LPDIRECTINPUTDEVICE8	m_DIJoypad;	// �R���g���[���[�f�o�C�X
//	DIJOYSTATE2 m_ControllerState;				//�R���g���[���[�̃v���X���
//	DIJOYSTATE2 m_ControllerStateTrigger;		//�R���g���[���[�̃g���K�[���
//	DIJOYSTATE2 m_ControllerStateRelease;		//�R���g���[���[�̃v���X���
//	CONTROLLER m_Controller[MAX_CONTROLLER];
//	static int m_nCntContoroller;
//};
//
//#endif