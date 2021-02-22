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
#include "Fire.h"
#include "number.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
CPlayer *CGame::m_pPlayer = NULL;
int CGame::m_nEnemyNum = 0;
int CGame::m_EnemyDeathTotal = 0;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGame::CGame()
{
	m_bEnemyCreate = true;
	m_nEnemyCreateTime = ENEMY_CREATE_TIME;
	for (int nCount = 0; nCount < MAX_NUMBER_CREATE; nCount++)
	{
		m_apNumber[nCount] = NULL;
	}
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
	CUi::Create(D3DXVECTOR3(150.0f, 600.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f), CUi::TYPE_HP);
	CUi::Create(D3DXVECTOR3(400.0f, 600.0f, 0.0f), D3DXVECTOR3(400.0f, 100.0f, 0.0f), CUi::TYPE_HPBACK);
	CUi::Create(D3DXVECTOR3(400.0f, 600.0f, 0.0f), D3DXVECTOR3(400.0f, 100.0f, 0.0f), CUi::TYPE_PLAYER_LIFE);
	CUi::Create(D3DXVECTOR3(400.0f, 600.0f, 0.0f), D3DXVECTOR3(400.0f, 100.0f, 0.0f), CUi::TYPE_HPFLAME);
	//CUi::Create(D3DXVECTOR3(1000.0f, 100.0f, 0.0f), D3DXVECTOR3(422.5f, 65.5f, 0.0f), CUi::TYPE_ENEMYREMAINDER);

	m_apNumber[0] = CNumber::Create(D3DXVECTOR3(1000.0f, 100.0f, 0.0f), D3DXVECTOR3(422.5f, 65.5f, 0.0f));
	m_apNumber[1] = CNumber::Create(D3DXVECTOR3(1000.0f, 100.0f, 0.0f), D3DXVECTOR3(422.5f, 65.5f, 0.0f));
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
	m_EnemyDeathTotal = 0;

	for (int nCount = 0; nCount < MAX_NUMBER_CREATE; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			m_apNumber[nCount]->Uninit();
			delete m_apNumber[nCount];
			m_apNumber[nCount] = NULL;
		}
	}
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

			// �G�̐���
			CEnemy::Create(D3DXVECTOR3((ENEMY_CREATE_DISTANCE.x / fDivide) * sinf(fCreateAngle), 35.0f, (ENEMY_CREATE_DISTANCE.z / fDivide) * cosf(fCreateAngle)),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMY_SIZE, CEnemy::ENEMYSTATE_NOMAL);

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

	if (m_EnemyDeathTotal >= MAX_ENEMY_NUM)
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

	for (int nCount = 0; nCount < MAX_NUMBER_CREATE; nCount++)
	{
		int nScore = (int)pow(10.0f, MAX_NUMBER_CREATE - nCount);
		int nScore2 = (int)pow(10.0f, MAX_NUMBER_CREATE - nCount - 1);
		int nAnswer = (MAX_ENEMY_NUM - m_EnemyDeathTotal) % nScore / nScore2;

		m_apNumber[nCount]->SetNumber(nAnswer);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CGame::Draw(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER_CREATE; nCount++)
	{
		m_apNumber[nCount]->Draw();
	}
}

//=============================================================================
// �v���C���[�̎擾
//=============================================================================
CPlayer *CGame::GetPlayer(void)
{
	return m_pPlayer;
}