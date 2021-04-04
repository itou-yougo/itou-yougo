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

	CTitleLogo();  // �R���X�g���N
	~CTitleLogo(); // �f�X�g���N�^

	static HRESULT Load(void); // ���[�h
	static void Unload(void);  // �A�����[�h

	static CTitleLogo *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, LOGOTYPE logoType); // �N���G�C�g

	HRESULT Init(void); // ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��

	void SetTitleLogo(D3DXVECTOR3 pos, D3DXVECTOR3 size, LOGOTYPE logoType) { // �^�C�g�����S�̐ݒ�
		m_pos = pos; m_size = size; m_LogoType = logoType;
		SetPosition(pos); SetSize(size);
	}

	void TitleLogo(void); // �^�C�g�����S�̏���
	void PlessEnter(void); // �v���X�G���^�[�̏���
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_LOGO_TEXTURE]; // �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3				  m_pos;	  // ���W
	D3DXVECTOR3				  m_size;	  // �傫��
	int						  m_nCount;	  // �J�E���g
	int						  m_nAlpha;	  // �����x
	bool					  m_bUse;	  // �g�p�\���̔���
	LOGOTYPE				  m_LogoType; // ���S�̃^�C�v
};
#endif