//=============================================================================
//
// �}�l�[�W���[�̏��� [manager.h]
// Author : �ɓ��z��
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "game.h"

//=============================================================================
// �O���錾
//=============================================================================
class CTitle;
class CGame;
class CResult;
class CRenderer;
class CScene2D;

class CInput;
class CInputKeyboard;
class CInputJoypad;
class CSound;
class CBg;
class CEnemy;
class CScore;
class CGauge;
class CFade;
class CTutorial;

//=============================================================================
// �}�l�[�W���[�N���X
//=============================================================================
class CManager
{
public:
	typedef enum MyEnum
	{
		MODE_TITLE = 0,
		MODE_TUTORIAL,
		MODE_GAME,
		MODE_END,
	}MODE;
	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetNumFPS(int nCountFPS) { m_nCountFPS = nCountFPS; }
	static void SetMode(MODE mode);
	static MODE GetMode(void);
	static CRenderer *GetRenderer(void);
	static CInputKeyboard *GetInputKeyboard(void);
	static CInputJoypad *GetInputJoypad(void);
	static CSound *GetSound(void);
	static CFade* GetFade(void);

private:
	static CTitle		  *m_pTitle;		 // �^�C�g���̃|�C���^
	static CTutorial	  *m_pTutorial;		 // �`���[�g���A���̃|�C���^
	static CGame		  *m_pGame;			 // �Q�[���̃|�C���^
	static CResult		  *m_pResult;		 // ���U���g�̃|�C���^
	static CRenderer	  *m_pRenderer;		 // �����_���[�̃|�C���^
	static CInputKeyboard *m_pInputkeyboard; // �L�[�{�[�h�̃|�C���^
	static CInputJoypad	  *m_pInputJoypad;	 // �W���C�p�b�h�̃|�C���^
	static CSound		  *m_pSound;		 // �T�E���h�̃|�C���^
	static CFade		  *m_pFade;			 // �t�F�[�h�̃|�C���^
	static MODE			  m_mode;			 // ���[�h
	int					  m_nCountFPS;		 // FPS�̒l

};
#endif