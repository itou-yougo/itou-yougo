//=============================================================================
//
// �v���C���[�̏��� [player.h]
// Author : �ɓ��z��
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "player.h"
#include "player2.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "sound.h"
#include "life.h"
#include "game.h"
#include "chargeshot.h"
#include "charge.h"
#include "gauge.h"
#include "extraattack.h"
#include "bomb.h"
#include "bossattack.h"
#include "effect.h"
#include "ojamaplayer2.h"
#include "select.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;
int	CPlayer::m_nDamage = 0;

//=============================================================================
// �v���C���[�N���X�̃R���X�g���N�^
//=============================================================================
CPlayer::CPlayer():CScene2D(OBJTYPE_PLAYER)
{
	m_pLife = NULL;
	m_pChargeShot = NULL;
	m_pEffect = NULL;
	memset(m_pBomb, 0, sizeof(m_pBomb));
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Getpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fSizeX = 0.0f;
	m_fSizeY = 0.0f;
	m_fGetSizeX = 0.0f;
	m_fGetSizeY = 0.0f;
	m_fAngle = 0.0f;
	m_nLife = 0;
	m_nBulletShotCount = 0;
	m_nHitCount = 0;
	m_nExtraAttackCount = 0;
	m_nPressTime = 0;
	m_bExtraAttack = false;
	m_bEffectCreate = true;
	m_PlayerState = PLAYERSTATE_NONE;
}

//=============================================================================
// �v���C���[�N���X�̃f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// �v���C���[�N���X�̃e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CPlayer::Load(void)
{
	// �C���X�^���X�����������̂��󂯎��
	CRenderer *pRenderer = CManager::GetRenderer();

	// �f�o�C�X���󂯎��
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PLAYER, &m_pTexture);

	return S_OK;
}

//=============================================================================
// �v���C���[�N���X�̃e�N�X�`���̔j��
//=============================================================================
void CPlayer::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}


//=============================================================================
// �v���C���[�N���X�̃C���X�^���X����
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fSizeX, float fSizeY, int nLife, OBJTYPE objType)
{
	// CPlayer�̃|�C���^
	CPlayer *pPlayer = NULL;

	// �������̊m��
	pPlayer = new CPlayer;

	// pPlayer��NULL����Ȃ��Ƃ�
	if (pPlayer != NULL)
	{
		// �v���C���[�̃Z�b�g
		pPlayer->SetPlayer(pos, move, fSizeX, fSizeY, nLife, objType);;

		// ����������
		pPlayer->Init();
	}

	// pPlayer��Ԃ�
	return pPlayer;
}

//=============================================================================
// �v���C���[�N���X�̏���������
//=============================================================================
HRESULT CPlayer::Init()
{
	// ���C�t�̐���
	m_pLife = CLife::Create(m_nLife, CLife::LIFE_TYPE_PLAYER, OBJTYPE_LIFE);
	
	// �`���[�W�V���b�g�̐���
	m_pChargeShot = CChargeshot::Create(D3DXVECTOR3(251.0f, SCREEN_HEIGHT - 80.0f, 0.0f), 362.0f, 40.0f, CChargeshot::CHARGESHOTTYPE_PLAYER, OBJTYPE_BG);

	// �{���̐���
	for (int nCount = 0; nCount < PLAYER_BOMB_MAX; nCount++)
	{
		m_pBomb[nCount] = CBomb::Create(D3DXVECTOR3(SCREEN_CENTER_X - (BOMB_SIZE_X * (nCount + 1)), SCREEN_HEIGHT - BOMB_SIZE_Y, 0.0f), BOMB_SIZE_X, BOMB_SIZE_Y, CBomb::BOMB_TYPE_PLAYER, OBJTYPE_BG);
	}

	// CScene2D�̏���������
	CScene2D::Init();

	// �e�N�X�`���̐ݒ�
	BindTexture(m_pTexture);

	srand((unsigned int)time(NULL));

	return S_OK;
}

//=============================================================================
// �v���C���[�N���X�̏I������
//=============================================================================
void CPlayer::Uninit(void)
{
	// CScene2D�̏I������
	CScene2D::Uninit();
}

//=============================================================================
// �v���C���[�N���X�̍X�V����
//=============================================================================
void CPlayer::Update(void)
{
	// CScene2D�̍X�V����
	CScene2D::Update();

	// CInput�̃|�C���^�̃C���X�^���X�����̎󂯎��
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	CInputJoypad *pInputJoypad = CManager::GetInputJoypad();

	//�R���g���[���[�̏����擾����
	DIJOYSTATE2 Controller = pInputJoypad->GetController(PLAYER_1);

	// �΂߂̂��߂̕ϐ�
	float r = 0.0f;

	// ���W���󂯎��
	m_pos = GetPosition();

	// �΂߂̈ړ��̌v�Z
	r = sqrtf((PLAYER_SPEED*PLAYER_SPEED) + (PLAYER_SPEED*PLAYER_SPEED));

	//�e�����J�E���g
	m_nBulletShotCount++;

	// �ʏ�̏�Ԃ̎�
	if (m_PlayerState == PLAYERSTATE_NOMAL)
	{
		m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �L�[�{�[�h�̑���
		//��
		if (pInputKeyboard->GetKeyboardPress(DIK_W))
		{
			// ��������Ă�Ƃ��ɉE�A�����������Ƃ�
			m_move.y -= pInputKeyboard->GetKeyboardPress(DIK_A) || pInputKeyboard->GetKeyboardPress(DIK_D) ? (r / 2) : PLAYER_SPEED;
		}
		//��
		if (pInputKeyboard->GetKeyboardPress(DIK_A))
		{
			// ���������Ă�Ƃ��ɏ�A�����������Ƃ�
			m_move.x -= pInputKeyboard->GetKeyboardPress(DIK_W) || pInputKeyboard->GetKeyboardPress(DIK_S) ? (r / 2) : PLAYER_SPEED;
		}
		//��
		if (pInputKeyboard->GetKeyboardPress(DIK_S))
		{
			// ���������Ă�Ƃ��ɉE�A�����������Ƃ�
			m_move.y += pInputKeyboard->GetKeyboardPress(DIK_A) || pInputKeyboard->GetKeyboardPress(DIK_D) ? (r / 2) : PLAYER_SPEED;
		}
		//�E
		if (pInputKeyboard->GetKeyboardPress(DIK_D))
		{
			// �E�������Ă�Ƃ��ɏ�A�����������Ƃ�
			m_move.x += pInputKeyboard->GetKeyboardPress(DIK_S) || pInputKeyboard->GetKeyboardPress(DIK_W) ? (r / 2) : PLAYER_SPEED;
		}
		// �Q�[���p�b�h�̑���
		//�X�e�B�b�N���|��Ă���Ȃ�ړ�
		if (Controller.lY != 0 || Controller.lX != 0)
		{
			//�X�e�B�b�N�̊p�x�����߂�
			float fAngle = atan2f((float)Controller.lX, (float)Controller.lY);//�X�e�B�b�N�̊p�x�����߂�

			// ���߂��p�x�̕��ɓ�����
			m_move.x = sinf(fAngle)*PLAYER_SPEED;
			m_move.y = cosf(fAngle)*PLAYER_SPEED;
		}

		// �L�[�{�[�h
		if (pInputKeyboard->GetKeyboardRelease(DIK_SPACE) == true && m_nBulletShotCount >= 10)
		{
			switch (m_pChargeShot->GetCharge()->GetChargeType())
			{
				// �`���[�W�Ȃ�
			case CCharge::CHARGETYPE_NONE:
				// �T�E���h�̍Đ�
				CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_BULLET_SE);
				
				// �e�̐���
				CBullet::Create(m_pos, D3DXVECTOR3(0.0f, -10.0f, 0.0f), BULLET_SIZE_X, BULLET_SIZE_Y, 200, 1, CBullet::BULLET_TYPE_PLAYER, CBullet::CHARGEBULLET_TYPE_NOMAL, CScene::OBJTYPE_BULLET);
				
				// m_nBulletShotCount�̏�����
				m_nBulletShotCount = 0;

				// m_pEffect��NULL����Ȃ��Ƃ�
				if (m_pEffect != NULL)
				{
					// m_pEffect�̏I������
					m_pEffect->Uninit();
					m_pEffect = NULL;
				}

				// �G�t�F�N�g���o����悤�ɂ���
				m_bEffectCreate = true;

				//�������Ԃ̏�����
				m_nPressTime = 0;
				break;

				// �`���[�W1�i�K��
			case CCharge::CHARGETYPE_1:
				// �T�E���h�̍Đ�
				CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_BULLET_SE);
				
				// �e�̐���
				CBullet::Create(m_pos, D3DXVECTOR3(0.0f, -20.0f, 0.0f), CHARGEBULLET_SIZE_X + 10.0f, CHARGEBULLET_SIZE_Y + 10.0f, 200, 10, CBullet::BULLET_TYPE_PLAYER, CBullet::CHARGEBULLET_TYPE_CHARGE, CScene::OBJTYPE_BULLET);
			
				// �`���[�W�����Q�[�W��������
				m_pChargeShot->GetCharge()->SetExtend(-300.0f, m_pChargeShot->GetGauge()->GetMaxExtend(), 0.0f, 0.0f);
				
				// m_nBulletShotCount�̏�����
				m_nBulletShotCount = 0;

				// m_pEffect��NULL����Ȃ��Ƃ�
				if (m_pEffect != NULL)
				{
					// m_pEffect�̏I������
					m_pEffect->Uninit();
					m_pEffect = NULL;
				}

				// �G�t�F�N�g���o����悤�ɂ���
				m_bEffectCreate = true;

				//�������Ԃ̏�����
				m_nPressTime = 0;
				break;

				// �`���[�W2�i�K��(�G�L�X�g���A�^�b�N)
			case CCharge::CHARGETYPE_2:
				// �T�E���h�̍Đ�
				CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_BULLET_SE);

				// �`���[�W�����Q�[�W��������
				m_pChargeShot->GetCharge()->SetExtend(-300.0f, m_pChargeShot->GetGauge()->GetMaxExtend(), 0.0f, 0.0f);
			
				// �Q�[�W�̍ő�ʂ�������
				m_pChargeShot->GetGauge()->SetExtend(-92.0f, 0.0f);

				// �G�N�X�g���A�^�b�N�𔭓�
				m_bExtraAttack = true;

				// m_nBulletShotCount�̏�����
				m_nBulletShotCount = 0;

				// m_pEffect��NULL����Ȃ��Ƃ�
				if (m_pEffect != NULL)
				{
					// m_pEffect�̏I������
					m_pEffect->Uninit();
					m_pEffect = NULL;
				}

				// �G�t�F�N�g���o����悤�ɂ���
				m_bEffectCreate = true;

				//�������Ԃ̏�����
				m_nPressTime = 0;
				break;

				// �`���[�W3�i�K��(�{�X�A�^�b�N)
			case CCharge::CHARGETYPE_3:
				// �T�E���h�̍Đ�
				CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_BULLET_SE);
				
				// �{�X�A�^�b�N�̐���
				CBossattck::Create(D3DXVECTOR3(PLAYER2_START_POS, 300.0f, 0.0f), D3DXVECTOR3(5.0f, 0.0f, 0.0f), 20, CBossattck::BOSSATTCK_PLAYER1, CBossattck::BOSSATTACK_BULLET, OBJTYPE_BOSSATTACK);

				// �`���[�W�����Q�[�W��������
				m_pChargeShot->GetCharge()->SetExtend(-300.0f, m_pChargeShot->GetGauge()->GetMaxExtend(), 0.0f, 0.0f);
				
				// �Q�[�W�̍ő�ʂ�������
				m_pChargeShot->GetGauge()->SetExtend(-184.0f, 0.0f);

				// m_nBulletShotCount�̏�����
				m_nBulletShotCount = 0;

				// m_pEffect��NULL����Ȃ��Ƃ�
				if (m_pEffect != NULL)
				{
					// m_pEffect�̏I������
					m_pEffect->Uninit();
					m_pEffect = NULL;
				}

				// �G�t�F�N�g���o����悤�ɂ���
				m_bEffectCreate = true;

				//�������Ԃ̏�����
				m_nPressTime = 0;
				break;

			default:
				break;
			}
		}
		else if (pInputJoypad->GetJoypadRelease(PLAYER_1, CInputJoypad::BUTTON_X) == true && m_nBulletShotCount >= 10)
		{
			switch (m_pChargeShot->GetCharge()->GetChargeType())
			{
				// �`���[�W�Ȃ�
			case CCharge::CHARGETYPE_NONE:
				// �T�E���h�̍Đ�
				CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_BULLET_SE);
				
				// �e�̐���
				CBullet::Create(m_pos, D3DXVECTOR3(0.0f, -10.0f, 0.0f), BULLET_SIZE_X, BULLET_SIZE_Y, 
					200, 1, CBullet::BULLET_TYPE_PLAYER, CBullet::CHARGEBULLET_TYPE_NOMAL, CScene::OBJTYPE_BULLET);
				
				// m_nBulletShotCount�̏�����
				m_nBulletShotCount = 0;

				// m_pEffect��NULL����Ȃ��Ƃ�
				if (m_pEffect != NULL)
				{
					// m_pEffect�̏I������
					m_pEffect->Uninit();
					m_pEffect = NULL;
				}

				// �G�t�F�N�g���o����悤�ɂ���
				m_bEffectCreate = true;

				//�������Ԃ̏�����
				m_nPressTime = 0;
				break;

				// �`���[�W1�i�K��
			case CCharge::CHARGETYPE_1:
				// �T�E���h�̍Đ�
				CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_CHARGESHOT);
				
				// �e�̐���
				CBullet::Create(m_pos, D3DXVECTOR3(0.0f, -20.0f, 0.0f), CHARGEBULLET_SIZE_X + 10.0f, CHARGEBULLET_SIZE_Y + 10.0f, 
					200, 10, CBullet::BULLET_TYPE_PLAYER, CBullet::CHARGEBULLET_TYPE_CHARGE, CScene::OBJTYPE_BULLET);
				
				// �`���[�W�����Q�[�W��������
				m_pChargeShot->GetCharge()->SetExtend(-300.0f, m_pChargeShot->GetGauge()->GetMaxExtend(), 0.0f, 0.0f);
				
				// m_nBulletShotCount�̏�����
				m_nBulletShotCount = 0;

				// m_pEffect��NULL����Ȃ��Ƃ�
				if (m_pEffect != NULL)
				{
					// m_pEffect�̏I������
					m_pEffect->Uninit();
					m_pEffect = NULL;
				}

				// �G�t�F�N�g���o����悤�ɂ���
				m_bEffectCreate = true;

				//�������Ԃ̏�����
				m_nPressTime = 0;
				break;

				// �`���[�W2�i�K��(�G�L�X�g���A�^�b�N)
			case CCharge::CHARGETYPE_2:
				// �T�E���h�̍Đ�
				CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_BULLET_SE);
				
				// �`���[�W�����Q�[�W��������
				m_pChargeShot->GetCharge()->SetExtend(-300.0f, m_pChargeShot->GetGauge()->GetMaxExtend(), 0.0f, 0.0f);
				
				// �Q�[�W�̍ő�ʂ�������
				m_pChargeShot->GetGauge()->SetExtend(-92.0f, 0.0f);

				// �G�N�X�g���A�^�b�N�𔭓�
				m_bExtraAttack = true;

				// m_nBulletShotCount�̏�����
				m_nBulletShotCount = 0;

				// m_pEffect��NULL����Ȃ��Ƃ�
				if (m_pEffect != NULL)
				{
					// m_pEffect�̏I������
					m_pEffect->Uninit();
					m_pEffect = NULL;
				}

				// �G�t�F�N�g���o����悤�ɂ���
				m_bEffectCreate = true;

				//�������Ԃ̏�����
				m_nPressTime = 0;
				break;

				// �`���[�W3�i�K��(�{�X�A�^�b�N)
			case CCharge::CHARGETYPE_3:
				// �T�E���h�̍Đ�
				CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_BOSSCREATE);
				
				// �{�X�A�^�b�N�̐���
				CBossattck::Create(D3DXVECTOR3(PLAYER2_START_POS, 300.0f, 0.0f), D3DXVECTOR3(5.0f, 0.0f, 0.0f), 20, CBossattck::BOSSATTCK_PLAYER1, CBossattck::BOSSATTACK_BULLET, OBJTYPE_BOSSATTACK);
				
				// �`���[�W�����Q�[�W��������
				m_pChargeShot->GetCharge()->SetExtend(-300.0f, m_pChargeShot->GetGauge()->GetMaxExtend(), 0.0f, 0.0f);
				
				// �Q�[�W�̍ő�ʂ�������
				m_pChargeShot->GetGauge()->SetExtend(-184.0f, 0.0f);

				// m_nBulletShotCount�̏�����
				m_nBulletShotCount = 0;

				// m_pEffect��NULL����Ȃ��Ƃ�
				if (m_pEffect != NULL)
				{
					// m_pEffect�̏I������
					m_pEffect->Uninit();
					m_pEffect = NULL;
				}

				// �G�t�F�N�g���o����悤�ɂ���
				m_bEffectCreate = true;

				//�������Ԃ̏�����
				m_nPressTime = 0;
				break;

			default:
				break;
			}
		}

		// NUMPADENTER���������Ƃ�
		if (pInputKeyboard->GetKeyboardPress(DIK_SPACE) && m_nBulletShotCount >= 10)
		{
			// �`���[�W���̃Q�[�W��L�΂�
			m_pChargeShot->GetCharge()->SetExtend(1.5f, m_pChargeShot->GetGauge()->GetMaxExtend(), 0.0f, 0.0f);

			// m_nPressTime�̉��Z
			m_nPressTime++;

			// m_nPressTime��10�ȏ�̎�
			if (m_nPressTime >= 10)
			{
				// �G�t�F�N�g���o�����Ԃ̎�
				if (m_bEffectCreate == true)
				{
					// �T�E���h�̍Đ�
					CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_CHARGE);

					// �G�t�F�N�g�̃N���G�C�g
					m_pEffect = m_pEffect->Create(D3DXVECTOR3(m_pos.x, m_pos.y - 50.0f, m_pos.x), 100.0f, 100.0f, 0, 255, 255, 255, 255, CEffect::EFFECTTYPE_CHARGESTATE, OBJTYPE_EFFECT);

					// �G�t�F�N�g���o���Ȃ���Ԃɂ���
					m_bEffectCreate = false;
				}
			}
			switch (m_pChargeShot->GetCharge()->GetChargeType())
			{
				// �`���[�W�Ȃ�
			case CCharge::CHARGETYPE_NONE:
				if (m_pEffect != NULL)
				{
					// �G�t�F�N�g�̍��W�̃Z�b�g�ƃA�j���[�V�����Z�b�g
					m_pEffect->SetPosition(D3DXVECTOR3(m_pos.x, m_pos.y - 50.0f, m_pos.x));
					m_pEffect->SetAnimationSelect(3, 3, 0, 10);
				}
				break;

				// �`���[�W1�i�K��
			case CCharge::CHARGETYPE_1:
				if (m_pEffect != NULL)
				{
					// �G�t�F�N�g�̍��W�̃Z�b�g�ƃA�j���[�V�����Z�b�g
					m_pEffect->SetPosition(D3DXVECTOR3(m_pos.x, m_pos.y - 50.0f, m_pos.x));
					m_pEffect->SetAnimationSelect(3, 3, 1, 10);
				}
				break;

				// �`���[�W2�i�K��(�G�L�X�g���A�^�b�N)
			case CCharge::CHARGETYPE_2:
				if (m_pEffect != NULL)
				{
					// �G�t�F�N�g�̍��W�̃Z�b�g�ƃA�j���[�V�����Z�b�g
					m_pEffect->SetPosition(D3DXVECTOR3(m_pos.x, m_pos.y - 50.0f, m_pos.x));
					m_pEffect->SetAnimationSelect(3, 3, 2, 10);
				}
				break;

				// �`���[�W3�i�K��(�{�X�A�^�b�N)
			case CCharge::CHARGETYPE_3:
				if (m_pEffect != NULL)
				{
					// �G�t�F�N�g�̍��W�̃Z�b�g�ƃA�j���[�V�����Z�b�g
					m_pEffect->SetPosition(D3DXVECTOR3(m_pos.x, m_pos.y - 50.0f, m_pos.x));
					m_pEffect->SetAnimationSelect(3, 3, 2, 10);
				}
				break;

			default:
				break;
			}
		}
		// X���������Ƃ�
		else if (pInputJoypad->GetJoypadPress(PLAYER_1, CInputJoypad::BUTTON_X) && m_nBulletShotCount >= 10)
		{
			// �`���[�W���̃Q�[�W��L�΂�
			m_pChargeShot->GetCharge()->SetExtend(1.5f, m_pChargeShot->GetGauge()->GetMaxExtend(), 0.0f, 0.0f);

			// m_nPressTime�̉��Z
			m_nPressTime++;

			// m_nPressTime��10�ȏ�̎�
			if (m_nPressTime >= 10)
			{
				// �G�t�F�N�g���o�����Ԃ̎�
				if (m_bEffectCreate == true)
				{
					// �T�E���h�̍Đ�
					CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_CHARGE);
					
					// �G�t�F�N�g�̃N���G�C�g
					m_pEffect = m_pEffect->Create(D3DXVECTOR3(m_pos.x, m_pos.y - 50.0f, m_pos.x), 100.0f, 100.0f, 0, 255, 255, 255, 255, CEffect::EFFECTTYPE_CHARGESTATE, OBJTYPE_EFFECT);
					
					// �G�t�F�N�g���o���Ȃ���Ԃɂ���
					m_bEffectCreate = false;
				}
			}
			switch (m_pChargeShot->GetCharge()->GetChargeType())
			{
				// �`���[�W�Ȃ�
			case CCharge::CHARGETYPE_NONE:
				if (m_pEffect != NULL)
				{
					// �G�t�F�N�g�̍��W�̃Z�b�g�ƃA�j���[�V�����Z�b�g
					m_pEffect->SetPosition(D3DXVECTOR3(m_pos.x, m_pos.y - 50.0f, m_pos.x));
					m_pEffect->SetAnimationSelect(3, 3, 0, 10);
				}
				break;

				// �`���[�W1�i�K��
			case CCharge::CHARGETYPE_1:
				if (m_pEffect != NULL)
				{
					// �G�t�F�N�g�̍��W�̃Z�b�g�ƃA�j���[�V�����Z�b�g
					m_pEffect->SetPosition(D3DXVECTOR3(m_pos.x, m_pos.y - 50.0f, m_pos.x));
					m_pEffect->SetAnimationSelect(3, 3, 1, 10);
				}
				break;

				// �`���[�W2�i�K��(�G�L�X�g���A�^�b�N)
			case CCharge::CHARGETYPE_2:
				if (m_pEffect != NULL)
				{
					// �G�t�F�N�g�̍��W�̃Z�b�g�ƃA�j���[�V�����Z�b�g
					m_pEffect->SetPosition(D3DXVECTOR3(m_pos.x, m_pos.y - 50.0f, m_pos.x));
					m_pEffect->SetAnimationSelect(3, 3, 2, 10);
				}
				break;

				// �`���[�W3�i�K��(�{�X�A�^�b�N)
			case CCharge::CHARGETYPE_3:
				if (m_pEffect != NULL)
				{
					// �G�t�F�N�g�̍��W�̃Z�b�g�ƃA�j���[�V�����Z�b�g
					m_pEffect->SetPosition(D3DXVECTOR3(m_pos.x, m_pos.y - 50.0f, m_pos.x));
					m_pEffect->SetAnimationSelect(3, 3, 2, 10);
				}
				break;

			default:
				break;
			}
		}
		else
		{
			// �{�^����������ĂȂ��Ƃ�
			m_pChargeShot->GetCharge()->SetExtend(-2.0f, m_pChargeShot->GetGauge()->GetMaxExtend(), 0.0f, 0.0f);
		}
	}

	// �Q�[���̏�Ԃ�GAMESTATE_START�̎�
	if (CGame::GetGameState() == CGame::GAMESTATE_START)
	{
		// �L�[�{�[�h�̑���
		// �{�����g����
		if (pInputKeyboard->GetKeyboardTrigger(DIK_B))
		{
			// ���̔ԍ��̃{������g���Ă���
			for (int nCount = PLAYER_BOMB_MAX - 1; nCount > -1; nCount--)
			{
				if (m_pBomb[nCount] != NULL)
				{
					// �{�����g����Ԃɂ���
					m_pBomb[nCount]->UseBomb();
					m_pBomb[nCount] = NULL;

					m_nHitCount = 76;
					break;
				}
			}
		}
		// �Q�[���p�b�h�̑���
		// �{�����g����
		else if (pInputJoypad->GetJoypadTrigger(PLAYER_1, CInputJoypad::BUTTON_A))
		{
			for (int nCount = PLAYER_BOMB_MAX - 1; nCount > -1; nCount--)
			{
				if (m_pBomb[nCount] != NULL)
				{
					// �{�����g����Ԃɂ���
					m_pBomb[nCount]->UseBomb();
					m_pBomb[nCount] = NULL;

					m_nHitCount = 76;
					break;
				}
			}
		}
	}

	// �G�N�X�g���A�^�b�N�𔭓������Ƃ�
	if (m_bExtraAttack == true)
	{
		//�@m_nExtraAttackCount�̉��Z
		m_nExtraAttackCount++;

		//�@m_nExtraAttackCount��8�Ŋ���鐔�̎�
		if (m_nExtraAttackCount % 8 == 0)
		{
			// �G�N�X�g���A�^�b�N����
			CExtraattck::Create(m_pos, D3DXVECTOR3(-10.0f, -10.0f, 0.0f), 50.0f, 50.0f, CExtraattck::EXTRAATTCK_PLAYER2, CExtraattck::EXTRAATTACK_TIKATIKA, OBJTYPE_EXTRAATTACK);
		}
		//�@m_nExtraAttackCount��32���傫���Ƃ�
		if (m_nExtraAttackCount >= 32)
		{
			// �G�N�X�g���A�^�b�N���I��点��
			m_bExtraAttack = false;

			//�@m_nExtraAttackCount�̏�����
			m_nExtraAttackCount = 0;
		}
	}

	// �G�ɓ������ăJ�E���g����������
	if (m_nHitCount > 0)
	{
		// �_�ł�����
		SetTransparency(true);

		// m_nHitCount�̌��Z
		m_nHitCount--;
	}
	
	//�����蔻��
	for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
	{
		// m_nHitCount��0�̎�
		if (m_nHitCount == 0)
		{
			// �_�ł����Ȃ�
			SetTransparency(false);

			// �v���C���[�̏�Ԃ��m�[�}���ɂ���
			m_PlayerState = PLAYERSTATE_NOMAL;

			// �G�ɓ��������Ƃ�
			CScene *pScene = GetScene(OBJTYPE_ENEMY, nCntScene);
			if (pScene != NULL)
			{
				// �I�u�W�F�^�C�v�̎󂯎��
				OBJTYPE objType = pScene->GetObjType();
				if (objType == OBJTYPE_ENEMY)
				{
					// ���W��T�C�Y�̎󂯎��
					m_Getpos = ((CScene2D*)pScene)->GetPosition();
					m_fGetSizeX = ((CScene2D*)pScene)->GetSizeX();
					m_fGetSizeY = ((CScene2D*)pScene)->GetSizeY();

					// �����蔻��
					if (m_pos.x - (m_fSizeX / 2) <= m_Getpos.x + (m_fGetSizeX / 2) &&
						m_pos.x + (m_fSizeX / 2) >= m_Getpos.x - (m_fGetSizeX / 2) &&
						m_pos.y - (m_fSizeY / 2) <= m_Getpos.y + (m_fGetSizeY / 2) &&
						m_pos.y + (m_fSizeY / 2) >= m_Getpos.y - (m_fGetSizeY / 2))
					{
						if (m_nLife > 1)
						{
							// �v���C���[�̃_���[�W
							PlayerDamage(1);
						}

						if (m_move == D3DXVECTOR3(0.0f, 0.0f, 0.0f))
						{
							// �m�b�N�o�b�N�̊p�x�ƈړ��ʂ̌v�Z
							m_fAngle = (float)(rand() % (int)((D3DX_PI * 2) * 100));
							m_move.x = cosf(m_fAngle) * PLAYER_SPEED * 3.0f;
							m_move.y = sinf(m_fAngle) * PLAYER_SPEED * 3.0f;
						}
						else
						{
							m_move *= -3.0f;
						}

						// PLAYER2�̃V�[���̎󂯎��
						pScene = GetScene(OBJTYPE_PLAYER2, 0);
						if (pScene != NULL)
						{
							//�I�u�W�F�^�C�v�̎󂯎��
							OBJTYPE objType = pScene->GetObjType();
							if (objType == OBJTYPE_PLAYER2)
							{
								// �v���C���[2�̃��C�t����
								((CPlayer2*)pScene)->PlayerAddLife2(1);
							}
						}

						// m_nHitCount�̑��
						m_nHitCount = 80;

						// �v���C���[�̏�Ԃ��_���[�W���󂯂���Ԃɂ���
						m_PlayerState = PLAYERSTATE_DAMAGE;
						break;
					}
				}
			}

			// ������܂ɓ��������Ƃ�
			pScene = GetScene(OBJTYPE_OJAMA2, nCntScene);
			if (pScene != NULL)
			{
				// �I�u�W�F�^�C�v�̎󂯎��
				OBJTYPE objType = pScene->GetObjType();
				if (objType == OBJTYPE_OJAMA2)
				{
					// ���W��T�C�Y�̎󂯎��
					m_Getpos = ((CScene2D*)pScene)->GetPosition();
					m_fGetSizeX = ((CScene2D*)pScene)->GetSizeX();
					m_fGetSizeY = ((CScene2D*)pScene)->GetSizeY();

					// �����蔻��
					if (m_pos.x - (m_fSizeX / 2) <= m_Getpos.x + (m_fGetSizeX / 2) &&
						m_pos.x + (m_fSizeX / 2) >= m_Getpos.x - (m_fGetSizeX / 2) &&
						m_pos.y - (m_fSizeY / 2) <= m_Getpos.y + (m_fGetSizeY / 2) &&
						m_pos.y + (m_fSizeY / 2) >= m_Getpos.y - (m_fGetSizeY / 2))
					{
						// �v���C���[�̃_���[�W
						PlayerDamage(1);

						// m_nHitCount�̑��
						m_nHitCount = 80;

						// �v���C���[�̏�Ԃ��_���[�W���󂯂���Ԃɂ���
						m_PlayerState = PLAYERSTATE_DAMAGE;

						// ������܂̏I������
						((COjamaplayer2*)pScene)->Uninit();
						break;
					}
				}
			}

			// �G�N�X�g���A�^�b�N�ɓ��������Ƃ�
			pScene = GetScene(OBJTYPE_EXTRAATTACK, nCntScene);
			if (pScene != NULL)
			{
				// �I�u�W�F�^�C�v�̎󂯎��
				OBJTYPE objType = pScene->GetObjType();
				if (objType == OBJTYPE_EXTRAATTACK)
				{
					switch (((CExtraattck*)pScene)->GetExtraAttack())
					{
						// ��������G�N�X�g���A�^�b�N
					case CExtraattck::EXTRAATTACK_EXPLOSION:
						// ���W��T�C�Y�̎󂯎��
						m_Getpos = ((CScene2D*)pScene)->GetPosition();
						m_fGetSizeX = ((CScene2D*)pScene)->GetSizeX();
						m_fGetSizeY = ((CScene2D*)pScene)->GetSizeY();

						// �����蔻��
						if (m_pos.x - (m_fSizeX / 2) <= m_Getpos.x + (m_fGetSizeX / 2) &&
							m_pos.x + (m_fSizeX / 2) >= m_Getpos.x - (m_fGetSizeX / 2) &&
							m_pos.y - (m_fSizeY / 2) <= m_Getpos.y + (m_fGetSizeY / 2) &&
							m_pos.y + (m_fSizeY / 2) >= m_Getpos.y - (m_fGetSizeY / 2))
						{
							// �v���C���[�̃_���[�W
							PlayerDamage(1);

							// m_nHitCount�̑��
							m_nHitCount = 80;

							// �v���C���[�̏�Ԃ��_���[�W���󂯂���Ԃɂ���
							m_PlayerState = PLAYERSTATE_DAMAGE;
							break;
						}
						break;

						// ��ɂ�����G�N�X�g���A�^�b�N
					case CExtraattck::EXTRAATTACK_LOCKET:
						// ���W��T�C�Y�̎󂯎��
						m_Getpos = ((CScene2D*)pScene)->GetPosition();
						m_fGetSizeX = ((CScene2D*)pScene)->GetSizeX();
						m_fGetSizeY = ((CScene2D*)pScene)->GetSizeY();

						// �����蔻��
						if (m_pos.x - (m_fSizeX / 2) <= m_Getpos.x + (m_fGetSizeX / 2) &&
							m_pos.x + (m_fSizeX / 2) >= m_Getpos.x - (m_fGetSizeX / 2) &&
							m_pos.y - (m_fSizeY / 2) <= m_Getpos.y + (m_fGetSizeY / 2) &&
							m_pos.y + (m_fSizeY / 2) >= m_Getpos.y - (m_fGetSizeY / 2))
						{
							// �v���C���[�̃_���[�W
							PlayerDamage(1);

							// m_nHitCount�̑��
							m_nHitCount = 80;

							// �v���C���[�̏�Ԃ��_���[�W���󂯂���Ԃɂ���
							m_PlayerState = PLAYERSTATE_DAMAGE;
							break;
						}
						break;

					default:
						break;
					}
				}
			}


			// �{�X�A�^�b�N�ɓ��������Ƃ�
			pScene = GetScene(OBJTYPE_BULLET, nCntScene);
			if (pScene != NULL)
			{
				OBJTYPE objType = pScene->GetObjType();
				if (objType == OBJTYPE_BULLET)
				{
					// �e�̃^�C�v��BULLET_TYPE_BOSS�̎�
					if (((CBullet*)pScene)->GetBulletType() == CBullet::BULLET_TYPE_BOSS)
					{
						switch (((CBullet*)pScene)->GetChargeBulletType())
						{
							// ���ʂ̒e
						case CBullet::CHARGEBULLET_TYPE_NOMAL:
							// ���W��T�C�Y�̎󂯎��
							m_Getpos = ((CScene2D*)pScene)->GetPosition();
							m_fGetSizeX = ((CScene2D*)pScene)->GetSizeX();
							m_fGetSizeY = ((CScene2D*)pScene)->GetSizeY();

							// �����蔻��
							if (m_pos.x - (m_fSizeX / 2) <= m_Getpos.x + (m_fGetSizeX / 2) &&
								m_pos.x + (m_fSizeX / 2) >= m_Getpos.x - (m_fGetSizeX / 2) &&
								m_pos.y - (m_fSizeY / 2) <= m_Getpos.y + (m_fGetSizeY / 2) &&
								m_pos.y + (m_fSizeY / 2) >= m_Getpos.y - (m_fGetSizeY / 2))
							{
								// �v���C���[�̃_���[�W
								PlayerDamage(1);

								// m_nHitCount�̑��
								m_nHitCount = 80;

								// �v���C���[�̏�Ԃ��_���[�W���󂯂���Ԃɂ���
								m_PlayerState = PLAYERSTATE_DAMAGE;
								break;
							}
							break;

							// �{�X�̃��[�U�[�e
						case CBullet::CHARGEBULLET_TYPE_BOSSLASER:
							// ���W��T�C�Y�̎󂯎��
							m_Getpos = ((CScene2D*)pScene)->GetPosition();
							m_fGetSizeX = ((CScene2D*)pScene)->GetSizeX();
							m_fGetSizeY = ((CScene2D*)pScene)->GetSizeY();

							// �����蔻��
							if (m_pos.x - (m_fSizeX / 2) <= m_Getpos.x + (m_fGetSizeX / 2) &&
								m_pos.x + (m_fSizeX / 2) >= m_Getpos.x - (m_fGetSizeX / 2) &&
								m_pos.y - (m_fSizeY / 2) <= m_Getpos.y + (m_fGetSizeY / 2) &&
								m_pos.y + (m_fSizeY / 2) >= m_Getpos.y - (m_fGetSizeY / 2))
							{
								// �v���C���[�̃_���[�W
								PlayerDamage(1);

								// m_nHitCount�̑��
								m_nHitCount = 80;

								// �v���C���[�̏�Ԃ��_���[�W���󂯂���Ԃɂ���
								m_PlayerState = PLAYERSTATE_DAMAGE;
								break;
							}
							break;

						default:
							break;
						}
					}
				}
			}
		}
	}

	// �_���[�W���󂯂���
	if (m_nDamage > 0)
	{
		m_nLife -= m_nDamage;
		m_nDamage = 0;
	}

	m_pos += m_move;

	// �_���[�W���󂯂���Ԃ̎�
	if (m_PlayerState == PLAYERSTATE_DAMAGE)
	{
		// �ړ��ʂ����炷
		if (m_move.x < 0.0f)
		{
			m_move.x += (m_move.x / 10) * -1.0f;
		}
		else if (m_move.x > 0.0f)
		{
			m_move.x -= m_move.x / 10;
		}
		if (m_move.y < 0.0f)
		{
			m_move.y += (m_move.y / 10) * -1.0f;
		}
		else if (m_move.y > 0.0f)
		{
			m_move.y -= m_move.y / 10;
		}

		// �ړ��ʂ�0�ɂȂ�悤�ɂ���
		if (m_move.y == 0.0f)
		{
			m_move.y = 0.0f;
		}
		if (m_move.x == 0.0f)
		{
			m_move.x = 0.0f;
		}

		// �ǂɓ��������甽�˂���悤�ɂ���
		if (m_pos.x < PLAYER_MOVABLE_RANGE_S + (PLAYER_SIZE_X / 2))
		{
			m_move *= -1.0f;
		}
		if (m_pos.x > PLAYER_MOVABLE_RANGE_L - (PLAYER_SIZE_X / 2))
		{
			m_move *= -1.0f;
		}
		if (m_pos.y < 0 + (PLAYER_SIZE_Y / 2))
		{
			m_move *= -1.0f;
		}
		if (m_pos.y > SCREEN_HEIGHT - (PLAYER_SIZE_Y / 2))
		{
			m_move *= -1.0f;
		}

		// m_pEffect��NULL����Ȃ��Ƃ�
		if (m_pEffect != NULL)
		{
			// m_pEffect�̏I������
			m_pEffect->Uninit();
			m_pEffect = NULL;
		}

		// �G�t�F�N�g���o����悤�ɂ���
		m_bEffectCreate = true;

		// m_nPressTime�̏�����
		m_nPressTime = 0;
	}

	// �ړ��ł���͈͂̐���
	if (m_pos.x < PLAYER_MOVABLE_RANGE_S + (PLAYER_SIZE_X / 2))
	{
		m_pos.x = PLAYER_MOVABLE_RANGE_S + (PLAYER_SIZE_X / 2);
	}
	if (m_pos.x > PLAYER_MOVABLE_RANGE_L - (PLAYER_SIZE_X / 2))
	{
		m_pos.x = PLAYER_MOVABLE_RANGE_L - (PLAYER_SIZE_X / 2);
	}
	if (m_pos.y < 0 + (PLAYER_SIZE_Y / 2))
	{
		m_pos.y = 0 + (PLAYER_SIZE_Y / 2);
	}
	if (m_pos.y > SCREEN_HEIGHT - (PLAYER_SIZE_Y / 2))
	{
		m_pos.y = SCREEN_HEIGHT - (PLAYER_SIZE_Y / 2);
	}

	// ���W�ƃT�C�Y��n��
	SetPosition(m_pos);
	SetSize(m_fSizeX, m_fSizeY);	

	// ��������Ԃ���Ȃ��Ƃ�
	if (m_PlayerState != PLAYERSTATE_LOSE)
	{
		// �̗͂�0�ȉ��ɂȂ����Ƃ�
		if (m_nLife <= 0)
		{
			// ���g�𕉂�����Ԃɂ���
			m_PlayerState = PLAYERSTATE_LOSE;

			// �Q�[���̏�Ԃ��I��点��
			CGame::SetGameState(CGame::GAMESTATE_END);
		}
	}
}

//=============================================================================
// �v���C���[�N���X�̕`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	// CScene2D�̕`�揈��
	CScene2D::Draw();
}

//=============================================================================
// �v���C���[�N���X�̃_���[�W�̏���
//=============================================================================
void CPlayer::PlayerDamage(int nDamage)
{
	// �̗͂̎󂯎��ƃ_���[�W�̌v�Z�ƃZ�b�g
	if (m_pLife != NULL)
	{
		m_nLife = m_pLife->GetLife();
		m_nLife -= nDamage;
		m_pLife->SetLife(m_nLife);
		m_pLife->Damage();
	}

	// �`���[�W�����Q�[�W��������
	m_pChargeShot->GetCharge()->SetExtend(-300.0f, m_pChargeShot->GetGauge()->GetMaxExtend(), 0.0f, 0.0f);
}

//=============================================================================
// �v���C���[�N���X�̉񕜂̏���
//=============================================================================
void CPlayer::PlayerAddLife(int nLife)
{
	// �̗͂̎󂯎��
	m_nLife = m_pLife->GetLife();

	// m_nLife��PLAYER_LIFE��菭�Ȃ��Ƃ�
	if (m_nLife < PLAYER_LIFE)
	{
		// ���C�t�̉��Z�ƃZ�b�g
		m_nLife += nLife;
		m_pLife->SetLife(m_nLife);
		m_pLife->Cure();
	}
}

//=============================================================================
// �v���C���[�N���X�̃`���[�W�V���b�g�|�C���^��Ԃ�����
//=============================================================================
CChargeshot* CPlayer::GetChargeShot(void)
{
	return m_pChargeShot;
}

//=============================================================================
// �v���C���[�N���X�̂��v���C���[�̏�Ԃ�Ԃ�����
//=============================================================================
CPlayer::PLAYERSTATE CPlayer::GetPlayerState(void)
{
	return m_PlayerState;
}
