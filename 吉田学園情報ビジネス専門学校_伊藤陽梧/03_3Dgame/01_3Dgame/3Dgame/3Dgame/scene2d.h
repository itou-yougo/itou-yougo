//=============================================================================
//
// 2D�|���S���̏��� [scene3d.h]
// Author : �ɓ��z��
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "scene.h"

//=============================================================================
// CScene2D�N���X
//=============================================================================
class CScene2D :public CScene
{
public:
	CScene2D(int nPriority = OBJTYPE_NONE);
	~CScene2D();

	static CScene2D *Create(float nPosX, float nPosY);

	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }		// �ʒu
	void SetSize(D3DXVECTOR3 size) { m_size = size; }		// �T�C�Y
	void SetColor(D3DXCOLOR color) { m_color = color;}		// �J���[
	void SetLifebar(float fMaxHp, float fCur, D3DXCOLOR col);	// HP�o�[�̐ݒ�

	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXCOLOR GetColor(void) { return m_color; }

private:
	LPDIRECT3DTEXTURE9		m_pTexture;				// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;				// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;					// �|���S���̈ʒu
	D3DXVECTOR3				m_size;
	D3DXCOLOR				m_color;
};

#endif // !_SCENE2D_H_
