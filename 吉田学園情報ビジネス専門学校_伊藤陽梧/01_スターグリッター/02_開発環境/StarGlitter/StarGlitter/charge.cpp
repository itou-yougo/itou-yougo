//=============================================================================
//
// �`���[�W�̏��� [charge.cpp]
// Author : �ɓ��z��
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "charge.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CCharge::m_pTexture = NULL;

//=============================================================================
// �`���[�W�N���X�̃R���X�g���N�^
//=============================================================================
CCharge::CCharge()
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCountColor = 0;
	m_fSizeX = 0.0f;
	m_fSizeY = 0.0f;
	m_fExtendX = 0.0f;
	m_fExtendY = 0.0f;
	m_fMaxExtendX = 0.0f;
	m_fMaxExtendY = 0.0f;
	m_chargetye = CHARGETYPE_NONE;
}

//=============================================================================
// �`���[�W�N���X�̃f�X�g���N�^
//=============================================================================
CCharge::~CCharge()
{

}

//=============================================================================
// �`���[�W�N���X�̃`���[�W�̃e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CCharge::Load(void)
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
// �`���[�W�N���X�̃`���[�W�̃e�N�X�`���̔j��
//=============================================================================
void CCharge::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// �`���[�W�N���X�̃C���X�^���X����
//=============================================================================
CCharge* CCharge::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	// CCharge�̃|�C���^
	CCharge *pGauge = NULL;

	// �������̊m��
	pGauge = new CCharge;

	// pGauge��NULL����Ȃ��Ƃ�
	if (pGauge != NULL)
	{
		pGauge->SetCharge(pos, fSizeX, fSizeY);

		// ����������
		pGauge->Init();
	}

	// pGauge��Ԃ�
	return pGauge;
}

//=============================================================================
// �`���[�W�N���X�̏���������
//=============================================================================
HRESULT CCharge::Init()
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
// �`���[�W�N���X�̏I������
//=============================================================================
void CCharge::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
// �`���[�W�N���X�̍X�V����
//=============================================================================
void CCharge::Update(void)
{
	// m_fExtendX��m_fMaxExtendX���傫���Ȃ�����
	if (m_fExtendX > m_fMaxExtendX)
	{
		m_fExtendX = m_fMaxExtendX;
	}
	// m_fExtendX��0.0f��菬�����Ȃ�����
	if (m_fExtendX < 0.0f)
	{
		m_fExtendX = 0.0f;
	}

	// VERTEX_2D�̃|�C���^
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y - (m_fSizeY / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_fExtendX / m_fMaxExtendX) * m_fMaxExtendX, m_pos.y - (m_fSizeY / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y + (m_fSizeY / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_fExtendX / m_fMaxExtendX) * m_fMaxExtendX, m_pos.y + (m_fSizeY / 2), 0.0f);

	// m_fExtendX��0.0f�ȏ�92.0f��菬����������
	if (m_fExtendX >= 0.0f && m_fExtendX < 92.0f)
	{
		pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

		// m_chargetye�̐ݒ�
		m_chargetye = CHARGETYPE_NONE;
	}
	// m_fExtendX��92.0f�ȏ�184.0f��菬����������
	if (m_fExtendX >= 92.0f && m_fExtendX < 184.0f)
	{
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

		// m_chargetye�̐ݒ�
		m_chargetye = CHARGETYPE_1;
	}
	// m_fExtendX��184.0f�ȏ�276.0f��菬����������
	if (m_fExtendX >= 184.0f && m_fExtendX < 276.0f)
	{
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);

		// m_chargetye�̐ݒ�
		m_chargetye = CHARGETYPE_2;
	}
	// m_fExtendX��276.0f��������
	if (m_fExtendX == 276.0f)
	{
		// m_nCountColor��0�̎�
		if (m_nCountColor == 0)
		{
			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

			// m_nCountColor�̉��Z
			m_nCountColor++;
		}
		// m_nCountColor��1�̎�
		else if (m_nCountColor == 1)
		{
			pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

			// m_nCountColor�̉��Z
			m_nCountColor++;
		}
		// m_nCountColor��2�̎�
		else if (m_nCountColor == 2)
		{
			pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);

			// m_nCountColor�̉��Z
			m_nCountColor++;
		}
		// m_nCountColor��3�̎�
		else if (m_nCountColor == 3)
		{
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			m_nCountColor = 0;
		}

		// m_chargetye�̐ݒ�
		m_chargetye = CHARGETYPE_3;
	}

	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �`���[�W�N���X�̕`�揈��
//=============================================================================
void CCharge::Draw(void)
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
// �`���[�W�N���X�̃`���[�W�̒i�K�̓n������
//=============================================================================
CCharge::CHARGETYPE CCharge::GetChargeType(void)
{
	return m_chargetye;
}

