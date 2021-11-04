//====================================================================
//
// ���͏��� [input.h]
// Author : �ɓ��z��
//
//====================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"

//================================================
// �}�N����`
//================================================
#define NUM_KEY_MAX (256)//�L�[�̍ő吔

#define MAX_CONTROLLER 2       //�Ȃ��R���g���[���[�̍ő吔

#define BUTTON_UP     (0)	    // �\���L�[��
#define BUTTON_DOWN   (18000)	// �\���L�[��
#define BUTTON_LEFT   (27000)	// �\���L�[��
#define BUTTON_RIGHT  (9000)	// �\���L�[�E

#define BUTTON_UP_RIGHT     (4500)	// �\���L�[��E
#define BUTTON_RIGHT_DOWN  (13500)	// �\���L�[�E��
#define BUTTON_DOWN_LEFT   (22500)	// �\���L�[����
#define BUTTON_LEFT_UP   (31500)	// �\���L�[����

#define BUTTON_NEUTRAL -1       // �������͂��Ă��Ȃ��Ƃ�
#define CROSSZONE (4500)        // �\���L�[�̋��e�͈�

// �v���C���[�̔ԍ�
#define PLAYER_1 (0)     // �v���C���[�̃R���g���[���[�ԍ� (1P)
#define PLAYER_2 (1)     // �v���C���[�̃R���g���[���[�ԍ� (2P)
#define PLAYER_3 (2)     // �v���C���[�̃R���g���[���[�ԍ� (3P)
#define PLAYER_4 (3)     // �v���C���[�̃R���g���[���[�ԍ� (4P)

//================================================
// �N���X�錾
//================================================

// ���͂̃N���X
class CInput
{
public:
	CInput();          // �R���X�g���N
	virtual ~CInput(); // �f�X�g���N�^  // �e�N���X�̃f�X�g���N�^��virtual�����邱�ƂŁA���������[�N��}����
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd); // ����������
	virtual void Uninit(void); 							  // �I������
	virtual void Update(void) = 0;						  // �X�V����

protected:
	LPDIRECTINPUTDEVICE8 m_pDevice;	// ���̓f�o�C�X�ւ̃|�C���^
	static LPDIRECTINPUT8 m_pInput;	// DirectInput�ւ̃|�C���^
};

// �L�[�{�[�h���͂̃N���X
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();  // �R���X�g���N
	~CInputKeyboard(); // �f�X�g���N�^ 
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);// ����������
	void Uninit(void);							 // �I������
	void Update(void);							 // �X�V����
	bool GetKeyboardPress(int nKey); // Press����
	bool GetKeyboardTrigger(int nKey); // Trigger����
	bool GetKeyboardRelease(int nKey); // Release����

private:
	BYTE m_aKeyStateOld[NUM_KEY_MAX];       // 1F�O�̃L�[�{�[�h�̓��͏�񃏁[�N
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];	// �L�[�{�[�h�̃g���K�[���
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];	// �L�[�{�[�h�̃����[�X���
};

// �W���C�p�b�h�̃N���X
class CInputJoypad :public CInput
{
public:

	// �{�^���̎��
	typedef enum
	{
		BUTTON_X = 0,
		BUTTON_Y,
		BUTTON_A,
		BUTTON_B,
		BUTTON_L1,
		BUTTON_R1,
		BUTTON_L2,
		BUTTON_R2,
		BUTTON_L3,
		BUTTON_R3,
		BUTTON_SELECT,
		BUTTON_START,
		BUTTON_GUIDE,
		MAX_BUTTON
	}BUTTON;

	// �R���g���[���̏��
	typedef struct
	{
		LPDIRECTINPUTDEVICE8 pDIJoypad = NULL; // �R���g���[���[�f�o�C�X
		DIJOYSTATE2 State;       // �R���g���[���[�̃v���X���
		DIJOYSTATE2 Trigger;     // �R���g���[���[�̃g���K�[���
		DIJOYSTATE2 Release;     // �R���g���[���[�̃v���X���
	}CONTROLLER;

	CInputJoypad();  // �R���X�g���N
	~CInputJoypad(); // �f�X�g���N�^ 
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);  // ����������
	void Update(void);							   // �X�V����
	void Release(void);							   // ���̓f�o�C�X�̊J��
	bool GetJoypadPress(int nController, int nButton); // Press����
	bool GetJoypadTrigger(int nController, int nButton); // Trigger����
	bool GetJoypadCrossKeyTrigger(int nController, int nButton);
	bool GetJoypadRelease(int nController, int nButton); // Release����
	DIJOYSTATE2 GetController(int nContllre); // �R���g���[���̏�Ԃ��擾
	static LPDIRECTINPUT8 GetInput(void) { return m_pInput; } // 
	HRESULT CreateDevice(LPDIDEVICEINSTANCE lpddi); // �f�o�C�X��Create

private:
	CONTROLLER m_Controller[MAX_CONTROLLER];    // �R���g���[���[�̏��
	static int m_nCntController;                // �R���g���[���[�̐ڑ���
};

#endif