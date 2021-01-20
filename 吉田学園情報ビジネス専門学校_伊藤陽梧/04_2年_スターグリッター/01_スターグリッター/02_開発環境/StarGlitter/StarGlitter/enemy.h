//=============================================================================
//
// �|���S���̕`��̏��� [enemy.h]
// Author : �ɓ��z��
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_


//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2d.h"
#include "bullet.h"
#include "enemyexplosion.h"

//=============================================================================
// �O���錾
//=============================================================================
class CSound;
class CScore;
class CGauge;

//=============================================================================
// �G�l�~�[�N���X
//=============================================================================
class CEnemy :public CScene2D
{
public:
	typedef enum
	{
		DAMAGE_TYPE_NONE = 0,
		DAMAGE_TYPE_BULLET,    // �e�̃_���[�W
		DAMAGE_TYPE_EXPLOSION, // �����̃_���[�W
		DAMAGE_TYPE_MAX,
	}DAMAGETYPE;

	CEnemy();  // �R���X�g���N
	~CEnemy(); // �f�X�g���N�^

	static HRESULT Load(void); // ���[�h
	static void Unload(void);  // �A�����[�h
	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,
		D3DXVECTOR3 size, int nLife, OBJTYPE objType); // �N���G�C�g

	HRESULT Init();    // ����������
	void Uninit(void); // �I������
	void Update(void); // �X�V����
	void Draw(void);   // �`�揈��

	void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, 
		D3DXVECTOR3 size, int nLife, OBJTYPE objType) { // �G�̃Z�b�g
		SetPosition(pos); SetSize(size); m_pos = pos;
		m_move = move; m_size = size;
		m_nLife = nLife; SetObjType(objType);
	}

	void Death(void); // �|���ꂽ�Ƃ��̏���
	void OjamanCreate(void); // ������܂���鏈��
	void EnemyExplosionCreate(CEnemyexplosion::EXPLOSIONTEXTURE ExplosionTexture); // �G�̔������o������
	void GaugeUp(void); // �Q�[�W�̍ő�l��L�΂�����
	void EnemyDamage(int nDamage, DAMAGETYPE DamageType, CBullet::BULLETTYPE BulletType); // �_���[�W�̏���
private:
	CGauge* m_pGauge; // �Q�[�W�̃|�C���^
	static LPDIRECT3DTEXTURE9 m_pTexture; // �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3			m_pos;		   // �ʒu
	D3DXVECTOR3			m_move;		   // ���x
	D3DXVECTOR3			m_size;		   // �傫��
	int					m_nLife;	   // �G�̗̑�
	int					m_nOjamaCount; // ������܂̃J�E���g
	DAMAGETYPE			m_DamageType;  // �_���[�W�̃^�C�v
	CBullet::BULLETTYPE m_BulletType;  // �N�̒e�Ȃ̂�
};
#endif