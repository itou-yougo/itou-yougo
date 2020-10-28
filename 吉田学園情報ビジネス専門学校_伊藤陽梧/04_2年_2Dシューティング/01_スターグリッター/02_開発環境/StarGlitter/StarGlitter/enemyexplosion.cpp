//=============================================================================
//
// �G�̔����̏��� [enemyexplosion.h]
// Author : �ɓ��z��
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "enemyexplosion.h"
#include "renderer.h"
#include "manager.h"
#include "enemy.h"
#include "sound.h"
#include "bullet.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define EXPLOSION_ANIMATION_COUNT (6)	// �����̃A�j���[�V�����̃J�E���g(���̃e�N�X�`���̕�����)
#define EXPLOSION_ANIMATION_PATTERN (1) // �����̃A�j���[�V�����̃p�^�[��(�c�̃e�N�X�`���̕�����)
#define EXPLOSION_ANIMATION_TIME (10) // �����̃A�j���[�V�����̎���
#define EXPLOSION_SIZE_X (100.0f)			// �����̏c�̒���
#define EXPLOSION_SIZE_Y (100.0f)			// �����̉��̒���

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CEnemyexplosion::m_apTexture[MAX_ENEMYEXPLOSION_TEXTURE] = {};

//=============================================================================
// �G�̔����N���X�̃R���X�g���N�^
//=============================================================================
CEnemyexplosion::CEnemyexplosion() :CScene2D(OBJTYPE_ENEMYEXPLOSION)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Getpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fSizeX = 0.0f;
	m_fSizeY = 0.0f;
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	m_nTimeAnim = EXPLOSION_ANIMATION_TIME;
	m_ExplosionType = EXPLOSIONTYPE_NONE;
	m_ExplosionTexture = EXPLOSIONTEXTURE_1;
}

//=============================================================================
// �G�̔����N���X�̃f�X�g���N�^
//=============================================================================
CEnemyexplosion::~CEnemyexplosion()
{

}

//=============================================================================
// �G�̔����N���X�̃e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CEnemyexplosion::Load(void)
{
	// �C���X�^���X�����������̂��󂯎��
	CRenderer *pRenderer = CManager::GetRenderer();

	// �f�o�C�X���󂯎��
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_ENEMYEXPLOSION1, &m_apTexture[EXPLOSIONTEXTURE_1]); // �e�ɓ������ē|���ꂽ�Ƃ��̃e�N�X�`��
	D3DXCreateTextureFromFile(pDevice, TEXTURE_ENEMYEXPLOSION2, &m_apTexture[EXPLOSIONTEXTURE_2]); // �����ɓ������ē|���ꂽ�Ƃ��̃e�N�X�`��

	return S_OK;
}

//=============================================================================
// �G�̔����N���X�̃e�N�X�`���̔j��
//=============================================================================
void CEnemyexplosion::Unload(void)
{
	for (int nCount = 0; nCount < MAX_ENEMYEXPLOSION_TEXTURE; nCount++)
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
// �G�̔����N���X�̃C���X�^���X����
//=============================================================================
CEnemyexplosion* CEnemyexplosion::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, EXPLOSIONTYPE ExplosionType, EXPLOSIONTEXTURE ExplosionTexture, OBJTYPE objType)
{
	// CEnemyexplosion�̃|�C���^
	CEnemyexplosion *pEnemyexplosion = NULL;

	// �������̊m��
	pEnemyexplosion = new CEnemyexplosion;

	CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_EXPLOSION_SE);

	// pEnemyexplosion��NULL����Ȃ��Ƃ�
	if (pEnemyexplosion != NULL)
	{
		// �G�̔����̃Z�b�g
		pEnemyexplosion->SetExplosion(pos, fSizeX, fSizeY, ExplosionType, ExplosionTexture, objType);

		// ����������
		pEnemyexplosion->Init();
	}

	// pEnemyexplosion��Ԃ�
	return pEnemyexplosion;
}

//=============================================================================
// �G�̔����N���X�̏���������
//=============================================================================
HRESULT CEnemyexplosion::Init()
{
	// CScene2D�̏���������
	CScene2D::Init();

	// �e�N�X�`���̐ݒ�
	BindTexture(m_apTexture[m_ExplosionTexture]);

	// �A�j���[�V�����̃Z�b�g
	CScene2D::SetAnimation(EXPLOSION_ANIMATION_COUNT, EXPLOSION_ANIMATION_PATTERN, EXPLOSION_ANIMATION_TIME);

	return S_OK;
}

//=============================================================================
// �G�̔����N���X�̏I������
//=============================================================================
void CEnemyexplosion::Uninit(void)
{
	// CScene2D�̏I������
	CScene2D::Uninit();
}

//=============================================================================
// �G�̔����N���X�̍X�V����
//=============================================================================
void CEnemyexplosion::Update(void)
{
	// �T�C�Y�̎󂯎��
	m_fSizeX = GetSizeX();
	m_fSizeY = GetSizeY();

	// CScene2D�̍X�V����
	CScene2D::Update();

	// �T�C�Y�̉��Z
	m_fSizeX++;
	m_fSizeY++;

	switch (m_ExplosionType)
	{
	case EXPLOSIONTYPE_PLAYER:
		for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
		{
			// �G�̃V�[���̎󂯎��
			CScene *pScene = GetScene(OBJTYPE_ENEMY, nCntScene);
			if (pScene != NULL)
			{
				// �I�u�W�F�^�C�v�̎󂯎��
				OBJTYPE objType = pScene->GetObjType();
				if (objType == OBJTYPE_ENEMY)
				{
					// ���W�̎󂯎��
					m_Getpos = ((CScene2D*)pScene)->GetPosition();

					// �����蔻��
					if (m_pos.x - (m_fSizeX / 2) <= m_Getpos.x + (ENEMY_SIZE_X / 2) &&
						m_pos.x + (m_fSizeX / 2) >= m_Getpos.x - (ENEMY_SIZE_X / 2) &&
						m_pos.y - (m_fSizeY / 2) <= m_Getpos.y + (ENEMY_SIZE_Y / 2) &&
						m_pos.y + (m_fSizeY / 2) >= m_Getpos.y - (ENEMY_SIZE_Y / 2))
					{
						// �G�̃_���[�W
						((CEnemy*)pScene)->EnemyDamage(5, CEnemy::DAMAGE_TYPE_EXPLOSION, CBullet::BULLET_TYPE_PLAYER);
						break;
					}
				}
			}
		}
		break;

	case EXPLOSIONTYPE_PLAYER2:
		for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
		{
			// �G�̃V�[���̎󂯎��
			CScene *pScene = GetScene(OBJTYPE_ENEMY, nCntScene);
			if (pScene != NULL)
			{
				// �I�u�W�F�^�C�v�̎󂯎��
				OBJTYPE objType = pScene->GetObjType();
				if (objType == OBJTYPE_ENEMY)
				{
					// ���W�̎󂯎��
					m_Getpos = ((CScene2D*)pScene)->GetPosition();

					// �����蔻��
					if (m_pos.x - (m_fSizeX / 2) <= m_Getpos.x + (PLAYER_SIZE_X / 2) &&
						m_pos.x + (m_fSizeX / 2) >= m_Getpos.x - (PLAYER_SIZE_X / 2) &&
						m_pos.y - (m_fSizeY / 2) <= m_Getpos.y + (PLAYER_SIZE_Y / 2) &&
						m_pos.y + (m_fSizeY / 2) >= m_Getpos.y - (PLAYER_SIZE_Y / 2))
					{
						// �G�̃_���[�W
						((CEnemy*)pScene)->EnemyDamage(5, CEnemy::DAMAGE_TYPE_EXPLOSION, CBullet::BULLET_TYPE_PLAYER2);
						break;
					}
				}
			}
		}
		break;

	default:
		break;
	}


	// ���W�ƃT�C�Y��n��
	SetPosition(m_pos);
	SetSize(m_fSizeX, m_fSizeY);
	
	// �A�j���[�V�������I�������I������
	if (m_nTimeAnim == EXPLOSION_ANIMATION_TIME)
	{
		m_nCounterAnim++;

		if (m_nCounterAnim % EXPLOSION_ANIMATION_COUNT == 0)
		{
			Uninit();
		}
		m_nTimeAnim = 0;
	}
	m_nTimeAnim++;
}

//=============================================================================
// �G�̔����N���X�̕`�揈��
//=============================================================================
void CEnemyexplosion::Draw(void)
{
	// CScene2D�̕`�揈��
	CScene2D::Draw();
}

//=============================================================================
// �G�̔����N���X�̔����̃^�C�v��n������
//=============================================================================
CEnemyexplosion::EXPLOSIONTYPE CEnemyexplosion::GetExplosionType(void)
{
	return m_ExplosionType;
}

