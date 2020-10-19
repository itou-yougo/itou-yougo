//=============================================================================
//
// �|���S���̕`��̏��� [player2.h]
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
#include "ojamaplayer.h"
#include "select.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CPlayer2::m_pTexture = NULL;
int	CPlayer2::m_nDamage = 0;

//=============================================================================
// �v���C���[�N���X�̃R���X�g���N�^
//=============================================================================
CPlayer2::CPlayer2() :CScene2D(OBJTYPE_PLAYER2)
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
	m_fAngle = 0;
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
CPlayer2::~CPlayer2()
{

}

//=============================================================================
// �v���C���[�N���X�̃e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CPlayer2::Load(void)
{
	// �C���X�^���X�����������̂��󂯎��
	CRenderer *pRenderer = CManager::GetRenderer();

	// �f�o�C�X���󂯎��
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PLAYER2, &m_pTexture);

	return S_OK;
}

//=============================================================================
// �v���C���[�N���X�̃e�N�X�`���̔j��
//=============================================================================
void CPlayer2::Unload(void)
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
CPlayer2 *CPlayer2::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fSizeX, float fSizeY, int nLife, OBJTYPE objType)
{
	// CPlayer2�̃|�C���^
	CPlayer2 *pPlayer2 = NULL;

	// �������̊m��
	pPlayer2 = new CPlayer2;

	// pPlayer2��NULL����Ȃ��Ƃ�
	if (pPlayer2 != NULL)
	{
		// �v���C���[2�̃Z�b�g
		pPlayer2->SetPlayer2(pos, move, fSizeX, fSizeY, nLife, objType);

		// ����������
		pPlayer2->Init();
	}

	// pPlayer2��Ԃ�
	return pPlayer2;
}

//=============================================================================
// �v���C���[�N���X�̏���������
//=============================================================================
HRESULT CPlayer2::Init()
{
	// ���C�t�̐���
	m_pLife = CLife::Create(m_nLife, CLife::LIFE_TYPE_PLAYER2, OBJTYPE_LIFE);
	
	// �`���[�W�V���b�g�̐���
	m_pChargeShot = CChargeshot::Create(D3DXVECTOR3(PLAYER2_MOVABLE_RANGE_L - 181.0f, SCREEN_HEIGHT - 80.0f, 0.0f), 362.0f, 40.0f, CChargeshot::CHARGESHOTTYPE_PLAYER2, OBJTYPE_BG);

	// �{���̐���
	for (int nCount = 0; nCount < PLAYER2_BOMB_MAX; nCount++)
	{
		m_pBomb[nCount] = CBomb::Create(D3DXVECTOR3(SCREEN_CENTER_X + (BOMB_SIZE_X * (nCount + 1)), SCREEN_HEIGHT - BOMB_SIZE_Y, 0.0f), BOMB_SIZE_X, BOMB_SIZE_Y, CBomb::BOMB_TYPE_PLAYER2, OBJTYPE_BG);
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
void CPlayer2::Uninit(void)
{
	// CScene2D�̏I������
	CScene2D::Uninit();
}

//=============================================================================
// �v���C���[�N���X�̍X�V����
//=============================================================================
void CPlayer2::Update(void)
{
	// CScene2D�̍X�V����
	CScene2D::Update();

	// CInput�̃|�C���^�̃C���X�^���X�����̎󂯎��
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	CInputJoypad *pInputJoypad = CManager::GetInputJoypad();

	//�R���g���[���[�̏����擾����
	DIJOYSTATE2 Controller = pInputJoypad->GetController(PLAYER_2);

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
		// ��
		if (pInputKeyboard->GetKeyboardPress(DIK_UP))
		{
			// ��������Ă�Ƃ��ɉE�A�����������Ƃ�
			m_move.y -= pInputKeyboard->GetKeyboardPress(DIK_LEFT) || pInputKeyboard->GetKeyboardPress(DIK_RIGHT) ? (r / 2) : PLAYER_SPEED;
		}
		// ��
		if (pInputKeyboard->GetKeyboardPress(DIK_LEFT))
		{
			// ���������Ă�Ƃ��ɏ�A�����������Ƃ�
			m_move.x -= pInputKeyboard->GetKeyboardPress(DIK_UP) || pInputKeyboard->GetKeyboardPress(DIK_DOWN) ? (r / 2) : PLAYER_SPEED;
		}
		// ��
		if (pInputKeyboard->GetKeyboardPress(DIK_DOWN))
		{
			// ���������Ă�Ƃ��ɉE�A�����������Ƃ�
			m_move.y += pInputKeyboard->GetKeyboardPress(DIK_LEFT) || pInputKeyboard->GetKeyboardPress(DIK_RIGHT) ? (r / 2) : PLAYER_SPEED;
		}
		// �E
		if (pInputKeyboard->GetKeyboardPress(DIK_RIGHT))
		{
			// �E�������Ă�Ƃ��ɏ�A�����������Ƃ�
			m_move.x += pInputKeyboard->GetKeyboardPress(DIK_DOWN) || pInputKeyboard->GetKeyboardPress(DIK_UP) ? (r / 2) : PLAYER_SPEED;
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

		// �e�̔���
		if (pInputKeyboard->GetKeyboardRelease(DIK_NUMPADENTER) == true && m_nBulletShotCount >= 10)
		{
			switch (m_pChargeShot->GetCharge()->GetChargeType())
			{
				// �`���[�W�Ȃ�
			case CCharge::CHARGETYPE_NONE:
				// �T�E���h�̍Đ�
				CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_BULLET_SE);
				
				// �e�̐���
				CBullet::Create(m_pos, D3DXVECTOR3(0.0f, -10.0f, 0.0f), BULLET_SIZE_X, BULLET_SIZE_Y, 
					200, 1, CBullet::BULLET_TYPE_PLAYER2, CBullet::CHARGEBULLET_TYPE_NOMAL, CScene::OBJTYPE_BULLET);
				
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
				CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - LASERBULLET_SIZE_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), LASERBULLET_SIZE_X, LASERBULLET_SIZE_Y, 
					80, 10, CBullet::BULLET_TYPE_PLAYER2, CBullet::CHARGEBULLET_TYPE_LASER, CScene::OBJTYPE_BULLET);

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
				// �{�X�A�^�b�N�̐���
				CBossattck::Create(D3DXVECTOR3(PLAYER_START_POS, 300.0f, 0.0f), D3DXVECTOR3(5.0f, 0.0f, 0.0f), 
					20, CBossattck::BOSSATTCK_PLAYER2, CBossattck::BOSSATTACK_BEAM, OBJTYPE_BOSSATTACK);

				
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
		// �e�̔���
		else if (pInputJoypad->GetJoypadRelease(PLAYER_2, CInputJoypad::BUTTON_X) == true && m_nBulletShotCount >= 10)
		{
			switch (m_pChargeShot->GetCharge()->GetChargeType())
			{
				// �`���[�W�Ȃ�
			case CCharge::CHARGETYPE_NONE:
				// �T�E���h�̍Đ�
				CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_BULLET_SE);

				// �e�̐���
				CBullet::Create(m_pos, D3DXVECTOR3(0.0f, -10.0f, 0.0f), BULLET_SIZE_X, BULLET_SIZE_Y, 200, 1, CBullet::BULLET_TYPE_PLAYER2, CBullet::CHARGEBULLET_TYPE_NOMAL, CScene::OBJTYPE_BULLET);

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
				CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - LASERBULLET_SIZE_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), LASERBULLET_SIZE_X, LASERBULLET_SIZE_Y, 80, 10, CBullet::BULLET_TYPE_PLAYER2, CBullet::CHARGEBULLET_TYPE_LASER, CScene::OBJTYPE_BULLET);

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
				CManager::GetSound()->StopSound(CManager::GetSound()->SOUND_LABEL_BOSSCREATE);

				// �{�X�A�^�b�N�̐���
				CBossattck::Create(D3DXVECTOR3(PLAYER_START_POS, 300.0f, 0.0f), D3DXVECTOR3(5.0f, 0.0f, 0.0f), 20, CBossattck::BOSSATTCK_PLAYER2, CBossattck::BOSSATTACK_BEAM, OBJTYPE_BOSSATTACK);

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
		if (pInputKeyboard->GetKeyboardPress(DIK_NUMPADENTER) && m_nBulletShotCount >= 10)
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
					m_pEffect = m_pEffect->Create(D3DXVECTOR3(m_pos.x, m_pos.y - 50.0f, m_pos.x), 100.0f, 100.0f, 
						0, 255, 255, 255, 255, CEffect::EFFECTTYPE_CHARGESTATE, OBJTYPE_EFFECT);
					
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
					m_pEffect->SetPosition(D3DXVECTOR3(m_pos.x, m_pos.y - 50.0f, m_pos.x));
					m_pEffect->SetAnimationSelect(3, 3, 0, 10);
				}
				break;

				// �`���[�W1�i�K��
			case CCharge::CHARGETYPE_1:
				if (m_pEffect != NULL)
				{
					m_pEffect->SetPosition(D3DXVECTOR3(m_pos.x, m_pos.y - 50.0f, m_pos.x));
					m_pEffect->SetAnimationSelect(3, 3, 1, 10);
				}
				break;

				// �`���[�W2�i�K��(�G�L�X�g���A�^�b�N)
			case CCharge::CHARGETYPE_2:
				if (m_pEffect != NULL)
				{
					m_pEffect->SetPosition(D3DXVECTOR3(m_pos.x, m_pos.y - 50.0f, m_pos.x));
					m_pEffect->SetAnimationSelect(3, 3, 2, 10);
				}
				break;

				// �`���[�W3�i�K��(�{�X�A�^�b�N)
			case CCharge::CHARGETYPE_3:
				if (m_pEffect != NULL)
				{
					m_pEffect->SetPosition(D3DXVECTOR3(m_pos.x, m_pos.y - 50.0f, m_pos.x));
					m_pEffect->SetAnimationSelect(3, 3, 2, 10);
				}
				break;

			default:
				break;
			}
		}
		// X���������Ƃ�
		else if (pInputJoypad->GetJoypadPress(PLAYER_2, CInputJoypad::BUTTON_X) && m_nBulletShotCount >= 10)
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
		if (pInputKeyboard->GetKeyboardTrigger(DIK_NUMPAD0))
		{
			// ���̔ԍ��̃{������g���Ă���
			for (int nCount = PLAYER2_BOMB_MAX - 1; nCount > -1; nCount--)
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
		else if (pInputJoypad->GetJoypadTrigger(PLAYER_2, CInputJoypad::BUTTON_A))
		{
			for (int nCount = PLAYER2_BOMB_MAX - 1; nCount > -1; nCount--)
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

	// �G�N�X�g���A�^�b�N�������Ƃ�
	if (m_bExtraAttack == true)
	{
		//�@m_nExtraAttackCount�̉��Z
		m_nExtraAttackCount++;

		//�@m_nExtraAttackCount��8�Ŋ���鐔�̎�
		if (m_nExtraAttackCount % 8 == 0)
		{
			// �G�N�X�g���A�^�b�N����
			CExtraattck::Create(m_pos, D3DXVECTOR3(-10.0f, -10.0f, 0.0f), 50.0f, 50.0f, CExtraattck::EXTRAATTCK_PLAYER1, CExtraattck::EXTRAATTACK_NERAU, OBJTYPE_EXTRAATTACK);
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
							PlayerDamage2(1);
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

						// PLAYER�̃V�[���̎󂯎��
						pScene = GetScene(OBJTYPE_PLAYER, 0);
						if (pScene != NULL)
						{
							//�I�u�W�F�^�C�v�̎󂯎��
							OBJTYPE objType = pScene->GetObjType();
							if (objType == OBJTYPE_PLAYER)
							{
								// �v���C���[�̃��C�t����
								((CPlayer*)pScene)->PlayerAddLife(1);
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
			pScene = GetScene(OBJTYPE_OJAMA, nCntScene);
			if (pScene != NULL)
			{
				// �I�u�W�F�^�C�v�̎󂯎��
				OBJTYPE objType = pScene->GetObjType();
				if (objType == OBJTYPE_OJAMA)
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
						PlayerDamage2(1);

						// m_nHitCount�̑��
						m_nHitCount = 80;

						// �v���C���[�̏�Ԃ��_���[�W���󂯂���Ԃɂ���
						m_PlayerState = PLAYERSTATE_DAMAGE;

						// ������܂̏I������
						((COjamaplayer*)pScene)->Uninit();
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
							PlayerDamage2(1);

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
							PlayerDamage2(1);

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
				// �I�u�W�F�^�C�v�̎󂯎��
				OBJTYPE objType = pScene->GetObjType();
				if (objType == OBJTYPE_BULLET)
				{
					// �e�̃^�C�v��BULLET_TYPE_BOSS�̎�
					if (((CBullet*)pScene)->GetBulletType() == CBullet::BULLET_TYPE_BOSS)
					{
						switch (((CBullet*)pScene)->GetChargeBulletType())
						{
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
								PlayerDamage2(1);

								// m_nHitCount�̑��
								m_nHitCount = 80;

								// �v���C���[�̏�Ԃ��_���[�W���󂯂���Ԃɂ���
								m_PlayerState = PLAYERSTATE_DAMAGE;
								break;
							}
							break;

						case CBullet::CHARGEBULLET_TYPE_BOSSLASER:
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
								PlayerDamage2(1);

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
		if (m_pos.x < PLAYER2_MOVABLE_RANGE_S + (PLAYER_SIZE_X / 2))
		{
			m_move *= -1.0f;
		}
		if (m_pos.x > PLAYER2_MOVABLE_RANGE_L - (PLAYER_SIZE_X / 2))
		{
			m_move *= -1.0f;
		}
		if (m_pos.y < (PLAYER_SIZE_Y / 2))
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
	if (m_pos.x < PLAYER2_MOVABLE_RANGE_S + (PLAYER_SIZE_X / 2))
	{
		m_pos.x = PLAYER2_MOVABLE_RANGE_S + (PLAYER_SIZE_X / 2);
	}
	if (m_pos.x > PLAYER2_MOVABLE_RANGE_L - (PLAYER_SIZE_X / 2))
	{
		m_pos.x = PLAYER2_MOVABLE_RANGE_L - (PLAYER_SIZE_X / 2);
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
// �v���C���[2�N���X�̕`�揈��
//=============================================================================
void CPlayer2::Draw(void)
{
	// CScene2D�̕`�揈��
	CScene2D::Draw();
}

//=============================================================================
// �v���C���[2�N���X�̃_���[�W�̏���
//=============================================================================
void CPlayer2::PlayerDamage2(int nDamage)
{
	// �̗͂̎󂯎��ƃ_���[�W�̌v�Z�ƃZ�b�g
	m_nLife = m_pLife->GetLife();
	m_nLife -= nDamage;
	m_pLife->SetLife(m_nLife);
	m_pLife->Damage();

	// �`���[�W�����Q�[�W��������
	m_pChargeShot->GetCharge()->SetExtend(-300.0f, m_pChargeShot->GetGauge()->GetMaxExtend(), 0.0f, 0.0f);
}

//=============================================================================
// �v���C���[2�N���X�̉񕜂̏���
//=============================================================================
void CPlayer2::PlayerAddLife2(int nLife)
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
CChargeshot * CPlayer2::GetChargeShot(void)
{
	return m_pChargeShot;
}

CPlayer2::PLAYERSTATE CPlayer2::GetPlayer2State(void)
{
	return m_PlayerState;
}
