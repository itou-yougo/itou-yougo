//=============================================================================
//
// �e�L�X�g�̏��� [text.cpp]
// Author : �ɓ��z��
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "text.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "player2.h"
#include "select.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_SIZE_Y (190.0f) // �c�̑傫���̍ő�l
#define MAX_TIME (60)		// ���Ԃ̍ő�l

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CText::m_apTexture[MAX_TEXT_TEXTURE] = {};

//=============================================================================
// �e�L�X�g�̃R���X�g���N�^
//=============================================================================
CText::CText() :CScene2D(OBJTYPE_TEXT)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nAlpha = 255;
	m_nCount = 0;
	m_fSizeX = 0.0f;
	m_fSizeY = 0.0f;
	m_bUse = true;
	m_TextType = TEXTTYPE_MAX;
}

//=============================================================================
// �e�L�X�g�̃f�X�g���N�^
//=============================================================================
CText::~CText()
{

}

//=============================================================================
// �e�L�X�g�̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CText::Load(void)
{
	// �C���X�^���X�����������̂��󂯎��
	CRenderer *pRenderer = CManager::GetRenderer();

	// �f�o�C�X���󂯎��
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_RESTART, &m_apTexture[TEXTTYPE_RESTART]);    // ������x�n�߂�
	D3DXCreateTextureFromFile(pDevice, TEXTURE_TITLEMODORU, &m_apTexture[TEXTTYPE_MODORU]);	// �^�C�g���ɖ߂�
	D3DXCreateTextureFromFile(pDevice, TEXTURE_READY, &m_apTexture[TEXTTYPE_READY]);		// READY�̕���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_GO, &m_apTexture[TEXTTYPE_GO]);				// GO�̕���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_KO, &m_apTexture[TEXTTYPE_KO]);				// KO�̕���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_WON, &m_apTexture[TEXTTYPE_WON]);			// WON�̕���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_LOST, &m_apTexture[TEXTTYPE_LOST]);			// LOST�̕���

	return S_OK;
}

//=============================================================================
// �e�L�X�g�̃e�N�X�`���j��
//=============================================================================
void CText::Unload(void)
{
	for (int nCount = 0; nCount < MAX_TEXT_TEXTURE; nCount++)
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
// �e�L�X�g�̃C���X�^���X����
//=============================================================================
CText * CText::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, TEXTTYPE TextType)
{
	// CText�̃|�C���^
	CText *pText = NULL;

	// �������̊m��
	pText = new CText;

	// pText��NULL����Ȃ��Ƃ�
	if (pText != NULL)
	{
		// ���W��T�C�Y�̃Z�b�g
		pText->SetText(pos, fSizeX, fSizeY, TextType);

		// ����������
		pText->Init();
	}

	// pNumber��Ԃ�
	return pText;
}

//=============================================================================
// �e�L�X�g�̏���������
//=============================================================================
HRESULT CText::Init()
{
	// CScene2D�̏���������
	CScene2D::Init();
	
	// m_apTexture��NULL����Ȃ��Ƃ�
	if (m_apTexture[m_TextType] != NULL)
	{
		//�@�e�N�X�`���̐ݒ�
		BindTexture(m_apTexture[m_TextType]);
	}

	// �I�u�W�F�^�C�v�̃Z�b�g
	SetObjType(OBJTYPE_TEXT);

	switch (m_TextType)
	{
		// GO�̕���
	case TEXTTYPE_GO:
		// �`�J�`�J������
		SetTransparency(true);
		break;

	default:
		break;
	}

	return S_OK;
}

//=============================================================================
// �e�L�X�g�̏I������
//=============================================================================
void CText::Uninit(void)
{
	// CScene2D�̏I������
	CScene2D::Uninit();
}

//=============================================================================
// �e�L�X�g�̍X�V����
//=============================================================================
void CText::Update(void)
{
	// CScene2D�̍X�V����
	CScene2D::Update();

	// �T�C�Y�̎󂯎��
	m_fSizeY = GetSizeY();

	switch (m_TextType)
	{
		// READY�̕���
	case TEXTTYPE_READY:
		// m_bUse���g�p��Ԃ̎�
		if (m_bUse == true)
		{
			m_fSizeY += 3.0f;

			// �T�C�Y��MAX_SIZE_Y���傫���Ȃ�����
			if (m_fSizeY >= MAX_SIZE_Y)
			{
				// m_bUse���g�p���Ȃ���Ԃɂ���
				m_bUse = false;
			}
		}
		// m_bUse���g�p���Ȃ���Ԃ̎�
		else if (m_bUse == false)
		{
			m_fSizeY -= 3.0f;

			// �T�C�Y��MAX_SIZE_Y��菬�����Ȃ�����
			if (m_fSizeY <= 0.0f)
			{
				// GO�̃N���G�C�g
				Create(m_pos, 632.0f, 232.0f, TEXTTYPE_GO);

				// �I������
				Uninit();
				return;
			}
		}
		break;

		// GO�̕���
	case TEXTTYPE_GO:
		m_nCount++;

		// m_nCount��MAX_TIME���傫���Ƃ�
		if (m_nCount >= MAX_TIME)
		{
			//�Q�[���̏�Ԃ�GAMESTATE_START�ɂ���
			CGame::SetGameState(CGame::GAMESTATE_START);

			// �I������
			Uninit();
		}
		break;

		// KO�̕���
	case TEXTTYPE_KO:
		m_nCount++;

		// m_nCount��MAX_TIME���傫���Ƃ�
		if (m_nCount >= MAX_TIME)
		{
			// m_bUse���g�p��Ԃ̎�
			if (m_bUse == true)
			{
				for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
				{
					// PLAYER�̃V�[���̎󂯎��
					CScene *pScene = CScene::GetScene(CScene::OBJTYPE_PLAYER, nCntScene);
					if (pScene != NULL)
					{
						// �I�u�W�F�^�C�v�̎󂯎��
						CScene::OBJTYPE objType = pScene->GetObjType();
						if (objType == CScene::OBJTYPE_PLAYER)
						{
							//PLAYER1��PLAYERSTATE_LOSE��������
							if (((CPlayer*)pScene)->GetPlayerState() == CPlayer::PLAYERSTATE_LOSE)
							{
								// LOST�̃e�L�X�g�̐���
								CText::Create(D3DXVECTOR3(PLAYER_START_POS, SCREEN_CENTER_Y, 0.0f), 652.0f, 232.0f, CText::TEXTTYPE_LOST);
							}
							else
							{
								// WON�̃e�L�X�g�̐���
								CText::Create(D3DXVECTOR3(PLAYER_START_POS, SCREEN_CENTER_Y, 0.0f), 592.0f, 232.0f, CText::TEXTTYPE_WON);
							}
						}
					}

					// PLAYER2�̃V�[���̎󂯎��
					pScene = CScene::GetScene(CScene::OBJTYPE_PLAYER2, nCntScene);
					if (pScene != NULL)
					{
						// �I�u�W�F�^�C�v�̎󂯎��
						CScene::OBJTYPE objType = pScene->GetObjType();
						if (objType == CScene::OBJTYPE_PLAYER2)
						{
							//PLAYER2��PLAYERSTATE_LOSE��������
							if (((CPlayer2*)pScene)->GetPlayer2State() == CPlayer2::PLAYERSTATE_LOSE)
							{
								// LOST�̃e�L�X�g�̐���
								CText::Create(D3DXVECTOR3(PLAYER2_START_POS, SCREEN_CENTER_Y, 0.0f), 652.0f, 232.0f, CText::TEXTTYPE_LOST);
							}
							else
							{
								// WON�̃e�L�X�g�̐���
								CText::Create(D3DXVECTOR3(PLAYER2_START_POS, SCREEN_CENTER_Y, 0.0f), 592.0f, 232.0f, CText::TEXTTYPE_WON);
							}
						}
					}
				}

				// m_bUse���g�p���Ȃ���Ԃɂ���
				m_bUse = false;

				// �I������
				Uninit();
			}
		}
		break;

	case TEXTTYPE_WON:
		m_nCount++;
		// �J�E���g��MAX_TIME�̂Q�{�̒l���傫���Ƃ�
		if (m_nCount >= MAX_TIME * 2)
		{
			// m_bUse���g�p��Ԃ̎�
			if (m_bUse == true)
			{
				// �����w�i�ƃ��j���[�̐���
				CSelect::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, CSelect::SELECTTYPE_KUROHAIKEI);
				CSelect::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), 850.0f, 625.0f, CSelect::SELECTTYPE_MENU);

				// m_bUse���g�p���Ȃ���Ԃɂ���
				m_bUse = false;
			}
		}
		break;

	default:
		break;
	}

	// �T�C�Y�̃Z�b�g
	SetSize(m_fSizeX, m_fSizeY);
}

//=============================================================================
// �e�L�X�g�̕`�揈��
//=============================================================================
void CText::Draw(void)
{
	// CScene2D�̕`�揈��
	CScene2D::Draw();
}