//=============================================================================
//
// �G�̏��� [enemy.h]
// Author : �ɓ��z��
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "enemy.h"
#include "renderer.h"
#include "manager.h"
#include "bullet.h"
#include "sound.h"
#include "enemyexplosion.h"
#include "ojama.h"
#include "chargeshot.h"
#include "gauge.h"
#include "player.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CEnemy::m_pTexture = NULL;

//=============================================================================
// �G�l�~�[�N���X�̃R���X�g���N�^
//=============================================================================
CEnemy::CEnemy() :CScene2D(OBJTYPE_ENEMY)
{
	m_pGauge = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_nOjamaCount = 0;
	m_DamageType = DAMAGE_TYPE_NONE;
}

//=============================================================================
// �G�l�~�[�N���X�̃f�X�g���N�^
//=============================================================================
CEnemy::~CEnemy()
{

}

//=============================================================================
// �G�l�~�[�N���X�̃e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CEnemy::Load(void)
{
	// �C���X�^���X�����������̂��󂯎��
	CRenderer *pRenderer = CManager::GetRenderer();

	// �f�o�C�X���󂯎��
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_ENEMY1, &m_pTexture);

	return S_OK;
}

//=============================================================================
// �G�l�~�[�N���X�̃e�N�X�`���̔j��
//=============================================================================
void CEnemy::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// �G�l�~�[�N���X�̃C���X�^���X����
//=============================================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nLife, OBJTYPE objType)
{
	// CEnemy�̃|�C���^
	CEnemy *pEnemy = NULL;

	// �������̊m��
	pEnemy = new CEnemy;

	// pEnemy��NULL����Ȃ��Ƃ�
	if (pEnemy != NULL)
	{
		// �G�̐ݒ�
		pEnemy->SetEnemy(pos, move, size, nLife, objType);

		// ����������
		pEnemy->Init();
	}

	// pEnemy��Ԃ�
	return pEnemy;
}

//=============================================================================
// �G�l�~�[�N���X�̏���������
//=============================================================================
HRESULT CEnemy::Init()
{
	//m_pBarrier = CBarrier::Create(m_pos, BARRIER_SIZE_X, BARRIER_SIZE_Y, 1, CBarrier::BARRIER_TYPE_BRUE, OBJTYPE_BARRIER);

	// CScene2D�̏���������
	CScene2D::Init();

	// �e�N�X�`���̐ݒ�
	BindTexture(m_pTexture);

	// �A�j���[�V�����̃Z�b�g
	SetAnimationSelect(3, 5, m_nLife - 1, 5);

	srand((unsigned int)time(NULL));

	return S_OK;
}

//=============================================================================
// �G�l�~�[�N���X�̏I������
//=============================================================================
void CEnemy::Uninit(void)
{
	// CScene2D�̏I������
	CScene2D::Uninit();
}

//=============================================================================
// �G�l�~�[�N���X�̍X�V����
//=============================================================================
void CEnemy::Update(void)
{
	// CScene2D�̍X�V����
	CScene2D::Update();

	// CInput�̃|�C���^�̃C���X�^���X�����̎󂯎��
	CInputKeyboard *pInput = CManager::GetInputKeyboard();

	// ���W�Ƒ̗͂��󂯎��
	m_pos = GetPosition();

	m_pos += m_move;

	// �|���ꂽ�Ƃ��̏���
	Death();

	// ���W�ƃT�C�Y�A�̗͂�n��
	SetPosition(m_pos);
	SetSize(m_size);

	// �ړ��ł���͈͂̐���
	if (m_pos.y > SCREEN_HEIGHT + (ENEMY_SIZE_X / 2))
	{
		Uninit();
		return;
	}
}

//=============================================================================
// �G�l�~�[�N���X�̕`�揈��
//=============================================================================
void CEnemy::Draw(void)
{
	// CScene2D�̕`�揈��
	CScene2D::Draw();
}

//=============================================================================
// �G�l�~�[�N���X�̓|���ꂽ�Ƃ��̏���
//=============================================================================
void CEnemy::Death(void)
{
	// �̗͂�0�ȉ��ɂȂ����Ƃ�
	if (m_nLife <= 0)
	{
		// ������܂���鏈��
		OjamanCreate();

		// �Q�[�W�̍ő�l��L�΂�����
		GaugeUp();

		// �I������
		Uninit();
		return;
	}
}

//=============================================================================
// �G�l�~�[�N���X�̂�����܂���鏈��
//=============================================================================
void CEnemy::OjamanCreate(void)
{
	// �����̃_���[�W�Ŏ��񂾂Ƃ�
	if (m_DamageType == DAMAGE_TYPE_EXPLOSION)
	{
		// �ǂ����̃v���C���[�̍U�������ʂ��ă����_���ł�����܂��o��
		switch (m_BulletType)
		{
			// PLAYER1�̒e
		case CBullet::BULLET_TYPE_1P:
			switch (rand() % 3)
			{
			case 0:
				COjama::Create(m_pos, D3DXVECTOR3(-10.0f, -10.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f),
					0, D3DXVECTOR3(2.0f, 2.0f, 0.0f), COjama::OJAMA_TYPE_THROUGH, COjama::OJAMAPLAYER_1P, OBJTYPE_OJAMA);
				break;

			case 1:
				COjama::Create(m_pos, D3DXVECTOR3(10.0f, -10.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), 0,
					D3DXVECTOR3((float)(rand() % 3) + 2.0f, -2.0f, 0.0f), COjama::OJAMA_TYPE_CURVE, COjama::OJAMAPLAYER_1P, OBJTYPE_OJAMA);
				break;

			case 2:
				COjama::Create(m_pos, D3DXVECTOR3((float)(rand() % 10) - 15.0f, (float)(rand() % 10) - 15.0f, 0.0f),
					D3DXVECTOR3(50.0f, 50.0f, 0.0f), 0, D3DXVECTOR3((float)(rand() % 5) + 5.0f, 5.0f, 0.0f),
					COjama::OJAMA_TYPE_FALL, COjama::OJAMAPLAYER_1P, OBJTYPE_OJAMA);
				break;

			default:
				break;
			}

			// �G�̔������o������
			EnemyExplosionCreate(CEnemyexplosion::EXPLOSIONTEXTURE_2);
			break;

			// PLAYER2�̒e
		case CBullet::BULLET_TYPE_2P:
			switch (rand() % 3)
			{
			case 0:
				COjama::Create(m_pos, D3DXVECTOR3(-10.0f, -10.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), 0,
					D3DXVECTOR3(2.0f, 2.0f, 0.0f), COjama::OJAMA_TYPE_THROUGH, COjama::OJAMAPLAYER_2P, OBJTYPE_OJAMA);
				break;

			case 1:
				COjama::Create(m_pos, D3DXVECTOR3(-10.0f, -10.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), 0,
					D3DXVECTOR3(-(float)(rand() % 3) - 2.0f, -2.0f, 0.0f), COjama::OJAMA_TYPE_CURVE, COjama::OJAMAPLAYER_2P, OBJTYPE_OJAMA);
				break;

			case 2:
				COjama::Create(m_pos, D3DXVECTOR3(-(float)(rand() % 10) + 15.0f, -(float)(rand() % 10) + 15.0f, 0.0f),
					D3DXVECTOR3(50.0f, 50.0f, 0.0f), 0, D3DXVECTOR3(-(float)(rand() % 5) - 5.0f, 5.0f, 0.0f),
					COjama::OJAMA_TYPE_FALL, COjama::OJAMAPLAYER_2P, OBJTYPE_OJAMA);
				break;
			default:
				break;
			}

			// �G�̔������o������
			EnemyExplosionCreate(CEnemyexplosion::EXPLOSIONTEXTURE_2);
			break;

		default:
			break;
		}
	}
	else
	{
		// �G�̔������o������
		EnemyExplosionCreate(CEnemyexplosion::EXPLOSIONTEXTURE_1);
	}
}

//=============================================================================
// �G�l�~�[�N���X�̓G�̔������o������
// ExplosionTexture�F�e�N�X�`���̔ԍ�
//=============================================================================
void CEnemy::EnemyExplosionCreate(CEnemyexplosion::EXPLOSIONTEXTURE ExplosionTexture)
{
	// �ǂ����̃v���C���[�̍U�������ʂ��Ĕ������N����
	switch (m_BulletType)
	{
		// PLAYER1�̒e
	case CBullet::BULLET_TYPE_1P:
		// �G�̔����̐���
		CEnemyexplosion::Create(m_pos, D3DXVECTOR3(100.0f, 100.0f, 0.0f), CEnemyexplosion::EXPLOSIONTYPE_PLAYER,
			ExplosionTexture, OBJTYPE_ENEMYEXPLOSION);
		break;

		// PLAYER2�̒e
	case CBullet::BULLET_TYPE_2P:
		// �G�̔����̐���
		CEnemyexplosion::Create(m_pos, D3DXVECTOR3(100.0f, 100.0f, 0.0f), CEnemyexplosion::EXPLOSIONTYPE_PLAYER2,
			ExplosionTexture, OBJTYPE_ENEMYEXPLOSION);
		break;
	}
}

//=============================================================================
// �G�l�~�[�N���X�̃Q�[�W�̍ő�l��L�΂�����
//=============================================================================
void CEnemy::GaugeUp(void)
{
	// �v���C���[�̃V�[�����󂯎��
	CScene *pScene = CScene::GetSceneTop(CScene::OBJTYPE_PLAYER);
	do
	{
		if (pScene != NULL)
		{
			// �I�u�W�F�N�g�̎󂯎��
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_PLAYER)
			{
				switch (m_BulletType)
				{
					// �v���C���[1�̂��������œ|���ꂽ��
				case CBullet::BULLET_TYPE_1P:
					if (((CPlayer*)pScene)->GetPlayerNum() == CPlayer::PLAYER_1P)
					{
						// PLAYER�̃`���[�W�V���b�g�̃Q�[�W�̍ő�l��L�΂�
						((((CPlayer*)pScene)->GetChargeShot())->GetGauge())->SetExtend(5.0f, 0.0f);
					}
					break;

					// �v���C���[2�̂��������œ|���ꂽ��
				case CBullet::BULLET_TYPE_2P:
					if (((CPlayer*)pScene)->GetPlayerNum() == CPlayer::PLAYER_2P)
					{
						// PLAYER2�̃`���[�W�V���b�g�̃Q�[�W�̍ő�l��L�΂�
						((((CPlayer*)pScene)->GetChargeShot())->GetGauge())->SetExtend(5.0f, 0.0f);
					}
					break;

				default:
					break;
				}
			}
			pScene = pScene->GetSceneNext();
		}
	} while (pScene != NULL);
}

//=============================================================================
// �G�l�~�[�N���X�̃_���[�W�̏���
//=============================================================================
void CEnemy::EnemyDamage(int nDamage, DAMAGETYPE DamageType, CBullet::BULLETTYPE BulletType)
{
	// �_���[�W�ƒe�̃^�C�v���󂯎��
	m_DamageType = DamageType;
	m_BulletType = BulletType;

	// nDamage�����C�t�����炷
	m_nLife = m_nLife - nDamage;

	// �A�j���[�V�����̃Z�b�g
	SetAnimationSelect(3, 5, m_nLife - 1, 5);
}