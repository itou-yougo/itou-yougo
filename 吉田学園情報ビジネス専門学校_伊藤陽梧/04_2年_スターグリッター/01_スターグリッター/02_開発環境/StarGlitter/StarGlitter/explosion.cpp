//=============================================================================
//
// �|���S���̕`��̏��� [explosion.h]
// Author : �ɓ��z��
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "explosion.h"
#include "renderer.h"
#include "manager.h"
#include "enemy.h"
#include "sound.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define EXPLOSION_ANIMATION_COUNT (7)		// �����̃A�j���[�V�����̃J�E���g(���̃e�N�X�`���̕�����)
#define EXPLOSION_ANIMATION_PATTERN (1)		// �����̃A�j���[�V�����̃p�^�[��(�c�̃e�N�X�`���̕�����)
#define BOSSEXPLOSION_ANIMATION_COUNT (7)	// �����̃A�j���[�V�����̃J�E���g(���̃e�N�X�`���̕�����)
#define BOSSEXPLOSION_ANIMATION_PATTERN (1) // �����̃A�j���[�V�����̃p�^�[��(�c�̃e�N�X�`���̕�����)
#define EXPLOSION_SIZE_X (100.0f)			// �����̏c�̒���
#define EXPLOSION_SIZE_Y (100.0f)			// �����̉��̒���

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture[MAX_EXPLOSION_TEXTUTE] = {};

//=============================================================================
// �o���b�g�N���X�̃R���X�g���N�^
//=============================================================================
CExplosion::CExplosion() :CScene2D(OBJTYPE_EXPLOSION)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCounterAnim = 0;
	m_ExplosionType = EXPLOSIONTYPE_NOMAL;
}

//=============================================================================
// �o���b�g�N���X�̃f�X�g���N�^
//=============================================================================
CExplosion::~CExplosion()
{

}

//=============================================================================
// �o���b�g�N���X�̃e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CExplosion::Load(void)
{
	// �C���X�^���X�����������̂��󂯎��
	CRenderer *pRenderer = CManager::GetRenderer();

	// �f�o�C�X���󂯎��
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_EXPLOSION, &m_pTexture[0]);	   // �e�̔���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BOSSEXPLOSION, &m_pTexture[1]); // �{�X�A�^�b�N�̔���

	return S_OK;
}

//=============================================================================
// �o���b�g�N���X�̃e�N�X�`���̔j��
//=============================================================================
void CExplosion::Unload(void)
{
	for (int nCount = 0; nCount < MAX_EXPLOSION_TEXTUTE; nCount++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
// �o���b�g�N���X�̃C���X�^���X����
//=============================================================================
CExplosion* CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, EXPLOSIONTYPE ExplosionType, OBJTYPE objType)
{
	// CExplosion�̃|�C���^
	CExplosion *pExplosion = NULL;

	// �������̊m��
	pExplosion = new CExplosion;

	// �T�E���h�̍Đ�
	CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_EXPLOSION_SE);

	// pExplosion��NULL����Ȃ��Ƃ�
	if (pExplosion != NULL)
	{
		// �����̃Z�b�g
		pExplosion->SetExplosion(pos, size, ExplosionType, objType);

		// ����������
		pExplosion->Init();
	}

	// pExplosion��Ԃ�
	return pExplosion;
}

//=============================================================================
// �o���b�g�N���X�̏���������
//=============================================================================
HRESULT CExplosion::Init()
{
	m_nCounterAnim = 0;

	// CScene2D�̏���������
	CScene2D::Init();

	switch (m_ExplosionType)
	{
		// �e�̔���
	case EXPLOSIONTYPE_NOMAL:
		// �e�N�X�`���̐ݒ�
		BindTexture(m_pTexture[0]);

		// �A�j���[�V�����̃Z�b�g
		CScene2D::SetAnimation(EXPLOSION_ANIMATION_COUNT, EXPLOSION_ANIMATION_PATTERN, 1);

		break;

		// �{�X�A�^�b�N�̔���
	case EXPLOSIONTYPE_BOSS:
		// �e�N�X�`���̐ݒ�
		BindTexture(m_pTexture[1]);

		// �A�j���[�V�����̃Z�b�g
   		CScene2D::SetAnimation(BOSSEXPLOSION_ANIMATION_COUNT, BOSSEXPLOSION_ANIMATION_PATTERN, 1);
		break;

	default:
		break;
	}
	
	return S_OK;
}

//=============================================================================
// �o���b�g�N���X�̏I������
//=============================================================================
void CExplosion::Uninit(void)
{
	// CScene2D�̏I������
	CScene2D::Uninit();
}

//=============================================================================
// �o���b�g�N���X�̍X�V����
//=============================================================================
void CExplosion::Update(void)
{
	// �T�C�Y�̎󂯎��
	m_size = GetSize();

	// �A�j���[�V�����̃J�E���g
	m_nCounterAnim++;

	// CScene2D�̍X�V����
	CScene2D::Update();

	// m_pos��n��
	SetPosition(m_pos);
	SetSize(m_size);

	switch (m_ExplosionType)
	{
	case EXPLOSIONTYPE_NOMAL:
		if (m_nCounterAnim % EXPLOSION_ANIMATION_COUNT == 0)
		{
			Uninit();
		}
		break;

	case EXPLOSIONTYPE_BOSS:
		if (m_nCounterAnim % BOSSEXPLOSION_ANIMATION_COUNT == 0)
		{
			Uninit();
		}
		break;

	default:
		break;
	}
}

//=============================================================================
// �o���b�g�N���X�̕`�揈��
//=============================================================================
void CExplosion::Draw(void)
{
	// CScene2D�̕`�揈��
	CScene2D::Draw();
}

