//=============================================================================
//
// �K�b�`�����̏��� [gattyann..h]
// Author : �ɓ��z��
//
//=============================================================================
#ifndef _GATTYANN_H_
#define _GATTYANN_H_

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_GATTYANN_TEXTURE (8)
#define GATTYANN_SPEED (10.0f)
#define GATTYANN_OPEN_SPEED (15)

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// �K�b�`�����N���X
//=============================================================================
class CGattyann :public CScene2D
{
public:
	typedef enum
	{
		GATTYANN_1 = 0, // 1����
		GATTYANN_2,		// 2����
		GATTYANN_3,		// 3����
		GATTYANN_4,		// 4����
		GATTYANN_5,		// 5����
		GATTYANN_6,		// 6����
		GATTYANN_7,		// 7����
		GATTYANN_8,		// 8����
	}GATTYANNTYPE;

	CGattyann();
	~CGattyann();

	static HRESULT Load(void);
	static void Unload(void);
	static CGattyann *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, GATTYANNTYPE GattyannType);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetGattyann(D3DXVECTOR3 pos, float fSizeX, float fSizeY, GATTYANNTYPE GattyannType) {
		m_pos = pos; m_fSizeX = fSizeX; m_fSizeY = fSizeY; m_GattyannType = GattyannType;
		SetPosition(pos); SetSize(fSizeX, fSizeY);
	}

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_GATTYANN_TEXTURE]; // �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3				  m_pos;		  // ���W
	float					  m_fSizeX;		  // ���̑傫��
	float					  m_fSizeY;		  // �c�̑傫��
	int						  m_nCount;		  // �J�E���g
	GATTYANNTYPE			  m_GattyannType; // �����ڂ�
};
#endif