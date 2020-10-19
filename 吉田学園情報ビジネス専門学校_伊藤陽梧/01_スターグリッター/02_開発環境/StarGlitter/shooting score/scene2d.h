//=============================================================================
//
// �|���S���̕`��̏��� [scene2d.h]
// Author : �ɓ��z��
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include"main.h"
#include"scene.h"

//=============================================================================
// �I�u�W�F�N�g�N���X
//=============================================================================
class CScene2D :public CScene
{
public:
	CScene2D(int nPriority = 1);
	virtual~CScene2D();

	static CScene2D *Create();
	void BindTexture(LPDIRECT3DTEXTURE9	Texture);

	virtual HRESULT Init();
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	D3DXVECTOR3 GetPosition(void);
	float GetSizeX(void);
	float GetSizeY(void);

	void UpdateAnimation();
	void UpdateAnimationSelect();
	void UpdateScroll();
	void UpdateTransparency();
	void UpdateColor();

	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }

	void SetSize(float fSizeX, float fSizeY) {
		m_fSizeX = fSizeX; m_fSizeY = fSizeY;
	}

	void SetAnimation(int nCounterAnim, int nPatternAnim, int nTimeAnim) {
		m_nGetCounterAnim = nCounterAnim; m_nGetPatternAnim = nPatternAnim;
		m_nTimeAnim = nTimeAnim; m_nTimeCount = nTimeAnim;
		m_AnimationType = TYPE_ANIMATION;
	}

	void SetAnimationSelect(int nCounterAnim, int nPatternAnim, int nSetPatternAnim, int nTimeAnim) {
		m_nGetCounterAnim = nCounterAnim; m_nGetPatternAnim = nPatternAnim; m_nPatternAnim = nSetPatternAnim;
		m_nTimeAnim = nTimeAnim; m_nTimeCount = nTimeAnim;
		m_AnimationType = TYPE_ANIMATIONSELECT;
	}

	void SetScroll(float nGetScrollX, float nGetScrollY) {
		m_fGetScrollMoveX = nGetScrollX; m_fGetScrollMoveY = nGetScrollY;
		m_AnimationType = TYPE_SCROLL;
	}

	void SetTransparency(bool bUse) {
		m_bTransparencyUse = bUse;
		m_AnimationType = TYPE_TRANSPARENCY;
	}

	void SetColor(int nRed, int nGreen, int nBrue, int nAlpha) {
		m_nRed = nRed; m_nGreen = nGreen;
		m_nBrue = nBrue; m_nAlpha = nAlpha;
		m_AnimationType = TYPE_COLOR;
	}

private:
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_ANIMATION,		  // �A�j���[�V����
		TYPE_ANIMATIONSELECT, // �C�ӂŕς�����A�j���[�V����
		TYPE_SCROLL,		  // ���炵�Ă����A�j���[�V����
		TYPE_TRANSPARENCY,	  // �����ɂ�����̂Ɩ߂��̂��J��Ԃ�
		TYPE_COLOR,			  // �F��ݒ�ł���
		TYPE_MAX,
	}ANIMATIONTYPE;

	LPDIRECT3DTEXTURE9		m_pTexture;		    // �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		    // ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;			    // �|���S���̈ʒu
	float					m_fSizeX;		    // �|���S���̉��̑傫��
	float					m_fSizeY;		    // �|���S���̏c�̑傫��
	float					m_fScrollX;		    // �X�N���[���̉��̈ړ�
	float					m_fScrollY;		    // �X�N���[���̏c�̈ړ�
	float					m_fGetScrollMoveX;  // �X�N���[���̉��̑����̎󂯎��
	float					m_fGetScrollMoveY;  // �X�N���[���̏c�̑����̎󂯎��
	float					m_fExtendX;		    // �e�N�X�`�������ɐL�΂�
	float					m_fExtendY;		    // �e�N�X�`�����c�ɐL�΂�
	int						m_nCounterAnim;	    // �A�j���[�V�����̃J�E���g
	int						m_nPatternAnim;     // �A�j���[�V�����̃p�^�[��
	int						m_nGetCounterAnim;  // �A�j���[�V�����̃J�E���g�̎󂯎��
	int						m_nGetPatternAnim;  // �A�j���[�V�����̃p�^�[���̎󂯎��
	int						m_nTimeAnim;	    // �A�j���[�V�����̎���
	int						m_nTimeCount;	    // �A�j���[�V�����̎��Ԃ̃J�E���g
	int						m_nRed;			    // ��
	int						m_nGreen;		    // ��
	int						m_nBrue;		    // ��
	int						m_nAlpha;		    // �����x
	bool					m_bTransparency;    // �����ɂ���J�E���g
	bool					m_bTransparencyUse; // �����ɂ��邩�ǂ���


	ANIMATIONTYPE m_AnimationType;
};
#endif
