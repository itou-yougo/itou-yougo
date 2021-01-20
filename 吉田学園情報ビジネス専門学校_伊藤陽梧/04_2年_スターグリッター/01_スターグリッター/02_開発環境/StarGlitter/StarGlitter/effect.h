//=============================================================================
//
// �G�t�F�N�g�̏��� [effect.h]
// Author : �ɓ��z��
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_EFFECT_TEXTURE (2)

//=============================================================================
// �G�t�F�N�g�N���X
//=============================================================================
class CEffect :public CScene2D
{
public:
	typedef enum
	{
		EFFECTTYPE_BULLET = 0,  // �e�̃G�t�F�N�g
		EFFECTTYPE_CHARGESTATE, // �`���[�W�̃G�t�F�N�g
	}EFFECTTYPE;

	CEffect();  // �R���X�g���N
	~CEffect();	// �f�X�g���N�^

	static HRESULT Load(void); // ���[�h
	static void Unload(void);  // �A�����[�h
	static CEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,
		int nLife, int nRed, int nGreen, int nBrue, int nAlpha, EFFECTTYPE EffectType, OBJTYPE objType); // �N���G�C�g

	HRESULT Init(void); // ����������
	void Uninit(void);  // �I������
	void Update(void);  // �X�V����
	void Draw(void);    // �`�揈��

	void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 size,
		int nLife, int nRed, int nGreen, int nBrue, int nAlpha, EFFECTTYPE EffectType, OBJTYPE objType) { // �G�t�F�N�g�̐ݒ�
		m_pos = pos; m_size = size;
		m_nLife = nLife; m_nRed = nRed; m_nGreen = nGreen;
		m_nBrue = nBrue; m_nAlpha = nAlpha;
		m_EffectType = EffectType;
		SetPosition(pos); SetSize(size);
		SetObjType(objType);
	}

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_EFFECT_TEXTURE]; // �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3				  m_pos;	  // ���W
	D3DXVECTOR3				  m_size;	  // �傫��
	int						  m_nLife;	  // �̗�
	int						  m_nRed;	  // ��
	int						  m_nGreen;	  // ��
	int						  m_nBrue;	  // ��
	int						  m_nAlpha;	  // �����x
	EFFECTTYPE m_EffectType;
};
#endif