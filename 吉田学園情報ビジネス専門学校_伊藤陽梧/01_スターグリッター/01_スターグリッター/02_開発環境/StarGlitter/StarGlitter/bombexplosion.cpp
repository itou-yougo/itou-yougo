//=============================================================================
//
// �{���̔����̏��� [bombexplosion.cpp]
// Author : �ɓ��z��
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "bombexplosion.h"
#include "renderer.h"
#include "manager.h"
#include "enemy.h"
#include "sound.h"
#include "bullet.h"
#include "collision.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define BOMBEXPLOSION_ANIMATION_COUNT (10)	// �����̃A�j���[�V�����̃J�E���g(���̃e�N�X�`���̕�����)
#define BOMBEXPLOSION_ANIMATION_PATTERN (2) // �����̃A�j���[�V�����̃p�^�[��(�c�̃e�N�X�`���̕�����)
#define BOMBEXPLOSION_SIZE_X (745.0f)			// �����̏c�̒���
#define BOMBEXPLOSION_SIZE_Y (1080.0f)			// �����̉��̒���

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CBombexplosion::m_pTexture = NULL;

//=============================================================================
// �{���̔����N���X�̃R���X�g���N�^
//=============================================================================
CBombexplosion::CBombexplosion() :CScene2D(OBJTYPE_EXPLOSION)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_BombExplosionType = BOMBEXPLOSION_NONE;
}

//=============================================================================
// �{���̔����N���X�̃f�X�g���N�^
//=============================================================================
CBombexplosion::~CBombexplosion()
{

}

//=============================================================================
// �{���̔����N���X�̃e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CBombexplosion::Load(void)
{
	// �C���X�^���X�����������̂��󂯎��
	CRenderer *pRenderer = CManager::GetRenderer();

	// �f�o�C�X���󂯎��
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BOMBEXPLOSION, &m_pTexture);

	return S_OK;
}

//=============================================================================
// �{���̔����N���X�̃e�N�X�`���̔j��
//=============================================================================
void CBombexplosion::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// �{���̔����N���X�̃C���X�^���X����
//=============================================================================
CBombexplosion* CBombexplosion::Create(D3DXVECTOR3 pos, int nLife, BOMBEXPLOSIONTYPE bombexplosiontype, OBJTYPE objType)
{
	// CBombexplosion�̃|�C���^
	CBombexplosion *pBombExplosion = NULL;

	// �������̊m��
	pBombExplosion = new CBombexplosion;

	// �T�E���h�̊J�n
	CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_EXPLOSION_SE);

	// pBombExplosion��NULL����Ȃ��Ƃ�
	if (pBombExplosion != NULL)
	{
		// �{���̔����̃Z�b�g
		pBombExplosion->SetBombexplosion(pos, nLife, bombexplosiontype, objType);

		// �T�C�Y�̃Z�b�g
		pBombExplosion->SetSize(D3DXVECTOR3(BOMBEXPLOSION_SIZE_X, BOMBEXPLOSION_SIZE_Y, 0.0f));

		// ����������
		pBombExplosion->Init();
	}

	// pBombExplosion��Ԃ�
	return pBombExplosion;
}

//=============================================================================
// �{���̔����N���X�̏���������
//=============================================================================
HRESULT CBombexplosion::Init()
{
	// CScene2D�̏���������
	CScene2D::Init();

	// �e�N�X�`���̐ݒ�
	BindTexture(m_pTexture);

	// �A�j���[�V�����̃Z�b�g
	CScene2D::SetAnimation(BOMBEXPLOSION_ANIMATION_COUNT, BOMBEXPLOSION_ANIMATION_PATTERN, 4);

	return S_OK;
}

//=============================================================================
// �{���̔����N���X�̏I������
//=============================================================================
void CBombexplosion::Uninit(void)
{
	// CScene2D�̏I������
	CScene2D::Uninit();
}

//=============================================================================
// �{���̔����N���X�̍X�V����
//=============================================================================
void CBombexplosion::Update(void)
{
	// �̗͂̌��Z
	m_nLife--;

	// CScene2D�̍X�V����
	CScene2D::Update();

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
				switch (m_BombExplosionType)
				{
					// �v���C���[1�̃{���̔���
				case BOMBEXPLOSION_PLAYER:

					// �����蔻��
					if (CCollision::PRectangleCollision(m_pos, D3DXVECTOR3(BOMBEXPLOSION_SIZE_X, BOMBEXPLOSION_SIZE_Y, 0.0f), pScene) == true)
					{
						// �G�̃_���[�W
						((CEnemy*)pScene)->EnemyDamage(100, CEnemy::DAMAGE_TYPE_BULLET, CBullet::BULLET_TYPE_1P);
						break;
					}
					break;

					// �v���C���[2�̃{���̔���
				case BOMBEXPLOSION_PLAYER2:

					// �����蔻��
					if (CCollision::PRectangleCollision(m_pos, D3DXVECTOR3(BOMBEXPLOSION_SIZE_X, BOMBEXPLOSION_SIZE_Y, 0.0f), pScene) == true)
					{
						// �G�̃_���[�W
						((CEnemy*)pScene)->EnemyDamage(100, CEnemy::DAMAGE_TYPE_BULLET, CBullet::BULLET_TYPE_2P);
						break;
					}
					break;

				default:
					break;
				}
			}
			pScene = pScene->GetSceneNext();
		}
	} while (pScene != NULL);

	// �̗͂�0�ȉ��ɂȂ�����I��
	if (m_nLife <= 0)
	{
		Uninit();
	}
}

//=============================================================================
// �{���̔����N���X�̕`�揈��
//=============================================================================
void CBombexplosion::Draw(void)
{
	// CScene2D�̕`�揈��
	CScene2D::Draw();
}