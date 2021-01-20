//=============================================================================
//
// �e�̏��� [bullet.cpp]
// Author : �ɓ��z��
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "bullet.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "explosion.h"
#include "enemy.h"
#include "life.h"
#include "effect.h"
#include "bossattack.h"
#include "collision.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define EXPLOSION_SIZE_X (75.0f)			// �����̏c�̒���
#define EXPLOSION_SIZE_Y (75.0f)			// �����̉��̒���

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CBullet::m_apTexture[MAX_BULLET_TEXTURE] = {};

//=============================================================================
// �o���b�g�N���X�̃R���X�g���N�^
//=============================================================================
CBullet::CBullet() :CScene2D(OBJTYPE_BULLET)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_nGetLife = 0;
	m_nDamage = 0;
	m_BulletType = BULLET_TYPE_NONE;
}

//=============================================================================
// �o���b�g�N���X�̃f�X�g���N�^
//=============================================================================
CBullet::~CBullet()
{

}

//=============================================================================
// �o���b�g�N���X�̃e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CBullet::Load(void)
{
	// �C���X�^���X�����������̂��󂯎��
	CRenderer *pRenderer = CManager::GetRenderer();

	// �f�o�C�X���󂯎��
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BULLET, &m_apTexture[CHARGEBULLET_TYPE_NONE]);				// �Ȃ�
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BULLET, &m_apTexture[CHARGEBULLET_TYPE_NOMAL]);				// ���ʂ̒e
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BULLETCHARGE, &m_apTexture[CHARGEBULLET_TYPE_CHARGE]);		// �`���[�W�����e
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BULLETLASER, &m_apTexture[CHARGEBULLET_TYPE_LASER]);			// ���[�U�[�e
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BULLETBOSSLASER, &m_apTexture[CHARGEBULLET_TYPE_BOSSLASER]); // �{�X�̃��[�U�[�e

	return S_OK;
}

//=============================================================================
// �o���b�g�N���X�̃e�N�X�`���̔j��
//=============================================================================
void CBullet::Unload(void)
{
	for (int nCount = 0; nCount < MAX_BULLET_TEXTURE; nCount++)
	{
		// �e�N�X�`���̔j��
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
// �o���b�g�N���X�̃C���X�^���X����
//=============================================================================
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nLife, int nDamage, BULLETTYPE BulletType, CHARGEBULLETTYPE ChargeBulletType, OBJTYPE objType)
{
	// pBullet�̃|�C���^
	CBullet *pBullet = NULL;

	// �������̊m��
	pBullet = new CBullet;

	// pBullet��NULL����Ȃ��Ƃ�
	if (pBullet != NULL)
	{
		// �e�̃Z�b�g
		pBullet->SetBullet(pos, move, size, nLife, nDamage, BulletType, ChargeBulletType, objType);

		// ����������
		pBullet->Init();
	}

	// pBullet��Ԃ�
	return pBullet;
}

//=============================================================================
// �o���b�g�N���X�̏���������
//=============================================================================
HRESULT CBullet::Init()
{
	// CScene2D�̏���������
	CScene2D::Init();

	// �e�N�X�`���̐ݒ�
	BindTexture(m_apTexture[m_ChargeBulletType]);

	switch (m_BulletType)
	{
		// PLAYER1�̒e
	case BULLET_TYPE_1P:
		// ���ʂ̒e
		if (m_ChargeBulletType == CHARGEBULLET_TYPE_NOMAL)
		{
			// �F�̃Z�b�g
			SetColor(255, 0, 0, 255);
		}
		// �`���[�W�����e
		if (m_ChargeBulletType == CHARGEBULLET_TYPE_CHARGE)
		{
			// �A�j���[�V�����̃Z�b�g
			SetAnimation(2, 1, 4);
		}
		break;

		// PLAYER2�̒e
	case BULLET_TYPE_2P:
		// ���ʂ̒e
		if (m_ChargeBulletType == CHARGEBULLET_TYPE_NOMAL)
		{
			// �F�̃Z�b�g
			SetColor(0, 0, 255, 255);
		}
		// �`���[�W�����e
		if (m_ChargeBulletType == CHARGEBULLET_TYPE_LASER)
		{
			// �A�j���[�V�����̃Z�b�g
			SetAnimation(2, 1, 4);
		}
		break;

		// �{�X�̒e
	case BULLET_TYPE_BOSS:
		// ���ʂ̒e
		if (m_ChargeBulletType == CHARGEBULLET_TYPE_NOMAL)
		{
			// �F�̃Z�b�g
			SetColor(255, 0, 0, 255);
		}
		// �{�X�̃��[�U�[�e
		if (m_ChargeBulletType == CHARGEBULLET_TYPE_BOSSLASER)
		{
			// �A�j���[�V�����̃Z�b�g
			SetAnimation(2, 1, 4);
		}
		break;

	default:
		break;
	}

	return S_OK;   
}

//=============================================================================
// �o���b�g�N���X�̏I������
//=============================================================================
void CBullet::Uninit(void)
{
	// CScene2D�̏I������
	CScene2D::Uninit();
}

//=============================================================================
// �o���b�g�N���X�̍X�V����
//=============================================================================
void CBullet::Update(void)
{
	// CScene2D�̍X�V����
	CScene2D::Update();

	// �e�𓮂�������
	Move();

	switch (m_BulletType)
	{
		// PLAYER1�̒e
	case BULLET_TYPE_1P:
		if (m_ChargeBulletType == CHARGEBULLET_TYPE_NOMAL)
		{
			CEffect::Create(m_pos, m_size + D3DXVECTOR3(5.0f, 5.0f, 0.0f) ,
				10, 255, 100, 100, 255, CEffect::EFFECTTYPE_BULLET, OBJTYPE_EFFECT);
		}

		// �e�̏���
		BulletNomal(BULLET_TYPE_1P);
		// �`���[�W�e�̏���
		BulletCharge(BULLET_TYPE_1P);
		// ���[�U�[�e�̏���
		BulletLaser(CPlayer::PLAYER_1P, BULLET_TYPE_1P);

		break;

		// PLAYER2�̒e
	case BULLET_TYPE_2P:
		if (m_ChargeBulletType == CHARGEBULLET_TYPE_NOMAL)
		{
			CEffect::Create(m_pos, m_size + D3DXVECTOR3(5.0f, 5.0f, 0.0f),
				10, 100, 255, 255, 255, CEffect::EFFECTTYPE_BULLET, OBJTYPE_EFFECT);
		}

		// �e�̏���
		BulletNomal(BULLET_TYPE_2P);
		// �`���[�W�e�̏���
		BulletCharge(BULLET_TYPE_2P);
		// ���[�U�[�e�̏���
		BulletLaser(CPlayer::PLAYER_2P, BULLET_TYPE_2P);
		break;

		// �{�X�̒e
	case BULLET_TYPE_BOSS:
		// �{�X�̃��[�U�[�e�̏���
		BulletBossLaser();
		break;

	default:
		break;
	}

	// ���W�ƃT�C�Y�A�̗͂�n��
	SetPosition(m_pos);
	SetSize(m_size);
}

//=============================================================================
// �o���b�g�N���X�̕`�揈��
//=============================================================================
void CBullet::Draw(void)
{
	// CScene2D�̕`�揈��
	CScene2D::Draw();
}

//=============================================================================
// �o���b�g�N���X�̒e�𓮂�������
//=============================================================================
void CBullet::Move(void)
{
	// ���W�Ƒ̗͂̎󂯎��
	m_pos = GetPosition();

	// �ړ��ʂ̉��Z
	m_pos += m_move;
	m_nLife--;

	// �̗͂��Ȃ��Ȃ����Ƃ�
	if (m_nLife <= 0)
	{
		Uninit();
		return;
	}

	// ��ʊO�ɏo����
	if (m_pos.y + m_size.y <= 0.0f)
	{
		Uninit();
		return;
	}
}

//=============================================================================
// �o���b�g�N���X�̒e�̏���
// BulletType�F�N���������e�Ȃ̂�
//=============================================================================
void CBullet::BulletNomal(BULLETTYPE BulletType)
{
	// �G�̃V�[���̎󂯎��
	CScene *pScene = CScene::GetSceneTop(CScene::OBJTYPE_ENEMY);
	do
	{
		if (pScene != NULL)
		{
			// �I�u�W�F�^�C�v�̎󂯎��
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_ENEMY)
			{
				// �`���[�W�e�̃^�C�v�����ʂ̒e�̎�
				if (m_ChargeBulletType == CHARGEBULLET_TYPE_NOMAL)
				{
					// �����蔻��
					if (CCollision::PRectangleCollision(m_pos, m_size, pScene) == true)
					{
						// �G�̃_���[�W
						((CEnemy*)pScene)->EnemyDamage(m_nDamage, CEnemy::DAMAGE_TYPE_BULLET, BulletType);

						// �����̐���
						CExplosion::Create(m_pos, D3DXVECTOR3(EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y, 0.0f),
							CExplosion::EXPLOSIONTYPE_NOMAL, CScene::OBJTYPE_EXPLOSION);

						// �I������
						Uninit();
						return;
					}
				}
			}
			pScene = pScene->GetSceneNext();
		}
	} while (pScene != NULL);
}

//=============================================================================
// �o���b�g�N���X�̃`���[�W�e�̏���
// BulletType�F�N���������e�Ȃ̂�
//=============================================================================
void CBullet::BulletCharge(BULLETTYPE BulletType)
{
	// �G�̃V�[���̎󂯎��
	CScene *pScene = CScene::GetSceneTop(CScene::OBJTYPE_ENEMY);
	do
	{
		if (pScene != NULL)
		{
			// �I�u�W�F�^�C�v�̎󂯎��
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_ENEMY)
			{
				// �`���[�W�e�̃^�C�v���`���[�W�����e�̎�
				if (m_ChargeBulletType == CHARGEBULLET_TYPE_CHARGE)
				{
					// �����蔻��
					if (CCollision::PRectangleCollision(m_pos, m_size, pScene) == true)
					{
						// �G�̃_���[�W
						((CEnemy*)pScene)->EnemyDamage(m_nDamage, CEnemy::DAMAGE_TYPE_BULLET, BulletType);

						// �����̐���
						CExplosion::Create(m_pos, D3DXVECTOR3(EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y, 0.0f),
							CExplosion::EXPLOSIONTYPE_NOMAL, CScene::OBJTYPE_EXPLOSION);
					}
				}
			}
			pScene = pScene->GetSceneNext();
		}
	} while (pScene != NULL);
}

//=============================================================================
// �o���b�g�N���X�̃��[�U�[�e�̏���
// PlayerNum�F�N���������e�Ȃ̂�
//=============================================================================
void CBullet::BulletLaser(CPlayer::PLAYERNUM PlayerNum, BULLETTYPE BulletType)
{
	// �`���[�W�e�̃^�C�v�����[�U�[�e�̎�
	if (m_ChargeBulletType == CHARGEBULLET_TYPE_LASER)
	{
		// PLAYER�̃V�[���̎󂯎��
		CScene *pScene = CScene::GetSceneTop(CScene::OBJTYPE_PLAYER);
		do
		{
			if (pScene != NULL)
			{
				// �I�u�W�F�^�C�v�̎󂯎��
				OBJTYPE objType = pScene->GetObjType();
				if (objType == OBJTYPE_PLAYER)
				{
					if (((CPlayer*)pScene)->GetPlayerNum() == PlayerNum)
					{
						// ���W�̎󂯎��Ƒ��
						m_pos = ((CScene2D*)pScene)->GetPosition();

						// LASERBULLET_SIZE_Y���c�̍��W��������
						m_pos.y = m_pos.y - (LASERBULLET_SIZE_Y / 2);
					}
				}
				pScene = pScene->GetSceneNext();
			}
		} while (pScene != NULL);

		// �G�̃V�[���̎󂯎��
		pScene = CScene::GetSceneTop(CScene::OBJTYPE_ENEMY);
		do
		{
			if (pScene != NULL)
			{
				// �I�u�W�F�^�C�v�̎󂯎��
				OBJTYPE objType = pScene->GetObjType();
				if (objType == OBJTYPE_ENEMY)
				{
					// �`���[�W�e�̃^�C�v���`���[�W�����e�̎�
					if (m_ChargeBulletType == CHARGEBULLET_TYPE_LASER)
					{
						// �����蔻��
						if (CCollision::PRectangleCollision(m_pos, m_size, pScene) == true)
						{
							// �G�̃_���[�W
							((CEnemy*)pScene)->EnemyDamage(m_nDamage, CEnemy::DAMAGE_TYPE_BULLET, BulletType);

							// �����̐���
							CExplosion::Create(m_pos, D3DXVECTOR3(EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y, 0.0f),
								CExplosion::EXPLOSIONTYPE_NOMAL, CScene::OBJTYPE_EXPLOSION);
						}
					}
				}
				pScene = pScene->GetSceneNext();
			}
		} while (pScene != NULL);
	}
}

//=============================================================================
// �o���b�g�N���X�̃{�X�̃��[�U�[�e�̏���
//=============================================================================
void CBullet::BulletBossLaser(void)
{
	if (m_ChargeBulletType == CHARGEBULLET_TYPE_NOMAL)
	{
		// �G�t�F�N�g�̐���
		CEffect::Create(m_pos, m_size + D3DXVECTOR3(5.0f, 5.0f, 0.0f),
			10, 100, 255, 255, 255, CEffect::EFFECTTYPE_BULLET, OBJTYPE_EFFECT);

		// ��ʊO�ɏo����
		if (m_pos.y + m_size.y <= 0.0f || m_pos.x - m_size.x <= SCREEN_CENTER_X)
		{
			// �I������
			Uninit();
			return;
		}
	}

	// ���W�Ƒ̗͂̎󂯎��
	m_pos = GetPosition();

	// �ړ��ʂ̉��Z
	m_pos += m_move;
	m_nLife--;

	// �̗͂��Ȃ��Ȃ����Ƃ�
	if (m_nLife <= 0)
	{
		Uninit();
		return;
	}
}

//=============================================================================
// �o���b�g�N���X�̒e�̃^�C�v��n������
//=============================================================================
CBullet::BULLETTYPE CBullet::GetBulletType(void)
{
	return m_BulletType;
}

//=============================================================================
// �o���b�g�N���X�̃`���[�W�e�̃^�C�v��n������
//=============================================================================
CBullet::CHARGEBULLETTYPE CBullet::GetChargeBulletType(void)
{
	return m_ChargeBulletType;
}


