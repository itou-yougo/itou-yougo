//=============================================================================
//
// �t�F�[�h�̏��� [fade.cpp]
// Author :�@�ɓ��z��
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "fade.h"
#include "renderer.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define FADE_RATE (0.05f)

//=============================================================================
// �t�F�[�h�N���X�̃R���X�g���N�^
//=============================================================================
CFade::CFade() :CScene(OBJTYPE_FADE)
{
	m_pVtxBuff = NULL;
	m_fade = FADE_NOME;
	m_modeNext = CManager::MODE_TITLE;
	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f); //�������(�s����)
}

//=============================================================================
// �t�F�[�h�N���X�̃f�X�g���N�^
//=============================================================================
CFade::~CFade()
{

}

//=============================================================================
// �t�F�[�h�N���X�̃N���G�C�g
//=============================================================================
CFade * CFade::Create()
{
	// CFade�̃|�C���^
	CFade *pFade = NULL;

	// �������̊m��
	pFade = new CFade;

	// pFade��NULL����Ȃ��Ƃ�
	if (pFade != NULL)
	{
		// ����������
		pFade->Init();
	}

	// pFade��Ԃ�
	return pFade;
}

//=============================================================================
// �t�F�[�h�N���X�̏���������
//=============================================================================
HRESULT CFade::Init()
{
	SetObjType(OBJTYPE_FADE);

	// �C���X�^���X�����������̂��󂯎��
	CRenderer *pRenderer = CManager::GetRenderer();

	// �f�o�C�X���󂯎��
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	VERTEX_2D *pVtx;//���_���̃|�C���^

	//�I�u�W�F�N�g�̒��_�o�b�t�@����
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�i�E���Őݒ肷��j
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[
	pVtx[0].col = m_colorFade;
	pVtx[1].col = m_colorFade;
	pVtx[2].col = m_colorFade;
	pVtx[3].col = m_colorFade;

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�f�[�^�A�����b�N
	m_pVtxBuff->Unlock();

	m_fade = FADE_IN;
	return S_OK;
}

//=============================================================================
// �t�F�[�h�N���X�̏I������
//=============================================================================
void CFade::Uninit(void)
{
	//���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	Release();
}

//=============================================================================
// �t�F�[�h�N���X�̍X�V����
//=============================================================================
void CFade::Update(void)
{
	VERTEX_2D *pVtx;

	if (m_fade != FADE_NOME)
	{//�t�F�[�h�C������
		if (m_fade == FADE_IN)
		{//�t�F�[�h�C������
			m_colorFade.a -= FADE_RATE;
			//���l�����Z���Č��̉�ʂ𕂂��オ�点��
			if (m_colorFade.a <= 0.0f)
			{
				//�t�F�[�h�����I��
				m_colorFade.a = 0.0f;
				m_fade = FADE_NOME;
			}
		}
		else if (m_fade == FADE_OUT)
		{//�t�F�[�h�A�E�g����
			m_colorFade.a += FADE_RATE;
			//���l�����Z���Č��̉�ʂ������Ă���
			if (m_colorFade.a >= 1.0f)
			{
				//�t�F�[�h�C�������ɐ؂�ւ�
				m_fade = FADE_IN;
				m_colorFade.a = 1.0f;
				//���[�h�ݒ�
				CManager::SetMode(m_modeNext);
			}
		}
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//���_�J���[��ݒ�i0�`255�̒l�Őݒ肷��j
		pVtx[0].col = m_colorFade;
		pVtx[1].col = m_colorFade;
		pVtx[2].col = m_colorFade;
		pVtx[3].col = m_colorFade;

		//���_�f�[�^���A�����b�N����
		m_pVtxBuff->Unlock();
	}
}

//=============================================================================
// �t�F�[�h�N���X�̕`�揈��
//=============================================================================
void CFade::Draw(void)
{
	// �C���X�^���X�����������̂��󂯎��
	CRenderer *pRenderer = CManager::GetRenderer();

	// �f�o�C�X���󂯎��
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	pDevice->SetTexture(0, NULL);
}

//=============================================================================
// �t�F�[�h�N���X�̃Z�b�g
//=============================================================================
void CFade::SetFade(CManager::MODE modeNext)
{
	m_fade = FADE_OUT;
	m_modeNext = modeNext;
}

//=============================================================================
// �t�F�[�h�̎擾��
//=============================================================================
CFade::FADE CFade::GetFade(void)
{
	return m_fade;
}