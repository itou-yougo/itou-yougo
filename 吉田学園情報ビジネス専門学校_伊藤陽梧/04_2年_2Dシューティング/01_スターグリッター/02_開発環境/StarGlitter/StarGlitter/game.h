//=============================================================================
//
// �Q�[���̏��� [game.h]
// Author : �ɓ��z��
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_SELECT (2) // �I���̍ő�l

//=============================================================================
// �O���錾
//=============================================================================
class CScene2D;
class CGauge;
class CSelect;

//=============================================================================
// �Q�[���N���X
//=============================================================================
class CGame
{
public:
	typedef enum
	{
		GAMESTATE_NONE = 0,
		GAMESTATE_NORMAL,   // �m�[�}���̏��
		GAMESTATE_START,	// �Q�[�����n�܂������
		GAMESTATE_END,		// �Q�[�����I��������
		GAMESTATE_MAX,
	}GAMESTATE;

	CGame();
	~CGame();

	static CGame *Create();

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static void SetGameState(GAMESTATE gamestate);
	static GAMESTATE GetGameState(void);
private:
	static GAMESTATE	  m_gamestate;			  // �Q�[���̏��
	static CSelect		  *m_pSelect[MAX_SELECT]; // �Z���N�g�N���X�̃|�C���^
	int					  m_nCountCreate;		  // ��������J�E���g
	int					  m_nSelectCount;		  // �I�񂾎��̃J�E���g
	int					  m_nCountText;			  // �e�L�X�g�̃J�E���g
	bool				  m_bPause;				  // �|�[�Y��Ԃ��ǂ���
	bool				  m_bGameStart;			  // �Q�[�����n�܂������ǂ���
};
#endif