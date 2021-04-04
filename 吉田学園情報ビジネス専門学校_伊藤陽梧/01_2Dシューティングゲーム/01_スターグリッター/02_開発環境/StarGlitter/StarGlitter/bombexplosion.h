//=============================================================================
//
// �{���̔����̏��� [bombexplosion.h]
// Author : �ɓ��z��
//
//=============================================================================
#ifndef _BOMBEXPLOSION_H_
#define _BOMBEXPLOSION_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// �O���錾
//=============================================================================
class CSound;

//=============================================================================
// �{���̔����N���X
//=============================================================================
class CBombexplosion :public CScene2D
{
public:
	typedef enum
	{
		BOMBEXPLOSION_NONE = 0,
		BOMBEXPLOSION_PLAYER,  // �v���C���[1�̃{���̔���
		BOMBEXPLOSION_PLAYER2, // �v���C���[2�̃{���̔���
		BOMBEXPLOSION_MAX,
	}BOMBEXPLOSIONTYPE;

	CBombexplosion();  // �R���X�g���N
	~CBombexplosion(); // �f�X�g���N�^

	static HRESULT Load(void); // ���[�h
	static void Unload(void);  // �A�����[�h
	static CBombexplosion *Create(D3DXVECTOR3 pos, int nLife, BOMBEXPLOSIONTYPE bombexplosiontype, OBJTYPE objType); // �N���G�C�g

	HRESULT Init();    // ����������
	void Uninit(void); // �I������
	void Update(void); // �X�V����
	void Draw(void);   // �`�揈��

	void SetBombexplosion(D3DXVECTOR3 pos, int nLife, BOMBEXPLOSIONTYPE bombexplosiontype, OBJTYPE objType) { // �{���̔����̐ݒ�
		m_pos = pos; m_nLife = nLife; 
		SetPosition(pos); m_BombExplosionType = bombexplosiontype; SetObjType(objType);
	}
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;  // �e�N�X�`���̃|�C���^
	D3DXVECTOR3		  m_pos;			   // �����̍��W
	int				  m_nLife;			   // �̗�
	BOMBEXPLOSIONTYPE m_BombExplosionType; // �{���̔����̃^�C�v
};
#endif