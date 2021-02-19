//=============================================================================
//
// �p�[�e�B�N���̏��� [particle.h]
// Author : �ɓ��z��
//
//=============================================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "billboard.h"

//=============================================================================
// �p�[�e�B�N���N���X
//=============================================================================
class CParticle : public CBillboard
{
public:
	typedef enum
		// �e�N�X�`���^�C�v
	{
		TEX_TYPE_NONE = 0,
		TEX_TYPE_1,
		TEX_TYPE_2,
		TEX_TYPE_SWORD,
		TEX_TYPE_SPARK,
		TEX_TYPE_SPESIALATTACK,
		TEX_TYPE_FIRE,
		TEX_TYPE_MAGICCIRCLE,
		TEX_TYPE_MAX,
	}TEX_TYPE;

	CParticle(int nPriority = OBJTYPE_PARTICLE);
	~CParticle();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(TEX_TYPE TexType);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetAngle(float fangle) { m_fAngle = fangle; }
	void SetMove(D3DXVECTOR3 move) { m_Move = move; }

	float GetAngle(void) { return m_fAngle; }
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[TEX_TYPE_MAX];	// texture
	TEX_TYPE m_TexType;									// �e�N�X�`���^�C�v
	float m_fAngle;										// �p�x
	D3DXVECTOR3 m_Move;									// �p�x
};
#endif