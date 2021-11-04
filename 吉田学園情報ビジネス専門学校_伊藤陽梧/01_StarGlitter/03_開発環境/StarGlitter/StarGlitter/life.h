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

	CLife();  // �R���X�g���N
	~CLife(); // �f�X�g���N�^

	static CLife *Create(int nLife, LIFETYPE LifeType, OBJTYPE objType); // �N���G�C�g

	HRESULT Init();    // ����������
	void Uninit(void); // �I������
	void Update(void); // �X�V����
	void Draw(void);   // �`�揈��

	int GetLife(void); // �̗͂�Ԃ�

	void Damage(); // �_���[�W�̏���
	void Cure(); // �񕜂̏���
	//void Damage(int nDamage) {
	//	m_nLife -= nDamage;
	//}

	void SetLife(int nLife) { // �̗͂̐ݒ�
		m_nLife = nLife;
	}

	void SetType(LIFETYPE LifeType, OBJTYPE objType) { // �̗͂̏���
		m_LifeType = LifeType;
		SetObjType(objType);
	}

private:
	CLifepolygon* m_pLifepolygon[MAX_LIFEPOLYGON]; // CLifepolygon�̃|�C���^
	int     m_nLife;							   // �̗�
	LIFETYPE m_LifeType;						   // �̗͂̃^�C�v
};
#endif