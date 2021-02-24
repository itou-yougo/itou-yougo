//=============================================================================
//
// �Q�[������ [game.cpp]
// Author : �ɓ��z��
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "game.h"
#include "manager.h"
#include "keyboard.h"
#include "joystick.h"
#include "fade.h"
#include "sound.h"
#include "ui.h"
#include "mode.h"
#include "player.h"
#include "enemy.h"
#include "camera.h"
#include "light.h"
#include "scene.h"
#include "map.h"
#include "skybox.h"
#include "fire.h"
#include "number.h"
#include "enemyremainder.h"
#include "magiccircle.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
CPlayer *CGame::m_pPlayer = NULL;
int CGame::m_nEnemyNum = 0;
int CGame::m_nEnemyDeathTotal = 0;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGame::CGame()
{
	m_bEnemyCreate = true;
	m_nEnemyCreateTime = ENEMY_CREATE_TIME;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGame::~CGame()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CGame::Init(void)
{
	//rand�̏�����
	srand((unsigned)time(NULL));

	//�T�E���h�̍Đ�
	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_GAME);

	//�J����
	CManager::CreateCamera();

	//���C�g
	CManager::CreateLight();
	m_pPlayer = CPlayer::Create(PLAYER_DEFAULT_POS, PLAYER_DEFAULT_ROT, PLAYER_DEFAULT_SIZE);
	CSkyBox::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 1000.0f, 2000.0f));
	CMap::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 200.0f));	

	// HP��UI
	CUi::Create(D3DXVECTOR3(150.0f, 600.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), CUi::TYPE_HP);
	CUi::Create(D3DXVECTOR3(400.0f, 600.0f, 0.0f), D3DXVECTOR3(450.0f, 50.0f, 0.0f), CUi::TYPE_HPSPBACK);
	CUi::Create(D3DXVECTOR3(400.0f, 600.0f, 0.0f), D3DXVECTOR3(450.0f, 50.0f, 0.0f), CUi::TYPE_PLAYER_LIFE);
	CUi::Create(D3DXVECTOR3(400.0f, 600.0f, 0.0f), D3DXVECTOR3(450.0f, 50.0f, 0.0f), CUi::TYPE_HPFLAME);

	// SP��UI
	CUi::Create(D3DXVECTOR3(750.0f, 600.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), CUi::TYPE_SP);
	CUi::Create(D3DXVECTOR3(1000.0f, 600.0f, 0.0f), D3DXVECTOR3(450.0f, 50.0f, 0.0f), CUi::TYPE_HPSPBACK);
	CUi::Create(D3DXVECTOR3(1000.0f, 600.0f, 0.0f), D3DXVECTOR3(450.0f, 50.0f, 0.0f), CUi::TYPE_PLAYER_SP);
	CUi::Create(D3DXVECTOR3(1000.0f, 600.0f, 0.0f), D3DXVECTOR3(450.0f, 50.0f, 0.0f), CUi::TYPE_SPFLAME);

	CEnemyremainder::Create(D3DXVECTOR3(1000.0f, 100.0f, 0.0f));
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CGame::Uninit(void)
{
	//�T�E���h�̒�~
	CManager::GetSound()->StopSound(CSound::SOUND_LABEL_BGM_GAME);

	//�w�肵���I�u�W�F�N�g�ȊO�̃������̊J������
	CScene::DesignationReleaseAll(CScene::OBJTYPE_FADE);

	m_pPlayer = NULL;
	m_nEnemyNum = 0;
	m_nEnemyDeathTotal = 0;

	m_bEnemyCreate = false;
	m_nEnemyCreateTime = 0;
}

//=============================================================================
// �X�V����
//=============================================================================
void CGame::Update(void)
{
	// ��������t���O�������Ă���Ȃ�
	if (m_bEnemyCreate == true)
	{
		// �G�𐶐����鎞�Ԃ̉��Z
		m_nEnemyCreateTime++;
		if (m_nEnemyCreateTime >= ENEMY_CREATE_TIME)
		{
			// ��������p�x
			float fCreateAngle = D3DXToRadian((rand() % ENEMY_CREATE_ANGLE));
			float fDivide = (float)(rand() % 3 + 1);

			// �G�𐶐�����Ƃ��̖��@�w�̐���
			CMagiccercle::Create(D3DXVECTOR3((ENEMY_CREATE_DISTANCE.x / fDivide) * sinf(fCreateAngle), 0.0f, (ENEMY_CREATE_DISTANCE.z / fDivide) * cosf(fCreateAngle)),
				MAGICCERCLE_DEFAULT_ROT, MAGICCERCLE_ENEMY_DEFAULT_SIZE, MAGICCERCLE_DEFAULT_COLOR,
				MAGICCERCLE_ENEMY_COUNTANIM * MAGICCERCLE_ENEMY_PATTERNANIM * MAGICCERCLE_ENEMY_TIMEANIM, CMagiccercle::MAGICCIRCLETYPE_ENEMY);

			// �G�̐��̉��Z
			m_nEnemyNum++;
			m_nEnemyCreateTime = 0;

			// �G�̑�������������
			if (m_nEnemyNum >= ENEMY_CREATE_NUM)
			{
				m_bEnemyCreate = false;
			}
		}
	}

	// �G�̐���0�ɂȂ�����
	if (m_nEnemyNum == 0)
	{
		m_bEnemyCreate = true;
	}

	if (m_nEnemyDeathTotal >= MAX_ENEMY_NUM)
	{
		if (CScene::GetUpdateStop() == false)
		{
			//�T�E���h�̒�~
			CManager::GetSound()->StopSound(CSound::SOUND_LABEL_BGM_GAME);
			CManager::GetSound()->StopSound(CSound::SOUND_LABEL_SE_DASH);

			//�t�F�[�h�̐���
			CManager::CreateFade(CManager::MODE_RESULT);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CGame::Draw(void)
{
}

//=============================================================================
// �v���C���[�̎擾
//=============================================================================
CPlayer *CGame::GetPlayer(void)
{
	return m_pPlayer;
}