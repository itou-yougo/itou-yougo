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
		BULLET_TYPE_PLAYER,  // PLAYER1�̒e
		BULLET_TYPE_PLAYER2, // PLAYER2�̒e
		BULLET_TYPE_BOSS,	 // �{�X�̒e
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

	CBullet();
	~CBullet();

	static HRESULT Load(void);
	static void Unload(void);
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fSizeX, float fSizeY, int nLife, int nDamage, BULLETTYPE BulletType, CHARGEBULLETTYPE ChargeBulletType, OBJTYPE objType);

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fSizeX, float fSizeY, int nLife, int nDamage, BULLETTYPE BulletType, CHARGEBULLETTYPE ChargeBulletType, OBJTYPE objType) {
		SetPosition(pos); SetSize(fSizeX, fSizeY);
		m_pos = pos; m_move = move;
		m_fSizeX = fSizeX; m_fSizeY = fSizeY;
		m_nLife = nLife; m_nDamage = nDamage;
		m_BulletType = BulletType; m_ChargeBulletType = ChargeBulletType;
		SetObjType(objType);
	}

	BULLETTYPE GetBulletType(void);
	CHARGEBULLETTYPE GetChargeBulletType(void);
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BULLET_TEXTURE]; // �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3	m_pos;					 // ���̈ʒu
	D3DXVECTOR3	m_move;					 // ���̑���
	D3DXVECTOR3 m_Getpos;				 // �󂯎�������W
	float	m_fSizeX;					 // �|���S���̉��̑傫��
	float	m_fSizeY;					 // �|���S���̏c�̑傫��
	float	m_fGetSizeX;				 // �|���S���̉��̑傫��
	float	m_fGetSizeY;				 // �|���S���̏c�̑傫��
	int     m_nLife;					 // �e�̗̑�
	int     m_nGetLife;					 // �󂯎�����̗�
	int		m_nDamage;					 // �e�̃_���[�W
	BULLETTYPE m_BulletType;			 // �e�̃^�C�v
	CHARGEBULLETTYPE m_ChargeBulletType; // �`���[�W�e�̃^�C�v
};
#endif