//=============================================================================
//
// �Z���N�g�̏��� [select.cpp]
// Author : �ɓ��z��
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "select.h"
#include "renderer.h"
#include "manager.h"
#include "text.h"
#include "input.h"
#include "fade.h"
#include "gattyann.h"
#include "sound.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CSelect::m_apTexture[MAX_SELECT_TEXTURE] = {};

//=============================================================================
// �Z���N�g�N���X�̃R���X�g���N�^
//=============================================================================
CSelect::CSelect() :CScene2D(OBJTYPE_TEXT)
{
	m_pVtxBuff = NULL;
	m_pText[0] = NULL;
	m_pText[1] = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCount = 0;
	m_nCountSelect = 0;
	m_bButtonPress = false;
	m_pSelectType = SELECTTYPE_KUROHAIKEI;
}

//=============================================================================
// �Z���N�g�N���X�̃f�X�g���N�^
//=============================================================================
CSelect::~CSelect()
{

}

//=============================================================================
// �Z���N�g�N���X�̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CSelect::Load(void)
{
	// �C���X�^���X�����������̂��󂯎��
	CRenderer *pRenderer = CManager::GetRenderer();

	// �f�o�C�X���󂯎��
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_MENUHAIKEI, &m_apTexture[SELECTTYPE_KUROHAIKEI]); // �����w�i
	D3DXCreateTextureFromFile(pDevice, TEXTURE_MENU, &m_apTexture[SELECTTYPE_MENU]);			 // ���j���[

	return S_OK;
}

//=============================================================================
// �Z���N�g�N���X�̃e�N�X�`���j��
//=============================================================================
void CSelect::Unload(void)
{
	for (int nCount = 0; nCount < MAX_SELECT_TEXTURE; nCount++)
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
// �Z���N�g�N���X�̃C���X�^���X����
//=============================================================================
CSelect * CSelect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, SELECTTYPE SelectType)
{
	// CText�̃|�C���^
	CSelect *pText = NULL;

	// �������̊m��
	pText = new CSelect;

	// pText��NULL����Ȃ��Ƃ�
	if (pText != NULL)
	{
		// ���W��T�C�Y�̃Z�b�g
		pText->SetSelect(pos, size, SelectType);

		// ����������
		pText->Init();
	}

	// pNumber��Ԃ�
	return pText;
}

//=============================================================================
// �Z���N�g�N���X�̏���������
//=============================================================================
HRESULT CSelect::Init()
{
	// CScene2D�̏���������
	CScene2D::Init();

	//�@�e�N�X�`���̐ݒ�
	BindTexture(m_apTexture[m_pSelectType]);

	// m_pSelectType�����j���[�̎�
	if (m_pSelectType == SELECTTYPE_MENU)
	{
		// �e�L�X�g�N���X�̃N���G�C�g�ƐF�̃Z�b�g
		m_pText[0] = m_pText[0]->Create(D3DXVECTOR3(m_pos.x, m_pos.y - 100.0f, m_pos.z), D3DXVECTOR3(662.0f, 150.0f, 0.0f), CText::TEXTTYPE_RESTART);
		m_pText[0]->SetColor(255, 255, 255, 255);
		m_pText[1] = m_pText[1]->Create(D3DXVECTOR3(m_pos.x, m_pos.y + 100.0f, m_pos.z), D3DXVECTOR3(695.0f, 132.0f, 0.0f), CText::TEXTTYPE_MODORU);
		m_pText[1]->SetColor(255, 255, 255, 100);
	}

	SetObjType(OBJTYPE_TEXT);
	return S_OK;
}

//=============================================================================
// �Z���N�g�N���X�̏I������
//=============================================================================
void CSelect::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_TEXT; nCount++)
	{
		// m_pText��NULL����Ȃ��Ƃ�
		if (m_pText[nCount] != NULL)
		{
			// m_pText�̏I������
			m_pText[nCount]->Uninit();
			m_pText[nCount] = NULL;
		}
	}

	// CScene2D�̏I������
	CScene2D::Uninit();
}

//=============================================================================
// �Z���N�g�N���X�̍X�V����
//=============================================================================
void CSelect::Update(void)
{
	// CScene2D�̍X�V����
	CScene2D::Update();

	Menu();
}

//=============================================================================
// �Z���N�g�N���X�̕`�揈��
//=============================================================================
void CSelect::Draw(void)
{
	// CScene2D�̕`�揈��
	CScene2D::Draw();
}

//=============================================================================
// �Z���N�g�N���X�̃��j���[�̏���
//=============================================================================
void CSelect::Menu(void)
{
	CInputJoypad *pInputJoypad = CManager::GetInputJoypad();

	// m_pSelectType�����j���[�̎�
	if (m_pSelectType == SELECTTYPE_MENU)
	{
		// �I�ԏ���
		Select();

		// ���߂鏈��
		Decision();
	}
}

//=============================================================================
// �Z���N�g�N���X�̑I�ԏ���
//=============================================================================
void CSelect::Select(void)
{
	CInputJoypad *pInputJoypad = CManager::GetInputJoypad();

	//�R���g���[���[�̏����擾����
	DIJOYSTATE2 Controller = pInputJoypad->GetController(PLAYER_1);
	// ��
	if (Controller.lY > 0)
	{
		m_nCount++;
	}
	// ��
	if (Controller.lY < 0)
	{
		m_nCount--;
	}

	Controller = pInputJoypad->GetController(PLAYER_2);
	// ��
	if (Controller.lY > 0)
	{
		// m_nCount�̌��Z
		m_nCount++;
	}
	// ��
	if (Controller.lY < 0)
	{
		// m_nCount�̉��Z
		m_nCount--;
	}

	// �I�񂾎��̃J�E���g�̌��Z
	m_nCountSelect--;

	// �{�^���������ĂȂ��Ƃ�
	if (m_bButtonPress == false)
	{
		// �I�񂾎��̃J�E���g��0��菬�����Ƃ�
		if (m_nCountSelect < 0)
		{
			// m_nCount��0��菬�����Ƃ�
			if (m_nCount < 0)
			{
				m_nCount = 0;

				// �e�L�X�g�̐F�̐ݒ�
				m_pText[m_nCount]->SetColor(255, 255, 255, 255);
				m_pText[m_nCount + 1]->SetColor(255, 255, 255, 100);

				// �T�E���h�̍Đ�
				CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_MENUKIRIKAE);

				// �I�񂾎��̃J�E���g�ɑ������
				m_nCountSelect = 50;
			}

			// m_nCount��1���傫���Ƃ�
			if (m_nCount > 1)
			{
				m_nCount = 1;

				// �e�L�X�g�̐F�̐ݒ�
				m_pText[m_nCount]->SetColor(255, 255, 255, 255);
				m_pText[m_nCount - 1]->SetColor(255, 255, 255, 100);

				// �T�E���h�̍Đ�
				CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_MENUKIRIKAE);

				// �I�񂾎��̃J�E���g�ɑ������
				m_nCountSelect = 50;
			}
		}
	}
}

//=============================================================================
// �Z���N�g�N���X�̌��߂鏈��
//=============================================================================
void CSelect::Decision(void)
{
	CInputJoypad *pInputJoypad = CManager::GetInputJoypad();

	// �J�E���g��0�ɂȂ�����
	if (m_nCount == 0)
	{
		// �{�^���������ĂȂ��Ƃ�
		if (m_bButtonPress == false)
		{
			// A�{�^������������
			if (pInputJoypad->GetJoypadTrigger(PLAYER_1, CInputJoypad::BUTTON_A))
			{
				// �K�b�`�����̃N���G�C�g
				CGattyann::Create(D3DXVECTOR3(SCREEN_CENTER_X / 4, SCREEN_HEIGHT + SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(432.0f, 1080.0f, 0.0f), CGattyann::GATTYANN_5);
				CGattyann::Create(D3DXVECTOR3(SCREEN_CENTER_X - SCREEN_CENTER_X / 4, -SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(432.0f, 1080.0f, 0.0f), CGattyann::GATTYANN_6);
				CGattyann::Create(D3DXVECTOR3(SCREEN_CENTER_X + SCREEN_CENTER_X / 4, SCREEN_HEIGHT + SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(432.0f, 1080.0f, 0.0f), CGattyann::GATTYANN_7);
				CGattyann::Create(D3DXVECTOR3(SCREEN_WIDTH - SCREEN_CENTER_X / 4, -SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(432.0f, 1080.0f, 0.0f), CGattyann::GATTYANN_8);

				// �|�[�Y��Ԃ̉���
				CScene::SetPause(false);

				// �T�E���h�̍Đ�
				CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_MENUKETTEI);

				//�{�^������������Ԃɂ���
				m_bButtonPress = true;
			}
			else if (pInputJoypad->GetJoypadTrigger(PLAYER_2, CInputJoypad::BUTTON_A))
			{
				// �K�b�`�����̃N���G�C�g
				CGattyann::Create(D3DXVECTOR3(SCREEN_CENTER_X / 4, SCREEN_HEIGHT + SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(432.0f, 1080.0f, 0.0f), CGattyann::GATTYANN_5);
				CGattyann::Create(D3DXVECTOR3(SCREEN_CENTER_X - SCREEN_CENTER_X / 4, -SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(432.0f, 1080.0f, 0.0f), CGattyann::GATTYANN_6);
				CGattyann::Create(D3DXVECTOR3(SCREEN_CENTER_X + SCREEN_CENTER_X / 4, SCREEN_HEIGHT + SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(432.0f, 1080.0f, 0.0f), CGattyann::GATTYANN_7);
				CGattyann::Create(D3DXVECTOR3(SCREEN_WIDTH - SCREEN_CENTER_X / 4, -SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(432.0f, 1080.0f, 0.0f), CGattyann::GATTYANN_8);

				// �|�[�Y��Ԃ̉���
				CScene::SetPause(false);

				// �T�E���h�̍Đ�
				CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_MENUKETTEI);

				//�{�^������������Ԃɂ���
				m_bButtonPress = true;
			}
		}
	}
	// �J�E���g��1�ɂȂ�����
	else if (m_nCount == 1)
	{
		// �{�^���������ĂȂ��Ƃ�
		if (m_bButtonPress == false)
		{
			// A�{�^������������
			if (pInputJoypad->GetJoypadTrigger(PLAYER_1, CInputJoypad::BUTTON_A))
			{
				if (CManager::GetFade() != NULL)
				{
					// �^�C�g���ɖ߂�
					CManager::GetFade()->SetFade(CManager::MODE_TITLE);

					// �|�[�Y��Ԃ̉���
					CScene::SetPause(false);

					// �T�E���h�̍Đ�
					CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_MENUKETTEI);

					//�{�^������������Ԃɂ���
					m_bButtonPress = true;
				}
			}
			else if (pInputJoypad->GetJoypadTrigger(PLAYER_2, CInputJoypad::BUTTON_A))
			{
				if (CManager::GetFade() != NULL)
				{
					// �^�C�g���ɖ߂�
					CManager::GetFade()->SetFade(CManager::MODE_TITLE);

					// �|�[�Y��Ԃ̉���
					CScene::SetPause(false);

					// �T�E���h�̍Đ�
					CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_MENUKETTEI);

					//�{�^������������Ԃɂ���
					m_bButtonPress = true;
				}
			}
		}
	}
}
