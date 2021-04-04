//=============================================================================
//
// �Q�[���̏��� [game.cpp]
// Author : �ɓ��z��
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "game.h"
#include "scene2d.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "explosion.h"
#include "bg.h"
#include "enemy.h"
#include "bullet.h"
#include "lifepolygon.h"
#include "effect.h"
#include "gauge.h"
#include "ojama.h"
#include "input.h"
#include "select.h"
#include "text.h"
#include "sound.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MENU_SELECT1 (0)	
#define MENU_SELECT2 (1) 

#define MENU_POS (D3DXVECTOR3(850.0f, 625.0f, 0.0f))

#define ENEMY_CREATE_COUNT (200)

#define STARTBOTTON_PRESS_COUNT (20)
#define ABOTTON_PRESS_COUNT (18)

#define PLAYER1_POS (D3DXVECTOR3(PLAYER_START_POS, SCREEN_HEIGHT - 200.0f, 0.0f))
#define PLAYER2_POS (D3DXVECTOR3(PLAYER2_START_POS, SCREEN_HEIGHT - 200.0f, 0.0f))
#define PLAYER1_READY_POS (D3DXVECTOR3(PLAYER_START_POS, SCREEN_CENTER_Y, 0.0f))
#define PLAYER2_READY_POS (D3DXVECTOR3(PLAYER2_START_POS, SCREEN_CENTER_Y, 0.0f))
#define READY_SIZE (D3DXVECTOR3(832.0f, 0.0f, 0.0f))
#define KO_POS (D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f))
#define KO_SIZE (D3DXVECTOR3(530.0f, 232.0f, 0.0f))

#define LEFTSCREEN_LEFT_ENEMY1_POS (D3DXVECTOR3(144.0f, -100.0f, 0.0f))
#define LEFTSCREEN_LEFT_ENEMY2_POS (D3DXVECTOR3(144.0f, -200.0f, 0.0f))
#define LEFTSCREEN_LEFT_ENEMY3_POS (D3DXVECTOR3(144.0f, -300.0f, 0.0f))
#define LEFTSCREEN_LEFT_ENEMY4_POS (D3DXVECTOR3(144.0f, -400.0f, 0.0f))
#define LEFTSCREEN_LEFT_ENEMY5_POS (D3DXVECTOR3(144.0f, -500.0f, 0.0f))

#define RIGHTSCREEN_LEFT_ENEMY1_POS (D3DXVECTOR3(1008.0f, -100.0f, 0.0f))
#define RIGHTSCREEN_LEFT_ENEMY2_POS (D3DXVECTOR3(1008.0f, -200.0f, 0.0f))
#define RIGHTSCREEN_LEFT_ENEMY3_POS (D3DXVECTOR3(1008.0f, -300.0f, 0.0f))
#define RIGHTSCREEN_LEFT_ENEMY4_POS (D3DXVECTOR3(1008.0f, -400.0f, 0.0f))
#define RIGHTSCREEN_LEFT_ENEMY5_POS (D3DXVECTOR3(1008.0f, -500.0f, 0.0f))

#define LEFTSCREEN_CENTER_ENEMY1_POS (D3DXVECTOR3(432.0f, -100.0f, 0.0f))
#define LEFTSCREEN_CENTER_ENEMY2_POS (D3DXVECTOR3(432.0f, -200.0f, 0.0f))
#define LEFTSCREEN_CENTER_ENEMY3_POS (D3DXVECTOR3(432.0f, -300.0f, 0.0f))
#define LEFTSCREEN_CENTER_ENEMY4_POS (D3DXVECTOR3(432.0f, -400.0f, 0.0f))
#define LEFTSCREEN_CENTER_ENEMY5_POS (D3DXVECTOR3(432.0f, -500.0f, 0.0f))

#define RIGHTSCREEN_CENTER_ENEMY1_POS (D3DXVECTOR3(1296.0f, -100.0f, 0.0f))
#define RIGHTSCREEN_CENTER_ENEMY2_POS (D3DXVECTOR3(1296.0f, -200.0f, 0.0f))
#define RIGHTSCREEN_CENTER_ENEMY3_POS (D3DXVECTOR3(1296.0f, -300.0f, 0.0f))
#define RIGHTSCREEN_CENTER_ENEMY4_POS (D3DXVECTOR3(1296.0f, -400.0f, 0.0f))
#define RIGHTSCREEN_CENTER_ENEMY5_POS (D3DXVECTOR3(1296.0f, -500.0f, 0.0f))rye��

#define LEFTSCREEN_RIGHT_ENEMY1_POS (D3DXVECTOR3(720.0f, -100.0f, 0.0f))
#define LEFTSCREEN_RIGHT_ENEMY2_POS (D3DXVECTOR3(720.0f, -200.0f, 0.0f))
#define LEFTSCREEN_RIGHT_ENEMY3_POS (D3DXVECTOR3(720.0f, -300.0f, 0.0f))
#define LEFTSCREEN_RIGHT_ENEMY4_POS (D3DXVECTOR3(720.0f, -400.0f, 0.0f))
#define LEFTSCREEN_RIGHT_ENEMY5_POS (D3DXVECTOR3(720.0f, -500.0f, 0.0f))

#define RIGHTSCREEN_RIGHT_ENEMY1_POS (D3DXVECTOR3(1584.0f, -100.0f, 0.0f))
#define RIGHTSCREEN_RIGHT_ENEMY2_POS (D3DXVECTOR3(1584.0f, -200.0f, 0.0f))
#define RIGHTSCREEN_RIGHT_ENEMY3_POS (D3DXVECTOR3(1584.0f, -300.0f, 0.0f))
#define RIGHTSCREEN_RIGHT_ENEMY4_POS (D3DXVECTOR3(1584.0f, -400.0f, 0.0f))
#define RIGHTSCREEN_RIGHT_ENEMY5_POS (D3DXVECTOR3(1584.0f, -500.0f, 0.0f))

#define ENEMY_SPEED (D3DXVECTOR3(0.0f, 3.0f, 0.0f))

#define ENEMY_SIZE1 (D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 0.0f))
#define ENEMY_SIZE2 (D3DXVECTOR3(ENEMY_SIZE_X - 5.0f, ENEMY_SIZE_Y - 5.0f, 0.0f))
#define ENEMY_SIZE3 (D3DXVECTOR3(ENEMY_SIZE_X - 10.0f, ENEMY_SIZE_Y - 10.0f, 0.0f))
#define ENEMY_SIZE4 (D3DXVECTOR3(ENEMY_SIZE_X - 15.0f, ENEMY_SIZE_Y - 15.0f, 0.0f))
#define ENEMY_SIZE5 (D3DXVECTOR3(ENEMY_SIZE_X - 20.0f, ENEMY_SIZE_Y - 20.0f, 0.0f))
#define ENEMY_SIZE6 (D3DXVECTOR3(ENEMY_SIZE_X - 25.0f, ENEMY_SIZE_Y - 25.0f, 0.0f))

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CGame::GAMESTATE CGame::m_gamestate = GAMESTATE_NONE;
CSelect *CGame::m_pSelect[MAX_SELECT] = {};

//=============================================================================
// �Q�[���N���X�̃R���X�g���N�^
//=============================================================================
CGame::CGame()
{
	m_nCountCreate = 200;
	m_nSelectCount = 0;
	m_nCountText = 0;
	m_bPause = true;
	m_bGameStart = false;
	m_pSelect[MENU_SELECT1] = NULL;
	m_pSelect[MENU_SELECT2] = NULL;
	m_gamestate = GAMESTATE_NORMAL;
}

//=============================================================================
// �Q�[���N���X�̃f�X�g���N�^
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// �Q�[���N���X�̃C���X�^���X����
//=============================================================================
CGame *CGame::Create()
{
	// CGame�̃|�C���^
	CGame *pGame = NULL;

	// �������̊m��
	pGame = new CGame;

	// pGame��NULL����Ȃ��Ƃ�
	if (pGame != NULL)
	{
		// ����������
		pGame->Init();
	}

	// pGame��Ԃ�
	return pGame;
}

//=============================================================================
// �Q�[���N���X�̏���������
//=============================================================================
HRESULT CGame::Init()
{
	// m_pBg�������̊m��
	CBg::Create(CBg::BGTYPE_GAME, CScene::OBJTYPE_BG);
	CBg::Create(CBg::BGTYPE_FRAME, CScene::OBJTYPE_BG);

	// CPlayer�̃N���G�C�g
	CPlayer::Create(PLAYER1_POS, D3DXVECTOR3(PLAYER_SPEED, PLAYER_SPEED, 0.0f),
		D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, 0.0f), PLAYER_LIFE, CPlayer::PLAYER_1P, CScene::OBJTYPE_PLAYER);

	// CPlayer�̃N���G�C�g
	CPlayer::Create(PLAYER2_POS, D3DXVECTOR3(PLAYER_SPEED, PLAYER_SPEED, 0.0f),
		D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, 0.0f), PLAYER_LIFE, CPlayer::PLAYER_2P, CScene::OBJTYPE_PLAYER);

	// �T�E���h�̍Đ�
	CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_GAMEBGM);

	srand((unsigned int)time(NULL));

	return S_OK;
}

//=============================================================================
// �Q�[���N���X�̏I������
//=============================================================================
void CGame::Uninit(void)
{
	// �I�u�W�F�N�g�̏I�������ƃ������̊J��
	CScene::NotFadeReleaseAll();
}

//=============================================================================
// �Q�[���N���X�̍X�V����
//=============================================================================
void CGame::Update(void)
{
	switch (m_gamestate)
	{
		// �m�[�}���̏��
	case GAMESTATE_NORMAL:
		// �Q�[�����n�܂��ĂȂ��Ƃ�
		if (m_bGameStart == false)
		{
			// �e�L�X�g�̃J�E���g�̉��Z
			m_nCountText++;

			// �e�L�X�g�̃J�E���g��120�ȏ�ɂȂ�����
			if (m_nCountText >= 120)
			{
				m_nCountText = 0;

				// READY�̕����̐���
				CText::Create(PLAYER1_READY_POS, READY_SIZE, CText::TEXTTYPE_READY);
				CText::Create(PLAYER2_READY_POS, READY_SIZE, CText::TEXTTYPE_READY);

				// �Q�[�����n�܂�����Ԃɂ���
				m_bGameStart = true;
			}
		}
		break;

		// �Q�[�����n�܂������
	case GAMESTATE_START:
		// �Q�[�����n�܂�����
		if (m_bGameStart == true)
		{
			if (CScene::GetPause() != true)
			{
				// �G����鏈��
				EnemyCreate();
			}

			// �|�[�Y���̏���
			Pause();
		}
		break;

		// �Q�[�����I��������
	case GAMESTATE_END:
		if (m_bGameStart == true)
		{
			//�|�[�Y��Ԃɂ���
			CScene::SetPause(true);

			// �e�L�X�g�N���X��KO�̐���
			CText::Create(KO_POS, KO_SIZE, CText::TEXTTYPE_KO);

			// �Q�[�����I����Ԃɂ���
			m_bGameStart = false;

			// �T�E���h�̒�~�ƍĐ�
			CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_KO);
			CManager::GetSound()->StopSound(CManager::GetSound()->SOUND_LABEL_GAMEBGM);
		}
		break;

	default:
		break;

	}
}

//=============================================================================
// �Q�[���N���X�̕`�揈��
//=============================================================================
void CGame::Draw(void)
{

}

//=============================================================================
// �Q�[���N���X�̓G����鏈��
//=============================================================================
void CGame::EnemyCreate(void)
{
	// ��������J�E���g
	m_nCountCreate++;
	// ��������J�E���g��200�ȏ�ɂȂ�����
	if (m_nCountCreate >= ENEMY_CREATE_COUNT)
	{
		// �����_���ŏo���G��ς���
		switch (rand() % 6)
		{
		case 0:
			// m_pEnemy�̃N���G�C�g
			CEnemy::Create(LEFTSCREEN_LEFT_ENEMY1_POS, ENEMY_SPEED, ENEMY_SIZE1, 5, CScene::OBJTYPE_ENEMY);
			CEnemy::Create(LEFTSCREEN_CENTER_ENEMY1_POS, ENEMY_SPEED, ENEMY_SIZE1, 4, CScene::OBJTYPE_ENEMY);
			CEnemy::Create(LEFTSCREEN_RIGHT_ENEMY1_POS, ENEMY_SPEED, ENEMY_SIZE1, 3, CScene::OBJTYPE_ENEMY);

			CEnemy::Create(RIGHTSCREEN_LEFT_ENEMY1_POS, ENEMY_SPEED, ENEMY_SIZE1, 2, CScene::OBJTYPE_ENEMY);
			CEnemy::Create(RIGHTSCREEN_CENTER_ENEMY1_POS, ENEMY_SPEED, ENEMY_SIZE1, 1, CScene::OBJTYPE_ENEMY);
			CEnemy::Create(RIGHTSCREEN_RIGHT_ENEMY1_POS, ENEMY_SPEED, ENEMY_SIZE1, 5, CScene::OBJTYPE_ENEMY);
			m_nCountCreate = 0;
			break;

		case 1:
			// m_pEnemy�̃N���G�C�g
			CEnemy::Create(LEFTSCREEN_LEFT_ENEMY1_POS, ENEMY_SPEED, ENEMY_SIZE6, 1, CScene::OBJTYPE_ENEMY);
			CEnemy::Create(LEFTSCREEN_LEFT_ENEMY2_POS, ENEMY_SPEED, ENEMY_SIZE5, 2, CScene::OBJTYPE_ENEMY);
			CEnemy::Create(LEFTSCREEN_LEFT_ENEMY3_POS, ENEMY_SPEED, ENEMY_SIZE4, 3, CScene::OBJTYPE_ENEMY);
			CEnemy::Create(LEFTSCREEN_LEFT_ENEMY4_POS, ENEMY_SPEED, ENEMY_SIZE3, 4, CScene::OBJTYPE_ENEMY);
			CEnemy::Create(LEFTSCREEN_LEFT_ENEMY5_POS, ENEMY_SPEED, ENEMY_SIZE2, 5, CScene::OBJTYPE_ENEMY);

			CEnemy::Create(RIGHTSCREEN_LEFT_ENEMY1_POS, ENEMY_SPEED, ENEMY_SIZE6, 1, CScene::OBJTYPE_ENEMY);
			CEnemy::Create(RIGHTSCREEN_LEFT_ENEMY2_POS, ENEMY_SPEED, ENEMY_SIZE5, 2, CScene::OBJTYPE_ENEMY);
			CEnemy::Create(RIGHTSCREEN_LEFT_ENEMY3_POS, ENEMY_SPEED, ENEMY_SIZE4, 3, CScene::OBJTYPE_ENEMY);
			CEnemy::Create(RIGHTSCREEN_LEFT_ENEMY4_POS, ENEMY_SPEED, ENEMY_SIZE3, 4, CScene::OBJTYPE_ENEMY);
			CEnemy::Create(RIGHTSCREEN_LEFT_ENEMY5_POS, ENEMY_SPEED, ENEMY_SIZE2, 5, CScene::OBJTYPE_ENEMY);
			m_nCountCreate = 0;
			break;

		case 2:
			// m_pEnemy�̃N���G�C�g
			CEnemy::Create(LEFTSCREEN_RIGHT_ENEMY1_POS, ENEMY_SPEED, ENEMY_SIZE6, 1, CScene::OBJTYPE_ENEMY);
			CEnemy::Create(LEFTSCREEN_RIGHT_ENEMY2_POS, ENEMY_SPEED, ENEMY_SIZE5, 2, CScene::OBJTYPE_ENEMY);
			CEnemy::Create(LEFTSCREEN_RIGHT_ENEMY3_POS, ENEMY_SPEED, ENEMY_SIZE4, 3, CScene::OBJTYPE_ENEMY);
			CEnemy::Create(LEFTSCREEN_RIGHT_ENEMY4_POS, ENEMY_SPEED, ENEMY_SIZE3, 4, CScene::OBJTYPE_ENEMY);
			CEnemy::Create(LEFTSCREEN_RIGHT_ENEMY5_POS, ENEMY_SPEED, ENEMY_SIZE2, 5, CScene::OBJTYPE_ENEMY);

			CEnemy::Create(RIGHTSCREEN_RIGHT_ENEMY1_POS, ENEMY_SPEED, ENEMY_SIZE6, 1, CScene::OBJTYPE_ENEMY);
			CEnemy::Create(RIGHTSCREEN_RIGHT_ENEMY2_POS, ENEMY_SPEED, ENEMY_SIZE5, 2, CScene::OBJTYPE_ENEMY);
			CEnemy::Create(RIGHTSCREEN_RIGHT_ENEMY3_POS, ENEMY_SPEED, ENEMY_SIZE4, 3, CScene::OBJTYPE_ENEMY);
			CEnemy::Create(RIGHTSCREEN_RIGHT_ENEMY4_POS, ENEMY_SPEED, ENEMY_SIZE3, 4, CScene::OBJTYPE_ENEMY);
			CEnemy::Create(RIGHTSCREEN_RIGHT_ENEMY5_POS, ENEMY_SPEED, ENEMY_SIZE2, 5, CScene::OBJTYPE_ENEMY);
			m_nCountCreate = 0;
			break;

		case 3:
			// m_pEnemy�̃N���G�C�g
			CEnemy::Create(LEFTSCREEN_CENTER_ENEMY1_POS, ENEMY_SPEED, ENEMY_SIZE1, 2, CScene::OBJTYPE_ENEMY);
			CEnemy::Create(LEFTSCREEN_CENTER_ENEMY2_POS, ENEMY_SPEED, ENEMY_SIZE1, 1, CScene::OBJTYPE_ENEMY);
			CEnemy::Create(LEFTSCREEN_CENTER_ENEMY3_POS, ENEMY_SPEED, ENEMY_SIZE1, 5, CScene::OBJTYPE_ENEMY);

			CEnemy::Create(RIGHTSCREEN_CENTER_ENEMY1_POS, ENEMY_SPEED, ENEMY_SIZE1, 4, CScene::OBJTYPE_ENEMY);
			CEnemy::Create(RIGHTSCREEN_CENTER_ENEMY2_POS, ENEMY_SPEED, ENEMY_SIZE1, 3, CScene::OBJTYPE_ENEMY);
			CEnemy::Create(RIGHTSCREEN_CENTER_ENEMY3_POS, ENEMY_SPEED, ENEMY_SIZE1, 2, CScene::OBJTYPE_ENEMY);
			m_nCountCreate = 0;
			break;

		case 4:
			// m_pEnemy�̃N���G�C�g
			CEnemy::Create(LEFTSCREEN_LEFT_ENEMY1_POS, ENEMY_SPEED, ENEMY_SIZE2, 5, CScene::OBJTYPE_ENEMY);
			CEnemy::Create(LEFTSCREEN_LEFT_ENEMY2_POS, ENEMY_SPEED, ENEMY_SIZE3, 4, CScene::OBJTYPE_ENEMY);
			CEnemy::Create(LEFTSCREEN_LEFT_ENEMY3_POS, ENEMY_SPEED, ENEMY_SIZE4, 3, CScene::OBJTYPE_ENEMY);
			CEnemy::Create(LEFTSCREEN_LEFT_ENEMY4_POS, ENEMY_SPEED, ENEMY_SIZE5, 2, CScene::OBJTYPE_ENEMY);
			CEnemy::Create(LEFTSCREEN_LEFT_ENEMY5_POS, ENEMY_SPEED, ENEMY_SIZE6, 1, CScene::OBJTYPE_ENEMY);

			CEnemy::Create(RIGHTSCREEN_LEFT_ENEMY1_POS, ENEMY_SPEED, ENEMY_SIZE2, 5, CScene::OBJTYPE_ENEMY);
			CEnemy::Create(RIGHTSCREEN_LEFT_ENEMY2_POS, ENEMY_SPEED, ENEMY_SIZE3, 4, CScene::OBJTYPE_ENEMY);
			CEnemy::Create(RIGHTSCREEN_LEFT_ENEMY3_POS, ENEMY_SPEED, ENEMY_SIZE4, 3, CScene::OBJTYPE_ENEMY);
			CEnemy::Create(RIGHTSCREEN_LEFT_ENEMY4_POS, ENEMY_SPEED, ENEMY_SIZE5, 2, CScene::OBJTYPE_ENEMY);
			CEnemy::Create(RIGHTSCREEN_LEFT_ENEMY5_POS, ENEMY_SPEED, ENEMY_SIZE6, 1, CScene::OBJTYPE_ENEMY);
			m_nCountCreate = 0;
			break;

		case 5:
			// m_pEnemy�̃N���G�C�g
			CEnemy::Create(LEFTSCREEN_RIGHT_ENEMY1_POS, ENEMY_SPEED, ENEMY_SIZE2, 5, CScene::OBJTYPE_ENEMY);
			CEnemy::Create(LEFTSCREEN_RIGHT_ENEMY2_POS, ENEMY_SPEED, ENEMY_SIZE3, 4, CScene::OBJTYPE_ENEMY);
			CEnemy::Create(LEFTSCREEN_RIGHT_ENEMY3_POS, ENEMY_SPEED, ENEMY_SIZE4, 3, CScene::OBJTYPE_ENEMY);
			CEnemy::Create(LEFTSCREEN_RIGHT_ENEMY4_POS, ENEMY_SPEED, ENEMY_SIZE5, 2, CScene::OBJTYPE_ENEMY);
			CEnemy::Create(LEFTSCREEN_RIGHT_ENEMY5_POS, ENEMY_SPEED, ENEMY_SIZE6, 1, CScene::OBJTYPE_ENEMY);

			CEnemy::Create(RIGHTSCREEN_RIGHT_ENEMY1_POS, ENEMY_SPEED, ENEMY_SIZE2, 5, CScene::OBJTYPE_ENEMY);
			CEnemy::Create(RIGHTSCREEN_RIGHT_ENEMY2_POS, ENEMY_SPEED, ENEMY_SIZE3, 4, CScene::OBJTYPE_ENEMY);
			CEnemy::Create(RIGHTSCREEN_RIGHT_ENEMY3_POS, ENEMY_SPEED, ENEMY_SIZE4, 3, CScene::OBJTYPE_ENEMY);
			CEnemy::Create(RIGHTSCREEN_RIGHT_ENEMY4_POS, ENEMY_SPEED, ENEMY_SIZE5, 2, CScene::OBJTYPE_ENEMY);
			CEnemy::Create(RIGHTSCREEN_RIGHT_ENEMY5_POS, ENEMY_SPEED, ENEMY_SIZE6, 1, CScene::OBJTYPE_ENEMY);
			m_nCountCreate = 0;
			break;

		default:
			break;
		}
	}
}

//=============================================================================
// �Q�[���N���X�̃|�[�Y���̏���
//=============================================================================
void CGame::Pause(void)
{
	// CInputJoypad�̃|�C���^�̃C���X�^���X�����̎󂯎��
	CInputJoypad *pInputJoypad = CManager::GetInputJoypad();

	// �|�[�Y��ʂ̏���
	// �I�񂾎��̃J�E���g�����Z����
	m_nSelectCount--;
	// �I�񂾎��̃J�E���g��0�ȉ��ɂȂ�����
	if (m_nSelectCount <= 0)
	{
		// �|�[�Y��Ԃ���Ȃ��A���[�h���Q�[���̎�
		if (m_bPause == true && CManager::GetMode() == CManager::MODE_GAME)
		{
			// �X�^�[�g�{�^������������
			if (pInputJoypad->GetJoypadTrigger(PLAYER_1, CInputJoypad::BUTTON_START))
			{
				//�|�[�Y��Ԃɂ���
				CScene::SetPause(true);

				// �Z���N�g�N���X�̐���
				m_pSelect[0] = CSelect::Create(SCREEN_CENTER_POS, SCREEN_SIZE, CSelect::SELECTTYPE_KUROHAIKEI);
				m_pSelect[1] = CSelect::Create(SCREEN_CENTER_POS, MENU_POS, CSelect::SELECTTYPE_MENU);
				// �|�[�Y��Ԃɂ���
				m_bPause = false;
				m_nSelectCount = STARTBOTTON_PRESS_COUNT;

				// �T�E���h�̒�~�ƍĐ�
				CManager::GetSound()->StopSound(CManager::GetSound()->SOUND_LABEL_GAMEBGM);
				CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_MENUCREATE);
				return;
			}
			if (pInputJoypad->GetJoypadTrigger(PLAYER_2, CInputJoypad::BUTTON_START))
			{
				//�|�[�Y��Ԃɂ���
				CScene::SetPause(true);

				// �Z���N�g�N���X�̐���
				m_pSelect[MENU_SELECT1] = CSelect::Create(SCREEN_CENTER_POS, SCREEN_SIZE, CSelect::SELECTTYPE_KUROHAIKEI);
				m_pSelect[MENU_SELECT2] = CSelect::Create(SCREEN_CENTER_POS, MENU_POS, CSelect::SELECTTYPE_MENU);
				// �|�[�Y��Ԃɂ���
				m_bPause = false;
				m_nSelectCount = STARTBOTTON_PRESS_COUNT;

				// �T�E���h�̒�~�ƍĐ�
				CManager::GetSound()->StopSound(CManager::GetSound()->SOUND_LABEL_GAMEBGM);
				CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_MENUCREATE);
				return;
			}

		}
		// �|�[�Y��Ԃ̎�
		else if (m_bPause == false)
		{
			// �X�^�[�g�{�^������������
			if (pInputJoypad->GetJoypadTrigger(PLAYER_1, CInputJoypad::BUTTON_START))
			{
				//�|�[�Y��Ԃ���������
				CScene::SetPause(false);

				// �T�E���h�̍Đ�
				CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_GAMEBGM);

				for (int nCount = 0; nCount < MAX_SELECT; nCount++)
				{
					// m_pSelect��NULL����Ȃ��Ƃ�
					if (m_pSelect[nCount] != NULL)
					{
						// m_pSelect�̏I������
						m_pSelect[nCount]->Uninit();
						m_pSelect[nCount] = NULL;
					}
				}
				// �|�[�Y��Ԃ���������
				m_bPause = true;
				m_nSelectCount = STARTBOTTON_PRESS_COUNT;
				return;
			}
			if (pInputJoypad->GetJoypadTrigger(PLAYER_2, CInputJoypad::BUTTON_START))
			{
				//�|�[�Y��Ԃ���������
				CScene::SetPause(false);

				// �T�E���h�̍Đ�
				CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_GAMEBGM);

				for (int nCount = 0; nCount < MAX_SELECT; nCount++)
				{
					// m_pSelect��NULL����Ȃ��Ƃ�
					if (m_pSelect[nCount] != NULL)
					{
						// m_pSelect�̏I������
						m_pSelect[nCount]->Uninit();
						m_pSelect[nCount] = NULL;
					}
				}
				// �|�[�Y��Ԃ���������
				m_bPause = true;
				m_nSelectCount = STARTBOTTON_PRESS_COUNT;
				return;
			}
			// A�{�^������������
			if (pInputJoypad->GetJoypadTrigger(PLAYER_1, CInputJoypad::BUTTON_A))
			{
				for (int nCount = 0; nCount < MAX_SELECT; nCount++)
				{
					if (m_pSelect[nCount] != NULL)
					{
						// m_pSelect��NULL����Ȃ��Ƃ�
						m_pSelect[nCount]->Uninit();
						m_pSelect[nCount] = NULL;
					}
				}
				// �|�[�Y��Ԃ���������
				m_bPause = true;
				m_nSelectCount = ABOTTON_PRESS_COUNT;
				return;
			}
			if (pInputJoypad->GetJoypadTrigger(PLAYER_2, CInputJoypad::BUTTON_A))
			{
				for (int nCount = 0; nCount < MAX_SELECT; nCount++)
				{
					if (m_pSelect[nCount] != NULL)
					{
						// m_pSelect��NULL����Ȃ��Ƃ�
						m_pSelect[nCount]->Uninit();
						m_pSelect[nCount] = NULL;
					}
				}
				// �|�[�Y��Ԃ���������
				m_bPause = true;
				m_nSelectCount = ABOTTON_PRESS_COUNT;
				return;
			}
		}
	}
}


//=============================================================================
// �Q�[���N���X�̃Q�[���̏�Ԃ̐ݒ�
//=============================================================================
void CGame::SetGameState(GAMESTATE gamestate)
{
	m_gamestate = gamestate;
}

//=============================================================================
// �Q�[���N���X�̃Q�[���̏�Ԃ�n������
//=============================================================================
CGame::GAMESTATE CGame::GetGameState(void)
{
	return m_gamestate;
}