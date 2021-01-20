//=============================================================================
//
// �G�N�X�g���A�^�b�N�̏��� [extraattack.cpp]
// Author : �ɓ��z��
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "extraattack.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "explosion.h"
#include "enemy.h"
#include "life.h"
#include "effect.h"
#include "bullet.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define EXPLOSION_SIZE_X (100.0f)			// �����̏c�̒���
#define EXPLOSION_SIZE_Y (100.0f)			// �����̉��̒���

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CExtraattck::m_pTexture[MAX_EXTRAATTACK_TEXTURE] = {};

//=============================================================================
// �G�N�X�g���A�^�b�N�N���X�̃R���X�g���N�^
//=============================================================================
CExtraattck::CExtraattck() :CScene2D(OBJTYPE_EXTRAATTACK)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Getpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCountColor = 0;
	m_ExtraPlayerNum = EXTRAATTCK_PLAYER_NONE;
	m_ExtraAttack = EXTRAATTACK_NONE;
}

//=============================================================================
// �G�N�X�g���A�^�b�N�N���X�̃f�X�g���N�^
//=============================================================================
CExtraattck::~CExtraattck()
{

}

//=============================================================================
// �G�N�X�g���A�^�b�N�N���X�̃e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CExtraattck::Load(void)
{
	// �C���X�^���X�����������̂��󂯎��
	CRenderer *pRenderer = CManager::GetRenderer();

	// �f�o�C�X���󂯎��
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_TIKATIKA, &m_pTexture[0]);		// �`�J�`�J���Ȃ��瑊��̕��ɍs���G�N�X�g���A�^�b�N
	D3DXCreateTextureFromFile(pDevice, TEXTURE_OBAKE, &m_pTexture[1]);			// �����_���G�N�X�g���A�^�b�N
	D3DXCreateTextureFromFile(pDevice, TEXTURE_EXTRAEXPLOSION, &m_pTexture[2]);	// ��������G�N�X�g���A�^�b�N
	D3DXCreateTextureFromFile(pDevice, TEXTURE_HONE, &m_pTexture[3]);			// ��ɂ�����G�N�X�g���A�^�b�N

	return S_OK;
}

//=============================================================================
// �G�N�X�g���A�^�b�N�N���X�̃e�N�X�`���̔j��
//=============================================================================
void CExtraattck::Unload(void)
{
	for (int nCount = 0; nCount < MAX_EXTRAATTACK_TEXTURE; nCount++)
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
// �G�N�X�g���A�^�b�N�N���X�̃C���X�^���X����
//=============================================================================
CExtraattck* CExtraattck::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, EXTRAATTCKPLAYERNUM Player, EXTRAATTACK Extraattack, OBJTYPE objType)
{
	// CExtraattck�̃|�C���^
	CExtraattck *pExtraattck = NULL;

	// �������̊m��
	pExtraattck = new CExtraattck;

	// pExtraattck��NULL����Ȃ��Ƃ�
	if (pExtraattck != NULL)
	{
		// �G�N�X�g���A�^�b�N�̃Z�b�g
		pExtraattck->SetExtraAttack(pos, move, size, Player, Extraattack, objType);

		// ����������
		pExtraattck->Init();
	}

	// pExtraattck��Ԃ�
	return pExtraattck;
}

//=============================================================================
// �G�N�X�g���A�^�b�N�N���X�̏���������
//=============================================================================
HRESULT CExtraattck::Init()
{
	// CScene2D�̏���������
	CScene2D::Init();

	//�v���C���[�̃V�[���̃Q�b�g
	CScene *pScene = CScene::GetSceneTop(CScene::OBJTYPE_PLAYER);

	switch (m_ExtraAttack)
	{
		// �`�J�`�J���Ȃ��瑊��̕��ɍs���G�N�X�g���A�^�b�N
	case EXTRAATTACK_BLINKING:
		// �e�N�X�`���̐ݒ�
		BindTexture(m_pTexture[0]);

		// �v���C���[1�̃G�N�X�g���A�^�b�N�̎�
		if (m_ExtraPlayerNum == EXTRAATTCK_PLAYER1)
		{
			// ���W�̐ݒ�
			m_Getpos.x = (float)(rand() % 745) + PLAYER2_MOVABLE_RANGE_S;
			m_Getpos.y = 1000.0f;
		}
		// �v���C���[2�̃G�N�X�g���A�^�b�N�̎�
		if (m_ExtraPlayerNum == EXTRAATTCK_PLAYER2)
		{
			// ���W�̐ݒ�
			m_Getpos.x = (float)(rand() % 745) + PLAYER_MOVABLE_RANGE_S;
			m_Getpos.y = 1000.0f;
		}
		break;

		// �����_���G�N�X�g���A�^�b�N
	case EXTRAATTACK_AIM:
		// �e�N�X�`���̐ݒ�
		BindTexture(m_pTexture[1]);
		// �A�j���[�V�����̃Z�b�g
		SetAnimation(4, 1, 10);

		do
		{
			if (pScene != NULL)
			{
				OBJTYPE objType = pScene->GetObjType();
				if (objType == OBJTYPE_PLAYER)
				{
					switch (m_ExtraPlayerNum)
					{
					case EXTRAATTCK_PLAYER1:

						// 2P�̍��W���~����
						if (((CPlayer*)pScene)->GetPlayerNum() == CPlayer::PLAYER_2P)
						{
							// ���W���󂯎��
							m_Getpos = ((CScene2D*)pScene)->GetPosition();
						}
						break;

					case EXTRAATTCK_PLAYER2:

						// 1P�̍��W���~����
						if (((CPlayer*)pScene)->GetPlayerNum() == CPlayer::PLAYER_1P)
						{
							// ���W���󂯎��
							m_Getpos = ((CScene2D*)pScene)->GetPosition();
						}
						break;

					default:
						break;
					}

				}
				pScene = pScene->GetSceneNext();
			}
		} while (pScene != NULL);
		break;

		// ��������G�N�X�g���A�^�b�N
	case EXTRAATTACK_EXPLOSION:
		// �e�N�X�`���̐ݒ�
		BindTexture(m_pTexture[2]);
		// �A�j���[�V�����̃Z�b�g
		SetAnimation(2, 1, 1);
		break;

		// ��ɂ�����G�N�X�g���A�^�b�N
	case EXTRAATTACK_LOCKET:
		// �e�N�X�`���̐ݒ�
		BindTexture(m_pTexture[3]);
		// �A�j���[�V�����̃Z�b�g
		SetAnimation(3, 1, 10);
		break;

	default:
		break;
	}

	return S_OK;
}

//=============================================================================
// �G�N�X�g���A�^�b�N�N���X�̏I������
//=============================================================================
void CExtraattck::Uninit(void)
{
	// CScene2D�̏I������
	CScene2D::Uninit();
}

//=============================================================================
// �G�N�X�g���A�^�b�N�N���X�̍X�V����
//=============================================================================
void CExtraattck::Update(void)
{
	// CScene2D�̍X�V����
	CScene2D::Update();

	// ���W�Ƒ̗͂̎󂯎��
	m_pos = GetPosition();

	switch (m_ExtraAttack)
	{
		// �`�J�`�J���Ȃ��瑊��̕��ɍs���G�N�X�g���A�^�b�N
	case EXTRAATTACK_BLINKING:
		Blinking();
		break;

		// �����_���G�N�X�g���A�^�b�N
	case EXTRAATTACK_AIM:
		Aim();
		break;

		// ��������G�N�X�g���A�^�b�N
	case EXTRAATTACK_EXPLOSION:
		Explosion();
		break;

		// ��ɂ�����G�N�X�g���A�^�b�N
	case EXTRAATTACK_LOCKET:
		Locket();
		break;

	default:
		break;
	}

	// ���W�ƃT�C�Y�A�̗͂�n��
	SetPosition(m_pos);
	SetSize(m_size);
}

//=============================================================================
// �G�N�X�g���A�^�b�N�N���X�̕`�揈��
//=============================================================================
void CExtraattck::Draw(void)
{
	// CScene2D�̕`�揈��
	CScene2D::Draw();
}

//=============================================================================
// �G�N�X�g���A�^�b�N�N���X�̃`�J�`�J����G�N�X�g���A�^�b�N�̏���
//=============================================================================
void CExtraattck::Blinking(void)
{
	// �ړ��ʂ̉��Z
	m_pos += m_move;

	// �p�x�̌v�Z
	m_fAngle = atan2f(m_pos.x - m_Getpos.x, m_pos.y - m_Getpos.y);

	// ���߂��p�x�̕��ɔ�΂�
	m_move.x = sinf(m_fAngle) * -10.0f;
	m_move.y = cosf(m_fAngle) * -10.0f;

	// �F�̃J�E���g��0�̎�
	if (m_nCountColor == 0)
	{
		// �F�̃Z�b�g
		SetColor(0, 0, 255, 255);
		m_nCountColor++;
	}
	// �F�̃J�E���g��1�̎�
	else if (m_nCountColor == 1)
	{
		// �F�̃Z�b�g
		SetColor(255, 255, 255, 255);
		m_nCountColor = 0;
	}

	switch (m_ExtraPlayerNum)
	{
		// �v���C���[1�̃G�N�X�g���A�^�b�N
	case EXTRAATTCK_PLAYER1:
		if (m_pos.x >= m_Getpos.x)
		{
			// �G�N�X�g���A�^�b�N�̐���
			Create(m_pos, D3DXVECTOR3(0.0f, -5.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f),
				EXTRAATTCK_PLAYER1, EXTRAATTACK_LOCKET, OBJTYPE_EXTRAATTACK);

			// �I������
			Uninit();
			return;
		}
		break;

		// �v���C���[2�̃G�N�X�g���A�^�b�N
	case EXTRAATTCK_PLAYER2:
		if (m_pos.x <= m_Getpos.x)
		{
			// �G�N�X�g���A�^�b�N�̐���
			Create(m_pos, D3DXVECTOR3(0.0f, -5.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f),
				EXTRAATTCK_PLAYER2, EXTRAATTACK_LOCKET, OBJTYPE_EXTRAATTACK);

			// �I������
			Uninit();
			return;
		}
		break;

	default:
		break;
	}
}

//=============================================================================
// �G�N�X�g���A�^�b�N�N���X�̑����_���G�N�X�g���A�^�b�N�̏���
//=============================================================================
void CExtraattck::Aim(void)
{
	// �ړ��ʂ̉��Z
	m_pos += m_move;

	// �p�x�̌v�Z
	m_fAngle = atan2f(m_pos.x - m_Getpos.x, m_pos.y - m_Getpos.y);

	// ���߂��p�x�̕��ɔ�΂�
	m_move.x = sinf(m_fAngle) * -10;
	m_move.y = cosf(m_fAngle) * -10;

	switch (m_ExtraPlayerNum)
	{
		// �v���C���[1�̃G�N�X�g���A�^�b�N
	case EXTRAATTCK_PLAYER1:
		if (m_pos.x >= m_Getpos.x)
		{
			// �G�N�X�g���A�^�b�N�̐���
			Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f),
				EXTRAATTCK_PLAYER1, EXTRAATTACK_EXPLOSION, OBJTYPE_EXTRAATTACK);

			// �I������
			Uninit();
			return;
		}
		break;

		// �v���C���[2�̃G�N�X�g���A�^�b�N
	case EXTRAATTCK_PLAYER2:
		if (m_pos.x <= m_Getpos.x)
		{
			// �G�N�X�g���A�^�b�N�̐���
			Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f),
				EXTRAATTCK_PLAYER2, EXTRAATTACK_EXPLOSION, OBJTYPE_EXTRAATTACK);

			// �I������
			Uninit();
			return;
		}
		break;

	default:
		break;
	}
}

//=============================================================================
// �G�N�X�g���A�^�b�N�N���X�̔�������G�N�X�g���A�^�b�N�̏���
//=============================================================================
void CExtraattck::Explosion(void)
{
	// �T�C�Y�̉��Z
	m_size.x += 2.0f;
	m_size.y += 2.0f;

	// �T�C�Y��200.0f�ȏ�Ȃ�I������������
	if (m_size.x >= 200.0f && m_size.y >= 200.0f)
	{
		// �I������
		Uninit();
		return;
	}
}

//=============================================================================
// �G�N�X�g���A�^�b�N�N���X�̏�ɂ�����G�N�X�g���A�^�b�N�̏���
//=============================================================================
void CExtraattck::Locket(void)
{
	m_pos += m_move;

	// ��ʊO�ɏo����I������������
	if (m_pos.y < -(m_size.y / 2))
	{
		// �I������
		Uninit();
		return;
	}
}

//=============================================================================
// �G�N�X�g���A�^�b�N�N���X�̃G�N�X�g���A�^�b�N�̃^�C�v��n������
//=============================================================================
CExtraattck::EXTRAATTACK CExtraattck::GetExtraAttack(void)
{
	return m_ExtraAttack;
}

CExtraattck::EXTRAATTCKPLAYERNUM CExtraattck::GetExtraPlayerNum(void)
{
	return m_ExtraPlayerNum;
}


