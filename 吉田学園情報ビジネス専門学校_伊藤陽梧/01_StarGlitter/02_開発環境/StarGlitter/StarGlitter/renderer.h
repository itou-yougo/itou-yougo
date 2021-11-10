//=============================================================================
//
// �����_���[�̏��� [renderer.h]
// Author : �ɓ��z��
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include"main.h"

//=============================================================================
// �����_�����O�N���X
//=============================================================================
class CRenderer
{
public:
	CRenderer();  // �R���X�g���N
	~CRenderer(); // �f�X�g���N�^

	HRESULT Init(HWND hWnd, bool bWindow); // ����������
	void Uninit(void);					   // �I������
	void Update(void);					   // �X�V����
	void Draw(void);					   // �`�揈��
	void SetNumFPS(int nCountFPS) { m_nCountFPS = nCountFPS; } // FPS�̐ݒ�

	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; } // �f�o�C�X��Ԃ�

private:
	void DrawFPS(void);
	LPDIRECT3D9				m_pD3D;			// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9		m_pD3DDevice;	// Device�I�u�W�F�N�g(�`��ɕK�v)
	int						m_nCountFPS;	// FPS�̒l
#ifdef _DEBUG
	LPD3DXFONT				m_pFont;			// �t�H���g�ւ̃|�C���^
#endif

};
#endif