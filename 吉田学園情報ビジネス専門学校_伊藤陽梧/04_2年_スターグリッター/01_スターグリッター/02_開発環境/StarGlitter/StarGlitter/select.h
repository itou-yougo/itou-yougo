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

	CSelect();  // �R���X�g���N
	~CSelect();	// �f�X�g���N�^

	static HRESULT Load(void); // ���[�h
	static void Unload(void);  // �A�����[�h
	static CSelect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, SELECTTYPE SelectType); // �N���G�C�g

	HRESULT Init(void); // ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��

	void SetSelect(D3DXVECTOR3 pos, D3DXVECTOR3 size, SELECTTYPE SelectType) { // �Z���N�g�̐ݒ�
		m_pos = pos; m_size = size; m_pSelectType = SelectType;
		SetPosition(pos); SetSize(size);
	}

	void Menu(void);	 // ���j���[�̏���
	void Select(void);	 // �I�ԏ���
	void Decision(void); // ����̏���
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_SELECT_TEXTURE]; // �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9   m_pVtxBuff;				 // ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				  m_pos;					 // �|���S���̈ʒu
	D3DXVECTOR3				  m_size;					 // �傫��
	int						  m_nCount;					 // �J�E���g
	int						  m_nCountSelect;			 // �I�񂾎��̃J�E���g
	bool					  m_bButtonPress;			 // �{�^�������������ǂ���
	CText*					  m_pText[MAX_TEXT]; // �e�L�X�g�̃|�C���^
	SELECTTYPE				  m_pSelectType;			 // �Z���N�g�̃^�C�v
};
#endif