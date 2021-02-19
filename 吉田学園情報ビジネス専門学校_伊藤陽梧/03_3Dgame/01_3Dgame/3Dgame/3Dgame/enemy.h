//=============================================================================
//
// �G�̏��� [enemy.h]
// Author : �ɓ��z��
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "character.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MOTION_ENEMY_TEXT ("data/MODEL/ENEMY/MOTION/motion.txt")	// ���[�V�����̃e�L�X�g
#define LOAD_ENEMY_TEXT ("data/MODEL/ENEMY/MOTION/enemy.txt")		// �e���f���p�[�c�̏����l

#define ENEMY_SIZE (D3DXVECTOR3(20.0f,50.0f,20.0f)) // �����蔻��T�C�Y
#define ENEMY_LIFE (10)								// �̗�
#define ENEMY_MOVE_SPEED (1.0f)						// �ړ���
#define ENEMY_DISTANCE_PLAYER (30.0f)				// �v���C���[�Ƃ̋���
#define ENEMY_CREATE_NUM (10)						// �G�𐶐����鐔
#define ENEMY_CREATE_ANGLE (360)					// �G�𐶐�����p�x
#define ENEMY_CREATE_DISTANCE (D3DXVECTOR3(1000.0f, 0.0f, 1000.0f))	// �G�𐶐����鋗��
#define ENEMY_CREATE_TIME (20)						// �G�𐶐����鎞��

//=============================================================================
// �O���錾
//=============================================================================
class CMotion;
class CModel;

//=============================================================================
// �G�l�~�[�N���X
//=============================================================================
class CEnemy :public CCharacter
{
public:
	typedef enum
	{
		ENEMYSTATE_NOMAL = 0,
	}ENEMYSTATE;

	CEnemy(int nPriority = CScene::OBJTYPE_ENEMY);//�R���X�g���N�^
	~CEnemy();//�f�X�g���N�^

	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, ENEMYSTATE EnemyState);//��������

	HRESULT Init(void);//����������
	void Uninit(void);//�I������
	void Update(void);//�X�V����
	void Draw(void);//�`�揈��
	void HitDamage(int nDamage);
	void EnemyCollision(void);
	static void SetChase(bool bChase);
	void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, ENEMYSTATE EnemyState);

private:
	bool m_bChase;						// �`�F�C�X����
	bool m_bHit;						// �_���[�W���󂯂Ă��锻��
	bool m_bAttack;						// �U������
	int m_nCntAttack;					// �U�����x
	int m_nCntFrame;					// �t���[���J�E���g
	ENEMYSTATE m_EnemyState;			// �G�̏��
};

#endif