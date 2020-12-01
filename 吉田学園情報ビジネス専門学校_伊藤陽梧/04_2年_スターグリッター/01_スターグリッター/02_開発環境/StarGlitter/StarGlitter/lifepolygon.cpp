//=============================================================================
//
// ���C�t�|���S���̏��� [lifepolygon.cpp]
// Author : �ɓ��z��
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "lifepolygon.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CLifepolygon::m_pTexture = NULL;

//=============================================================================
// ���C�t�|���S���N���X�̃R���X�g���N�^
//=============================================================================
CLifepolygon::CLifepolygon()
{
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fSizeX = 0.0f;
	m_fSizeY = 0.0f;
}

//=============================================================================
// ���C�t�|���S���N���X�̃f�X�g���N�^
//=============================================================================
CLifepolygon::~CLifepolygon()
{

}

//=============================================================================
// ���C�t�|���S���N���X�̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CLifepolygon::Load(void)
{
	// �C���X�^���X�����������̂��󂯎��
	CRenderer *pRenderer = CManager::GetRenderer();

	// �f�o�C�X���󂯎��
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	HRESULT hr = D3DXCreateTextureFromFile(pDevice, TEXTURE_LIFE, &m_pTexture);

	return S_OK;
}

//=============================================================================
// ���C�t�|���S���N���X�̃e�N�X�`���j��
//=============================================================================
void CLifepolygon::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// ���C�t�|���S���N���X�̃C���X�^���X����
//=============================================================================
CLifepolygon * CLifepolygon::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nDivide, int nCount)
{
	// CLifepolygon�̃|�C���^
	CLifepolygon *pLifepolygon = NULL;

	// �������̊m��
	pLifepolygon = new CLifepolygon;

	// pLifepolygon��NULL����Ȃ��Ƃ�
	if (pLifepolygon != NULL)
	{
		// ����������
		pLifepolygon->Init();

		// ���C�t�|���S���̃Z�b�g
		pLifepolygon->SetLifePolygon(nDivide, nCount);
		pLifepolygon->SetPosition(pos);
		pLifepolygon->SetSize(fSizeX, fSizeY);
	}

	// pLifepolygon��Ԃ�
	return pLifepolygon;
}

//=============================================================================
// ���C�t�|���S���N���X�̏���������
//=============================================================================
HRESULT CLifepolygon::Init()
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


	return S_OK;
}

//=============================================================================
// ���C�t�|���S���N���X�̏I������
//=============================================================================
void CLifepolygon::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
// ���C�t�|���S���N���X�̍X�V����
//=============================================================================
void CLifepolygon::Update(void)
{
	// VERTEX_2D�̃|�C���^
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - (m_fSizeX / 2), m_pos.y - (m_fSizeY / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_fSizeX / 2), m_pos.y - (m_fSizeY / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (m_fSizeX / 2), m_pos.y + (m_fSizeY / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_fSizeX / 2), m_pos.y + (m_fSizeY / 2), 0.0f);

	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// ���C�t�|���S���N���X�̕`�揈��
//=============================================================================
void CLifepolygon::Draw(void)
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
// ���C�t�|���S���N���X�̃e�N�X�`���̏���
//=============================================================================
void CLifepolygon::SetLifePolygon(int nDivide, int nCount)
{
	// VERTEX_2D�̃|�C���^
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0); // ���̏����͕ς��Ȃ�����

	// �e�N�X�`���̍��W
	pVtx[0].tex = D3DXVECTOR2((float)(1.0f / nDivide)* nCount, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((float)(1.0f / nDivide)* (nCount + 1), 0.0f);
	pVtx[2].tex = D3DXVECTOR2((float)(1.0f / nDivide)* nCount, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((float)(1.0f / nDivide)* (nCount + 1), 1.0f);

	// ���_�f�[�^�A�����b�N
	m_pVtxBuff->Unlock();
}
