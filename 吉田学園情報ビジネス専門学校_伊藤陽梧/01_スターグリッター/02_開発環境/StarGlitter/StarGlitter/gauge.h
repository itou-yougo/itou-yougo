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
	CGauge();
	~CGauge();

	static HRESULT Load(void);
	static void Unload(void);

	static CGauge *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY);
	void SetGauge(D3DXVECTOR3 pos, float fSizeX, float fSizeY) {
		m_pos = pos; m_fSizeX = fSizeX; m_fSizeY = fSizeY;
	}

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetExtend(float fExtendX, float fExtendY) {
		m_fMaxExtendX += fExtendX; m_fMaxExtendY += fExtendY;
	}
	float GetMaxExtend(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;  // �e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	   // ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;		   // ���W
	float					m_fSizeX;	   // ���̑傫��
	float					m_fSizeY;	   // �c�̑傫��
	float					m_fExtendX;	   // �e�N�X�`�������ɐL�΂�
	float					m_fExtendY;	   // �e�N�X�`�����c�ɐL�΂�
	float					m_fMaxExtendX; // �e�N�X�`�������ɐL�΂��ő�l
	float					m_fMaxExtendY; // �e�N�X�`�����c�ɐL�΂��ő�l
};
#endif