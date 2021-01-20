//=============================================================================
//
// ������܂̏��� [ojama.cpp]
// Author : �ɓ��z��
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "ojama.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "explosion.h"
#include "enemy.h"
#include "life.h"
#include "effect.h"
#include "bullet.h"
#include "extraattack.h"
#include "enemyexplosion.h"
#include "collision.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define EXPLOSION_SIZE_X (100.0f)			// �����̏c�̒���
#define EXPLOSION_SIZE_Y (100.0f)			// �����̉��̒���

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 COjama::m_pTexture = NULL;

//=============================================================================
// ������܃v���C���[�N���X�̃R���X�g���N�^
//=============================================================================
COjama::COjama() :CScene2D(OBJTYPE_OJAMA)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Getpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_GetSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Fallpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_middle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_accele = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCount = 0;
	m_nOjamaCount = 0;
	m_fAngle = 0.0f;
	m_bFirstmove = false;
	m_bSecondmove = false;
	m_OjamaType = OJAMA_TYPE_NONE;
}

//=============================================================================
// ������܃v���C���[�N���X�̃f�X�g���N�^
//=============================================================================
COjama::~COjama()
{

}

//=============================================================================
// ������܃v���C���[�N���X�̃e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT COjama::Load(void)
{
	// �C���X�^���X�����������̂��󂯎��
	CRenderer *pRenderer = CManager::GetRenderer();

	// �f�o�C�X���󂯎��
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BULLET, &m_pTexture);

	return S_OK;
}

//=============================================================================
// ������܃v���C���[�N���X�̃e�N�X�`���̔j��
//=============================================================================
void COjama::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// ������܃v���C���[�N���X�̃C���X�^���X����
//=============================================================================
COjama* COjama::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nCount, D3DXVECTOR3 Accele, OJAMATYPE OjamaType, OJAMAPLAYERNUM OjamaPlayer, OBJTYPE objType)
{
	// COjama�̃|�C���^
	COjama *pOjamaplayer = NULL;

	// �������̊m��
	pOjamaplayer = new COjama;

	// pOjamaplayer��NULL����Ȃ��Ƃ�
	if (pOjamaplayer != NULL)
	{
		// ������܃v���C���[�̃Z�b�g
		pOjamaplayer->SetCOjama(pos, move, size, nCount, Accele, OjamaType, OjamaPlayer, objType);

		// ����������
		pOjamaplayer->Init();
	}

	// pOjamaplayer��Ԃ�
	return pOjamaplayer;
}

//=============================================================================
// ������܃v���C���[�N���X�̏���������
//=============================================================================
HRESULT COjama::Init()
{
	// CScene2D�̏���������
	CScene2D::Init();

	// �e�N�X�`���̐ݒ�
	BindTexture(m_pTexture);

	//�v���C���[�̃V�[���̃Q�b�g
	CScene *pScene = CScene::GetSceneTop(CScene::OBJTYPE_PLAYER);
	switch (m_OjamaPlayerNum)
	{
		// 1P�̂������
	case OJAMAPLAYER_1P:
		// �F�̃Z�b�g
		SetColor(255, 0, 0, 255);

		do
		{
			if (pScene != NULL)
			{
				// �I�u�W�F�^�C�v�̎󂯎��
				OBJTYPE objType = pScene->GetObjType();
				if (objType == OBJTYPE_PLAYER)
				{
					// 2P�ɓ��Ă�������̍��W�����炤
					if (((CPlayer*)pScene)->GetPlayerNum() == CPlayer::PLAYER_2P)
					{
						m_Getpos = ((CScene2D*)pScene)->GetPosition();
					}
				}
				pScene = pScene->GetSceneNext();
			}
		} while (pScene != NULL);

		switch (m_OjamaType)
		{
			// �Ȃ��邨�����
		case OJAMA_TYPE_FALL:
			// ���S�Ɗp�x�̑��
			m_middle = D3DXVECTOR3(SCREEN_CENTER_X, 50.0f, 0.0f);
			m_fAngle = atan2f(m_pos.x - m_middle.x, m_pos.y - m_middle.y);
			break;

			// �܂����������������
		case OJAMA_TYPE_CURVE:
			// ���S�̑��
			m_middle = D3DXVECTOR3(SCREEN_CENTER_X, (float)(rand() % 455) + 125.0f, 0.0f);
			break;

			// �����邨�����
		case OJAMA_TYPE_THROUGH:
			// �p�x�̌v�Z
			m_fAngle = atan2f(m_pos.x - m_Getpos.x, m_pos.y - m_Getpos.y);
			break;

		default:
			break;
		}
		break;

		// 2P�̂������
	case OJAMAPLAYER_2P:
		// �F�̃Z�b�g
		SetColor(0, 0, 255, 255);
		do
		{
			if (pScene != NULL)
			{
				// �I�u�W�F�^�C�v�̎󂯎��
				OBJTYPE objType = pScene->GetObjType();
				if (objType == OBJTYPE_PLAYER)
				{
					// 1P�ɓ��Ă�������̍��W�����炤
					if (((CPlayer*)pScene)->GetPlayerNum() == CPlayer::PLAYER_1P)
					{
						m_Getpos = ((CScene2D*)pScene)->GetPosition();
					}
				}
				pScene = pScene->GetSceneNext();
			}
		} while (pScene != NULL);

		switch (m_OjamaType)
		{
			// �Ȃ��邨�����
		case OJAMA_TYPE_FALL:
			// ���S�Ɗp�x�̑��
			m_middle = D3DXVECTOR3(SCREEN_CENTER_X, 50.0f, 0.0f);
			m_fAngle = atan2f(m_middle.x - m_pos.x, m_middle.y - m_pos.y);
			break;

			// �܂����������������
		case OJAMA_TYPE_CURVE:
			// ���S�̑��
			m_middle = D3DXVECTOR3(SCREEN_CENTER_X, (float)(rand() % 455) + 125.0f, 0.0f);
			break;

			// �����邨�����
		case OJAMA_TYPE_THROUGH:
			// �p�x�̌v�Z
			m_fAngle = atan2f(m_pos.x - m_Getpos.x, m_pos.y - m_Getpos.y);
			break;

		default:
			break;
		}
		break;

	default:
		break;
	}

	return S_OK;
}

//=============================================================================
// ������܃v���C���[�N���X�̏I������
//=============================================================================
void COjama::Uninit(void)
{
	// CScene2D�̏I������
	CScene2D::Uninit();
}

//=============================================================================
// ������܃v���C���[�N���X�̍X�V����
//=============================================================================
void COjama::Update(void)
{
	switch (m_OjamaPlayerNum)
	{
		// 1P�̂������
	case OJAMAPLAYER_1P:
		// �G�t�F�N�g�̃N���G�C�g
		CEffect::Create(m_pos, m_size + D3DXVECTOR3(5.0f, 5.0f, 0.0f), 10, 255, 100, 100, 255, CEffect::EFFECTTYPE_BULLET, OBJTYPE_EFFECT);
		break;

		// 2P�̂������
	case OJAMAPLAYER_2P:	// �G�t�F�N�g�̃N���G�C�g
		CEffect::Create(m_pos, m_size + D3DXVECTOR3(5.0f, 5.0f, 0.0f), 10, 100, 255, 255, 255, CEffect::EFFECTTYPE_BULLET, OBJTYPE_EFFECT);
		break;

	default:
		break;
	}
	// CScene2D�̍X�V����
	CScene2D::Update();

	// ���W�Ƒ̗͂̎󂯎��
	m_pos = GetPosition();

	switch (m_OjamaType)
	{
		// �����邨�����
	case OJAMA_TYPE_FALL:
		Fall();
		break;

		// �܂����������������
	case OJAMA_TYPE_THROUGH:
		Through();
		break;

		// �Ȃ��邨�����
	case OJAMA_TYPE_CURVE:
		Curve();
		break;

	default:
		break;

	}

	Hit();

	//m_pos += m_move;

	// ���W�ƃT�C�Y�A�̗͂�n��
	SetPosition(m_pos);
	SetSize(m_size);

	// ��ʊO�ɏo����I������
	if (m_pos.y > SCREEN_HEIGHT + m_size.y)
	{
		Uninit();
	}
}

//=============================================================================
// ������܃v���C���[�N���X�̕`�揈��
//=============================================================================
void COjama::Draw(void)
{
	// CScene2D�̕`�揈��
	CScene2D::Draw();
}

//=============================================================================
// ������܃N���X�̋Ȃ����ē�������
//=============================================================================
void COjama::Curve(void)
{
	switch (m_OjamaPlayerNum)
	{
		// 1P�̂������
	case OJAMAPLAYER_1P:
		// ���S��菬�����Ƃ�
		if (m_pos.x < m_middle.x)
		{
			// �p�x�����߂�
			m_fAngle = atan2f(m_pos.x - m_middle.x, m_pos.y - m_middle.y);
			if (m_fAngle > D3DX_PI)
			{
				m_fAngle -= D3DX_PI;
			}
			if (m_fAngle < -D3DX_PI)
			{
				m_fAngle += D3DX_PI;
			}
			// ���߂��p�x�̕��ɓ�����
			m_move.x = sinf(m_fAngle) * -10;
			m_move.y = cosf(m_fAngle) * -10;
		}
		// ���S���傫���Ƃ�
		else if (m_pos.x >= m_middle.x)
		{
			// �p�x�����߂�
			m_fAngle = atan2f(m_middle.x - m_Getpos.x, m_middle.y - m_Getpos.y);
			if (m_fAngle > D3DX_PI)
			{
				m_fAngle -= D3DX_PI;
			}
			if (m_fAngle < -D3DX_PI)
			{
				m_fAngle += D3DX_PI;
			}
			// ���߂��p�x�̕��ɓ�����
			m_move.x = sinf(m_fAngle) * -10;
			m_move.y = cosf(m_fAngle) * -10;
		}
		break;

		// 2P�̂������
	case OJAMAPLAYER_2P:
		// ���S���傫���Ƃ�
		if (m_pos.x > m_middle.x)
		{
			// �p�x�����߂�
			m_fAngle = atan2f(m_pos.x - m_middle.x, m_pos.y - m_middle.y);
			if (m_fAngle > D3DX_PI)
			{
				m_fAngle -= D3DX_PI;
			}
			if (m_fAngle < -D3DX_PI)
			{
				m_fAngle += D3DX_PI;
			}
			// ���߂��p�x�̕��ɓ�����
			m_move.x = sinf(m_fAngle) * -10;
			m_move.y = cosf(m_fAngle) * -10;
		}
		// ���S��菬�����Ƃ�
		else if (m_pos.x <= m_middle.x)
		{
			// �p�x�����߂�
			m_fAngle = atan2f(m_middle.x - m_Getpos.x, m_middle.y - m_Getpos.y);
			if (m_fAngle > D3DX_PI)
			{
				m_fAngle -= D3DX_PI;
			}
			if (m_fAngle < -D3DX_PI)
			{
				m_fAngle += D3DX_PI;
			}
			// ���߂��p�x�̕��ɓ�����
			m_move.x = sinf(m_fAngle) * -10;
			m_move.y = cosf(m_fAngle) * -10;
		}
		break;

	default:
		break;
	}
	m_pos += m_move;
}

//=============================================================================
// ������܃N���X�̂܂�������������
//=============================================================================
void COjama::Through(void)
{
	if (m_fAngle > D3DX_PI)
	{
		m_fAngle -= D3DX_PI * 2.0f;
	}
	if (m_fAngle < -D3DX_PI)
	{
		m_fAngle += D3DX_PI * 2.0f;
	}

	// �ړ��ʂ̉��Z
	m_pos += D3DXVECTOR3(sinf(m_fAngle) * m_move.x, cosf(m_fAngle) * m_move.y, 0.0f);
}

//=============================================================================
// ������܃N���X�̗����ē�������
//=============================================================================
void COjama::Fall(void)
{
	if (m_fAngle > D3DX_PI)
	{
		m_fAngle -= D3DX_PI * 2.0f;
	}
	if (m_fAngle < D3DX_PI)
	{
		m_fAngle += D3DX_PI * 2.0f;
	}

	// ��A���ڂ̓�����false�̎�
	if (m_bFirstmove == false && m_bSecondmove == false)
	{
		// �ړ��ʂ̉��Z
		m_pos += D3DXVECTOR3(sinf(m_fAngle) * m_move.x, cosf(m_fAngle) * m_move.y, 0.0f);
	}

	switch (m_OjamaPlayerNum)
	{
		// 1P�̂������
	case OJAMAPLAYER_1P:
		// ���S��菬�����Ƃ�
		if (m_middle.y >= m_pos.y)
		{
			// ���ڂ̓�����true�ɂ���
			m_bFirstmove = true;
			m_bSecondmove = false;

			// ��������W�����߂�
			m_Fallpos.x = (float)(rand() % 400 - 200) + m_Getpos.x;
			if (m_Fallpos.x < PLAYER2_MOVABLE_RANGE_S)
			{
				m_Fallpos.x = PLAYER2_MOVABLE_RANGE_S;
			}
			if (m_Fallpos.x > PLAYER2_MOVABLE_RANGE_L)
			{
				m_Fallpos.x = PLAYER2_MOVABLE_RANGE_L;
			}
		}

		// ���ڂ̓�����true�̎�
		if (m_bFirstmove == true)
		{
			m_pos.x += m_accele.x;

			// ��������W���傫���Ȃ�����
			if (m_Fallpos.x <= m_pos.x)
			{
				// ���ڂ̓�����false�A���ڂ̓�����true�ɂ���
				m_bFirstmove = false;
				m_bSecondmove = true;
			}
		}
		// ���ڂ̓�����true�̎�
		if (m_bSecondmove == true)
		{
			m_pos.y += m_accele.y;
		}
		break;

		// 2P�̂������
	case OJAMAPLAYER_2P:
		// ���S��菬�����Ƃ�
		if (m_middle.y >= m_pos.y)
		{
			// ���ڂ̓�����true�ɂ���
			m_bFirstmove = true;
			m_bSecondmove = false;

			// ��������W�����߂�
			m_Fallpos.x = (float)(rand() % 400 - 200) + m_Getpos.x;
			if (m_Fallpos.x < PLAYER_MOVABLE_RANGE_S)
			{
				m_Fallpos.x = PLAYER_MOVABLE_RANGE_S;
			}
			if (m_Fallpos.x > PLAYER_MOVABLE_RANGE_L)
			{
				m_Fallpos.x = PLAYER_MOVABLE_RANGE_L;
			}
		}

		// ���ڂ̓�����true�̎�
		if (m_bFirstmove == true)
		{
			m_pos.x += m_accele.x;

			// ��������W��菬�����Ȃ�����
			if (m_Fallpos.x >= m_pos.x)
			{
				// ���ڂ̓�����false�A���ڂ̓�����true�ɂ���
				m_bFirstmove = false;
				m_bSecondmove = true;
			}
		}
		// ���ڂ̓�����true�̎�
		if (m_bSecondmove == true)
		{
			m_pos.y += m_accele.y;
		}
		break;

	default:
		break;
	}
}

//=============================================================================
// ������܃N���X�̓��������Ƃ��̏���
//=============================================================================
void COjama::Hit(void)
{
	// �e�̃V�[�����󂯎��
	CScene *pScene = CScene::GetSceneTop(CScene::OBJTYPE_BULLET);
	do
	{
		if (pScene != NULL)
		{
			// �I�u�W�F�^�C�v�̎󂯎��
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_BULLET)
			{
				// �����蔻��
				if (CCollision::PRectangleCollision(m_pos, m_size, pScene) == true)
				{
					HitBullet(pScene);
				}
			}
			pScene = pScene->GetSceneNext();
		}
	} while (pScene != NULL);

	// �G�̔����̃V�[�����󂯎��
	pScene = CScene::GetSceneTop(CScene::OBJTYPE_ENEMYEXPLOSION);
	do
	{
		if (pScene != NULL)
		{
			// �I�u�W�F�^�C�v�̎󂯎��
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_ENEMYEXPLOSION)
			{
				// �����蔻��
				if (CCollision::PRectangleCollision(m_pos, m_size, pScene) == true)
				{
					HitExplosion(pScene);
				}
			}
			pScene = pScene->GetSceneNext();
		}
	} while (pScene != NULL);
}

//=============================================================================
// ������܃N���X�̒e�ɓ��������Ƃ��̏���
// pScene�F�����̃V�[���̃|�C���^
//=============================================================================
void COjama::HitBullet(CScene *pScene)
{
	// �󂯎�����e�̃^�C�v��1P�̎�
	if (((CBullet*)pScene)->GetBulletType() == CBullet::BULLET_TYPE_1P)
	{
		if (m_OjamaPlayerNum == OJAMAPLAYER_2P)
		{
			// �v���C���[2�ɓ��Ă�ꂽ��v���C���[2�̂�����܂��N���G�C�g(2��ڂ͂�����N���G�C�g)
			if (m_nCount < 1)
			{
				m_nOjamaCount = rand() % 3;
				switch (m_nOjamaCount)
				{
				case 0:
					COjama::Create(m_pos, D3DXVECTOR3(-10.0f, -10.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f),
						m_nCount + 1, D3DXVECTOR3(2.0f, 2.0f, 0.0f), COjama::OJAMA_TYPE_THROUGH, COjama::OJAMAPLAYER_1P, OBJTYPE_OJAMA);
					break;

				case 1:
					COjama::Create(m_pos, D3DXVECTOR3(-10.0f, -10.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f),
						m_nCount + 1, D3DXVECTOR3(-(float)(rand() % 3) - 2.0f, -2.0f, 0.0f), COjama::OJAMA_TYPE_CURVE, COjama::OJAMAPLAYER_1P, OBJTYPE_OJAMA);
					break;

				case 2:
					COjama::Create(m_pos, D3DXVECTOR3(-(float)(rand() % 10) + 15.0f, -(float)(rand() % 10) + 15.0f, 0.0f),
						D3DXVECTOR3(50.0f, 50.0f, 0.0f), m_nCount + 1,
						D3DXVECTOR3(-(float)(rand() % 5) - 5.0f, 5.0f, 0.0f), COjama::OJAMA_TYPE_FALL, COjama::OJAMAPLAYER_1P, OBJTYPE_OJAMA);
					break;
				default:
					break;
				}

				//�I������
				Uninit();
				return;
			}
			else
			{
				ExtraAttackCreate(CPlayer::PLAYER_1P);
			}
		}
	}
	// �󂯎�����e�̃^�C�v��2P�̎�
	if (((CBullet*)pScene)->GetBulletType() == CBullet::BULLET_TYPE_2P)
	{
		if (m_OjamaPlayerNum == OJAMAPLAYER_1P)
		{
			// �v���C���[2�ɓ��Ă�ꂽ��v���C���[2�̂�����܂��N���G�C�g(2��ڂ͂�����N���G�C�g)
			if (m_nCount < 1)
			{
				m_nOjamaCount = rand() % 3;
				switch (m_nOjamaCount)
				{
				case 0:
					COjama::Create(m_pos, D3DXVECTOR3(-10.0f, -10.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f),
						m_nCount + 1, D3DXVECTOR3(2.0f, 2.0f, 0.0f), COjama::OJAMA_TYPE_THROUGH, COjama::OJAMAPLAYER_2P, OBJTYPE_OJAMA);
					break;

				case 1:
					COjama::Create(m_pos, D3DXVECTOR3(-10.0f, -10.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f),
						m_nCount + 1, D3DXVECTOR3(-(float)(rand() % 3) - 2.0f, -2.0f, 0.0f), COjama::OJAMA_TYPE_CURVE, COjama::OJAMAPLAYER_2P, OBJTYPE_OJAMA);
					break;

				case 2:
					COjama::Create(m_pos, D3DXVECTOR3(-(float)(rand() % 10) + 15.0f, -(float)(rand() % 10) + 15.0f, 0.0f),
						D3DXVECTOR3(50.0f, 50.0f, 0.0f), m_nCount + 1,
						D3DXVECTOR3(-(float)(rand() % 5) - 5.0f, 5.0f, 0.0f), COjama::OJAMA_TYPE_FALL, COjama::OJAMAPLAYER_2P, OBJTYPE_OJAMA);
					break;

				default:
					break;
				}
				//�I������
				Uninit();
				return;
			}
			else
			{
				ExtraAttackCreate(CPlayer::PLAYER_2P);
			}
		}
	}
}

//=============================================================================
// ������܃N���X�̔����ɓ��������Ƃ��̏���
// pScene�F�����̃V�[���̃|�C���^
//=============================================================================
void COjama::HitExplosion(CScene *pScene)
{
	// �󂯎�����e�̃^�C�v��1P�̎�
	if (((CBullet*)pScene)->GetBulletType() == CBullet::BULLET_TYPE_1P)
	{
		// �v���C���[�ɓ��Ă�ꂽ��v���C���[�̂�����܂��N���G�C�g(2��ڂ͂�����N���G�C�g)
		if (m_nCount < 1)
		{
			m_nOjamaCount = rand() % 3;
			switch (m_nOjamaCount)
			{
			case 0:
				COjama::Create(m_pos, D3DXVECTOR3(-10.0f, -10.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f),
					m_nCount + 1, D3DXVECTOR3(2.0f, 2.0f, 0.0f), COjama::OJAMA_TYPE_THROUGH, COjama::OJAMAPLAYER_1P, OBJTYPE_OJAMA);
				break;

			case 1:
				COjama::Create(m_pos, D3DXVECTOR3(10.0f, -10.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f),
					m_nCount + 1, D3DXVECTOR3((float)(rand() % 3) + 2.0f, -2.0f, 0.0f), COjama::OJAMA_TYPE_CURVE, COjama::OJAMAPLAYER_1P, OBJTYPE_OJAMA);
				break;

			case 2:
				COjama::Create(m_pos, D3DXVECTOR3((float)(rand() % 10) - 15.0f, (float)(rand() % 10) - 15.0f, 0.0f),
					D3DXVECTOR3(50.0f, 50.0f, 0.0f), m_nCount + 1,
					D3DXVECTOR3((float)(rand() % 5) + 5.0f, 5.0f, 0.0f), COjama::OJAMA_TYPE_FALL, COjama::OJAMAPLAYER_1P, OBJTYPE_OJAMA);
				break;

			default:
				break;
			}
			//�I������
			Uninit();
		}
		else
		{
			ExtraAttackCreate(CPlayer::PLAYER_2P);
		}
	}

	// �󂯎�����e�̃^�C�v��2P�̎�
	if (((CBullet*)pScene)->GetBulletType() == CBullet::BULLET_TYPE_2P)
	{
		// �v���C���[�ɓ��Ă�ꂽ��v���C���[�̂�����܂��N���G�C�g(2��ڂ͂�����N���G�C�g)
		if (m_nCount < 1)
		{
			m_nOjamaCount = rand() % 3;
			switch (m_nOjamaCount)
			{
			case 0:
				COjama::Create(m_pos, D3DXVECTOR3(-10.0f, -10.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f),
					m_nCount + 1, D3DXVECTOR3(2.0f, 2.0f, 0.0f), COjama::OJAMA_TYPE_THROUGH, COjama::OJAMAPLAYER_2P, OBJTYPE_OJAMA);
				break;

			case 1:
				COjama::Create(m_pos, D3DXVECTOR3(-10.0f, -10.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f),
					m_nCount + 1, D3DXVECTOR3(-(float)(rand() % 3) - 2.0f, -2.0f, 0.0f), COjama::OJAMA_TYPE_CURVE, COjama::OJAMAPLAYER_2P, OBJTYPE_OJAMA);
				break;

			case 2:
				COjama::Create(m_pos, D3DXVECTOR3(-(float)(rand() % 10) + 15.0f, -(float)(rand() % 10) + 15.0f, 0.0f),
					D3DXVECTOR3(50.0f, 50.0f, 0.0f), m_nCount + 1,
					D3DXVECTOR3(-(float)(rand() % 5) - 5.0f, 5.0f, 0.0f), COjama::OJAMA_TYPE_FALL, COjama::OJAMAPLAYER_2P, OBJTYPE_OJAMA);
				break;

			default:
				break;
			}
			Uninit();
			return;
		}
		else
		{
			ExtraAttackCreate(CPlayer::PLAYER_1P);
		}
	}
}

//=============================================================================
// ������܃N���X�̃G�N�X�g���A�^�b�N����鏈��
// PlayerNum�F�v���C���[�̔ԍ�
//=============================================================================
void COjama::ExtraAttackCreate(CPlayer::PLAYERNUM PlayerNum)
{
	//�v���C���[�̃V�[���̃Q�b�g
	CScene *pScene = CScene::GetSceneTop(CScene::OBJTYPE_PLAYER);
	do
	{
		if (pScene != NULL)
		{
			OBJTYPE objType = pScene->GetObjType();

			// �I�u�W�F�^�C�v���v���C���[�̎�
			if (objType == OBJTYPE_PLAYER)
			{
				switch (PlayerNum)
				{
				case CPlayer::PLAYER_1P:
					if (((CPlayer*)pScene)->GetPlayerNum() == PlayerNum)
					{
						// �p�x�����߂�
						m_fAngle = atan2f(m_pos.x - ((CScene2D*)pScene)->GetPosition().x, m_pos.y - ((CScene2D*)pScene)->GetPosition().y);

						// �G�N�X�g���A�^�b�N�̐���
						CExtraattck::Create(m_pos, D3DXVECTOR3(sinf(m_fAngle) * -10.0f, cosf(m_fAngle) * -10.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f),
							CExtraattck::EXTRAATTCK_PLAYER1, CExtraattck::EXTRAATTACK_BLINKING, OBJTYPE_EXTRAATTACK);

						//�I������
						Uninit();
						return;
					}

					break;

				case CPlayer::PLAYER_2P:
					if (((CPlayer*)pScene)->GetPlayerNum() == PlayerNum)
					{
						// �p�x�����߂�
						m_fAngle = atan2f(m_pos.x - ((CScene2D*)pScene)->GetPosition().x, m_pos.y - ((CScene2D*)pScene)->GetPosition().y);

						// �G�N�X�g���A�^�b�N�̐���
						CExtraattck::Create(m_pos, D3DXVECTOR3(sinf(m_fAngle) * -10.0f, cosf(m_fAngle) * -10.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f),
							CExtraattck::EXTRAATTCK_PLAYER2, CExtraattck::EXTRAATTACK_AIM, OBJTYPE_EXTRAATTACK);

						//�I������
						Uninit();
						return;
					}
					break;

				default:
					break;
				}
			}
			pScene = pScene->GetSceneNext();
		}
	} while (true);
}

//=============================================================================
// ������܃N���X�̃v���C���[�̔ԍ���Ԃ�����
//=============================================================================
COjama::OJAMAPLAYERNUM COjama::GetOjamaPlayerNum(void)
{
	return m_OjamaPlayerNum;
}


