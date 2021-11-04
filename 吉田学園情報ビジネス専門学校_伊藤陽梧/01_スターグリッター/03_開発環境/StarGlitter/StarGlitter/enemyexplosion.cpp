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
#include "collision.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define EXPLOSION_ANIMATION_COUNT (6)	// �����̃A�j���[�V�����̃J�E���g(���̃e�N�X�`���̕�����)
#define EXPLOSION_ANIMATION_PATTERN (1) // �����̃A�j���[�V�����̃p�^�[��(�c�̃e�N�X�`���̕�����)
#define EXPLOSION_ANIMATION_TIME (10) // �����̃A�j���[�V�����̎���
#define EXPLOSION_SIZE_X (100.0f)			// �����̏c�̒���
#define EXPLOSION_SIZE_Y (100.0f)			// �����̉��̒���

#define ENEMY_DAMAGE (5)

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
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
CEnemyexplosion* CEnemyexplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, EXPLOSIONTYPE ExplosionType, EXPLOSIONTEXTURE ExplosionTexture, OBJTYPE objType)
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
		pEnemyexplosion->SetExplosion(pos, size, ExplosionType, ExplosionTexture, objType);

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
	m_size = GetSize();

	// CScene2D�̍X�V����
	CScene2D::Update();

	// �T�C�Y�̉��Z
	m_size.x++;
	m_size.y++;

	// �G�ɓ��������Ƃ�
	Hit();

	// ���W�ƃT�C�Y��n��
	SetPosition(m_pos);
	SetSize(m_size);
	
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
// �G�̔����N���X�̓��������Ƃ��̏���
//=============================================================================
void CEnemyexplosion::Hit(void)
{
	// �G�̃V�[�����󂯎��
	CScene *pScene = CScene::GetSceneTop(CScene::OBJTYPE_ENEMY);
	do
	{
		if (pScene != NULL)
		{
			// �I�u�W�F�^�C�v�̎󂯎��
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_ENEMY)
			{
				switch (m_ExplosionType)
				{
				case EXPLOSIONTYPE_PLAYER:
					// �����蔻��
					if (CCollision::PRectangleCollision(m_pos, m_size, pScene) == true)
					{
						// �G�̃_���[�W
						((CEnemy*)pScene)->EnemyDamage(ENEMY_DAMAGE, CEnemy::DAMAGE_TYPE_EXPLOSION, CBullet::BULLET_TYPE_1P);
					}
					break;

				case EXPLOSIONTYPE_PLAYER2:
					// �����蔻��
					if (CCollision::PRectangleCollision(m_pos, m_size, pScene) == true)
					{
						// �G�̃_���[�W
						((CEnemy*)pScene)->EnemyDamage(ENEMY_DAMAGE, CEnemy::DAMAGE_TYPE_EXPLOSION, CBullet::BULLET_TYPE_2P);
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
// �G�̔����N���X�̔����̃^�C�v��n������
//=============================================================================
CEnemyexplosion::EXPLOSIONTYPE CEnemyexplosion::GetExplosionType(void)
{
	return m_ExplosionType;
}

