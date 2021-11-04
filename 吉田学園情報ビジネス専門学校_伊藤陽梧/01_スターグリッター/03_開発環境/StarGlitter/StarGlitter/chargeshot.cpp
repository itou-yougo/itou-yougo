//=============================================================================
//
// �`���[�W�V���b�g�̏��� [chargeshot.cpp]
// Author : �ɓ��z��
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "chargeshot.h"
#include "charge.h"
#include "gauge.h"
#include "manager.h"
#include "input.h"
#include "renderer.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CChargeshot::m_pTexture = NULL;

//=============================================================================
// �`���[�W�V���b�g�N���X�̃R���X�g���N�^
//=============================================================================
CChargeshot::CChargeshot() :CScene(OBJTYPE_GAUGE)
{
	pGauge = NULL;
	pCharge = NULL;
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �`���[�W�V���b�g�N���X�̃f�X�g���N�^
//=============================================================================
CChargeshot::~CChargeshot()
{

}

//=============================================================================
// �`���[�W�V���b�g�N���X�̃e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CChargeshot::Load(void)
{
	// �C���X�^���X�����������̂��󂯎��
	CRenderer *pRenderer = CManager::GetRenderer();

	// �f�o�C�X���󂯎��
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_GAUGE, &m_pTexture);

	return S_OK;
}

//=============================================================================
// �`���[�W�V���b�g�N���X�̃e�N�X�`���̔j��
//=============================================================================
void CChargeshot::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// �`���[�W�V���b�g�N���X�̃C���X�^���X����
//=============================================================================
CChargeshot * CChargeshot::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CHARGESHOTTYPE chargeshottype, OBJTYPE objType)
{
	// CChargeshot�̃|�C���^
	CChargeshot *pChargeshot = NULL;

	// �������̊m��
	pChargeshot = new CChargeshot;

	// pChargeshot��NULL����Ȃ��Ƃ�
	if (pChargeshot != NULL)
	{
		// �`���[�W�V���b�g�̃Z�b�g
		pChargeshot->SetChargeShot(pos, size, chargeshottype, objType);

		// ����������
		pChargeshot->Init();
	}

	// pChargeshot��Ԃ�
	return pChargeshot;
}

//=============================================================================
// �`���[�W�V���b�g�N���X�̃f�X�g���N�^
//=============================================================================
HRESULT CChargeshot::Init()
{
	SetObjType(OBJTYPE_GAUGE);

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
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();

	// �Q�[�W�ƃ`���[�W�̐���
	pGauge = CGauge::Create(D3DXVECTOR3(m_pos.x - 136.0f, m_pos.y, 0.0f), D3DXVECTOR3(0.0f, m_size.y, 0.0f));
	pCharge = CCharge::Create(D3DXVECTOR3(m_pos.x - 136.0f, m_pos.y, 0.0f), D3DXVECTOR3(100.0f, m_size.y, 0.0f));

	return S_OK;
}

//=============================================================================
// �`���[�W�V���b�g�N���X�̃f�X�g���N�^
//=============================================================================
void CChargeshot::Uninit(void)
{
	// pGauge��NULL����Ȃ��Ƃ�
	if (pGauge != NULL)
	{
		// pGauge�̏I������
		pGauge->Uninit();
	}

	// pCharge��NULL����Ȃ��Ƃ�
	if (pCharge != NULL)
	{
		// pCharge�̏I������
		pCharge->Uninit();
	}

	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	Release();
}

//=============================================================================
// �`���[�W�V���b�g�N���X�̃f�X�g���N�^
//=============================================================================
void CChargeshot::Update(void)
{
	// CInput�̃|�C���^�̃C���X�^���X�����̎󂯎��
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	CInputJoypad *pInputJoypad = CManager::GetInputJoypad();

	// VERTEX_2D�̃|�C���^
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2), m_pos.y - (m_size.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y - (m_size.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);

	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();

	// pGauge��NULL����Ȃ��Ƃ�
	if (pGauge != NULL)
	{
		// pGauge�̍X�V����
		pGauge->Update();
	}

	// pCharge��NULL����Ȃ��Ƃ�
	if (pCharge != NULL)
	{
		// pCharge�̍X�V����
		pCharge->Update();
	}
}

//=============================================================================
// �`���[�W�V���b�g�N���X�̃f�X�g���N�^
//=============================================================================
void CChargeshot::Draw(void)
{
	// pGauge��NULL����Ȃ��Ƃ�
	if (pGauge != NULL)
	{
		// pGauge�̕`�揈��
		pGauge->Draw();
	}

	// pCharge��NULL����Ȃ��Ƃ�
	if (pCharge != NULL)
	{
		// pCharge�̕`�揈��
		pCharge->Draw();
	}

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
// �`���[�W�V���b�g�N���X�̃Q�[�W�̃|�C���^��Ԃ�����
//=============================================================================
CGauge* CChargeshot::GetGauge(void)
{
	return pGauge;
}

//=============================================================================
// �`���[�W�V���b�g�N���X�̃`���[�W�̃|�C���^��Ԃ�����
//=============================================================================
CCharge * CChargeshot::GetCharge(void)
{
	return pCharge;
}
