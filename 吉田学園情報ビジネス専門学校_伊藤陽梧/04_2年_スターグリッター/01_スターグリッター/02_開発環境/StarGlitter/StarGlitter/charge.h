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

	CCharge();
	~CCharge();

	static HRESULT Load(void);
	static void Unload(void);

	static CCharge *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY);
	void SetCharge(D3DXVECTOR3 pos, float fSizeX, float fSizeY) {
		m_pos = pos; m_fSizeX = fSizeX; m_fSizeY = fSizeY;
	}

	void SetExtend(float fExtendX, float fMaxExtendX, float fExtendY, float fMaxExtendY) {
		m_fExtendX += fExtendX; m_fMaxExtendX = fMaxExtendX;
		m_fExtendY += fExtendY; m_fMaxExtendY = fMaxExtendY;
	}

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	CHARGETYPE GetChargeType(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;  // �e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	   // ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;		   // ���W
	int						m_nCountColor; // �F��ς���J�E���g
	float					m_fSizeX;	   // ���̑傫��
	float					m_fSizeY;	   // �c�̑傫��
	float					m_fExtendX;	   // �e�N�X�`�������ɐL�΂�
	float					m_fExtendY;	   // �e�N�X�`�����c�ɐL�΂�
	float					m_fMaxExtendX; // �e�N�X�`�������ɐL�΂��ő�l
	float					m_fMaxExtendY; // �e�N�X�`�����c�ɐL�΂��ő�l
	CHARGETYPE				m_chargetye;   // �`���[�W�̒i�K
};
#endif