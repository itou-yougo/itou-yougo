#pragma once
//=============================================================================
//
// �t�F�[�h�̏��� [fade.h]
// Author : �ɓ��z��
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene.h"
#include "manager.h"

//=============================================================================
// �t�F�[�h�N���X
//=============================================================================
class CFade :public CScene
{
public:
	typedef enum
	{
		FADE_NOME = 0,  //�����Ȃ����
		FADE_IN,      //�t�F�[�h�C������
		FADE_OUT,     //�t�F�[�h�A�E�g����
		FADE_MAX
	}FADE;

	CFade();  // �R���X�g���N
	~CFade(); // �f�X�g���N�^

	static CFade *Create(void); // �N���G�C�g

	HRESULT Init(void); // ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��

	void SetFade(CManager::MODE modeNext); // �t�F�[�h�̐ݒ�
	void SetFadeType(FADE fade) { // �^�C�v�̐ݒ�
		m_fade = fade; SetObjType(OBJTYPE_FADE);
	}

	FADE GetFade(void); // �t�F�[�h�̏�Ԃ̎󂯎��

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;  //���_�o�b�t�@�ւ̃|�C���^
	FADE					m_fade;		 //�t�F�[�h���
	CManager::MODE			m_modeNext;	 //���̉��(���[�h)
	D3DXCOLOR				m_colorFade; //�t�F�[�h�F
};

#endif
