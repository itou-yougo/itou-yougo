//=============================================================================
//
// �{�X�A�^�b�N�̏��� [bossattack.h]
// Author : �ɓ��z��
//
//=============================================================================
#ifndef _BOSSATTACK_H_
#define _BOSSATTACK_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2d.h"
#include "bullet.h"
#include "player.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define BOSS_SIZE_X (300.0f)			// �{�X�̉��̒���
#define BOSS_SIZE_Y (300.0f)			// �{�X�̏c�̒���
#define MAX_BOSS_TEXTURE (2)			// �{�X�̃e�N�X�`���̍ő吔

//=============================================================================
// �{�X�A�^�b�N�N���X
//=============================================================================
class CBossattck :public CScene2D
{
public:
	typedef enum
	{
		BOSSATTCK_PLAYER_NONE = 0,
		BOSSATTCK_PLAYER1, // �v���C���[1�̃{�X�A�^�b�N
		BOSSATTCK_PLAYER2, // �v���C���[2�̃{�X�A�^�b�N
		BOSSATTCK_PLAYER_MAX,
	}PLAYER;

	typedef enum
	{
		BOSSATTACK_BEAM,   // �r�[�������{�X�A�^�b�N
		BOSSATTACK_BULLET, // ���܂����{�X�A�^�b�N
		BOSSATTACK_MAX,
	}BOSSATTACK;

	CBossattck();   // �R���X�g���N
	~CBossattck(); 	// �f�X�g���N�^
	
	static HRESULT Load(void); // ���[�h
	static void Unload(void);  // �A�����[�h
	static CBossattck *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife,
		PLAYER Player, BOSSATTACK BossAttack, OBJTYPE objType); // �N���G�C�g

	HRESULT Init();    // ����������
	void Uninit(void); // �I������
	void Update(void); // �X�V����
	void Draw(void);   // �`�揈��

	void BossAttackDamage(int nDamage); // �_���[�W���󂯂����̏���

	void SetBossAttack(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife,
		PLAYER Player, BOSSATTACK BossAttack, OBJTYPE objType) { // �{�X�A�^�b�N�̐ݒ�
		SetPosition(pos); m_pos = pos; m_move = move;
		m_nLife = nLife; m_Player = Player;
		m_BossAttack = BossAttack; SetObjType(objType);
	}

	void BossBeam(void); // �r�[�������{�X�̏���
	void BossBullet(void); // �e�����{�X�̏���
	void BossAttackBeam(void); // �r�[����������
	void BossAttackBullet(CPlayer::PLAYERNUM PlayerNum); // �e��������

	void Hit(void); // �����鏈��
	void HitDamage(void); // ������Ƃ��̃_���[�W�̏���
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BOSS_TEXTURE];  // �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3	m_pos;						   // ���W
	D3DXVECTOR3	m_move;						   // ����
	D3DXVECTOR3 m_size;						   // �傫��
	float		m_fAngle;					   // �p�x
	int			m_nCount;					   // �J�E���g
	int			m_nInvincibleTime;			   // ���G����
	int			m_nCountBullet;				   // �e�����J�E���g
	int			m_nCountStop;				   // �~�܂�Ƃ��̃J�E���g
	int			m_nLife;					   // �̗�
	bool		m_bStop;					   // �~�܂������̔���
	PLAYER		m_Player;					   // �v���C���[�̎��
	BOSSATTACK  m_BossAttack;				   // �{�X�A�^�b�N�̎��
};
#endif