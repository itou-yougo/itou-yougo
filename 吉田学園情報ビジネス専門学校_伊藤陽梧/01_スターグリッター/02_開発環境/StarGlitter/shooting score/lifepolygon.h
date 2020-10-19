//=============================================================================
//
// ���C�t�|���S���̏��� [lifepolygon.h]
// Author : �ɓ��z��
//
//=============================================================================
#ifndef _LIFEPOLYGON_H_
#define _LIFEPOLYGON_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// ���C�t�|���S���N���X
//=============================================================================
class CLifepolygon
{
public:

	CLifepolygon();
	~CLifepolygon();

	static HRESULT Load(void);
	static void Unload(void);
	static CLifepolygon *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nDivide, int nCount);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetLifePolygon(int nDivide, int nCount);

	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetSize(float fSizeX, float fSizeY) {
		m_fSizeX = fSizeX; m_fSizeY = fSizeY;
	}

private:
	static LPDIRECT3DTEXTURE9 m_pTexture; // �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	  // ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;		  // ���W
	float					m_fSizeX;	  // ���̑傫��
	float					m_fSizeY;	  // �c�̑傫��
};
#endif