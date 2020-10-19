//=============================================================================
//
// �^�C�g�����S�̏��� [titlelogo.h]
// Author : �ɓ��z��
//
//=============================================================================
#ifndef _TITLELOGO_H_
#define _TITLELOGO_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_LOGO_TEXTURE (3)

//=============================================================================
// �O���錾
//=============================================================================
class CFade;

//=============================================================================
// �^�C�g�����S�N���X
//=============================================================================
class CTitleLogo :public CScene2D
{
public:
	typedef enum
	{
		LOGOTYPE_NONE = 0,
		LOGOTYPE_SIROHAIKEI, // �����w�i
		LOGOTYPE_TITLE,		 // �^�C�g��
		LOGOTYPE_PRESSENTER, // �v���X�G���^�[
		LOGOTYPE_MAX,
	}LOGOTYPE;

	CTitleLogo();
	~CTitleLogo();

	static HRESULT Load(void);
	static void Unload(void);
	static CTitleLogo *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, LOGOTYPE logoType);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetText(D3DXVECTOR3 pos, float fSizeX, float fSizeY, LOGOTYPE logoType) {
		m_pos = pos; m_fSizeX = fSizeX; m_fSizeY = fSizeY; m_LogoType = logoType;
		SetPosition(pos); SetSize(fSizeX, fSizeY);
	}

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_LOGO_TEXTURE]; // �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3				  m_pos;	  // ���W
	float					  m_fSizeX;   // ���̑傫��
	float					  m_fSizeY;   // �c�̑傫��
	int						  m_nCount;	  // �J�E���g
	int						  m_nAlpha;	  // �����x
	bool					  m_bUse;	  // �g�p�\���̔���
	LOGOTYPE				  m_LogoType; // ���S�̃^�C�v
};
#endif