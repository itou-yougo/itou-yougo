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

	CLifepolygon();  // �R���X�g���N
	~CLifepolygon(); // �f�X�g���N�^

	static HRESULT Load(void); // ���[�h
	static void Unload(void);  // �A�����[�h

	static CLifepolygon *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nDivide, int nCount); // �N���G�C�g

	HRESULT Init(void); // ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��

	void SetLifePolygon(int nDivide, int nCount); // ���C�t�̃e�N�X�`���̐ݒ�

	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; } // ���W�̐ݒ�
	void SetSize(D3DXVECTOR3 size) { // �T�C�Y�̐ݒ�
		m_size = size;
	}

private:
	static LPDIRECT3DTEXTURE9 m_pTexture; // �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	  // ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;		  // ���W
	D3DXVECTOR3				m_size;		  // �傫��
};
#endif