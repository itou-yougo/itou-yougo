//=============================================================================
//
// �|���S���̕`��̏��� [bg.h]
// Author : �ɓ��z��
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "bg.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "explosion.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define BG1_SCROLL_SPEED (-0.001f)			// �w�i�𓮂�������

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CBg::m_apTexture[MAX_BG_TEXTURE];

//=============================================================================
// �w�i�N���X�̃R���X�g���N�^
//=============================================================================
CBg::CBg() :CScene(OBJTYPE_BG)
{
	for (int nCount = 0; nCount < MAX_BG_TEXTURE; nCount++)
	{
		m_apScene[nCount] = NULL;
	}
	m_BgType = BGTYPE_GAME;
}

//=============================================================================
// �w�i�N���X�̃f�X�g���N�^
//=============================================================================
CBg::~CBg()
{

}

//=============================================================================
// �w�i�N���X�̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CBg::Load(void)
{
	// �C���X�^���X�����������̂��󂯎��
	CRenderer *pRenderer = CManager::GetRenderer();

	// �f�o�C�X���󂯎��
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BG1, &m_apTexture[BGTYPE_GAME]);			   // �Q�[���̔w�i
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BG4, &m_apTexture[BGTYPE_FRAME]);		   // �Q�[���̘g
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BGTUTORIAL, &m_apTexture[BGTYPE_TUTORIAL]); // �`���[�g���A���̔w�i
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BGRESULT, &m_apTexture[BGTYPE_RESULT]);	   // ���U���g�̔w�i

	return S_OK;
}

//=============================================================================
// �w�i�N���X�̃e�N�X�`���j��
//=============================================================================
void CBg::Unload(void)
{
	for (int nCount = 0; nCount < MAX_BG_TEXTURE; nCount++)
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
// �w�i�N���X�̃C���X�^���X����
//=============================================================================
CBg *CBg::Create(BGTYPE bgtype, OBJTYPE objType)
{
	// pBg�̃|�C���^
	CBg *pBg = NULL;

	// �������̊m��
	pBg = new CBg;

	// pBg��NULL����Ȃ��Ƃ�
	if (pBg != NULL)
	{
		pBg->SetBG(bgtype, objType);

		// ����������
		pBg->Init();
	}

	// pBg��Ԃ�
	return pBg;
}

//=============================================================================
// �w�i�N���X�̏���������
//=============================================================================
HRESULT CBg::Init()
{
	switch (m_BgType)
	{
		// �`���[�g���A���̔w�i
	case BGTYPE_TUTORIAL:
		BgCreate(m_BgType);
		break;

		// �Q�[���̔w�i
	case BGTYPE_GAME:
		BgCreate(m_BgType);

		// bg�̃A�j���[�V�����̃Z�b�g
		m_apScene[m_BgType]->SetScroll(0.0f, BG1_SCROLL_SPEED);
		break;

		// �Q�[���̘g
	case BGTYPE_FRAME:
		BgCreate(m_BgType);
		break;

		// ���U���g�̔w�i
	case BGTYPE_RESULT:
		BgCreate(m_BgType);
		break;

	default:
		break;
	}
	
	return S_OK;
}

//=============================================================================
// �w�i�N���X�̏I������
//=============================================================================
void CBg::Uninit(void)
{
	switch (m_BgType)
	{
		// �`���[�g���A���̔w�i
	case BGTYPE_TUTORIAL:
		if (m_apScene[m_BgType] != NULL)
		{
			// CScene2D�̏I������
			m_apScene[m_BgType]->Uninit();
		}
		break;

		// �Q�[���̔w�i
	case BGTYPE_GAME:
		if (m_apScene[m_BgType] != NULL)
		{
			// CScene2D�̏I������
			m_apScene[m_BgType]->Uninit();
		}
		break;

		// �Q�[���̘g
	case BGTYPE_FRAME:
		if (m_apScene[m_BgType] != NULL)
		{
			// CScene2D�̏I������
			m_apScene[m_BgType]->Uninit();
		}
		break;

		// ���U���g�̔w�i
	case BGTYPE_RESULT:
		if (m_apScene[m_BgType] != NULL)
		{
			// CScene2D�̏I������
			m_apScene[m_BgType]->Uninit();
		}
		break;

	default:
		break;
	}

	Release();
}

//=============================================================================
// �w�i�N���X�̍X�V����
//=============================================================================
void CBg::Update(void)
{
	for (int nCount = 0; nCount < MAX_BG_TEXTURE; nCount++)
	{
		// CScene2D�̍X�V����
		if (m_apScene[nCount] != NULL)
		{
			m_apScene[nCount]->Update();
		}
	}
}

//=============================================================================
// �w�i�N���X�̕`�揈��
//=============================================================================
void CBg::Draw(void)
{
	for (int nCount = 0; nCount < MAX_BG_TEXTURE; nCount++)
	{
		// CScene2D�̕`�揈��
		if (m_apScene[nCount] != NULL)
		{
			m_apScene[nCount]->Draw();
		}
	}
}

//=============================================================================
// �w�i�N���X�̃|���S������鏈��
//=============================================================================
void CBg::BgCreate(BGTYPE BgType)
{
	m_apScene[BgType] = CScene2D::Create();

	// CScene2D�̏���������
	m_apScene[BgType]->Init();

	m_apScene[BgType]->SetObjType(OBJTYPE_SCENE);

	// �e�N�X�`���̐ݒ�
	m_apScene[BgType]->BindTexture(m_apTexture[m_BgType]);

	// ���W�Əc�Ɖ��̒�����n��
	m_apScene[BgType]->SetPosition(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f));
	m_apScene[BgType]->SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
}
