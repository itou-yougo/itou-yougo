//=============================================================================
//
// �v���C���[�̏��� [player.h]
// Author : �ɓ��z��
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "character.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_PLAYER_PARTS (15) // �v���C���[�̃��f���̃p�[�c�̍ő吔
#define MOTION_PLAYER_TEXT ("data/MODEL/PLAYER/MOTION/motion.txt") // ���[�V�����̃e�L�X�g
#define LOAD_PLAYER_TEXT ("data/MODEL/PLAYER/MOTION/player.txt") // �e���f���p�[�c�̏����l4
#define PLAYER_LIFE (100)

#define SWORD_COLISION_SIZE (D3DXVECTOR3(5.0f, 5.0f, 5.0f)) // ���̓����蔻��̑傫��

#define MOVE_SPEED (2.0f)	  // �������x
#define SUBTRACT_FLAME (1.0f) // ���炷�t���[���̗�

//=============================================================================
// �O���錾
//=============================================================================
class CMotion;
class CModel;
class CReticle;
class CEnemy;

//=============================================================================
// �v���C���[�N���X
//=============================================================================
class CPlayer :public CCharacter
{
public:

	typedef enum
	{
		MOTION_IDLE = 0,
		MOTION_RUN,
		MOTION_SLASH,
		MOTION_N,
		MOTION_L
	}MOTION;

	typedef enum
	{
		PLAYERSTATE_NOMAL = 0,
		PLAYERSTATE_ATTACK,
		PLAYERSTATE_DAMAGE
	}PLAYERSTATE;

	CPlayer(int nPriority = CScene::OBJTYPE_PLAYER);//�R���X�g���N�^
	~CPlayer();//�f�X�g���N�^

	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);//��������

	HRESULT Init(void);//����������
	void Uninit(void);//�I������
	void Update(void);//�X�V����
	void Draw(void);//�`�揈��

	void SetPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);//�e��ݒ�

	void GamePad(void);//�Q�[���p�b�h����
	void Attack(D3DXVECTOR3 Distance); // �U���̏���
	void Swordeffect(D3DXVECTOR3 Distance); // ���̃G�t�F�N�g

	void HitDamage(int nDamage);	//�_���[�W����
	static void DeathFlag(void);	//���S�t���O


	bool GetDeath(void) { return m_bDeath; }//���S�t���O

private:
	float m_fNotControl;	// ����ł��Ȃ�����
	bool m_bAttackHit;		// �U�����������Ă��邩

	int m_nDamageMotionCnt;				// �_���[�W���[�V�����̃J�E���g
	bool m_bDamageMotion;				// �_���[�W���[�V�����̔���

	int m_nDeathMotionCnt;				// ���S���[�V�����̃J�E���g
	bool m_bDeathMotion;				// ���S���[�V�����̔���
	static bool m_bDeath;				// ���S�t���O

	int m_nSwordEffectTime; // ���̃G�t�F�N�g�̏o������

	CEnemy *m_pEnemy;					// �G�N���X�̃|�C���^
	PLAYERSTATE m_Playerstate;			// �v���C���[�̏��

};

#endif