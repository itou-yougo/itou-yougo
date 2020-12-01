//=============================================================================
//
// �|���S���̕`��̏��� [bullet.cpp]
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
#include "ojamaplayer.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "player2.h"
#include "explosion.h"
#include "enemy.h"
#include "life.h"
#include "effect.h"
#include "bullet.h"
#include "ojamaplayer2.h"
#include "extraattack.h"
#include "enemyexplosion.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define EXPLOSION_SIZE_X (100.0f)			// �����̏c�̒���
#define EXPLOSION_SIZE_Y (100.0f)			// �����̉��̒���

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 COjamaplayer::m_pTexture = NULL;

//=============================================================================
// ������܃v���C���[�N���X�̃R���X�g���N�^
//=============================================================================
COjamaplayer::COjamaplayer() :CScene2D(OBJTYPE_OJAMA)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Getpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_middle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posPlayer2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_GetposPlayer2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_accele = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fSizeX = 0.0f;
	m_fSizeY = 0.0f;
	m_fGetSizeX = 0.0f;
	m_fGetSizeY = 0.0f;
	m_nCount = 0;
	m_nOjamaCount = 0;
	m_bFirstmove = false;
	m_bSecondmove = false;
	m_OjamaType = OJAMA_TYPE_NONE;
}

//=============================================================================
// ������܃v���C���[�N���X�̃f�X�g���N�^
//=============================================================================
COjamaplayer::~COjamaplayer()
{

}

//=============================================================================
// ������܃v���C���[�N���X�̃e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT COjamaplayer::Load(void)
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
void COjamaplayer::Unload(void)
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
COjamaplayer* COjamaplayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fSizeX, float fSizeY, int nCount, D3DXVECTOR3 Accele, OJAMATYPE OjamaType, OBJTYPE objType)
{
	// COjamaplayer�̃|�C���^
	COjamaplayer *pOjamaplayer = NULL;

	// �������̊m��
	pOjamaplayer = new COjamaplayer;

	// pOjamaplayer��NULL����Ȃ��Ƃ�
	if (pOjamaplayer != NULL)
	{
		// ������܃v���C���[�̃Z�b�g
		pOjamaplayer->SetCOjama(pos, move, fSizeX, fSizeY, nCount, Accele, OjamaType, objType);

		// ����������
		pOjamaplayer->Init();
	}

	// pOjamaplayer��Ԃ�
	return pOjamaplayer;
}

//=============================================================================
// ������܃v���C���[�N���X�̏���������
//=============================================================================
HRESULT COjamaplayer::Init()
{
	// CScene2D�̏���������
	CScene2D::Init();

	// �e�N�X�`���̐ݒ�
	BindTexture(m_pTexture);

	// �F�̃Z�b�g
	SetColor(255, 0, 0, 255);

	for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
	{
		//PLAYER2�̃V�[���̃Q�b�g
		CScene *pScene = GetScene(OBJTYPE_PLAYER2, nCntScene);
		if (pScene != NULL)
		{
			OBJTYPE objType = pScene->GetObjType();

			// �I�u�W�F�^�C�v���v���C���[2�̎�
			if (objType == OBJTYPE_PLAYER2)
			{
				m_GetposPlayer2 = ((CScene2D*)pScene)->GetPosition();
			}
		}
	}

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
		m_fAngle = atan2f(m_pos.x - m_GetposPlayer2.x, m_pos.y - m_GetposPlayer2.y);
		break;

	default:
		break;
	}

	return S_OK;
}

//=============================================================================
// ������܃v���C���[�N���X�̏I������
//=============================================================================
void COjamaplayer::Uninit(void)
{
	// CScene2D�̏I������
	CScene2D::Uninit();
}

//=============================================================================
// ������܃v���C���[�N���X�̍X�V����
//=============================================================================
void COjamaplayer::Update(void)
{
	// �G�t�F�N�g�̃N���G�C�g
	CEffect::Create(m_pos, m_fSizeX + 5.0f, m_fSizeY + 5.0f, 10, 255, 100, 100, 255, CEffect::EFFECTTYPE_BULLET, OBJTYPE_EFFECT);

	// CScene2D�̍X�V����
	CScene2D::Update();

	// ���W�Ƒ̗͂̎󂯎��
	m_pos = GetPosition();

	switch (m_OjamaType)
	{
		// �����邨�����
	case OJAMA_TYPE_FALL:
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

		// ���S��菬�����Ƃ�
		if (m_middle.y >= m_pos.y)
		{
			// ���ڂ̓�����true�ɂ���
			m_bFirstmove = true;
			m_bSecondmove = false;

			// ��������W�����߂�
			m_posPlayer2.x = (float)(rand() % 400 - 200) + m_GetposPlayer2.x;
			if (m_posPlayer2.x < PLAYER2_MOVABLE_RANGE_S)
			{
				m_posPlayer2.x = PLAYER2_MOVABLE_RANGE_S;
			}
			if (m_posPlayer2.x > PLAYER2_MOVABLE_RANGE_L)
			{
				m_posPlayer2.x = PLAYER2_MOVABLE_RANGE_L;
			}
		}

		// ���ڂ̓�����true�̎�
		if (m_bFirstmove == true)
		{
			m_pos.x += m_accele.x;

			// ��������W���傫���Ȃ�����
			if (m_posPlayer2.x <= m_pos.x)
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

		// �܂����������������
	case OJAMA_TYPE_THROUGH:

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
		break;

		// �Ȃ��邨�����
	case OJAMA_TYPE_CURVE:
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
			m_fAngle = atan2f(m_middle.x - m_GetposPlayer2.x, m_middle.y - m_GetposPlayer2.y);
			
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
		m_pos += m_move;
		break;

	default:
		break;

	}
	
	// ���W�ƃT�C�Y�A�̗͂�n��
	SetPosition(m_pos);
	SetSize(m_fSizeX, m_fSizeY);

	for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
	{
		// �e�̃V�[���̃Q�b�g
		CScene *pScene = GetScene(OBJTYPE_BULLET, nCntScene);
		if (pScene != NULL)
		{
			OBJTYPE objType = pScene->GetObjType();

			// �I�u�W�F�^�C�v���e�̎�
			if (objType == OBJTYPE_BULLET)
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
					// �󂯎�����e�̃^�C�v���v���C���[2�̎�
					if (((CBullet*)pScene)->GetBulletType() == CBullet::BULLET_TYPE_PLAYER2)
					{
						// �v���C���[2�ɓ��Ă�ꂽ��v���C���[2�̂�����܂��N���G�C�g(2��ڂ͂�����N���G�C�g)
						if (m_nCount < 1)
						{
							m_nOjamaCount = rand() % 3;
							switch (m_nOjamaCount)
							{
							case 0:
								COjamaplayer2::Create(m_pos, D3DXVECTOR3(-10.0f, -10.0f, 0.0f), 50.0f, 50.0f, m_nCount + 1, D3DXVECTOR3(2.0f, 2.0f, 0.0f), COjamaplayer2::OJAMA_TYPE_THROUGH, OBJTYPE_OJAMA);
								break;

							case 1:
								COjamaplayer2::Create(m_pos, D3DXVECTOR3(-10.0f, -10.0f, 0.0f), 50.0f, 50.0f, m_nCount + 1, D3DXVECTOR3(-(float)(rand() % 3) - 2.0f, -2.0f, 0.0f), COjamaplayer2::OJAMA_TYPE_CURVE, OBJTYPE_OJAMA);
								break;

							case 2:
								COjamaplayer2::Create(m_pos, D3DXVECTOR3(-(float)(rand() % 10) + 15.0f, -(float)(rand() % 10) + 15.0f, 0.0f), 50.0f, 50.0f, m_nCount + 1, D3DXVECTOR3(-(float)(rand() % 5) - 5.0f, 5.0f, 0.0f), COjamaplayer2::OJAMA_TYPE_FALL, OBJTYPE_OJAMA);
								break;
							default:
								break;
							}
							//�I������
							Uninit();
						}
						else
						{
							for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
							{
								// �I�u�W�F�^�C�v��PLAYER�̎�
								CScene *pScene = GetScene(OBJTYPE_PLAYER, nCntScene);
								if (pScene != NULL)
								{
									OBJTYPE objType = pScene->GetObjType();

									// �I�u�W�F�^�C�v���v���C���[2�̎�
									if (objType == OBJTYPE_PLAYER)
									{
										m_GetposPlayer2 = ((CScene2D*)pScene)->GetPosition();
									}
								}
							}
							// �p�x�����߂�
							m_fAngle = atan2f(m_pos.y - m_GetposPlayer2.y, m_pos.x - m_GetposPlayer2.x);
							
							// �G�N�X�g���A�^�b�N�̐���
							CExtraattck::Create(m_pos, D3DXVECTOR3(sinf(m_fAngle) * -10.0f, cosf(m_fAngle) * -10.0f, 0.0f), 50.0f, 50.0f, CExtraattck::EXTRAATTCK_PLAYER1, CExtraattck::EXTRAATTACK_NERAU, OBJTYPE_EXTRAATTACK);
							
							//�I������
							Uninit();
						}
					}
					break;
				}
			}
		}
		// �G�̔����̃V�[���̃Q�b�g
		pScene = GetScene(OBJTYPE_ENEMYEXPLOSION, nCntScene);
		if (pScene != NULL)
		{
			OBJTYPE objType = pScene->GetObjType();

			// �I�u�W�F�^�C�v���e�̎�
			if (objType == OBJTYPE_ENEMYEXPLOSION)
			{
				// �I�u�W�F�^�C�v���e�̎�
				m_Getpos = ((CScene2D*)pScene)->GetPosition();
				m_fGetSizeX = ((CScene2D*)pScene)->GetSizeX();
				m_fGetSizeY = ((CScene2D*)pScene)->GetSizeY();

				// �����蔻��
				if (m_pos.x - (m_fSizeX / 2) <= m_Getpos.x + (m_fGetSizeX / 2) &&
					m_pos.x + (m_fSizeX / 2) >= m_Getpos.x - (m_fGetSizeX / 2) &&
					m_pos.y - (m_fSizeY / 2) <= m_Getpos.y + (m_fGetSizeY / 2) &&
					m_pos.y + (m_fSizeY / 2) >= m_Getpos.y - (m_fGetSizeY / 2))
				{
					// �󂯎�����e�̃^�C�v���v���C���[�̎�
					if (((CEnemyexplosion*)pScene)->GetExplosionType() == CEnemyexplosion::EXPLOSIONTYPE_PLAYER2)
					{
						// �v���C���[�ɓ��Ă�ꂽ��v���C���[�̂�����܂��N���G�C�g(2��ڂ͂�����N���G�C�g)
						if (m_nCount < 1)
						{
							m_nOjamaCount = rand() % 3;
							switch (m_nOjamaCount)
							{
							case 0:
								COjamaplayer2::Create(m_pos, D3DXVECTOR3(-10.0f, -10.0f, 0.0f), 50.0f, 50.0f, m_nCount + 1, D3DXVECTOR3(2.0f, 2.0f, 0.0f), COjamaplayer2::OJAMA_TYPE_THROUGH, OBJTYPE_OJAMA);
								break;

							case 1:
								COjamaplayer2::Create(m_pos, D3DXVECTOR3(-10.0f, -10.0f, 0.0f), 50.0f, 50.0f, m_nCount + 1, D3DXVECTOR3(-(float)(rand() % 3) - 2.0f, -2.0f, 0.0f), COjamaplayer2::OJAMA_TYPE_CURVE, OBJTYPE_OJAMA);
								break;

							case 2:
								COjamaplayer2::Create(m_pos, D3DXVECTOR3(-(float)(rand() % 10) + 15.0f, -(float)(rand() % 10) + 15.0f, 0.0f), 50.0f, 50.0f, m_nCount + 1, D3DXVECTOR3(-(float)(rand() % 5) - 5.0f, 5.0f, 0.0f), COjamaplayer2::OJAMA_TYPE_FALL, OBJTYPE_OJAMA);
								break;

							default:
								break;
							}
							Uninit();
						}
						else
						{
							for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
							{
								CScene *pScene = GetScene(OBJTYPE_PLAYER2, nCntScene);
								if (pScene != NULL)
								{
									OBJTYPE objType = pScene->GetObjType();

									// �I�u�W�F�^�C�v���v���C���[2�̎�
									if (objType == OBJTYPE_PLAYER2)
									{
										m_GetposPlayer2 = ((CScene2D*)pScene)->GetPosition();
									}
								}
							}
							// �p�x�����߂�
							m_fAngle = atan2f(m_pos.x - m_GetposPlayer2.x, m_pos.y - m_GetposPlayer2.y);
							
							// �G�N�X�g���A�^�b�N�̐���
							CExtraattck::Create(m_pos, D3DXVECTOR3(sinf(m_fAngle) * -10.0f, cosf(m_fAngle) * -10.0f, 0.0f), 50.0f, 50.0f, CExtraattck::EXTRAATTCK_PLAYER1, CExtraattck::EXTRAATTACK_NERAU, OBJTYPE_EXTRAATTACK);
							
							//�I������
							Uninit();
						}
					}
					break;
				}
			}
		}
	}

	// ��ʊO�ɏo����I������
	if (m_pos.y > SCREEN_HEIGHT + m_fSizeY)
	{
		Uninit();
	}
}

//=============================================================================
// ������܃v���C���[�N���X�̕`�揈��
//=============================================================================
void COjamaplayer::Draw(void)
{
	// CScene2D�̕`�揈��
	CScene2D::Draw();
}


