//=============================================================================
//
// �K�E�Z�̃G�t�F�N�g�̏��� [spesialattackeffect.cpp]
// Author : �ɓ��z��
//
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "billboard.h"
#include "particle.h"
#include "spesialattackeffect.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSpesialattackeffect::CSpesialattackeffect()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSpesialattackeffect::~CSpesialattackeffect()
{
}

//=============================================================================
// ��������
//=============================================================================
CSpesialattackeffect * CSpesialattackeffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, int Life)
{
	// CSpesialattackeffect�N���X�̃|�C���^
	CSpesialattackeffect *pSpesialattackeffect;

	// �������m��
	pSpesialattackeffect = new CSpesialattackeffect;

	// �ʒu���W�ݒ�
	pSpesialattackeffect->SetPos(pos);

	// �T�C�Y�ݒ�
	pSpesialattackeffect->SetSize(size);

	// �J���[�ݒ�
	pSpesialattackeffect->SetColor(col);

	// �J���[�ݒ�
	pSpesialattackeffect->SetLife(Life);

	// �A�j���[�V�����̐ݒ�
	pSpesialattackeffect->SetAnimation(SPESIALATTACKEFFECT_COUNTANIM, SPESIALATTACKEFFECT_PATTERNANIM, SPESIALATTACKEFFECT_TIMEANIM);

	// ������
	pSpesialattackeffect->Init();

	// CSpark�N���X�̃|�C���^��Ԃ�
	return pSpesialattackeffect;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CSpesialattackeffect::Init()
{
	// CParticle�N���X��Init
	CParticle::Init(TEX_TYPE_SPESIALATTACK);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CSpesialattackeffect::Uninit(void)
{
	// �I��
	CParticle::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CSpesialattackeffect::Update(void)
{
	// �X�V
	CParticle::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CSpesialattackeffect::Draw(void)
{
	// ���Z�����̃t���O
	SetAdditiveSynthesis();

	// �`��
	CParticle::Draw();
}