//=============================================================================
//
// �Q�[�W�̏��� [gauge.h]
// Author : �ɓ��z��
//
//=============================================================================
#ifndef _GAUGE_H_
#define _GAUGE_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_GAUGE_TEXTURE (3)
#define MAX_GAUGE_EXTEND (276.0f)

//=============================================================================
// �Q�[�W�N���X
//=============================================================================
class CGauge
{
public:
	CGauge();  // �R���X�g���N
	~CGauge(); // �f�X�g���N�^

	static HRESULT Load(void); // ���[�h
	static void Unload(void);  // �A�����[�h

	static CGauge *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size); // �N���G�C�g
	void SetGauge(D3DXVECTOR3 pos, D3DXVECTOR3 size) {		  // ���W�ƃT�C�Y�̐ݒ�
		m_pos = pos; m_size = size;
	}

	HRESULT Init();    // ����������
	void Uninit(void); // �I������
	void Update(void); // �X�V����
	void Draw(void);   // �`�揈��

	void SetExtend(float fExtendX, float fExtendY) { // �������Z�b�g���鏈��
		m_fMaxExtendX += fExtendX; m_fMaxExtendY += fExtendY;
	}
	float GetMaxExtend(void); // �����̍ő�l��Ԃ�
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;  // �e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	   // ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;		   // ���W
	D3DXVECTOR3				m_size;		   // ���W
	float					m_fExtendX;	   // �e�N�X�`�������ɐL�΂�
	float					m_fExtendY;	   // �e�N�X�`�����c�ɐL�΂�
	float					m_fMaxExtendX; // �e�N�X�`�������ɐL�΂��ő�l
	float					m_fMaxExtendY; // �e�N�X�`�����c�ɐL�΂��ő�l
};
#endif