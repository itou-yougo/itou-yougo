//=============================================================================
//
// �{�X�A�^�b�N�̏��� [bossattack.cpp]
// Author : �ɓ��z��
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "bossattack.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "explosion.h"
#include "enemy.h"
#include "life.h"
#include "effect.h"
#include "bullet.h"
#include "collision.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define EXPLOSION_SIZE_X (100.0f)			// �����̏c�̒���
#define EXPLOSION_SIZE_Y (100.0f)			// �����̉��̒���

#define BOSSEXPLOSION_SIZE_X (200.0f)			// �{�X�̔����̏c�̒���
#define BOSSEXPLOSION_SIZE_Y (200.0f)			// �{�X�̔����̉��̒���

#define BOSSCREATEALPHA (100) 
#define BOSSMOVEALPHA (255)
#define BOSS_SIZE_EXTEND (5.0f)
#define BOSS_SPEED (5.0f)

#define BEAM_BOSS_STOPCOUNT (150)
#define BEAM_BOSS_MOVECOUNT (130)
#define BEAM_BOSS_SHOTCOUNT (50)

#define BEAM_POS (D3DXVECTOR3(m_pos.x, m_pos.y + (LASERBULLET_SIZE_Y / 2) + 50.0f, 0.0f))
#define BEAM_LIFE (80)
#define BEAM_DAMAGE (1)

#define BULLET_SPEED (-10.0f)
#define BULLET_LIFE (200)
#define BULLET_DAMAGE (1)
#define BULLET_BOSS_SHOTCOUNT (100)

#define CHARGEHIT_INCREDIBLE_TIME (40)
#define CHARGEHIT_DAMAGE (3)

#define BEAMHIT_INCREDIBLE_TIME (80)
#define BEAMHIT_DAMAGE (3)

#define BULLETHIT_DAMAGE (1)

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CBossattck::m_apTexture[MAX_BOSS_TEXTURE] = {};

//=============================================================================
// �{�X�A�^�b�N�N���X�̃R���X�g���N�^
//=============================================================================
CBossattck::CBossattck() :CScene2D(OBJTYPE_BOSSATTACK)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, BOSS_SIZE_Y, 0.0f);
	m_nCount = 0;
	m_nInvincibleTime = 0;
	m_nCountBullet = 0;
	m_nCountStop = 0;
	m_nLife = 0;
	m_bStop = false;
	m_Player = BOSSATTCK_PLAYER_NONE;
	m_BossAttack = BOSSATTACK_BEAM;
}

//=============================================================================
// �{�X�A�^�b�N�N���X�̃f�X�g���N�^
//=============================================================================
CBossattck::~CBossattck()
{

}

//=============================================================================
// �{�X�A�^�b�N�N���X�̃e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CBossattck::Load(void)
{
	// �C���X�^���X�����������̂��󂯎��
	CRenderer *pRenderer = CManager::GetRenderer();

	// �f�o�C�X���󂯎��
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BOSSMAHOU, &m_apTexture[BOSSATTACK_BULLET]); // �r�[�������{�X�A�^�b�N
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BOSSKABOTYA, &m_apTexture[BOSSATTACK_BEAM]);	// ���܂����{�X�A�^�b�N

	return S_OK;
}

//=============================================================================
// �{�X�A�^�b�N�N���X�̃e�N�X�`���̔j��
//=============================================================================
void CBossattck::Unload(void)
{
	for (int nCount = 0; nCount < BOSSATTACK_MAX; nCount++)
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
// �{�X�A�^�b�N�N���X�̃C���X�^���X����
//=============================================================================
CBossattck* CBossattck::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, PLAYER Player, BOSSATTACK BossAttack, OBJTYPE objType)
{
	// CBossattck�̃|�C���^
	CBossattck *pBossattck = NULL;

	// �������̊m��
	pBossattck = new CBossattck;

	// pBossattck��NULL����Ȃ��Ƃ�
	if (pBossattck != NULL)
	{
		pBossattck->SetBossAttack(pos, move, nLife, Player, BossAttack, objType);

		// ����������
		pBossattck->Init();
	}

	// pBossattck��Ԃ�
 	return pBossattck;
}

//=============================================================================
// �{�X�A�^�b�N�N���X�̏���������
//=============================================================================
HRESULT CBossattck::Init()
{
	// CScene2D�̏���������
	CScene2D::Init();

	// �e�N�X�`���̐ݒ�
	BindTexture(m_apTexture[m_BossAttack]);

	srand((unsigned)time(NULL));

	return S_OK;
}

//=============================================================================
// �{�X�A�^�b�N�N���X�̏I������
//=============================================================================
void CBossattck::Uninit(void)
{
	// CScene2D�̏I������
	CScene2D::Uninit();
}

//=============================================================================
// �{�X�A�^�b�N�N���X�̍X�V����
//=============================================================================
void CBossattck::Update(void)
{
	// CScene2D�̍X�V����
	CScene2D::Update();

	// ���W�Ƒ̗͂̎󂯎��
	m_pos = GetPosition();

	//�@���̃T�C�Y��BOSS_SIZE_X��菬����������
	if (m_size.x < BOSS_SIZE_X)
	{
		SetColor(255, 255, 255, BOSSCREATEALPHA);
		m_size.x += BOSS_SIZE_EXTEND;
	}

	//�@���̃T�C�Y��BOSS_SIZE_X���傫���Ȃ�����
	if (m_size.x >= BOSS_SIZE_X)
	{
		m_size.x = BOSS_SIZE_X;
		SetColor(255, 255, 255, BOSSMOVEALPHA);
		
		// ���C�t��0���傫��������
		if (m_nLife > 0)
		{
			switch (m_BossAttack)
			{
				// �r�[�������{�X�A�^�b�N
			case BOSSATTACK_BEAM:
				BossBeam();
				break;

				// ���܂����{�X�A�^�b�N
			case BOSSATTACK_BULLET:
				BossBullet();
				break;

			default:
				break;
			}
		}
	}

	// ������Ƃ��̏���
	Hit();

	// ���C�t��0�ȉ��̎�
	if (m_nLife <= 0)
	{
		// �ړ��ʂ̉��Z
		m_pos.y += BOSS_SPEED;

		// �J�E���g�̉��Z
		m_nCount++;

		// �J�E���g��10�̎�
		if (m_nCount == 10)
		{
			CExplosion::Create(m_pos + D3DXVECTOR3((float)(rand() % (int)BOSS_SIZE_X) - BOSS_SIZE_X / 2.0f, ((float)(rand() % (int)BOSS_SIZE_Y) - BOSS_SIZE_Y / 2.0f), 0.0f),
				D3DXVECTOR3(BOSSEXPLOSION_SIZE_X, BOSSEXPLOSION_SIZE_Y, 0.0f), CExplosion::EXPLOSIONTYPE_BOSS, CScene::OBJTYPE_EXPLOSION);
			m_nCount = 0;
		}
	}

	// ���G���Ԃ̃J�E���g�̌��Z
	m_nInvincibleTime--;
	if (m_nInvincibleTime < 0)
	{
		m_nInvincibleTime = 0;
	}

	// ���W�ƃT�C�Y�A�̗͂�n��
	SetPosition(m_pos);
	SetSize(m_size);

	// ���ɍs������Uninit����
	if (m_pos.y - (m_size.y / 2) > SCREEN_HEIGHT)
	{
		Uninit();
	}
}

//=============================================================================
// �{�X�A�^�b�N�N���X�̕`�揈��
//=============================================================================
void CBossattck::Draw(void)
{
	// CScene2D�̕`�揈��
	CScene2D::Draw();
}

//=============================================================================
// �{�X�A�^�b�N�N���X�̃_���[�W���󂯂����̏���
//=============================================================================
void CBossattck::BossAttackDamage(int nDamage)
{
	m_nLife -= nDamage;
}

//=============================================================================
// �{�X�A�^�b�N�N���X�̃r�[�������{�X�̏���
//=============================================================================
void CBossattck::BossBeam(void)
{
	switch (m_Player)
	{
		// �v���C���[1�̃{�X�A�^�b�N
	case BOSSATTCK_PLAYER1:
		BossAttackBeam();

		// ���̈ړ��̐���
		if (m_pos.x - (m_size.x / 2) <= PLAYER2_MOVABLE_RANGE_S ||
			m_pos.x + (m_size.x / 2) >= PLAYER2_MOVABLE_RANGE_L)
		{
			// �ړ��̔��]
			m_move *= -1.0f;
		}
		break;

		// �v���C���[2�̃{�X�A�^�b�N
	case BOSSATTCK_PLAYER2:
		BossAttackBeam();

		// ���̈ړ��̐���
		if (m_pos.x - (m_size.x / 2) <= PLAYER_MOVABLE_RANGE_S ||
			m_pos.x + (m_size.x / 2) >= PLAYER_MOVABLE_RANGE_L)
		{
			// �ړ��̔��]
			m_move *= -1.0f;
		}
		break;

	default:
		break;
	}
}

//=============================================================================
// �{�X�A�^�b�N�N���X�̒e�����{�X�̏���
//=============================================================================
void CBossattck::BossBullet(void)
{
	CScene *pScene = NULL;
	switch (m_Player)
	{
		// �v���C���[1�̃{�X�A�^�b�N
	case BOSSATTCK_PLAYER1:
		// �{�X�A�^�b�N�̍U��
		BossAttackBullet(CPlayer::PLAYER_2P);

		// ���̈ړ��̐���
		if (m_pos.x - (m_size.x / 2) <= PLAYER2_MOVABLE_RANGE_S ||
			m_pos.x + (m_size.x / 2) >= PLAYER2_MOVABLE_RANGE_L)
		{
			// ���̈ړ��̔��]
			m_move *= -1.0f;
		}
		break;

		// �v���C���[2�̃{�X�A�^�b�N
	case BOSSATTCK_PLAYER2:
		// �{�X�A�^�b�N�̍U��
		BossAttackBullet(CPlayer::PLAYER_1P);

		// ���̈ړ��̐���
		if (m_pos.x - (m_size.x / 2) <= PLAYER_MOVABLE_RANGE_S ||
			m_pos.x + (m_size.x / 2) >= PLAYER_MOVABLE_RANGE_L)
		{
			// ���̈ړ��̔��]
			m_move *= -1.0f;
		}
		break;

	default:
		break;
	}
}

//=============================================================================
// �{�X�A�^�b�N�N���X�̃r�[����������
//=============================================================================
void CBossattck::BossAttackBeam(void)
{
	// �~�܂�Ƃ��̃J�E���g�̉��Z
	m_nCountStop++;

	// �~�܂��ĂȂ��Ƃ�
	if (m_bStop == false)
	{
		m_pos += m_move;

		// �e�����J�E���g��100�ȏ�ɂȂ�����
		if (m_nCountStop >= BEAM_BOSS_STOPCOUNT)
		{
			m_bStop = true;
			m_nCountStop = 0;
		}
	}
	// �~�܂�Ƃ�
	else if (m_bStop == true)
	{
		// �e�����J�E���g�̉��Z
		m_nCountBullet++;

		// �e�����J�E���g��50�ȏ�ɂȂ�����
		if (m_nCountBullet == BEAM_BOSS_SHOTCOUNT)
		{
			CBullet::Create(BEAM_POS, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(LASERBULLET_SIZE_X, LASERBULLET_SIZE_Y, 0.0f), BEAM_LIFE, BEAM_DAMAGE, CBullet::BULLET_TYPE_BOSS,
				CBullet::CHARGEBULLET_TYPE_BOSSLASER, CScene::OBJTYPE_BULLET);
		}

		// �~�܂�Ƃ��̃J�E���g��90�ȏ�ɂȂ�����
		if (m_nCountStop >= BEAM_BOSS_MOVECOUNT)
		{
			m_bStop = false;
			m_nCountStop = 0;
			m_nCountBullet = 0;
		}
	}
}

//=============================================================================
// �{�X�A�^�b�N�N���X�̒e��������
//=============================================================================
void CBossattck::BossAttackBullet(CPlayer::PLAYERNUM PlayerNum)
{
	m_pos += m_move;

	// �e�����J�E���g�̉��Z
	m_nCountBullet++;

	// �e�����J�E���g��100�ȏ�̎�
	if (m_nCountBullet >= BULLET_BOSS_SHOTCOUNT)
	{
		// �v���C���[�̃V�[���̎󂯎��
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
						// �p�x�̌v�Z
						m_fAngle = atan2f(m_pos.x - ((CScene2D*)pScene)->GetPosition().x, m_pos.y - ((CScene2D*)pScene)->GetPosition().y);

						// �e�̐���
						CBullet::Create(m_pos, D3DXVECTOR3(sinf(m_fAngle) * BULLET_SPEED, cosf(m_fAngle) * BULLET_SPEED, 0.0f),
							D3DXVECTOR3(EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y, 0.0f), BULLET_LIFE, BULLET_DAMAGE,
							CBullet::BULLET_TYPE_BOSS, CBullet::CHARGEBULLET_TYPE_NOMAL, CScene::OBJTYPE_BULLET);

						m_nCountBullet = 0;
					}
				}
				pScene = pScene->GetSceneNext();
			}
		} while (pScene != NULL);
	}
}

//=============================================================================
// �{�X�A�^�b�N�N���X�̓�����Ƃ��̏���
//=============================================================================
void CBossattck::Hit(void)
{
	// ���C�t��0���傫��������
	if (m_nLife > 0)
	{
		switch (m_BossAttack)
		{
			// �r�[�������{�X�A�^�b�N
		case BOSSATTACK_BEAM:
			switch (m_Player)
			{
				// �v���C���[1�̃{�X�A�^�b�N
			case BOSSATTCK_PLAYER1:
				HitDamage();
				break;

				// �v���C���[2�̃{�X�A�^�b�N
			case BOSSATTCK_PLAYER2:
				HitDamage();
				break;

			default:
				break;
			}
			break;

			// ���܂����{�X�A�^�b�N
		case BOSSATTACK_BULLET:
			switch (m_Player)
			{
				// �v���C���[1�̃{�X�A�^�b�N
			case BOSSATTCK_PLAYER1:
				HitDamage();
				break;

				// �v���C���[2�̃{�X�A�^�b�N
			case BOSSATTCK_PLAYER2:
				HitDamage();
				break;

			default:
				break;
			}
			break;

		default:
			break;
		}
	}
}

//=============================================================================
// �{�X�A�^�b�N�N���X�̓�����Ƃ��̃_���[�W�̏���
//=============================================================================
void CBossattck::HitDamage(void)
{
	// �e�̃V�[���̎󂯎��
	CScene *pScene = CScene::GetSceneTop(CScene::OBJTYPE_BULLET);
	do
	{
		if (pScene != NULL)
		{
			// �I�u�W�F�^�C�v�̎󂯎��
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_BULLET)
			{
				// �e�̃^�C�v���{�X�̒e�̎�
				if (((CBullet*)pScene)->GetBulletType() != CBullet::BULLET_TYPE_BOSS)
				{
					switch (((CBullet*)pScene)->GetChargeBulletType())
					{
						// ���ʂ̒e
					case CBullet::CHARGEBULLET_TYPE_NOMAL:
						// �����蔻��
						if (CCollision::PRectangleCollision(m_pos, m_size, pScene) == true)
						{
							// �e�̏I������
							((CBullet*)pScene)->Uninit();

							// �{�X�A�^�b�N�̃_���[�W
							BossAttackDamage(BULLETHIT_DAMAGE);

							// �����̐���
							CExplosion::Create(((CScene2D*)pScene)->GetPosition(), D3DXVECTOR3(EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y, 0.0f),
								CExplosion::EXPLOSIONTYPE_NOMAL, CScene::OBJTYPE_EXPLOSION);
							break;
						}
						break;

						// �`���[�W�����e
					case CBullet::CHARGEBULLET_TYPE_CHARGE:
						// ���������Ƃ��̃J�E���g��0�̎�
						if (m_nInvincibleTime == 0)
						{
							// �����蔻��
							if (CCollision::PRectangleCollision(m_pos, m_size, pScene) == true)
							{
								// �{�X�A�^�b�N�̃_���[�W
								BossAttackDamage(CHARGEHIT_DAMAGE);

								// �����̐���
								CExplosion::Create(((CScene2D*)pScene)->GetPosition(), D3DXVECTOR3(EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y, 0.0f),
									CExplosion::EXPLOSIONTYPE_NOMAL, CScene::OBJTYPE_EXPLOSION);

								// �J�E���g�̑��
								m_nInvincibleTime = CHARGEHIT_INCREDIBLE_TIME;
								break;
							}
						}
						break;

						// �`���[�W�����e
					case CBullet::CHARGEBULLET_TYPE_LASER:
						// ���������Ƃ��̃J�E���g��0�̎�
						if (m_nInvincibleTime == 0)
						{
							// �����蔻��
							if (CCollision::PRectangleCollision(m_pos, m_size, pScene) == true)
							{
								// �{�X�A�^�b�N�̃_���[�W
								BossAttackDamage(BEAMHIT_DAMAGE);

								// �����̐���
								CExplosion::Create(((CScene2D*)pScene)->GetPosition(), D3DXVECTOR3(EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y, 0.0f),
									CExplosion::EXPLOSIONTYPE_NOMAL, CScene::OBJTYPE_EXPLOSION);

								// �J�E���g�̑��
								m_nInvincibleTime = BEAMHIT_INCREDIBLE_TIME;
								break;
							}
						}
						break;

					default:
						break;
					}
				}
			}
			pScene = pScene->GetSceneNext();
		}
	} while (pScene != NULL);
}