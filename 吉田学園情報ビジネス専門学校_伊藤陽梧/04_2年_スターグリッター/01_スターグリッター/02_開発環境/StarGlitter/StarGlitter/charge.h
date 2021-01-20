//=============================================================================
//
// �`���[�W�̏��� [charge.h]
// Author : �ɓ��z��
//
//=============================================================================
#ifndef _CHARGE_H_
#define _CHARGE_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// �`���[�W�N���X
//=============================================================================
class CCharge
{
public:
	typedef enum
	{
		CHARGETYPE_NONE = 0,
		CHARGETYPE_1, // �`���[�W��1�i�K��
		CHARGETYPE_2, // �`���[�W��2�i�K��
		CHARGETYPE_3, // �`���[�W��3�i�K��
		CHARGETYPE_MAX,
	}CHARGETYPE;

	CCharge();  // �R���X�g���N
	~CCharge();	// �f�X�g���N�^ 

	static HRESULT Load(void); // ���[�h
	static void Unload(void);  // �A�����[�h

	static CCharge *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size); // �N���G�C�g
	void SetCharge(D3DXVECTOR3 pos, D3DXVECTOR3 size) {		   // ���W�ƃT�C�Y�̐ݒ�
		m_pos = pos; m_size = size;
	}

	void SetExtend(float fExtendX, float fMaxExtendX, float fExtendY, float fMaxExtendY) { // �������Z�b�g���鏈��
		m_fExtendX += fExtendX; m_fMaxExtendX = fMaxExtendX;
		m_fExtendY += fExtendY; m_fMaxExtendY = fMaxExtendY;
	}

	HRESULT Init();	   // ����������
	void Uninit(void); // �I������
	void Update(void); // �X�V����
	void Draw(void);   // �`�揈��

	void ChangeColor(void);			// �F�ƒ�����ς��鏈��
	CHARGETYPE GetChargeType(void); // �`���[�W�̒i�K��Ԃ�
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;  // �e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	   // ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;		   // ���W
	D3DXVECTOR3				m_size;		   // �傫��
	int						m_nCountColor; // �F��ς���J�E���g
	float					m_fExtendX;	   // �e�N�X�`�������ɐL�΂�
	float					m_fExtendY;	   // �e�N�X�`�����c�ɐL�΂�
	float					m_fMaxExtendX; // �e�N�X�`�������ɐL�΂��ő�l
	float					m_fMaxExtendY; // �e�N�X�`�����c�ɐL�΂��ő�l
	CHARGETYPE				m_chargetye;   // �`���[�W�̒i�K
};
#endif