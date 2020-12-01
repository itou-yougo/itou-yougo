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

	CExplosion();
	~CExplosion();

	static HRESULT Load(void);
	static void Unload(void);
	static CExplosion *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, EXPLOSIONTYPE ExplosionType, OBJTYPE objType);

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetExplosion(D3DXVECTOR3 pos, float fSizeX, float fSizeY, EXPLOSIONTYPE ExplosionType, OBJTYPE objType) {
		m_pos = pos; m_fSizeX = fSizeX; m_fSizeY = fSizeY;
		SetPosition(pos); SetSize(fSizeX, fSizeY);
		m_ExplosionType = ExplosionType; SetObjType(objType);
	}
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_EXPLOSION_TEXTUTE]; // �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3		  m_pos;		   // ���W
	float			  m_fSizeX;		   // ���̑傫��
	float			  m_fSizeY;		   // �c�̑傫��
	int				  m_nCounterAnim;  // �A�j���[�V�����̃J�E���g
	EXPLOSIONTYPE	  m_ExplosionType; // �����̃^�C�v
};
#endif