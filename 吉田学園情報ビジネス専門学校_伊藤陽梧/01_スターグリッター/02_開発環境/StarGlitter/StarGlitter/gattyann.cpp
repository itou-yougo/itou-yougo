//=============================================================================
//
// �K�b�`�����̏��� [gattyann.cpp]
// Author : �ɓ��z��
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "gattyann.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "fade.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CGattyann::m_pTexture[MAX_GATTYANN_TEXTURE] = {};

//=============================================================================
// �K�b�`�����N���X�̃R���X�g���N�^
//=============================================================================
CGattyann::CGattyann() :CScene2D(OBJTYPE_GATTYANN)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fSizeX = 0.0f;
	m_fSizeY = 0.0f;
	m_nCount = 0;
	m_GattyannType = GATTYANN_1;
}

//=============================================================================
// �K�b�`�����N���X�̃f�X�g���N�^
//=============================================================================
CGattyann::~CGattyann()
{

}

//=============================================================================
// �K�b�`�����N���X�̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CGattyann::Load(void)
{
	// �C���X�^���X�����������̂��󂯎��
	CRenderer *pRenderer = CManager::GetRenderer();

	// �f�o�C�X���󂯎��
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_GATTYANN1, &m_pTexture[GATTYANN_1]); // 1����
	D3DXCreateTextureFromFile(pDevice, TEXTURE_GATTYANN2, &m_pTexture[GATTYANN_2]); // 2����
	D3DXCreateTextureFromFile(pDevice, TEXTURE_GATTYANN3, &m_pTexture[GATTYANN_3]); // 3����
	D3DXCreateTextureFromFile(pDevice, TEXTURE_GATTYANN4, &m_pTexture[GATTYANN_4]); // 4����
	D3DXCreateTextureFromFile(pDevice, TEXTURE_GATTYANN5, &m_pTexture[GATTYANN_5]); // 5����
	D3DXCreateTextureFromFile(pDevice, TEXTURE_GATTYANN6, &m_pTexture[GATTYANN_6]); // 6����
	D3DXCreateTextureFromFile(pDevice, TEXTURE_GATTYANN7, &m_pTexture[GATTYANN_7]); // 7����
	D3DXCreateTextureFromFile(pDevice, TEXTURE_GATTYANN8, &m_pTexture[GATTYANN_8]); // 8����

	return S_OK;
}

//=============================================================================
// �K�b�`�����N���X�̃e�N�X�`���j��
//=============================================================================
void CGattyann::Unload(void)
{
	for (int nCount = 0; nCount < MAX_GATTYANN_TEXTURE; nCount++)
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
// �K�b�`�����N���X�̃C���X�^���X����
//=============================================================================
CGattyann * CGattyann::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, GATTYANNTYPE GattyannType)
{
	// CGattyann�̃|�C���^
	CGattyann *pText = NULL;

	// �������̊m��
	pText = new CGattyann;

	// pText��NULL����Ȃ��Ƃ�
	if (pText != NULL)
	{
		// ���W��T�C�Y�̃Z�b�g
		pText->SetGattyann(pos, fSizeX, fSizeY, GattyannType);

		// ����������
		pText->Init();
	}

	// pNumber��Ԃ�
	return pText;
}

//=============================================================================
// �K�b�`�����N���X�̏���������
//=============================================================================
HRESULT CGattyann::Init()
{
	// CScene2D�̏���������
	CScene2D::Init();

	// m_apTexture��NULL����Ȃ��Ƃ�
	if (m_pTexture[m_GattyannType] != NULL)
	{
		//�@�e�N�X�`���̐ݒ�
		BindTexture(m_pTexture[m_GattyannType]);
	}

	return S_OK;
}

//=============================================================================
// �K�b�`�����N���X�̏I������
//=============================================================================
void CGattyann::Uninit(void)
{
	// CScene2D�̏I������
	CScene2D::Uninit();
}

//=============================================================================
// �K�b�`�����N���X�̍X�V����
//=============================================================================
void CGattyann::Update(void)
{
	// CScene2D�̍X�V����
	CScene2D::Update();

	m_pos = GetPosition();

	switch (m_GattyannType)
	{
		// 1����
	case GATTYANN_1:
		// �J�E���g�̉��Z
		m_nCount++;
		if (m_nCount >= GATTYANN_OPEN_SPEED)
		{
			// GATTYANN_SPEED�����Z
			m_pos.y += -GATTYANN_SPEED;
			if (m_pos.y <= -m_fSizeY)
			{
				Uninit();
			}
		}
		break;

		// 2����
	case GATTYANN_2:
		// �J�E���g�̉��Z
		m_nCount++;
		if (m_nCount >= GATTYANN_OPEN_SPEED)
		{
			// GATTYANN_SPEED�����Z
			m_pos.x += (GATTYANN_SPEED + 5.0f);
			if (m_fSizeX >= m_fSizeX + SCREEN_WIDTH)
			{
				Uninit();
			}
		}
		break;

		// 3����
	case GATTYANN_3:
		// �J�E���g�̉��Z
		m_nCount++;
		if (m_nCount >= GATTYANN_OPEN_SPEED)
		{
			// GATTYANN_SPEED�����Z
			m_pos.x += -(GATTYANN_SPEED + 5.0f);
			if (m_pos.x <= -m_fSizeX)
			{
				Uninit();
			}
		}
		break;

		// 4����
	case GATTYANN_4:
		// �J�E���g�̉��Z
		m_nCount++;
		if (m_nCount >= GATTYANN_OPEN_SPEED)
		{
			// GATTYANN_SPEED�����Z
			m_pos.y += GATTYANN_SPEED;
			if (m_fSizeY >= m_fSizeY + SCREEN_HEIGHT)
			{
				Uninit();
			}
		}
		break;

		// 5����
	case GATTYANN_5:
		// GATTYANN_SPEED�����Z
		m_pos.y += -GATTYANN_SPEED;
		if (m_pos.y <= SCREEN_CENTER_Y)
		{
			m_pos.y = SCREEN_CENTER_Y;

			// �J�E���g�̉��Z
			m_nCount++;

			if (m_nCount == GATTYANN_OPEN_SPEED * 2)
			{
				// ���[�h�̃Z�b�g
				CManager::SetMode(CManager::MODE_GAME);

				// ���̎l���𐶐�
				Create(D3DXVECTOR3(SCREEN_CENTER_X / 2, SCREEN_CENTER_Y / 2, 0.0f), 864.0f, 540.0f, GATTYANN_1);
				Create(D3DXVECTOR3(SCREEN_WIDTH - SCREEN_CENTER_X / 2, SCREEN_CENTER_Y / 2, 0.0f), 864.0f, 540.0f, GATTYANN_2);
				Create(D3DXVECTOR3(SCREEN_CENTER_X / 2, SCREEN_HEIGHT - SCREEN_CENTER_Y / 2, 0.0f), 864.0f, 540.0f, GATTYANN_3);
				Create(D3DXVECTOR3(SCREEN_WIDTH - SCREEN_CENTER_X / 2, SCREEN_HEIGHT - SCREEN_CENTER_Y / 2, 0.0f), 864.0f, 540.0f, GATTYANN_4);
				m_nCount = 0;
			}
		}
		break;

		// 5����
	case GATTYANN_6:
		// GATTYANN_SPEED�����Z
		m_pos.y += GATTYANN_SPEED;
		if (m_pos.y >= SCREEN_CENTER_Y)
		{
			m_pos.y = SCREEN_CENTER_Y;

			// �J�E���g�̉��Z
			m_nCount++;
		}
		break;

		// 6����
	case GATTYANN_7:
		// GATTYANN_SPEED�����Z
		m_pos.y += -GATTYANN_SPEED;
		if (m_pos.y <= SCREEN_CENTER_Y)
		{
			m_pos.y = SCREEN_CENTER_Y;

			// �J�E���g�̉��Z
			m_nCount++;
		}
		break;

		// 7����
	case GATTYANN_8:
		// GATTYANN_SPEED�����Z
		m_pos.y += GATTYANN_SPEED;
		if (m_pos.y >= SCREEN_CENTER_Y)
		{
			m_pos.y = SCREEN_CENTER_Y;

			// �J�E���g�̉��Z
			m_nCount++;
		}
		break;

	default:
		break;
	}

	// ���W�̃Z�b�g
	SetPosition(m_pos);
}

//=============================================================================
// �K�b�`�����N���X�̕`�揈��
//=============================================================================
void CGattyann::Draw(void)
{
	// CScene2D�̕`�揈��
	CScene2D::Draw();
}