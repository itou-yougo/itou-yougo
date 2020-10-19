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
	CEffect();
	~CEffect();

	static HRESULT Load(void);
	static void Unload(void);
	static CEffect *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nLife, int nRed, int nGreen, int nBrue, int nAlpha, EFFECTTYPE EffectType, OBJTYPE objType);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetEffect(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nLife, int nRed, int nGreen, int nBrue, int nAlpha, EFFECTTYPE EffectType, OBJTYPE objType) {
		m_pos = pos; m_fSizeX = fSizeX; m_fSizeY = fSizeY;
		m_nLife = nLife; m_nRed = nRed; m_nGreen = nGreen;
		m_nBrue = nBrue; m_nAlpha = nAlpha;
		m_EffectType = EffectType;
		SetPosition(pos); SetSize(fSizeX, fSizeY);
		SetObjType(objType);
	}

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_EFFECT_TEXTURE]; // �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3				  m_pos;	  // ���W
	int						  m_nLife;	  // �̗�
	int						  m_nRed;	  // ��
	int						  m_nGreen;	  // ��
	int						  m_nBrue;	  // ��
	int						  m_nAlpha;	  // �����x
	float					  m_fSizeX;	  // ���̑傫��
	float					  m_fSizeY;	  // �c�̑傫��
	EFFECTTYPE m_EffectType;
};
#endif