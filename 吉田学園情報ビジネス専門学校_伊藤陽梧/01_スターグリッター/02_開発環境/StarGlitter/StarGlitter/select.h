//=============================================================================
//
// �Z���N�g�̏��� [select.h]
// Author : �ɓ��z��
//
//=============================================================================
#ifndef _SELECT_H_
#define _SELECT_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_SELECT_TEXTURE (2) // �Z���N�g�̃e�N�X�`���̍ő吔
#define MAX_TEXT (2) // �e�L�X�g�̍ő吔

//=============================================================================
// �O���錾
//=============================================================================
class CText;

//=============================================================================
// �Z���N�g�N���X
//=============================================================================
class CSelect :public CScene2D
{
public:
	typedef enum
	{
		SELECTTYPE_KUROHAIKEI = 0, // �����w�i
		SELECTTYPE_MENU,		   // ���j���[
	}SELECTTYPE;
	CSelect();
	~CSelect();

	static HRESULT Load(void);
	static void Unload(void);
	static CSelect *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, SELECTTYPE SelectType);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetText(D3DXVECTOR3 pos, float fSizeX, float fSizeY, SELECTTYPE SelectType) {
		m_pos = pos; m_fSizeX = fSizeX; m_fSizeY = fSizeY; m_pSelectType = SelectType;
		SetPosition(pos); SetSize(fSizeX, fSizeY);
	}

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_SELECT_TEXTURE]; // �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9   m_pVtxBuff;				 // ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				  m_pos;					 // �|���S���̈ʒu
	int						  m_nCount;					 // �J�E���g
	int						  m_nCountSelect;			 // �I�񂾎��̃J�E���g
	float					  m_fSizeX;					 // �|���S���̉��̑傫��
	float					  m_fSizeY;					 // �|���S���̏c�̑傫��
	bool					  m_bButtonPress;			 // �{�^�������������ǂ���
	CText*					  m_pText[MAX_TEXT]; // �e�L�X�g�̃|�C���^
	SELECTTYPE				  m_pSelectType;			 // �Z���N�g�̃^�C�v
};
#endif