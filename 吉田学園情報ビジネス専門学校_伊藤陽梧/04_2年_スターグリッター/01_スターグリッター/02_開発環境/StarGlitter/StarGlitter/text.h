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

	CText();
	~CText();

	static HRESULT Load(void);
	static void Unload(void);
	static CText *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, TEXTTYPE TextType);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetText(D3DXVECTOR3 pos, float fSizeX, float fSizeY, TEXTTYPE TextType) {
		m_pos = pos; m_fSizeX = fSizeX; m_fSizeY = fSizeY; m_TextType = TextType;
		SetPosition(pos); SetSize(fSizeX, fSizeY);
	}

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_TEXT_TEXTURE]; // �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3				  m_pos;	  // ���W
	int						  m_nAlpha;   // �����x
	int						  m_nCount;   // �J�E���g
	float					  m_fSizeX;   // ���̑傫��
	float					  m_fSizeY;   // �c�̑傫��
	bool					  m_bUse;	  // �g���Ă��邩�̔���
	TEXTTYPE				  m_TextType; // �e�L�X�g�̃^�C�v
};
#endif