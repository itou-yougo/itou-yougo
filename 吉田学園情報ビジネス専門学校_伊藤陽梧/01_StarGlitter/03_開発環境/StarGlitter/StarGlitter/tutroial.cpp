//=============================================================================
//
// �`���[�g���A���̏��� [tutroial.cpp]
// Author : �ɓ��z��
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "tutorial.h"
#include "renderer.h"
#include "player.h"
#include "input.h"
#include "sound.h"
#include "bg.h"
#include "manager.h"
#include "fade.h"
#include "gattyann.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define GATTYAN1_POS (D3DXVECTOR3(SCREEN_CENTER_X / 4, SCREEN_HEIGHT + SCREEN_CENTER_Y, 0.0f))
#define GATTYAN2_POS (D3DXVECTOR3(SCREEN_CENTER_X - SCREEN_CENTER_X / 4, -SCREEN_CENTER_Y, 0.0f))
#define GATTYAN3_POS (D3DXVECTOR3(SCREEN_CENTER_X + SCREEN_CENTER_X / 4, SCREEN_HEIGHT + SCREEN_CENTER_Y, 0.0f))
#define GATTYAN4_POS (D3DXVECTOR3(SCREEN_WIDTH - SCREEN_CENTER_X / 4, -SCREEN_CENTER_Y, 0.0f))

#define GTTYANN_SIZE (D3DXVECTOR3(432.0f, 1080.0f, 0.0f))

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CTutorial::m_pTexture;

//=============================================================================
// �`���[�g���A���N���X�̃R���X�g���N�^
//=============================================================================
CTutorial::CTutorial()
{
	m_bTrriger = false;
}

//=============================================================================
// �`���[�g���A���N���X�̃f�X�g���N�^
//=============================================================================
CTutorial::~CTutorial()
{

}

//=============================================================================
// �w�i�N���X�̃C���X�^���X����
//=============================================================================
CTutorial *CTutorial::Create()
{
	// pTitle�̃|�C���^
	CTutorial *pTutorial = NULL;

	// �������̊m��
	pTutorial = new CTutorial;

	// pTutorial��NULL����Ȃ��Ƃ�
	if (pTutorial != NULL)
	{
		// ����������
		pTutorial->Init();
	}

	// pTutorial��Ԃ�
	return pTutorial;
}

//=============================================================================
// �`���[�g���A���N���X�̏���������
//=============================================================================
HRESULT CTutorial::Init()
{
	// m_pBg�������̊m��
	CBg::Create(CBg::BGTYPE_TUTORIAL, CScene::OBJTYPE_BG);

	// �T�E���h�̒�~
	CManager::GetSound()->StopSound(CManager::GetSound()->SOUND_LABEL_TITLEBGM);
	return S_OK;
}

//=============================================================================
// �`���[�g���A���N���X�̏I������
//=============================================================================
void CTutorial::Uninit(void)
{
	// �I�u�W�F�N�g�̏I�������ƃ������̊J��
	CScene::NotFadeReleaseAll();
}

//=============================================================================
// �`���[�g���A���N���X�̍X�V����
//=============================================================================
void CTutorial::Update(void)
{
	// CInput�̃|�C���^�̃C���X�^���X�����̎󂯎��
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	CInputJoypad *pInputJoypad = CManager::GetInputJoypad();

	// �����Ă��Ȃ��Ƃ�
	if (m_bTrriger == false)
	{
		if (pInput->GetKeyboardTrigger(DIK_RETURN) && CManager::GetFade()->GetFade() == CFade::FADE_NOME)
		{
			// �K�b�`�����̐���
			CGattyann::Create(GATTYAN1_POS, GTTYANN_SIZE, CGattyann::GATTYANN_5);
			CGattyann::Create(GATTYAN2_POS, GTTYANN_SIZE, CGattyann::GATTYANN_6);
			CGattyann::Create(GATTYAN3_POS, GTTYANN_SIZE, CGattyann::GATTYANN_7);
			CGattyann::Create(GATTYAN4_POS, GTTYANN_SIZE, CGattyann::GATTYANN_8);

			// �����Ă��Ȃ��Ƃ�
			m_bTrriger = true;
		}
		else if (pInputJoypad->GetJoypadTrigger(PLAYER_1, CInputJoypad::BUTTON_START) && CManager::GetFade()->GetFade() == CFade::FADE_NOME)
		{
			// �K�b�`�����̐���
			CGattyann::Create(GATTYAN1_POS, GTTYANN_SIZE, CGattyann::GATTYANN_5);
			CGattyann::Create(GATTYAN2_POS, GTTYANN_SIZE, CGattyann::GATTYANN_6);
			CGattyann::Create(GATTYAN3_POS, GTTYANN_SIZE, CGattyann::GATTYANN_7);
			CGattyann::Create(GATTYAN4_POS, GTTYANN_SIZE, CGattyann::GATTYANN_8);

			// �����Ă��Ȃ��Ƃ�
			m_bTrriger = true;
		}
	}
}

//=============================================================================
// �`���[�g���A���N���X�̕`�揈��
//=============================================================================
void CTutorial::Draw(void)
{

}