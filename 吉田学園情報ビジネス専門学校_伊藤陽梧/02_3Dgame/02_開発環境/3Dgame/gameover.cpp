//=============================================================================
//
// �Q�[���I�[�o�[���� [gameover.cpp]
// Author : �ɓ��z��
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "gameover.h"
#include "renderer.h"
#include "manager.h"
#include "keyboard.h"
#include "joystick.h"
#include "time.h"
#include "sound.h"
#include "ui.h"
#include "mode.h"
#include "fade.h"

//=============================================================================
// �ÓI�����o�ϐ�������
//=============================================================================
LPDIRECT3DTEXTURE9 CGameover::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGameover::CGameover()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGameover::~CGameover()
{
}

//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
HRESULT CGameover::Load(void)
{
	CRenderer * pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_GAMEOVER, &m_pTexture);
	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h
//=============================================================================
void CGameover::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CGameover::Init()
{
	//�T�E���h�̍Đ�
	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_RESULT);

	//�Q�[���^�C�g����UI�̐���
	CUi::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CUi::TYPE_GAMEOVER);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CGameover::Uninit(void)
{
	//�T�E���h�̒�~
	CManager::GetSound()->StopSound(CSound::SOUND_LABEL_BGM_RESULT);

	//�w�肵���I�u�W�F�N�g�ȊO�̃������̊J������
	CScene::DesignationReleaseAll(CScene::OBJTYPE_FADE);
}

//=============================================================================
// �X�V����
//=============================================================================
void CGameover::Update(void)
{
	if (CManager::GetFade()->GetFadeState() == CFade::FADE_NONE)
	{
		if (CManager::GetInputKeyboard()->GetKeyTrigger(DIK_RETURN) || CManager::GetInputJoystick()->GetJoystickTrigger(CInputJoystick::BUTTON_B))
		{ //Enter�L�[�܂���B�{�^�����������Ƃ�
			//�T�E���h�̍Đ�
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_DECISION);

			//�t�F�[�h�̐���
			CManager::GetFade()->SetFade(CManager::MODE_TITLE);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CGameover::Draw(void)
{
}