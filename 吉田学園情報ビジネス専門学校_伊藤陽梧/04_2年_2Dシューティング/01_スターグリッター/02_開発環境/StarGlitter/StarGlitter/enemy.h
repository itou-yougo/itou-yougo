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

	CEnemy();
	~CEnemy();

	static HRESULT Load(void);
	static void Unload(void);
	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fSizeX, float fSizeY, int nLife, OBJTYPE objType);

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fSizeX, float fSizeY, int nLife, OBJTYPE objType) {
		SetPosition(pos); SetSize(fSizeX, fSizeY); m_pos = pos;
		m_move = move; m_fSizeX = fSizeX; m_fSizeY = fSizeY;
		m_nLife = nLife; SetObjType(objType);
	}

	void EnemyDamage(int nDamage, DAMAGETYPE DamageType, CBullet::BULLETTYPE BulletType);
private:
	CGauge* m_pGauge; // �Q�[�W�̃|�C���^
	static LPDIRECT3DTEXTURE9 m_pTexture; // �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3			m_pos;		   // �ʒu
	D3DXVECTOR3			m_move;		   // ���x
	float				m_fSizeX;	   // ���̑傫��
	float				m_fSizeY;	   // �c�̑傫��
	int					m_nLife;	   // �G�̗̑�
	int					m_nOjamaCount; // ������܂̃J�E���g
	DAMAGETYPE			m_DamageType;  // �_���[�W�̃^�C�v
	CBullet::BULLETTYPE m_BulletType;  // �N�̒e�Ȃ̂�
};
#endif