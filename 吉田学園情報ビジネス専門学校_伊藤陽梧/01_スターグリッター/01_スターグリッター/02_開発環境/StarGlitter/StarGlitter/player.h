//=============================================================================
//
// �|���S���̕`��̏��� [player.h]
// Author : �ɓ��z��
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2d.h"
#include "extraattack.h"

//=============================================================================
// �O���錾
//=============================================================================
class CSound;
class CLife;
class CChargeshot;
class CBomb;
class CEffect;

//=============================================================================
// �}�N����`
//=============================================================================
#define PLAYER_SPEED (10.0f)			  // 1P�̑���
#define PLAYER_MOVABLE_RANGE_S (70.0f)	  // 1P�̈ړ��ł���͈�(�Z���ق�)
#define PLAYER_MOVABLE_RANGE_L (815.0f)	  // 1P�̈ړ��ł���͈�(�����ق�)
#define PLAYER2_SPEED (10.0f)			  // 2P�̑���
#define PLAYER2_MOVABLE_RANGE_S (915.0f)  // 2P�̈ړ��ł���͈�(�Z���ق�)
#define PLAYER2_MOVABLE_RANGE_L (1658.0f) // 2P�̈ړ��ł���͈�(�����ق�)
#define PLAYER_BOMB_MAX (2)				  // ���@�̃{���̍ő吔
#define PLAYER_INVINCIBLE (180)			  // ���G����
#define PLAYER_RIGORE (80)			  // ���G����

//=============================================================================
// �v���C���[�N���X
//=============================================================================
class CPlayer :public CScene2D
{
public:
	typedef enum
	{
		PLAYERSTATE_NONE = 0,
		PLAYERSTATE_NOMAL,  // �m�[�}�����
		PLAYERSTATE_DAMAGE, // �_���[�W���󂯂����
		PLAYERSTATE_LOSE,   // ���������̏��
		PLAYERSTATE_MAX,
	}PLAYERSTATE;

	typedef enum
	{
		PLAYER_1P,		 // 1P
		PLAYER_2P,		 // 2P
		PLAYER_MAX,
	}PLAYERNUM;

	CPlayer();  // �R���X�g���N
	~CPlayer();	// �f�X�g���N�^

	static HRESULT Load(void); // ���[�h
	static void Unload(void);  // �A�����[�h
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nLife, PLAYERNUM PlayerNum, OBJTYPE objType); // �N���G�C�g

	HRESULT Init();    // ����������
	void Uninit(void); // �I������
	void Update(void); // �X�V����
	void Draw(void);   // �`�揈��

	void SetPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nLife, PLAYERNUM PlayerNum, OBJTYPE objType) { // �v���C���[�̐ݒ�
		SetPosition(pos); m_pos = pos; m_move = move;
		m_size = m_size; SetSize(size);
		m_nLife = nLife; m_PlayerNum = PlayerNum;
		SetObjType(objType);
	}

	void PlayerDamage(int nDamage); // �_���[�W�̏���
	void PlayerAddLife(int nLife);  // �񕜂̏���
	void GamePad(void); // �Q�[���p�b�h�̏���
	void keyBoard(void); // �L�[�{�[�h�̏���
	void Shot(void); // �e��������
	void ChargeShot(void); // �`���[�W�e��������
	void ExtraAttack(void); // �G�N�X�g���A�^�b�N�̏���
	void BossAttack(void); // �{�X�A�^�b�N�̏���
	void ExtraAttackInvocating(void); // �G�N�X�g���A�^�b�N�𔭓����鏈��
	void HitEnemy(void); // �G�ɓ�����������
	void HitOjama(void); // ������܂ɓ�����������
	void HitExtraAttack(CExtraattck::EXTRAATTCKPLAYERNUM ExtraAttackPlayerNum); // �G�N�X�g���A�^�b�N�ɓ�����������
	void HitBossAttack(void); // �{�X�ɓ�����������
	void DamageState(void); // �_���[�W�̏��
	void Charging(void); // �`���[�W���̏���
	CChargeshot* GetChargeShot(void); // �`���[�W�V���b�g�̃|�C���^��Ԃ�
	PLAYERSTATE GetPlayerState(void); // �v���C���[�̏�Ԃ�Ԃ�
	PLAYERNUM GetPlayerNum(void); // �v���C���[�̔ԍ���Ԃ�
private:
	CLife*					  m_pLife;					// �̗͂̃|�C���^
	CChargeshot*			  m_pChargeShot;			// �`���[�W�V���b�g�̃|�C���^
	CBomb*					  m_pBomb[PLAYER_BOMB_MAX]; // �{���̃|�C���^
	CEffect*				  m_pEffect;				// �G�t�F�N�g�̃|�C���^
	static LPDIRECT3DTEXTURE9 m_apTexture[PLAYER_MAX];				// �e�N�X�`���ւ̃|�C���^
	static int				  m_nDamage;				// �󂯂��_���[�W�̒l
	D3DXVECTOR3				  m_pos;					// �ʒu
	D3DXVECTOR3				  m_Getpos;					// �G�̈ʒu
	D3DXVECTOR3				  m_move;					// ����
	D3DXVECTOR3				  m_size;					// �傫��
	D3DXVECTOR3				  m_GetSize;				// �󂯎�����傫��
	float					  m_fAngle;					// �p�x
	int						  m_nLife;					// ���@�̗̑�
	int						  m_nBulletShotCount;		// �e�����Ԋu
	int						  m_nInvincibleTime;		// ���G����
	int						  m_nRigorTime;				// �d������
	int						  m_nExtraAttackCount;		// �G�N�X�g���A�^�b�N�̃J�E���g
	int						  m_nPressTime;				// �{�^������������
	bool					  m_bExtraAttack;			// �G�N�X�g���A�^�b�N������t���O
	bool					  m_bEffectCreate;			// �G�t�F�N�g���o���t���O
	PLAYERSTATE				  m_PlayerState;			// �v���C���[�̏��
	PLAYERNUM				  m_PlayerNum;				// �v���C���[�̔ԍ�
};
#endif