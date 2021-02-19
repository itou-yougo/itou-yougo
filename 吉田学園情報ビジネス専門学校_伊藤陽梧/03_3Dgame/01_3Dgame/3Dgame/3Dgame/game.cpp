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

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
CPlayer *CGame::m_pPlayer = NULL;
int CGame::m_nEnemyNum = 0;

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
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 40.0f, 0.0f), D3DXVECTOR3(0.0f, 1.5f, 0.0f), D3DXVECTOR3(25.0f, 50.0f, 25.0f));
	CSkyBox::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 1000.0f, 2000.0f));
	CMap::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 200.0f));	
	//CEnemy::Create(D3DXVECTOR3(0.0f, 50.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMY_SIZE, CEnemy::ENEMYSTATE_NOMAL);
	CUi::Create(D3DXVECTOR3((float)SCREEN_CENTER_X, 500.0f, 0.0f), D3DXVECTOR3(200.0f, 50.0f, 0.0f), CUi::TYPE_PLAYER_LIFE);
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
			CEnemy::Create(D3DXVECTOR3((ENEMY_CREATE_DISTANCE.x / fDivide) * sinf(fCreateAngle), 50.0f, (ENEMY_CREATE_DISTANCE.z / fDivide) * cosf(fCreateAngle)),
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