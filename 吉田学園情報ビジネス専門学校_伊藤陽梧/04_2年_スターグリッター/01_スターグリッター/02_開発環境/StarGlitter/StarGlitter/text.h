//=============================================================================
//
// �����̕`��̏��� [text.h]
// Author : �ɓ��z��
//
//=============================================================================
#ifndef _TEXT_H_
#define _TEXT_H_

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_TEXT_TEXTURE (6)

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// �v���C���[�N���X
//=============================================================================
class CText :public CScene2D
{
public:
	typedef enum
	{
		TEXTTYPE_RESTART = 0, // ������x�n�߂�
		TEXTTYPE_MODORU,	  // �^�C�g���ɖ߂�
		TEXTTYPE_READY,		  // READY�̕���
		TEXTTYPE_GO,		  // GO�̕���
		TEXTTYPE_KO,		  // KO�̕���
		TEXTTYPE_WON,		  // WON�̕���
		TEXTTYPE_LOST,		  // LOST�̕���
		TEXTTYPE_MAX,
	}TEXTTYPE;

	CText();  // �R���X�g���N
	~CText(); // �f�X�g���N�^

	static HRESULT Load(void); // ���[�h
	static void Unload(void);  // �A�����[�h
	static CText *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TEXTTYPE TextType); // �N���G�C�g

	HRESULT Init(void); // ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��

	void SetText(D3DXVECTOR3 pos, D3DXVECTOR3 size, TEXTTYPE TextType) { // �e�L�X�g�̐ݒ�
		m_pos = pos; m_size = size; m_TextType = TextType;
		SetPosition(pos); SetSize(size);
	}

	void Ready(void); // Ready�̕����̏���
	void Go(void);	  // Go�̕����̏���
	void Ko(void);	  // Ko�̕����̏���
	void Won(void);   // Won�̕����̏���
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_TEXT_TEXTURE]; // �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3				  m_pos;	  // ���W
	D3DXVECTOR3				  m_size;	  // �傫��
	int						  m_nAlpha;   // �����x
	int						  m_nCount;   // �J�E���g
	bool					  m_bUse;	  // �g���Ă��邩�̔���
	TEXTTYPE				  m_TextType; // �e�L�X�g�̃^�C�v
};
#endif