//=============================================================================
//
// �G�t�F�N�g�̏��� [effect.cpp]
// Author : �ɓ��z��
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "effect.h"
#include "renderer.h"
#include "manager.h"
#include "life.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CEffect::m_apTexture[MAX_EFFECT_TEXTURE] = {};

//=============================================================================
// �G�t�F�N�g�N���X�̃R���X�g���N�^
//=============================================================================
CEffect::CEffect() :CScene2D(OBJTYPE_EFFECT)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_nRed = 0;
	m_nGreen = 0;
	m_nBrue = 0;
	m_nAlpha = 0;
	m_EffectType = EFFECTTYPE_BULLET;
}

//=============================================================================
// �G�t�F�N�g�N���X�̃f�X�g���N�^
//=============================================================================
CEffect::~CEffect()
{

}

//=============================================================================
// �G�t�F�N�g�N���X�̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CEffect::Load(void)
{
	// �C���X�^���X�����������̂��󂯎��
	CRenderer *pRenderer = CManager::GetRenderer();

	// �f�o�C�X���󂯎��
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	HRESULT hr = D3DXCreateTextureFromFile(pDevice, TEXTURE_EFFECT_BULLET, &m_apTexture[0]);
	hr = D3DXCreateTextureFromFile(pDevice, TEXTURE_EFFECT_CHARGE, &m_apTexture[1]);

	return S_OK;
}

//=============================================================================
// �G�t�F�N�g�N���X�̃e�N�X�`���j��
//=============================================================================
void CEffect::Unload(void)
{
	for (int nCount = 0; nCount < MAX_EFFECT_TEXTURE; nCount++)
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
// �G�t�F�N�g�N���X�̃C���X�^���X����
//=============================================================================
CEffect * CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nLife, int nRed, int nGreen, int nBrue, int nAlpha, EFFECTTYPE EffectType, OBJTYPE objType)
{
	// CDice�̃|�C���^
	CEffect *Effect = NULL;

	// �������̊m��
	Effect = new CEffect;

	// Effect��NULL����Ȃ��Ƃ�
	if (Effect != NULL)
	{
		Effect->SetEffect(pos, size, nLife, nRed, nGreen, nBrue, nAlpha, EffectType, objType);
		
		// ����������
		Effect->Init();
	}

	// Effect��Ԃ�
	return Effect;
}

//=============================================================================
// �G�t�F�N�g�N���X�̏���������
//=============================================================================
HRESULT CEffect::Init()
{
	// CScene2D�̏���������
	CScene2D::Init();

	switch (m_EffectType)
	{
	case EFFECTTYPE_BULLET:
		// �e�N�X�`���̐ݒ�
		BindTexture(m_apTexture[m_EffectType]);
		break;

	case EFFECTTYPE_CHARGESTATE:
		// �e�N�X�`���̐ݒ�
		BindTexture(m_apTexture[m_EffectType]);

		// �A�j���[�V�����̃Z�b�g
		SetAnimationSelect(3, 3, 0, 10);
		break;

	default:
		break;
	}
	
	return S_OK;
}

//=============================================================================
// �G�t�F�N�g�N���X�̏I������
//=============================================================================
void CEffect::Uninit(void)
{
	// CScene2D�̏I������
	CScene2D::Uninit();
}

//=============================================================================
// �G�t�F�N�g�N���X�̍X�V����
//=============================================================================
void CEffect::Update(void)
{
	// CScene2D�̍X�V����
	CScene2D::Update();
	SetColor(m_nRed, m_nGreen, m_nBrue, m_nAlpha);

	// ���W�ƃT�C�Y���󂯎��
	m_pos = GetPosition();
	m_size = GetSize();

	switch (m_EffectType)
	{
		// �e�̃G�t�F�N�g
	case EFFECTTYPE_BULLET:
		// �T�C�Y�����������Ă���
		m_size -= D3DXVECTOR3(1.0f, 1.0f, 0.0f);

		// �T�C�Y��0.0f��菬�����Ȃ�����
		if (m_size < D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		{
			m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}

		// �̗͂Ɠ����x�̌��Z
		m_nLife--;
		m_nAlpha--;

		// �̗͂�0�ȉ��ɂȂ�����
		if (m_nLife <= 0)
		{
			Uninit();
		}
		break;

	default:
		break;
	}
	
	// ���W�ƃT�C�Y��n��
	SetPosition(m_pos);
	SetSize(m_size);
}

//=============================================================================
// �G�t�F�N�g�N���X�̕`�揈��
//=============================================================================
void CEffect::Draw(void)
{
	// �C���X�^���X�����������̂��󂯎��
	CRenderer *pRenderer = CManager::GetRenderer();

	// �f�o�C�X���󂯎��
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	
	// CScene2D�̕`�揈��
	CScene2D::Draw();

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}