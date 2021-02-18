//=============================================================================
//
// �^�C�g�����S�̏��� [titlelogo.cpp]
// Author : �ɓ��z��
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "titlelogo.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "gattyann.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TITLE_POS (350.0f)
#define START_COUNT (40)

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CTitleLogo::m_pTexture[MAX_LOGO_TEXTURE] = {};

//=============================================================================
// �^�C�g�����S�N���X�̃R���X�g���N�^
//=============================================================================
CTitleLogo::CTitleLogo()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCount = 0;
	m_nAlpha = 0;
	m_bUse = true;
	m_LogoType = LOGOTYPE_SIROHAIKEI;
}

//=============================================================================
// �^�C�g�����S�N���X�̃f�X�g���N�^
//=============================================================================
CTitleLogo::~CTitleLogo()
{

}

//=============================================================================
// �^�C�g�����S�N���X�̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CTitleLogo::Load(void)
{
	// �C���X�^���X�����������̂��󂯎��
	CRenderer *pRenderer = CManager::GetRenderer();

	// �f�o�C�X���󂯎��
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_SIROHAIKEI, &m_pTexture[LOGOTYPE_NONE]);		  // �Ȃ�
	D3DXCreateTextureFromFile(pDevice, TEXTURE_SIROHAIKEI, &m_pTexture[LOGOTYPE_SIROHAIKEI]); // �����w�i
	D3DXCreateTextureFromFile(pDevice, TEXTURE_TITLELOGO, &m_pTexture[LOGOTYPE_TITLE]);		  // �^�C�g��
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PRESSENTER, &m_pTexture[LOGOTYPE_PRESSENTER]); // �v���X�G���^�[

	return S_OK;
}

//=============================================================================
// �^�C�g�����S�N���X�̃e�N�X�`���j��
//=============================================================================
void CTitleLogo::Unload(void)
{
	for (int nCount = 0; nCount < MAX_LOGO_TEXTURE; nCount++)
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
// �^�C�g�����S�N���X�̃C���X�^���X����
//=============================================================================
CTitleLogo * CTitleLogo::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, LOGOTYPE logoType)
{
	// CTitleLogo�̃|�C���^
	CTitleLogo *pText = NULL;

	// �������̊m��
	pText = new CTitleLogo;

	// pText��NULL����Ȃ��Ƃ�
	if (pText != NULL)
	{
		// ���W��T�C�Y�̃Z�b�g
		pText->SetTitleLogo(pos, size, logoType);

		// ����������
		pText->Init();
	}

	// pNumber��Ԃ�
	return pText;
}

//=============================================================================
// �^�C�g�����S�N���X�̏���������
//=============================================================================
HRESULT CTitleLogo::Init()
{
	// CScene2D�̏���������
	CScene2D::Init();

	// m_pTexture��NULL����Ȃ��Ƃ�
	if (m_pTexture[m_LogoType] != NULL)
	{
		//�@�e�N�X�`���̐ݒ�
		BindTexture(m_pTexture[m_LogoType]);
	}

	// �v���X�G���^�[
	if (m_LogoType == LOGOTYPE_PRESSENTER)
	{
		// �F�̐ݒ�
		SetColor(255, 255, 255, m_nAlpha);
	}

	return S_OK;
}

//=============================================================================
// �^�C�g�����S�N���X�̏I������
//=============================================================================
void CTitleLogo::Uninit(void)
{
	// CScene2D�̏I������
	CScene2D::Uninit();
}

//=============================================================================
// �^�C�g�����S�N���X�̍X�V����
//=============================================================================
void CTitleLogo::Update(void)
{
	// CScene2D�̍X�V����
	CScene2D::Update();

	// ���W�̎󂯎��
	m_pos = GetPosition();

	switch (m_LogoType)
	{
		// �^�C�g��
	case LOGOTYPE_TITLE:
		TitleLogo();
		break;

		// �v���X�G���^�[
	case LOGOTYPE_PRESSENTER:
		PlessEnter();
		break;

	default:
		break;
	}

	// ���W�̃Z�b�g
	SetPosition(m_pos);
}

//=============================================================================
// �^�C�g�����S�N���X�̕`�揈��
//=============================================================================
void CTitleLogo::Draw(void)
{
	// CScene2D�̕`�揈��
	CScene2D::Draw();
}

//=============================================================================
// �^�C�g�����S�N���X�̃^�C�g�����S�𓮂�������
//=============================================================================
void CTitleLogo::TitleLogo(void)
{
	// CInput�̃|�C���^�̃C���X�^���X�����̎󂯎��
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	CInputJoypad *pInputJoypad = CManager::GetInputJoypad();

	m_pos.y += 3.0f;

	// ���W��TITLE_POS���傫���Ƃ�
	if (m_pos.y > TITLE_POS)
	{
		m_pos.y = TITLE_POS;
	}

	//�G���^�[�L�[�����ꂽ���ǂ���
	if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN))
	{
		m_pos.y = TITLE_POS;
	}
	//start�������ꂽ���ǂ���
	else if (pInputJoypad->GetJoypadTrigger(PLAYER_1, CInputJoypad::BUTTON_START))
	{
		m_pos.y = TITLE_POS;
	}

	// m_bUse���g�p��Ԃ̎�
	if (m_bUse == true)
	{
		// ���W��TITLE_POS�Ɠ����Ƃ�
		if (m_pos.y == TITLE_POS)
		{
			// �v���X�G���^�[�̐���
			CTitleLogo::Create(D3DXVECTOR3(SCREEN_CENTER_X, 800.0f, 0.0f), D3DXVECTOR3(1220.0f, 166.0f, 0.0f), CTitleLogo::LOGOTYPE_PRESSENTER);

			// m_bUse���g�p���Ȃ���Ԃɂ���
			m_bUse = false;
		}
	}
}

//=============================================================================
// �^�C�g�����S�N���X�̃v���X�G���^�[�̕����𓮂�������
//=============================================================================
void CTitleLogo::PlessEnter(void)
{
	// CInput�̃|�C���^�̃C���X�^���X�����̎󂯎��
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	CInputJoypad *pInputJoypad = CManager::GetInputJoypad();

	// m_bUse���g�p��Ԃ̎�
	if (m_bUse == true)
	{
		m_nAlpha += 3;

		// �F�̃Z�b�g
		SetColor(255, 255, 255, m_nAlpha);

		//m_nAlpha��255�ȏ�ɂȂ�����
		if (m_nAlpha >= 255)
		{
			// m_bUse���g�p���Ȃ���Ԃɂ���
			m_bUse = false;
		}
	}
	// m_bUse���g�p���Ȃ���Ԃ̎�
	else if (m_bUse == false)
	{
		m_nAlpha -= 3;

		// �F�̃Z�b�g
		SetColor(255, 255, 255, m_nAlpha);

		//m_nAlpha��0�ȉ��ɂȂ�����
		if (m_nAlpha <= 0)
		{
			// m_bUse���g�p�����Ԃɂ���
			m_bUse = true;
		}
	}

	m_nCount++;

	// �J�E���g��START_COUNT�ȏ�ɂȂ�����
	if (m_nCount >= START_COUNT)
	{
		//�G���^�[�L�[�����ꂽ���ǂ���
		if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) && CManager::GetFade()->GetFade() == CFade::FADE_NOME)
		{
			if (CManager::GetFade() != NULL)
			{
				// ���[�h���`���[�g���A���ɂ���
				CManager::GetFade()->SetFade(CManager::MODE_TUTORIAL);

				// �T�E���h�̍Đ�
				CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_PRESSENTER);
			}
		}
		//START�������ꂽ���ǂ���
		else if (pInputJoypad->GetJoypadTrigger(PLAYER_1, CInputJoypad::BUTTON_START) && CManager::GetFade()->GetFade() == CFade::FADE_NOME)
		{
			if (CManager::GetFade() != NULL)
			{
				// ���[�h���`���[�g���A���ɂ���
				CManager::GetFade()->SetFade(CManager::MODE_TUTORIAL);

				// �T�E���h�̍Đ�
				CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_PRESSENTER);
			}
		}
	}
}
