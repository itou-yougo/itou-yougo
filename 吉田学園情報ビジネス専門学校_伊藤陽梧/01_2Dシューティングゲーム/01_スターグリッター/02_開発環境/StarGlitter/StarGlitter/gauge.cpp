//=============================================================================
//
// �Q�[�W�̏��� [gauge.cpp]
// Author : �ɓ��z��
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "gauge.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CGauge::m_pTexture = NULL;

//=============================================================================
// �Q�[�W�N���X�̃R���X�g���N�^
//=============================================================================
CGauge::CGauge()
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fExtendX = 0.0f;
	m_fExtendY = 0.0f;
	m_fMaxExtendX = MAX_GAUGE_EXTEND;
	m_fMaxExtendY = 0.0f;
}

//=============================================================================
// �Q�[�W�N���X�̃f�X�g���N�^
//=============================================================================
CGauge::~CGauge()
{

}

//=============================================================================
// �Q�[�W�N���X�̃e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CGauge::Load(void)
{
	// �C���X�^���X�����������̂��󂯎��
	CRenderer *pRenderer = CManager::GetRenderer();

	// �f�o�C�X���󂯎��
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "", &m_pTexture);

	return S_OK;
}

//=============================================================================
// �Q�[�W�N���X�̃e�N�X�`���̔j��
//=============================================================================
void CGauge::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// �Q�[�W�N���X�̃C���X�^���X����
//=============================================================================
CGauge* CGauge::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CGauge�̃|�C���^
	CGauge *pGauge = NULL;

	// �������̊m��
	pGauge = new CGauge;

	// pGauge��NULL����Ȃ��Ƃ�
	if (pGauge != NULL)
	{
		pGauge->SetGauge(pos, size);

		// ����������
		pGauge->Init();
	}

	// pGauge��Ԃ�
	return pGauge;
}

//=============================================================================
// �Q�[�W�N���X�̏���������
//=============================================================================
HRESULT CGauge::Init()
{
	// VERTEX_2D�̃|�C���^
	VERTEX_2D *pVtx;

	// �C���X�^���X�����������̂��󂯎��
	CRenderer *pRenderer = CManager::GetRenderer();

	// �f�o�C�X���󂯎��
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_�o�b�t�@����
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);

	// rhw�̐ݒ�(�l��1.0�ŌŒ�)
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�(0�`255�͈̔͂Őݒ�)
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �Q�[�W�N���X�̏I������
//=============================================================================
void CGauge::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
// �Q�[�W�N���X�̍X�V����
//=============================================================================
void CGauge::Update(void)
{
	// m_fExtendX��m_fMaxExtendX���傫���Ȃ�Ȃ��悤�ɂ���
	if (m_fExtendX > m_fMaxExtendX)
	{
		m_fExtendX = m_fMaxExtendX;
	}

	// m_fMaxExtendX��MAX_GAUGE_EXTEND���傫���Ȃ�Ȃ��悤�ɂ���
	if (m_fMaxExtendX > MAX_GAUGE_EXTEND)
	{
		m_fMaxExtendX = MAX_GAUGE_EXTEND;
	}

	// VERTEX_2D�̃|�C���^
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y - (m_size.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fMaxExtendX, m_pos.y - (m_size.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y + (m_size.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fMaxExtendX, m_pos.y + (m_size.y / 2), 0.0f);

	// ���_�J���[�̐ݒ�(0�`255�͈̔͂Őݒ�)
	pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �Q�[�W�N���X�̕`�揈��
//=============================================================================
void CGauge::Draw(void)
{
	// �C���X�^���X�����������̂��󂯎��
	CRenderer *pRenderer = CManager::GetRenderer();

	// �f�o�C�X���󂯎��
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// �Q�[�W�N���X�̃Q�[�W�̍ő�l��Ԃ�����
//=============================================================================
float CGauge::GetMaxExtend(void)
{
	return m_fMaxExtendX;
}

