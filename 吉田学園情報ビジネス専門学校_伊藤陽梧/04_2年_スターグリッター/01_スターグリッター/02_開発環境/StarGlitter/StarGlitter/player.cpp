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
#include "ojama.h"
#include "select.h"
#include "collision.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CPlayer::m_apTexture[PLAYER_MAX] = {};
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
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_GetSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fAngle = 0.0f;
	m_nLife = 0;
	m_nBulletShotCount = 0;
	m_nInvincibleTime = 0;
	m_nRigorTime = 0;
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
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PLAYER, &m_apTexture[PLAYER_1P]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PLAYER2, &m_apTexture[PLAYER_2P]);

	return S_OK;
}

//=============================================================================
// �v���C���[�N���X�̃e�N�X�`���̔j��
//=============================================================================
void CPlayer::Unload(void)
{
	for (int nCount = 0; nCount < PLAYER_MAX; nCount++)
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
// �v���C���[�N���X�̃C���X�^���X����
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nLife, PLAYERNUM PlayerNum, OBJTYPE objType)
{
	// CPlayer�̃|�C���^
	CPlayer *pPlayer = NULL;

	// �������̊m��
	pPlayer = new CPlayer;

	// pPlayer��NULL����Ȃ��Ƃ�
	if (pPlayer != NULL)
	{
		// �v���C���[�̃Z�b�g
		pPlayer->SetPlayer(pos, move, size, nLife, PlayerNum, objType);

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
	switch (m_PlayerNum)
	{
	case PLAYER_1P:
		// ���C�t�̐���
		m_pLife = CLife::Create(m_nLife, CLife::LIFE_TYPE_PLAYER, OBJTYPE_LIFE);

		// �`���[�W�V���b�g�̐���
		m_pChargeShot = CChargeshot::Create(D3DXVECTOR3(251.0f, SCREEN_HEIGHT - 80.0f, 0.0f), D3DXVECTOR3(362.0f, 40.0f, 0.0f),
			CChargeshot::CHARGESHOTTYPE_PLAYER, OBJTYPE_BG);

		// �{���̐���
		for (int nCount = 0; nCount < PLAYER_BOMB_MAX; nCount++)
		{
			m_pBomb[nCount] = CBomb::Create(D3DXVECTOR3(SCREEN_CENTER_X - (BOMB_SIZE_X * (nCount + 1)), SCREEN_HEIGHT - BOMB_SIZE_Y, 0.0f),
				D3DXVECTOR3(BOMB_SIZE_X, BOMB_SIZE_Y, 0.0f), CBomb::BOMB_TYPE_PLAYER, OBJTYPE_BG);
		}
		break;

	case PLAYER_2P:
		// ���C�t�̐���
		m_pLife = CLife::Create(m_nLife, CLife::LIFE_TYPE_PLAYER2, OBJTYPE_LIFE);

		// �`���[�W�V���b�g�̐���
		m_pChargeShot = CChargeshot::Create(D3DXVECTOR3(PLAYER2_MOVABLE_RANGE_L - 181.0f, SCREEN_HEIGHT - 80.0f, 0.0f),
			D3DXVECTOR3(362.0f, 40.0f, 0.0f), CChargeshot::CHARGESHOTTYPE_PLAYER2, OBJTYPE_BG);

		// �{���̐���
		for (int nCount = 0; nCount < PLAYER_BOMB_MAX; nCount++)
		{
			m_pBomb[nCount] = CBomb::Create(D3DXVECTOR3(SCREEN_CENTER_X + (BOMB_SIZE_X * (nCount + 1)), SCREEN_HEIGHT - BOMB_SIZE_Y, 0.0f),
				D3DXVECTOR3(BOMB_SIZE_X, BOMB_SIZE_Y, 0.0f), CBomb::BOMB_TYPE_PLAYER2, OBJTYPE_BG);
		}
		break;
	default:
		break;
	}
	

	// CScene2D�̏���������
	CScene2D::Init();

	// �e�N�X�`���̐ݒ�
	BindTexture(m_apTexture[m_PlayerNum]);

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

	// ���W���󂯎��
	m_pos = GetPosition();
	m_size = GetSize();

	//�e�����J�E���g
	m_nBulletShotCount++;

	// �ʏ�̏�Ԃ̎�
	if (m_PlayerState == PLAYERSTATE_NOMAL)
	{
		m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �Q�[���p�b�h�̏���
		GamePad();

		// �L�[�{�[�h�̏���
		keyBoard();
	}

	// �G�ɓ������ăJ�E���g����������
	if (m_nRigorTime > 0)
	{
		m_nRigorTime--;
	}

	// m_nRigorTime��0�̎�
	if (m_nRigorTime == 0)
	{
		// �v���C���[�̏�Ԃ��m�[�}���ɂ���
		m_PlayerState = PLAYERSTATE_NOMAL;
	}

	// �G�ɓ������ăJ�E���g����������
	if (m_nInvincibleTime > 0)
	{
		// �_�ł�����
		SetTransparency(true);

		// m_nInvincibleTime�̌��Z
		m_nInvincibleTime--;
	}

	// m_nInvincibleTime��0�̎�
	if (m_nInvincibleTime == 0)
	{
		// �_�ł����Ȃ�
		SetTransparency(false);

		// �G�ɓ��������Ƃ�
		HitEnemy();

		// ������܂ɓ��������Ƃ�
		HitOjama();
		
		switch (m_PlayerNum)
		{
		case PLAYER_1P:
			// �G�N�X�g���A�^�b�N�ɓ��������Ƃ�
			HitExtraAttack(CExtraattck::EXTRAATTCK_PLAYER2);
			break;

		case PLAYER_2P:
			// �G�N�X�g���A�^�b�N�ɓ��������Ƃ�
			HitExtraAttack(CExtraattck::EXTRAATTCK_PLAYER1);
			break;

		default:
			break;
		}
		
		// �{�X�A�^�b�N�ɓ��������Ƃ�
		HitBossAttack();
	
	}

	// �_���[�W���󂯂���Ԃ̎�
	if (m_PlayerState == PLAYERSTATE_DAMAGE)
	{
		// �_���[�W���󂯂���Ԃ̎��̏���
		DamageState();
	}

	m_pos += m_move;

	switch (m_PlayerNum)
	{
	case PLAYER_1P:
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
		break;

	case PLAYER_2P:
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
		break;

	default:
		break;
	}


	// ���W�ƃT�C�Y��n��
	SetPosition(m_pos);
	SetSize(m_size);	

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
// �v���C���[�N���X�̃Q�[���p�b�h�̏���
//=============================================================================
void CPlayer::GamePad(void)
{
	CInputJoypad *pInputJoypad = CManager::GetInputJoypad();

	//�R���g���[���[�̏����擾����
	DIJOYSTATE2 Controller = pInputJoypad->GetController(m_PlayerNum);

	// �ʏ�̏�Ԃ̎�
	if (m_PlayerState == PLAYERSTATE_NOMAL)
	{
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

		if (pInputJoypad->GetJoypadRelease(m_PlayerNum, CInputJoypad::BUTTON_X) == true && m_nBulletShotCount >= 10)
		{
			switch (m_pChargeShot->GetCharge()->GetChargeType())
			{
				// �`���[�W�Ȃ�
			case CCharge::CHARGETYPE_NONE:
				// �e��������
				Shot();
				break;

				// �`���[�W1�i�K��
			case CCharge::CHARGETYPE_1:
				// �`���[�W�V���b�g�̏���
				ChargeShot();
				break;

				// �`���[�W2�i�K��(�G�L�X�g���A�^�b�N)
			case CCharge::CHARGETYPE_2:
				// �G�N�X�g���A�^�b�N�̏���
				ExtraAttack();
				break;

				// �`���[�W3�i�K��(�{�X�A�^�b�N)
			case CCharge::CHARGETYPE_3:
				// �{�X�A�^�b�N�̏���
				BossAttack();
				break;

			default:
				break;
			}
		}

		// X���������Ƃ�
		if (pInputJoypad->GetJoypadPress(m_PlayerNum, CInputJoypad::BUTTON_X) && m_nBulletShotCount >= 10)
		{
			// �`���[�W���̏���
			Charging();
		}
		else
		{
			// �{�^����������ĂȂ��Ƃ�
			m_pChargeShot->GetCharge()->SetExtend(-2.0f, m_pChargeShot->GetGauge()->GetMaxExtend(), 0.0f, 0.0f);
		}

		// �Q�[���̏�Ԃ�GAMESTATE_START�̎�
		if (CGame::GetGameState() == CGame::GAMESTATE_START)
		{
			// �Q�[���p�b�h�̑���
			// �{�����g����
			if (pInputJoypad->GetJoypadTrigger(m_PlayerNum, CInputJoypad::BUTTON_A))
			{
				for (int nCount = PLAYER_BOMB_MAX - 1; nCount > -1; nCount--)
				{
					if (m_pBomb[nCount] != NULL)
					{
						// �{�����g����Ԃɂ���
						m_pBomb[nCount]->UseBomb();
						m_pBomb[nCount] = NULL;

						m_nInvincibleTime = PLAYER_INVINCIBLE;
						m_nRigorTime = PLAYER_RIGORE;
						break;
					}
				}
			}

			// �G�N�X�g���A�^�b�N�𔭓����鏈��
			ExtraAttackInvocating();
		}
	}
}

//=============================================================================
// �v���C���[�N���X�̃L�[�p�b�h�̏���
//=============================================================================
void CPlayer::keyBoard(void)
{
	// CInput�̃|�C���^�̃C���X�^���X�����̎󂯎��
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �΂߂̈ړ��̌v�Z
	float r = sqrtf((PLAYER_SPEED*PLAYER_SPEED) + (PLAYER_SPEED*PLAYER_SPEED));

	// �ʏ�̏�Ԃ̎�
	if (m_PlayerState == PLAYERSTATE_NOMAL)
	{
		switch (m_PlayerNum)
		{
		case PLAYER_1P:
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

			// �L�[�{�[�h
			if (pInputKeyboard->GetKeyboardRelease(DIK_SPACE) == true && m_nBulletShotCount >= 10)
			{
				switch (m_pChargeShot->GetCharge()->GetChargeType())
				{
					// �`���[�W�Ȃ�
				case CCharge::CHARGETYPE_NONE:
					// �e��������
					Shot();
					break;

					// �`���[�W1�i�K��
				case CCharge::CHARGETYPE_1:
					// �`���[�W�V���b�g�̏���
					ChargeShot();
					break;

					// �`���[�W2�i�K��(�G�L�X�g���A�^�b�N)
				case CCharge::CHARGETYPE_2:
					// �G�N�X�g���A�^�b�N�̏���
					ExtraAttack();
					break;

					// �`���[�W3�i�K��(�{�X�A�^�b�N)
				case CCharge::CHARGETYPE_3:
					// �{�X�A�^�b�N�̏���
					BossAttack();
					break;

				default:
					break;
				}
			}
			// NUMPADENTER���������Ƃ�
			if (pInputKeyboard->GetKeyboardPress(DIK_SPACE) && m_nBulletShotCount >= 10)
			{
				// �`���[�W���̏���
				Charging();
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

							m_nInvincibleTime = PLAYER_INVINCIBLE;
							m_nRigorTime = PLAYER_RIGORE;
							break;
						}
					}
				}
				// �G�N�X�g���A�^�b�N�𔭓����鏈��
				ExtraAttackInvocating();
			}
			break;

		case PLAYER_2P:
			// �L�[�{�[�h�̑���
			//��
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

			// �L�[�{�[�h
			if (pInputKeyboard->GetKeyboardRelease(DIK_NUMPADENTER) == true && m_nBulletShotCount >= 10)
			{
				switch (m_pChargeShot->GetCharge()->GetChargeType())
				{
					// �`���[�W�Ȃ�
				case CCharge::CHARGETYPE_NONE:
					// �e��������
					Shot();
					break;

					// �`���[�W1�i�K��
				case CCharge::CHARGETYPE_1:
					// �`���[�W�V���b�g�̏���
					ChargeShot();
					break;

					// �`���[�W2�i�K��(�G�L�X�g���A�^�b�N)
				case CCharge::CHARGETYPE_2:
					// �G�N�X�g���A�^�b�N�̏���
					ExtraAttack();
					break;

					// �`���[�W3�i�K��(�{�X�A�^�b�N)
				case CCharge::CHARGETYPE_3:
					// �{�X�A�^�b�N�̏���
					BossAttack();
					break;

				default:
					break;
				}
			}
			// NUMPADENTER���������Ƃ�
			if (pInputKeyboard->GetKeyboardPress(DIK_NUMPADENTER) && m_nBulletShotCount >= 10)
			{
				// �`���[�W���̏���
				Charging();
			}

			// �Q�[���̏�Ԃ�GAMESTATE_START�̎�
			if (CGame::GetGameState() == CGame::GAMESTATE_START)
			{
				// �L�[�{�[�h�̑���
				// �{�����g����
				if (pInputKeyboard->GetKeyboardTrigger(DIK_NUMPAD0))
				{
					// ���̔ԍ��̃{������g���Ă���
					for (int nCount = PLAYER_BOMB_MAX - 1; nCount > -1; nCount--)
					{
						if (m_pBomb[nCount] != NULL)
						{
							// �{�����g����Ԃɂ���
							m_pBomb[nCount]->UseBomb();
							m_pBomb[nCount] = NULL;

							m_nInvincibleTime = PLAYER_INVINCIBLE;
							m_nRigorTime = PLAYER_RIGORE;
							break;
						}
					}
				}
				// �G�N�X�g���A�^�b�N�𔭓����鏈��
				ExtraAttackInvocating();
			}
			break;

		default:
			break;
		}

		
	}
}

//=============================================================================
// �v���C���[�N���X�̒e�����̏���
//=============================================================================
void CPlayer::Shot(void)
{
	// �T�E���h�̍Đ�
	CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_BULLET_SE);

	switch (m_PlayerNum)
	{
	case PLAYER_1P:
		// �e�̐���
		CBullet::Create(m_pos, D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f),
			200, 1, CBullet::BULLET_TYPE_1P, CBullet::CHARGEBULLET_TYPE_NOMAL, CScene::OBJTYPE_BULLET);
		break;

	case PLAYER_2P:
		// �e�̐���
		// �e�̐���
		CBullet::Create(m_pos, D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f),
			200, 1, CBullet::BULLET_TYPE_2P, CBullet::CHARGEBULLET_TYPE_NOMAL, CScene::OBJTYPE_BULLET);
		break;
	default:
		break;
	}

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
}

//=============================================================================
// �v���C���[�N���X�̃`���[�W�V���b�g�̏���
//=============================================================================
void CPlayer::ChargeShot(void)
{
	// �T�E���h�̍Đ�
	CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_CHARGESHOT);

	switch (m_PlayerNum)
	{
	case PLAYER_1P:
		// �e�̐���
		CBullet::Create(m_pos, D3DXVECTOR3(0.0f, -20.0f, 0.0f), D3DXVECTOR3(CHARGEBULLET_SIZE_X + 10.0f, CHARGEBULLET_SIZE_Y + 10.0f, 0.0f),
			200, 10, CBullet::BULLET_TYPE_1P, CBullet::CHARGEBULLET_TYPE_CHARGE, CScene::OBJTYPE_BULLET);
		break;

	case PLAYER_2P:
		// �e�̐���
		CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - LASERBULLET_SIZE_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(LASERBULLET_SIZE_X, LASERBULLET_SIZE_Y, 0.0f), 80, 10,
			CBullet::BULLET_TYPE_2P, CBullet::CHARGEBULLET_TYPE_LASER, CScene::OBJTYPE_BULLET);
		break;
	default:
		break;
	}

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
}

//=============================================================================
// �v���C���[�N���X�̃G�N�X�g���A�^�b�N�̏���
//=============================================================================
void CPlayer::ExtraAttack(void)
{
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
}

//=============================================================================
// �v���C���[�N���X�̃{�X�A�^�b�N�̏���
//=============================================================================
void CPlayer::BossAttack(void)
{
	// �T�E���h�̍Đ�
	CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_BOSSCREATE);

	switch (m_PlayerNum)
	{
	case PLAYER_1P:
		// �{�X�A�^�b�N�̐���
		CBossattck::Create(D3DXVECTOR3(PLAYER2_START_POS, 300.0f, 0.0f), D3DXVECTOR3(5.0f, 0.0f, 0.0f), 20,
			CBossattck::BOSSATTCK_PLAYER1, CBossattck::BOSSATTACK_BULLET, OBJTYPE_BOSSATTACK);
		break;

	case PLAYER_2P:
		// �{�X�A�^�b�N�̐���
		CBossattck::Create(D3DXVECTOR3(PLAYER_START_POS, 300.0f, 0.0f), D3DXVECTOR3(5.0f, 0.0f, 0.0f), 20,
			CBossattck::BOSSATTCK_PLAYER2, CBossattck::BOSSATTACK_BEAM, OBJTYPE_BOSSATTACK);
		break;
	default:
		break;
	}

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
}

//=============================================================================
// �v���C���[�N���X�̃G�N�X�g���A�^�b�N�𔭓�����Ƃ��̏���
//=============================================================================
void CPlayer::ExtraAttackInvocating(void)
{
	// �G�N�X�g���A�^�b�N�𔭓������Ƃ�
	if (m_bExtraAttack == true)
	{
		//�@m_nExtraAttackCount�̉��Z
		m_nExtraAttackCount++;

		//�@m_nExtraAttackCount��8�Ŋ���鐔�̎�
		if (m_nExtraAttackCount % 8 == 0)
		{
			switch (m_PlayerNum)
			{
			case PLAYER_1P:
				// �G�N�X�g���A�^�b�N����
				CExtraattck::Create(m_pos, D3DXVECTOR3(-10.0f, -10.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f),
					CExtraattck::EXTRAATTCK_PLAYER1, CExtraattck::EXTRAATTACK_BLINKING, OBJTYPE_EXTRAATTACK);
				break;

			case PLAYER_2P:
				// �G�N�X�g���A�^�b�N����
				CExtraattck::Create(m_pos, D3DXVECTOR3(-10.0f, -10.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f),
					CExtraattck::EXTRAATTCK_PLAYER2, CExtraattck::EXTRAATTACK_AIM, OBJTYPE_EXTRAATTACK);
				break;
			default:
				break;
			}
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
}

//=============================================================================
// �v���C���[�N���X�̓G�ɓ��������Ƃ��̏���
//=============================================================================
void CPlayer::HitEnemy(void)
{
	// �G�ɓ��������Ƃ�
	CScene *pScene = CScene::GetSceneTop(CScene::OBJTYPE_ENEMY);

	// �v���C���[�̃V�[���̎󂯎��
	CScene *pScene2 = CScene::GetSceneTop(CScene::OBJTYPE_PLAYER);
	do
	{
		if (pScene != NULL)
		{
			// �I�u�W�F�^�C�v�̎󂯎��
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_ENEMY)
			{
				if (CCollision::PRectangleCollision(m_pos, m_size, pScene) == true)
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

					// ���C�t�̉�
					do
					{
						if (pScene2 != NULL)
						{
							//�I�u�W�F�^�C�v�̎󂯎��
							OBJTYPE objType = pScene2->GetObjType();
							if (objType == OBJTYPE_PLAYER)
							{
								switch (m_PlayerNum)
								{
								case PLAYER_1P:
									if (((CPlayer*)pScene2)->GetPlayerNum() == CPlayer::PLAYER_2P)
									{
										// �v���C���[2�̃��C�t����
										((CPlayer*)pScene2)->PlayerAddLife(1);
									}
									break;

								case PLAYER_2P:
									if (((CPlayer*)pScene2)->GetPlayerNum() == CPlayer::PLAYER_1P)
									{
										// �v���C���[2�̃��C�t����
										((CPlayer*)pScene2)->PlayerAddLife(1);
									}
									break;

								default:
									break;
								}
							}
							pScene2 = pScene2->GetSceneNext();
						}
					} while (pScene2 != NULL);

					// m_nInvincibleTime�̑��
					m_nInvincibleTime = PLAYER_INVINCIBLE;
					m_nRigorTime = PLAYER_RIGORE;

					// �v���C���[�̏�Ԃ��_���[�W���󂯂���Ԃɂ���
					m_PlayerState = PLAYERSTATE_DAMAGE;
					return;
				}
			}
			pScene = pScene->GetSceneNext();
		}
	} while (pScene != NULL);
}

//=============================================================================
// �v���C���[�N���X�̂�����܂ɓ��������Ƃ��̏���
//=============================================================================
void CPlayer::HitOjama(void)
{
	// ������܂ɓ��������Ƃ�
	CScene *pScene = CScene::GetSceneTop(CScene::OBJTYPE_OJAMA);
	do
	{
		if (pScene != NULL)
		{
			// �I�u�W�F�^�C�v�̎󂯎��
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_OJAMA)
			{
				switch (m_PlayerNum)
				{
				case PLAYER_1P:

					// �����蔻��
					if (CCollision::PRectangleCollision(m_pos, m_size, pScene) == true)
					{
						// 2P�ɂ���đ����Ă���������܂�������
						if (((COjama*)pScene)->GetOjamaPlayerNum() == COjama::OJAMAPLAYER_2P)
						{
							// �v���C���[�̃_���[�W
							PlayerDamage(1);

							// m_nInvincibleTime�̑��
							m_nInvincibleTime = PLAYER_INVINCIBLE;
							m_nRigorTime = PLAYER_RIGORE;

							// �v���C���[�̏�Ԃ��_���[�W���󂯂���Ԃɂ���
							m_PlayerState = PLAYERSTATE_DAMAGE;

							// ������܂̏I������
							((COjama*)pScene)->Uninit();
						}
						return;
					}
					break;

				case PLAYER_2P:
					// �����蔻��
					if (CCollision::PRectangleCollision(m_pos, m_size, pScene) == true)
					{
						// 1P�ɂ���đ����Ă���������܂�������
						if (((COjama*)pScene)->GetOjamaPlayerNum() == COjama::OJAMAPLAYER_1P)
						{
							// �v���C���[�̃_���[�W
							PlayerDamage(1);

							// m_nInvincibleTime�̑��
							m_nInvincibleTime = PLAYER_INVINCIBLE;
							m_nRigorTime = PLAYER_RIGORE;

							// �v���C���[�̏�Ԃ��_���[�W���󂯂���Ԃɂ���
							m_PlayerState = PLAYERSTATE_DAMAGE;

							// ������܂̏I������
							((COjama*)pScene)->Uninit();
						}
						return;
					}
					break;

				default:
					break;
				}
			}
			pScene = pScene->GetSceneNext();
		}
	} while (pScene != NULL);
}

//=============================================================================
// �v���C���[�N���X�̃G�N�X�g���A�^�b�N�ɓ��������Ƃ��̏���
//=============================================================================
void CPlayer::HitExtraAttack(CExtraattck::EXTRAATTCKPLAYERNUM ExtraAttackPlayerNum)
{
	// �G�N�X�g���A�^�b�N�ɓ��������Ƃ�
	CScene *pScene = CScene::GetSceneTop(CScene::OBJTYPE_EXTRAATTACK);
	do
	{
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
					// �����蔻��
					if (CCollision::PRectangleCollision(m_pos, m_size, pScene) == true)
					{
						if (((CExtraattck*)pScene)->GetExtraPlayerNum() == ExtraAttackPlayerNum)
						{
							// �v���C���[�̃_���[�W
							PlayerDamage(1);

							// m_nInvincibleTime�̑��
							m_nInvincibleTime = PLAYER_INVINCIBLE;
							m_nRigorTime = PLAYER_RIGORE;

							// �v���C���[�̏�Ԃ��_���[�W���󂯂���Ԃɂ���
							m_PlayerState = PLAYERSTATE_DAMAGE;
						}
						break;
					}
					break;

					// ��ɂ�����G�N�X�g���A�^�b�N
				case CExtraattck::EXTRAATTACK_LOCKET:
					// �����蔻��
					if (CCollision::PRectangleCollision(m_pos, m_size, pScene) == true)
					{
						if (((CExtraattck*)pScene)->GetExtraPlayerNum() == ExtraAttackPlayerNum)
						{
							// �v���C���[�̃_���[�W
							PlayerDamage(1);

							// m_nInvincibleTime�̑��
							m_nInvincibleTime = PLAYER_INVINCIBLE;
							m_nRigorTime = PLAYER_RIGORE;

							// �v���C���[�̏�Ԃ��_���[�W���󂯂���Ԃɂ���
							m_PlayerState = PLAYERSTATE_DAMAGE;
						}
						break;
					}
					break;

				default:
					break;
				}
			}
			pScene = pScene->GetSceneNext();
		}
	} while (pScene != NULL);
}

//=============================================================================
// �v���C���[�N���X�̃{�X�A�^�b�N�ɓ��������Ƃ��̏���
//=============================================================================
void CPlayer::HitBossAttack(void)
{
	// �{�X�A�^�b�N�ɓ��������Ƃ�
	CScene *pScene = CScene::GetSceneTop(CScene::OBJTYPE_BULLET);
	do
	{
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
						// �����蔻��
						if (CCollision::PRectangleCollision(m_pos, m_size, pScene) == true)
						{
							// �v���C���[�̃_���[�W
							PlayerDamage(1);

							// m_nInvincibleTime�̑��
							m_nInvincibleTime = PLAYER_INVINCIBLE;
							m_nRigorTime = PLAYER_RIGORE;

							// �v���C���[�̏�Ԃ��_���[�W���󂯂���Ԃɂ���
							m_PlayerState = PLAYERSTATE_DAMAGE;
							break;
						}
						break;

						// �{�X�̃��[�U�[�e
					case CBullet::CHARGEBULLET_TYPE_BOSSLASER:
						// �����蔻��
						if (CCollision::PRectangleCollision(m_pos, m_size, pScene) == true)
						{
							// �v���C���[�̃_���[�W
							PlayerDamage(1);

							// m_nInvincibleTime�̑��
							m_nInvincibleTime = PLAYER_INVINCIBLE;
							m_nRigorTime = PLAYER_RIGORE;

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
			pScene = pScene->GetSceneNext();
		}
	} while (pScene != NULL);
}

//=============================================================================
// �v���C���[�N���X�̃_���[�W��Ԃ̂Ƃ��̏���
//=============================================================================
void CPlayer::DamageState(void)
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

	switch (m_PlayerNum)
	{
	case PLAYER_1P:
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
		break;

	case PLAYER_2P:
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
		break;

	default:
		break;
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

	// �_���[�W���󂯂���
	if (m_nDamage > 0)
	{
		m_nLife -= m_nDamage;
		m_nDamage = 0;
	}
}

//=============================================================================
// �v���C���[�N���X�̃`���[�W���̏���
//=============================================================================
void CPlayer::Charging(void)
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
			m_pEffect = m_pEffect->Create(D3DXVECTOR3(m_pos.x, m_pos.y - 50.0f, m_pos.x), D3DXVECTOR3(100.0f, 100.0f, 0.0f),
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

//=============================================================================
// �v���C���[�N���X�̂��v���C���[�ԍ���Ԃ�����
//=============================================================================
CPlayer::PLAYERNUM CPlayer::GetPlayerNum(void)
{
	return m_PlayerNum;
}
