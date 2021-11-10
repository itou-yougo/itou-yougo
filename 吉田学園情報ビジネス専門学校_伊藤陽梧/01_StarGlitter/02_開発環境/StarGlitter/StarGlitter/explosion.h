//=============================================================================
//
// �|���S���̕`��̏��� [explosion.h]
// Author : �ɓ��z��
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_EXPLOSION_TEXTUTE (2)

//=============================================================================
// �O���錾
//=============================================================================
class CSound;

//=============================================================================
// �G�N�X�v���[�W�����N���X
//=============================================================================
class CExplosion :public CScene2D
{
public:
	typedef enum
	{
		EXPLOSIONTYPE_NOMAL = 0, // �e�̔���
		EXPLOSIONTYPE_BOSS,		 // �{�X�A�^�b�N�̔���
	}EXPLOSIONTYPE;

	CExplosion();  // �R���X�g���N
	~CExplosion(); // �f�X�g���N�^

	static HRESULT Load(void); // ���[�h
	static void Unload(void);  // �A�����[�h
	static CExplosion *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, 
		EXPLOSIONTYPE ExplosionType, OBJTYPE objType); // �N���G�C�g

	HRESULT Init();    // ����������
	void Uninit(void); // �I������
	void Update(void); // �X�V����
	void Draw(void);   // �`�揈��

	void SetExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 size, 
		EXPLOSIONTYPE ExplosionType, OBJTYPE objType) { // �����̐ݒ�
		m_pos = pos; m_size = size;
		SetPosition(pos); SetSize(size);
		m_ExplosionType = ExplosionType; SetObjType(objType);
	}
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_EXPLOSION_TEXTUTE]; // �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3		  m_pos;		   // ���W
	D3DXVECTOR3		  m_size;		   // �傫��
	int				  m_nCounterAnim;  // �A�j���[�V�����̃J�E���g
	EXPLOSIONTYPE	  m_ExplosionType; // �����̃^�C�v
};
#endif