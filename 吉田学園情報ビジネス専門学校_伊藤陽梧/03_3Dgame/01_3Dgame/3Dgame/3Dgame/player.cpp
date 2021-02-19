//=============================================================================
//
// �v���C���[�̏��� [player.cpp]
// Author : �ɓ��z��
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "joystick.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "motion.h"
#include "collision.h"
#include "sound.h"
#include "camera.h"
#include "slash.h"
#include "debugcollision.h"
#include "swordeffect.h"
#include "spark.h"
#include "spesialattackeffect.h"
#include "magiccircle.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
bool CPlayer::m_bDeath = false;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer(int nPriority) : CCharacter(nPriority)
{
	m_fNotControl = 0.0f;
	m_bAttackHit = false;

	//�_���[�W���[�V����
	m_nDamageMotionCnt = 0;
	m_bDamageMotion = false;

	//���S���[�V����
	m_nDeathMotionCnt = 0;
	m_bDeathMotion = false;

	//���S�t���O
	m_bDeath = false;

	m_nSwordEffectTime = 0;

	m_pEnemy = NULL;
	m_Playerstate = PLAYERSTATE_NOMAL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// ��������
//=============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CPlayer *pPlayer;
	pPlayer = new CPlayer;
	pPlayer->SetPlayer(pos, rot, size);
	pPlayer->Init();
	return pPlayer;
}

//=============================================================================
//����������
//=============================================================================
HRESULT CPlayer::Init(void)
{
	SetObjType(OBJTYPE_PLAYER);
	SetType(CHARACTERTYPE_PLAYER);
	LoadInitialPosition(MOTION_PLAYER_TEXT);
	CCharacter::Init();

	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CPlayer::Uninit(void)
{
	// �t�F�[�h�̐���
	CManager::CreateFade(CManager::MODE_GAMEOVER);

	CCharacter::Uninit();

	// �����[�X
	Release();
}

//=============================================================================
//�X�V����
//=============================================================================
void CPlayer::Update(void)
{
	CCharacter::Update();

	// �R���g���[���ł��Ȃ����Ԃ�0�ȉ���������
	if (m_fNotControl <= 0.0f)
	{
		m_Playerstate = PLAYERSTATE_NOMAL;
	}

	// �S�[��������
	if (GetPos().z >= 830.0f)
	{
		if (CScene::GetUpdateStop() == false)
		{
			//�T�E���h�̒�~
			CManager::GetSound()->StopSound(CSound::SOUND_LABEL_BGM_GAME);
			CManager::GetSound()->StopSound(CSound::SOUND_LABEL_SE_DASH);

			//�t�F�[�h�̐���
			CManager::CreateFade(CManager::MODE_RESULT);
		}
	}
	
	// ���̐�Ǝ�����̈ʒu�̋���
	D3DXVECTOR3 Top = D3DXVECTOR3(GetModelParts(12)->GetMtxWorld()._41, GetModelParts(12)->GetMtxWorld()._42, GetModelParts(12)->GetMtxWorld()._43);
	D3DXVECTOR3 Bottom = D3DXVECTOR3(GetModelParts(11)->GetMtxWorld()._41, GetModelParts(11)->GetMtxWorld()._42, GetModelParts(11)->GetMtxWorld()._43);
	D3DXVECTOR3 Distance = D3DXVECTOR3(Top.x - Bottom.x, Top.y - Bottom.y, Top.z - Bottom.z);

	// ����ł��Ȃ��Ȃ�
	if (m_bDeath == false)
	{
		if (m_Playerstate == PLAYERSTATE_NOMAL)
		{
			//�Q�[���p�b�h����
			GamePad();
			
			// �����蔻��𕜊�������
			m_bAttackHit = false;
		}
		if (m_Playerstate == PLAYERSTATE_ATTACK)
		{
			//�U���̏���
			Attack(Distance);
		}

		// ���̃G�t�F�N�g�̏���
		Swordeffect(Distance);
	}

	// ���񂾂Ȃ�
	if (m_bDeath == true)
	{
		if (m_bDeathMotion == false)
		{
			//// ���S���[�V����
			//GetMotion()->SetMotion(CMotion::MOTION_DEATH);
			m_bDeathMotion = true;
			//�T�E���h�̒�~
			CManager::GetSound()->StopSound(CSound::SOUND_LABEL_SE_DASH);
			return;
		}
		//���S���[�V�������Ȃ�
		if (m_bDeathMotion == true)
		{
			m_nDeathMotionCnt++;
			//120�t���[���Ń��Z�b�g
			if (m_nDeathMotionCnt % 120 == 0)
			{
				m_bDeathMotion = false;
				m_nDeathMotionCnt = 0;
				Uninit();
				CManager::CreateFade(CManager::MODE_GAMEOVER);
			}
		}
	}

#ifdef _DEBUG
	// �����蔻��̉���
	D3DXVECTOR3 GetDistance = Distance / SWORD_EFFECT_NUM;
	for (int nCount = 0; nCount < SWORD_EFFECT_NUM; nCount++)
	{
		CDebugCollision::Create(D3DXVECTOR3(GetModelParts(11)->GetMtxWorld()._41,
			GetModelParts(11)->GetMtxWorld()._42,
			GetModelParts(11)->GetMtxWorld()._43) + (GetDistance * (float)nCount),
			D3DXVECTOR3(5.0f, 5.0f, 5.0f), CDebugCollision::TYPE_SQUARE);
	}

	CDebugCollision::Create(GetPos(), GetSize(), CDebugCollision::TYPE_SQUARE);

	CDebugCollision::Create(GetPos(), D3DXVECTOR3(GetSize().y, GetSize().y, GetSize().y), CDebugCollision::TYPE_SPHERE);
#endif
}

//=============================================================================
//�`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	CCharacter::Draw();
}

//=============================================================================
//�Q�[���p�b�h����
//=============================================================================
void CPlayer::GamePad(void)
{
	//�R���g���[���[�̎擾����
	DIJOYSTATE pStick = {};
	CInputJoystick *pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 pJoystickDevice = CInputJoystick::GetDevice();
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	if (pJoystickDevice != NULL)
	{
		pJoystickDevice->Poll();
		pJoystickDevice->GetDeviceState(sizeof(DIJOYSTATE), &pStick);
	}
	if (pJoystickDevice != NULL)
	{
		//�_���[�W���[�V�������łȂ��Ȃ�
		if (m_bDamageMotion == false)
		{
			//�ʏ탂�[�V����
			GetMotion()->SetMotion(MOTION_IDLE);
		}

		//--------------------------
		//�ړ�
		//--------------------------
		// �X�e�B�b�N�̓��͂���������
		if (pStick.lY != 0 || pStick.lX != 0)
		{
			// �X�e�B�b�N�̊p�x�����߂�
			float fAngle = atan2(pStick.lX * -1.0f, pStick.lY);

			// �X�e�B�b�N�̊p�x����ړ�������������߂�
			pos.x -= sinf(CManager::GetCamera()->GetAngle() + fAngle) * MOVE_SPEED;
			pos.z -= cosf(CManager::GetCamera()->GetAngle() + fAngle) * MOVE_SPEED;

			// �L�����̌�����ς���
			rot.y = CManager::GetCamera()->GetAngle() + fAngle;

			// ���郂�[�V����
			GetMotion()->SetMotion(MOTION_RUN);
		}

		if (rot.y > D3DX_PI)
		{
			rot.y -= D3DX_PI * 2;
		}
		if (rot.y < -D3DX_PI)
		{
			rot.y += D3DX_PI * 2;
		}

		// X�{�^������������
		if (pInputJoystick->GetJoystickTrigger(CInputJoystick::BUTTON_X))
		{
			// �a�郂�[�V����
			GetMotion()->SetMotion(MOTION_SLASH);
			m_Playerstate = PLAYERSTATE_ATTACK;
			m_fNotControl = SLASH_FLAME;
		}

		// Y�{�^������������
		if (pInputJoystick->GetJoystickTrigger(CInputJoystick::BUTTON_Y))
		{
			// ���@�w�̐���
			CMagiccercle::Create(D3DXVECTOR3(pos.x, 0.0f, pos.z), MAGICCERCLE_DEFAULT_ROT, MAGICCERCLE_DEFAULT_SIZE, MAGICCERCLE_DEFAULT_COLOR, 1200);
			
			// �K�E�Z�̃G�t�F�N�g�̐���
			CSpesialattackeffect::Create(GetPos(), SPESIALATTACKEFFECT_SIZE,
				SPESIALATTACKEFFECT_COLOR, SPESIALATTACKEFFECT_COUNTANIM * SPESIALATTACKEFFECT_PATTERNANIM * SPESIALATTACKEFFECT_TIMEANIM);
		}

	}

	// ���W�Ɖ�]�̃Z�b�g
	SetPos(pos);
	SetRot(rot);
}

//=============================================================================
// �U������
//=============================================================================
void CPlayer::Attack(D3DXVECTOR3 Distance)
{
	D3DXVECTOR3 rot = GetRot();
	D3DXVECTOR3 GetDistance = Distance / SWORD_EFFECT_NUM;
	// ����ł��Ȃ�����
	if (m_fNotControl > 0.0f)
	{
		if (m_fNotControl < SLASH_FLAME - SLASH_FLAME_EFFECT_START && m_fNotControl > 10.0f)
		{
			// �ړ��̊p�x�����߂�
			D3DXVECTOR3 moveAngle = D3DXVECTOR3(sinf(rot.y) * -1, 0.0f, cosf(rot.y) * -1);

			//CSlash::Create(D3DXVECTOR3(GetModelParts(11)->GetMtxWorld()._41,
			//	GetModelParts(11)->GetMtxWorld()._42,
			//	GetModelParts(11)->GetMtxWorld()._43) + Distance,
			//	SLASH_SIZE, moveAngle,
			//	SLASH_COLOR, SLASH_LIFE, CSlash::TYPE_SLASH_1);

			// �G�ւ̓����蔻��
			CScene *pScene = CScene::GetSceneTop(CScene::OBJTYPE_ENEMY);
			do
			{
				if (pScene != NULL)
				{
					OBJTYPE objType = pScene->GetObjType();
					if (objType == OBJTYPE_ENEMY)
					{
						// ���W�ƃT�C�Y�̎󂯎��
						D3DXVECTOR3 pos = ((CEnemy*)pScene)->GetPos();
						D3DXVECTOR3 Size = ((CEnemy*)pScene)->GetSize();

						for (int nCount = 0; nCount < SWORD_EFFECT_NUM; nCount++)
						{
							if (m_bAttackHit == false)
							{
								// �����蔻��
								if (CCollision::RectangleCollision3D(D3DXVECTOR3(GetModelParts(11)->GetMtxWorld()._41,
									GetModelParts(11)->GetMtxWorld()._42,
									GetModelParts(11)->GetMtxWorld()._43) + (GetDistance * (float)nCount),
									SWORD_COLISION_SIZE, pos, Size) == true)
								{
									CSpark::Create(D3DXVECTOR3(GetModelParts(11)->GetMtxWorld()._41,
										GetModelParts(11)->GetMtxWorld()._42,
										GetModelParts(11)->GetMtxWorld()._43) + (GetDistance * (float)nCount),
										D3DXVECTOR3(200.0f, 200.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), SPARK_COUNTANIM * SPARK_PATTERNANIM * SPARK_TIMEANIM);

									// �����蔻����Ȃ���
									m_bAttackHit = true;

									// �G�ւ̃_���[�W
									((CEnemy*)pScene)->HitDamage(5);
								}
							}
						}
					}
					pScene = pScene->GetSceneNext();
				}
			} while (pScene != NULL);
		}

		m_fNotControl -= SUBTRACT_FLAME;
	}
}

//=============================================================================
// ���̃G�t�F�N�g�̏���
//=============================================================================
void CPlayer::Swordeffect(D3DXVECTOR3 Distance)
{
	D3DXVECTOR3 GetDistance = (float)(rand() % SWORD_EFFECT_NUM) * (Distance / SWORD_EFFECT_NUM);

	m_nSwordEffectTime++;
	if (m_nSwordEffectTime >= SWORD_EFFECT_CREATE_TIME)
	{
		// ���̃G�t�F�N�g
		CSwordeffect::Create(D3DXVECTOR3(GetModelParts(11)->GetMtxWorld()._41,
			GetModelParts(11)->GetMtxWorld()._42,
			GetModelParts(11)->GetMtxWorld()._43) + GetDistance,
			SWORD_EFFECT_SIZE, D3DXVECTOR3(0.0f, 0.1f, 0.0f),
			SWORD_EFFECT_COLOR, SWORD_EFFECT_LIFE);
		m_nSwordEffectTime = 0;
	}
}

//=============================================================================
// �����ݒ�
//=============================================================================
void CPlayer::SetPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	SetObjType(OBJTYPE_PLAYER); //�I�u�W�F�N�g�^�C�v�̐ݒ�
	SetPos(pos);
	SetRot(rot);
	SetSize(size);
	SetLife(PLAYER_LIFE);
}

//=============================================================================
//�v���C���[���_���[�W���󂯂���
//=============================================================================
void CPlayer::HitDamage(int nDamage)
{
	//�T�E���h�̍Đ�
	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_PLAYER_DAMAGE);

	if (m_bDamageMotion == false)
	{	
		////�_���[�W���[�V����
		//GetMotion()->SetMotion(CMotion::MOTION_DAMAGE);
		m_bDamageMotion = true;
	}
}

//=============================================================================
//���S�t���O
//=============================================================================
void CPlayer::DeathFlag(void)
{
	m_bDeath = true;
}