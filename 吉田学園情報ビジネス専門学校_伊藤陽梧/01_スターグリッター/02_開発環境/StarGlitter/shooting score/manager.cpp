//=============================================================================
//
// �}�l�[�W���[�̏��� [manager.cpp]
// Author : �ɓ��z��
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "scene2d.h"
#include "input.h"
#include "player.h"
#include "player2.h"
#include "explosion.h"
#include "sound.h"
#include "bg.h"
#include "enemy.h"
#include "bullet.h"
#include "lifepolygon.h"
#include "effect.h"
#include "gauge.h"
#include "ojamaplayer.h"
#include "ojamaplayer2.h"
#include "title.h"
#include "game.h"
#include "enemyexplosion.h"
#include "fade.h"
#include "charge.h"
#include "gauge.h"
#include "chargeshot.h"
#include "input.h"
#include "extraattack.h"
#include "bomb.h"
#include "bombexplosion.h"
#include "bossattack.h"
#include "titlelogo.h"
#include "tutorial.h"
#include "gattyann.h"
#include "text.h"
#include "select.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CTitle *CManager::m_pTitle = NULL;
CTutorial *CManager::m_pTutorial = NULL;
CGame *CManager::m_pGame = NULL;
CResult *CManager::m_pResult = NULL;
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputkeyboard = NULL;
CInputJoypad *CManager::m_pInputJoypad = NULL;
CSound *CManager::m_pSound = NULL;
CFade *CManager::m_pFade = NULL;
CManager::MODE CManager::m_mode = MODE_TITLE;

//=============================================================================
// �}�l�[�W���[�N���X�̃R���X�g���N�^
//=============================================================================
CManager::CManager()
{
	m_nCountFPS = 0;
}

//=============================================================================
// �}�l�[�W���[�N���X�̃f�X�g���N�^
//=============================================================================
CManager::~CManager()
{

}

//=============================================================================
// �}�l�[�W���[�N���X�̏���������
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	if (m_pRenderer == NULL)
	{
		// �����_���[�̃������̊m��
		m_pRenderer = new CRenderer;
	}
	// �����_���[�̏���������
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{
		return -1;
	}

	if (m_pInputkeyboard == NULL)
	{
		// �L�[�{�[�h�̃������m��
		m_pInputkeyboard = new CInputKeyboard;
	}
	// �L�[�{�[�h�̏���������
	if (FAILED(m_pInputkeyboard->Init(hInstance, hWnd)))
	{
		return -1;
	}

	if (m_pInputJoypad == NULL)
	{
		// �L�[�{�[�h�̃������m��
		m_pInputJoypad = new CInputJoypad;
	}
	// �L�[�{�[�h�̏���������
	if (FAILED(m_pInputJoypad->Init(hInstance, hWnd)))
	{
		return -1;
	}

	if (m_pSound == NULL)
	{
		// �T�E���h�̃������m��
		m_pSound = new CSound;
	}
	// �T�E���h�̏���������
	if (FAILED(m_pSound->Init(hWnd)))
	{
		return -1;
	}
	
	// �e�N�X�`���̃��[�h
	CBg::Load();
	CPlayer::Load();
	CPlayer2::Load();
	CEnemy::Load();
	CBullet::Load();
	CExplosion::Load();
	CLifepolygon::Load();
	CEffect::Load();
	COjamaplayer::Load();
	COjamaplayer2::Load();
	CEnemyexplosion::Load();
	CCharge::Load();
	CGauge::Load();
	CChargeshot::Load();
	CExtraattck::Load();
	CBomb::Load();
	CBombexplosion::Load();
	CBossattck::Load();
	CTitleLogo::Load();
	CGattyann::Load();
	CText::Load();
	CSelect::Load();


	SetMode(MODE_TITLE);
	m_pFade = CFade::Create();

	return S_OK;
}

//=============================================================================
// �}�l�[�W���[�N���X�̏I������
//=============================================================================
void CManager::Uninit(void)
{
	// m_pSound��NULL����Ȃ��Ƃ�
	if (m_pSound != NULL)
	{
		// �T�E���h�̏I������
		m_pSound->Uninit();

		// �������̊J��(�T�E���h�̃N���X)
		delete m_pSound;
		m_pSound = NULL;
	}

	// m_pInputkeyboard��NULL����Ȃ��Ƃ�
	if (m_pInputkeyboard != NULL)
	{
		// �L�[�{�[�h�̏I������
		m_pInputkeyboard->Uninit();

		// �������̊J��(�L�[�{�[�h�N���X)
		delete m_pInputkeyboard;
		m_pInputkeyboard = NULL;
	}

	// m_pInputJoypad��NULL����Ȃ��Ƃ�
	if (m_pInputJoypad != NULL)
	{
		// �W���C�p�b�h�̏I������
		m_pInputJoypad->Uninit();

		// �������̊J��(�W���C�p�b�h�N���X)
		delete m_pInputJoypad;
		m_pInputJoypad = NULL;
	}

	// �e�N�X�`���̃A�����[�h
	CBg::Unload();
	CPlayer::Unload();
	CPlayer2::Unload();
	CEnemy::Unload();
	CBullet::Unload();
	CExplosion::Unload();
	CLifepolygon::Unload();
	CEffect::Unload();
	COjamaplayer::Unload();
	COjamaplayer2::Unload();
	CEnemyexplosion::Unload();
	CCharge::Unload();
	CGauge::Unload();
	CChargeshot::Unload();
	CExtraattck::Unload();
	CBomb::Unload();
	CBombexplosion::Unload();
	CBossattck::Unload();
	CTitleLogo::Unload();
	CGattyann::Unload();
	CText::Unload();
	CSelect::Unload();

	// �I�u�W�F�N�g�̏I�������ƃ������̊J��
	CScene::ReleaseAll();

	// m_pRenderer��NULL����Ȃ��Ƃ�
	if (m_pRenderer != NULL)
	{
		// �����_���[�̏I������
		m_pRenderer->Uninit();

		// �������̊J��(�����_�����O�N���X)
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

//=============================================================================
// �}�l�[�W���[�N���X�̍X�V����
//=============================================================================
void CManager::Update(void)
{
	// CInput�̃|�C���^�̃C���X�^���X�����̎󂯎��
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	CInputJoypad *pInputJoypad = CManager::GetInputJoypad();

	switch (m_mode)
	{
	case MODE_TITLE:
		// m_pTitle��NULL����Ȃ��Ƃ�
		if (m_pTitle != NULL)
		{
			// ����������
			m_pTitle->Update();
		}
		break;

	case MODE_TUTORIAL:
		// m_pTutorial��NULL����Ȃ��Ƃ�
		if (m_pTutorial != NULL)
		{
			// ����������
			m_pTutorial->Update();
		}
		break;

	case MODE_GAME:
		// m_pGame��NULL����Ȃ��Ƃ�
		if (m_pGame != NULL)
		{
			// ����������
			m_pGame->Update();
		}
		break;
	}

	// m_pInputkeyboard��NULL����Ȃ��Ƃ�
	if (m_pInputkeyboard != NULL)
	{
		m_pInputkeyboard->Update();
	}

	// m_pInputJoypad��NULL����Ȃ��Ƃ�
	if (m_pInputJoypad != NULL)
	{
		m_pInputJoypad->Update();
	}

	// m_pRenderer��NULL����Ȃ��Ƃ�
	if (m_pRenderer != NULL)
	{
		// FPS�̃Z�b�g
		m_pRenderer->SetNumFPS(m_nCountFPS);

		// �X�V����
		m_pRenderer->Update();
	}

}

//=============================================================================
// �}�l�[�W���[�N���X�̕`�揈��
//=============================================================================
void CManager::Draw(void)
{
	if (m_pRenderer != NULL)
	{
		// �`�揈��
		m_pRenderer->Draw();
	}

	switch (m_mode)
	{
	case MODE_TITLE:
		// m_pTitle��NULL����Ȃ��Ƃ�
		if (m_pTitle != NULL)
		{
			// ����������
			m_pTitle->Draw();
		}
		break;

	case MODE_GAME:
		// m_pGame��NULL����Ȃ��Ƃ�
		if (m_pGame != NULL)
		{
			// ����������
			m_pGame->Draw();
		}
		break;

		break;
	}
}


//=============================================================================
// �}�l�[�W���[�N���X�̃��[�h��ݒ肷�鏈��
//=============================================================================
void CManager::SetMode(MODE mode)
{
	m_mode = mode;

	if (m_pTitle != NULL)
	{
		m_pTitle->Uninit();

		delete m_pTitle;
		m_pTitle = NULL;
	}

	if (m_pTutorial != NULL)
	{
		m_pTutorial->Uninit();

		delete m_pTutorial;
		m_pTutorial = NULL;
	}

	if (m_pGame != NULL)
	{
		m_pGame->Uninit();

		delete m_pGame;
		m_pGame = NULL;
	}

	switch (m_mode)
	{
	case MODE_TITLE:
		if (m_pTitle == NULL)
		{
			// �^�C�g���̃N���G�C�g
			m_pTitle = CTitle::Create();
		}
		break;

	case MODE_TUTORIAL:
		if (m_pTutorial == NULL)
		{
			// �`���[�g���A���̃N���G�C�g
			m_pTutorial = CTutorial::Create();
		}
		break;

	case MODE_GAME:
		if (m_pGame == NULL)
		{
			// �Q�[���̃N���G�C�g
			m_pGame = CGame::Create();
		}
		break;
	}
}

//=============================================================================
// �}�l�[�W���[�N���X�̃��[�h��ݒ肷�鏈��
//=============================================================================
CManager::MODE CManager::GetMode(void)
{
	return m_mode;
}

//=============================================================================
// �}�l�[�W���[�N���X�̃����_���[�̃|�C���^��n������
//=============================================================================
CRenderer* CManager::GetRenderer(void)
{
	// m_pRenderer��Ԃ�
	return m_pRenderer;
}

//=============================================================================
// �}�l�[�W���[�N���X�̃L�[�{�[�h�̃|�C���^��n������
//=============================================================================
CInputKeyboard* CManager::GetInputKeyboard(void)
{
	// m_pInputkeyboard��Ԃ�
	return m_pInputkeyboard;
}

//=============================================================================
// �}�l�[�W���[�N���X�̃W���C�p�b�h�̃|�C���^��n������
//=============================================================================
CInputJoypad * CManager::GetInputJoypad(void)
{
	// m_pInputJoypad��Ԃ�
	return m_pInputJoypad;
}

//=============================================================================
// �}�l�[�W���[�N���X�̃T�E���h�̃|�C���^��n������
//=============================================================================
CSound * CManager::GetSound(void)
{
	// m_pSound��Ԃ�
	return m_pSound;
}

//=============================================================================
// �}�l�[�W���[�N���X�̃t�F�[�h�̃|�C���^��n������
//=============================================================================
CFade * CManager::GetFade(void)
{
	// m_pFade��Ԃ�
	return m_pFade;
}
