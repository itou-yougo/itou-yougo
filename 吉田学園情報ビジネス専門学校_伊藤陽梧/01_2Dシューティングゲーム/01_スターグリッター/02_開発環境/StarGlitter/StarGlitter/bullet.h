//=============================================================================
//
// �e�̏��� [bullet.h]
// Author : �ɓ��z��
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2d.h"
#include "player.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_BULLET_TEXTURE (5) // �e�̃e�N�X�`���̍ő吔

//=============================================================================
// �o���b�g�N���X
//=============================================================================
class CBullet :public CScene2D
{
public:
	typedef enum
	{
		BULLET_TYPE_NONE = 0,
		BULLET_TYPE_1P,   // PLAYER1�̒e
		BULLET_TYPE_2P,   // PLAYER2�̒e
		BULLET_TYPE_BOSS, // �{�X�̒e
		BULLET_TYPE_MAX,
	}BULLETTYPE;

	typedef enum
	{
		CHARGEBULLET_TYPE_NONE = 0,
		CHARGEBULLET_TYPE_NOMAL,	 // ���ʂ̒e
		CHARGEBULLET_TYPE_CHARGE,	 // �`���[�W�����e
		CHARGEBULLET_TYPE_LASER,	 // ���[�U�[�e
		CHARGEBULLET_TYPE_BOSSLASER, // �{�X�̃��[�U�[�e
		CHARGEBULLET_TYPE_MAX,
	}CHARGEBULLETTYPE;

	CBullet();  // �R���X�g���N
	~CBullet();	// �f�X�g���N�^

	static HRESULT Load(void); // ���[�h
	static void Unload(void);  // �A�����[�h
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size,
		int nLife, int nDamage, BULLETTYPE BulletType, CHARGEBULLETTYPE ChargeBulletType, OBJTYPE objType); // �N���G�C�g

	HRESULT Init();    // ����������
	void Uninit(void); // �I������
	void Update(void); // �X�V����
	void Draw(void);   // �`�揈��

	void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size,
		int nLife, int nDamage, BULLETTYPE BulletType, CHARGEBULLETTYPE ChargeBulletType, OBJTYPE objType) { // �e�̐ݒ�
		SetPosition(pos); SetSize(size);
		m_pos = pos; m_move = move; m_size = size;
		m_nLife = nLife; m_nDamage = nDamage;
		m_BulletType = BulletType; m_ChargeBulletType = ChargeBulletType;
		SetObjType(objType);
	}

	void Move(void); // ��������
	void BulletNomal(BULLETTYPE BulletType); // �e�̏���
	void BulletCharge(BULLETTYPE BulletType); // �`���[�W�e�̏���
	void BulletLaser(CPlayer::PLAYERNUM PlayerNum, BULLETTYPE BulletType); // ���[�U�[�e�̏���
	void BulletBossLaser(void); // ���[�U�[�e�̏���
	BULLETTYPE GetBulletType(void); // �e�̃^�C�v��Ԃ�
	CHARGEBULLETTYPE GetChargeBulletType(void); // �`���[�W�e�̃^�C�v��Ԃ�
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BULLET_TEXTURE]; // �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3	m_pos;					 // ���̈ʒu
	D3DXVECTOR3	m_move;					 // ���̑���
	D3DXVECTOR3 m_size;					 // �傫��
	int     m_nLife;					 // �e�̗̑�
	int     m_nGetLife;					 // �󂯎�����̗�
	int		m_nDamage;					 // �e�̃_���[�W
	BULLETTYPE m_BulletType;			 // �e�̃^�C�v
	CHARGEBULLETTYPE m_ChargeBulletType; // �`���[�W�e�̃^�C�v
};
#endif