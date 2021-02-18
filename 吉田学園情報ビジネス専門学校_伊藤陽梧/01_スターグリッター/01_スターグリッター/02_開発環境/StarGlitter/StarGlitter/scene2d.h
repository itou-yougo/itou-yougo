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
	CScene2D(int nPriority = 1); // �R���X�g���N
	virtual~CScene2D();			 // �f�X�g���N�^

	static CScene2D *Create(); // �N���G�C�g
	void BindTexture(LPDIRECT3DTEXTURE9	Texture); // �e�N�X�`���̃o�C���h

	virtual HRESULT Init();    // ����������
	virtual void Uninit(void); // �I������
	virtual void Update(void); // �X�V����
	virtual void Draw(void);   // �`�揈��

	D3DXVECTOR3 GetPosition(void); // ���W��Ԃ�
	D3DXVECTOR3 GetSize(void);	   // �T�C�Y��Ԃ�

	void UpdateAnimation(); // �A�j���[�V�����̏���
	void UpdateAnimationSelect(); // �C�ӂŕς�����A�j���[�V�����̏���
	void UpdateScroll(); // �X�N���[���̏���
	void UpdateTransparency(); // �������̏���
	void UpdateColor(); // �F�̏���

	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }

	void SetSize(D3DXVECTOR3 size) { m_size = size; }

	void SetAnimation(int nCounterAnim, int nPatternAnim, int nTimeAnim) { // �A�j���[�V�����̐ݒ�
		m_nGetCounterAnim = nCounterAnim; m_nGetPatternAnim = nPatternAnim;
		m_nTimeAnim = nTimeAnim; m_nTimeCount = nTimeAnim;
		m_AnimationType = TYPE_ANIMATION;
	}

	void SetAnimationSelect(int nCounterAnim, int nPatternAnim, int nSetPatternAnim, int nTimeAnim) { // �C�ӂŕς�����A�j���[�V�����̐ݒ�
		m_nGetCounterAnim = nCounterAnim; m_nGetPatternAnim = nPatternAnim; m_nPatternAnim = nSetPatternAnim;
		m_nTimeAnim = nTimeAnim; m_nTimeCount = nTimeAnim;
		m_AnimationType = TYPE_ANIMATIONSELECT;
	}

	void SetScroll(float nGetScrollX, float nGetScrollY) { // �X�N���[���̐ݒ�
		m_fGetScrollMoveX = nGetScrollX; m_fGetScrollMoveY = nGetScrollY;
		m_AnimationType = TYPE_SCROLL;
	}

	void SetTransparency(bool bUse) { // �������̐ݒ�
		m_bTransparencyUse = bUse;
		m_AnimationType = TYPE_TRANSPARENCY;
	}

	void SetColor(int nRed, int nGreen, int nBrue, int nAlpha) { // �F�̐ݒ�
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
	D3DXVECTOR3				m_size;			    // �|���S���̈ʒu
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
