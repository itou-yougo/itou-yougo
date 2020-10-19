//=============================================================================
//
// ���C�t�̏��� [hp.h]
// Author : �ɓ��z��
//
//=============================================================================
#ifndef _HP_H_
#define _HP_H_

//=============================================================================
// �O���錾
//=============================================================================
class CLifepolygon;

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene.h"

//=============================================================================
// ���C�t�N���X
//=============================================================================
class CLife : public CScene
{
public:
	typedef enum
	{
		LIFE_TYPE_NONE = 0,
		LIFE_TYPE_PLAYER,  // PLAYER1�̗̑�
		LIFE_TYPE_PLAYER2, // PLAYER2�̗̑�
		LIFE_TYPE_MAX,
	}LIFETYPE;

	CLife();
	~CLife();

	static CLife *Create(int nLife, LIFETYPE LifeType, OBJTYPE objType);

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	int GetLife(void);

	void Damage();
	void Cure();
	//void Damage(int nDamage) {
	//	m_nLife -= nDamage;
	//}

	void SetLife(int nLife) {
		m_nLife = nLife;
	}

	void SetType(LIFETYPE LifeType, OBJTYPE objType) {
		m_LifeType = LifeType;
		SetObjType(objType);
	}

private:
	CLifepolygon* m_pLifepolygon[MAX_LIFEPOLYGON]; // CLifepolygon�̃|�C���^
	int     m_nLife;							   // �̗�
	LIFETYPE m_LifeType;						   // �̗͂̃^�C�v
};
#endif