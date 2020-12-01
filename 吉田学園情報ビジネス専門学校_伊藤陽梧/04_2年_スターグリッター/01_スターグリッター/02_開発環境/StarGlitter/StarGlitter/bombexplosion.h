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
// �}�N����`
//=============================================================================
#define BOMBEXPLOSION_ANIMATION_COUNT (10)	// �����̃A�j���[�V�����̃J�E���g(���̃e�N�X�`���̕�����)
#define BOMBEXPLOSION_ANIMATION_PATTERN (2) // �����̃A�j���[�V�����̃p�^�[��(�c�̃e�N�X�`���̕�����)
#define BOMBEXPLOSION_SIZE_X (745.0f)			// �����̏c�̒���
#define BOMBEXPLOSION_SIZE_Y (1080.0f)			// �����̉��̒���

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

	CBombexplosion();
	~CBombexplosion();

	static HRESULT Load(void);
	static void Unload(void);
	static CBombexplosion *Create(D3DXVECTOR3 pos, int nLife, BOMBEXPLOSIONTYPE bombexplosiontype, OBJTYPE objType);

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetExplosion(D3DXVECTOR3 pos, int nLife, BOMBEXPLOSIONTYPE bombexplosiontype, OBJTYPE objType) {
		m_pos = pos; m_nLife = nLife; 
		SetPosition(pos); SetSize(BOMBEXPLOSION_SIZE_X, BOMBEXPLOSION_SIZE_Y);
		m_BombExplosionType = bombexplosiontype; SetObjType(objType);
	}
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;  // �e�N�X�`���̃|�C���^
	D3DXVECTOR3		  m_pos;			   // �����̍��W
	D3DXVECTOR3		  m_Getpos;			   // �󂯎�������W
	float			  m_fSizeX;			   // ���̑傫��
	float			  m_fSizeY;			   // �c�̑傫��
	float			  m_fGetSizeX;		   // �󂯎�������̃T�C�Y
	float			  m_fGetSizeY;		   // �󂯎�����c�̃T�C�Y
	int				  m_nLife;			   // �̗�
	BOMBEXPLOSIONTYPE m_BombExplosionType; // �{���̔����̃^�C�v
};
#endif