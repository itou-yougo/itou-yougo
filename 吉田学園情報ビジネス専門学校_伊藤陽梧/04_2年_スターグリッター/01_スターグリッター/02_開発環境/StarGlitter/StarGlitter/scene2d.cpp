//=============================================================================
//
// �|���S���̕`��̏��� [scene2d.h]
// Author : �ɓ��z��
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include"main.h"
#include"scene.h"
#include"scene2d.h"
#include"renderer.h"
#include"manager.h"
#include"input.h"

//=============================================================================
// �I�u�W�F�N�g�N���X�̃R���X�g���N�^
//=============================================================================
CScene2D::CScene2D(int nPriority) :CScene(nPriority)
{
	m_pTexture = NULL;					   // �e�N�X�`���ւ̃|�C���^
	m_pVtxBuff = NULL;					   // ���_�o�b�t�@�ւ̃|�C���^
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); // �|���S���̈ʒu
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	m_nGetCounterAnim = 0;
	m_nGetPatternAnim = 0;
	m_nTimeAnim = 0;
	m_nTimeCount = 0;
	m_nRed = 0;
	m_nGreen = 0;
	m_nBrue = 0;
	m_nAlpha = 0;
	m_bTransparency = false;
	m_bTransparencyUse = false;
	m_fScrollX = 0.0f;
	m_fScrollY = 0.0f;
	m_fGetScrollMoveX = 0.0f;
	m_fGetScrollMoveY = 0.0f;
	m_AnimationType = TYPE_NONE;
}

//=============================================================================
// �I�u�W�F�N�g�N���X�̃f�X�g���N�^
//=============================================================================
CScene2D::~CScene2D()
{

}

//=============================================================================
// �I�u�W�F�N�g�N���X�̃C���X�^���X����
//=============================================================================
CScene2D *CScene2D::Create()
{
	// CScene2D�̃|�C���^
	CScene2D *pScene2D = NULL;

	// �������̊m��
	pScene2D = new CScene2D;

	// pScene2D��NULL����Ȃ��Ƃ�
	if (pScene2D != NULL)
	{
		// ����������
		pScene2D->Init();
	}

	// pScene2D��Ԃ�
	return pScene2D;
}

//=============================================================================
// �I�u�W�F�N�g�N���X�̃e�N�X�`���̎󂯎��
//=============================================================================
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 Texture)
{
	m_pTexture = Texture;
}

//=============================================================================
// �I�u�W�F�N�g�N���X�̏���������
//=============================================================================
HRESULT CScene2D::Init()
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
// �I�u�W�F�N�g�N���X�̏I������
//=============================================================================
void CScene2D::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �I�u�W�F�N�g�N���X�̍X�V����
//=============================================================================
void CScene2D::Update(void)
{
	//// VERTEX_2D�̃|�C���^
	//VERTEX_2D *pVtx;

	//// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
 //	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//// ���_����ݒ�
	//pVtx[0].pos = D3DXVECTOR3(m_pos.x - (m_fSizeX / 2), m_pos.y - (m_fSizeY / 2), 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_fSizeX / 2), m_pos.y - (m_fSizeY / 2), 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(m_pos.x - (m_fSizeX / 2), m_pos.y + (m_fSizeY / 2), 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_fSizeX / 2), m_pos.y + (m_fSizeY / 2), 0.0f);

	////���_�f�[�^���A�����b�N����
	//m_pVtxBuff->Unlock();

	switch (m_AnimationType)
	{
	case TYPE_ANIMATION:
		UpdateAnimation();
		break;

	case TYPE_ANIMATIONSELECT:
		UpdateAnimationSelect();
		break;

	case TYPE_SCROLL:
		UpdateScroll();
		break;

	case TYPE_TRANSPARENCY:
		UpdateTransparency();
		break;

	case TYPE_COLOR:
		UpdateColor();
		break;

	default:
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
		break;
	}

}

//=============================================================================
// �I�u�W�F�N�g�N���X�̕`�揈��
//=============================================================================
void CScene2D::Draw(void)
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

	pDevice->SetTexture(0, NULL);
}

//=============================================================================
// �I�u�W�F�N�g�N���X�̍��W�̎󂯓n��
//=============================================================================
D3DXVECTOR3 CScene2D::GetPosition(void)
{
	// m_pos��Ԃ�
	return m_pos;
}

//=============================================================================
// �I�u�W�F�N�g�N���X�̃T�C�Y�̎󂯓n��
//=============================================================================
D3DXVECTOR3 CScene2D::GetSize(void)
{
	// m_size��Ԃ�
	return m_size;
}

//=============================================================================
// �I�u�W�F�N�g�N���X�̃A�j���[�V�����̐ݒ�
//=============================================================================
void CScene2D::UpdateAnimation()
{
	// VERTEX_2D�̃|�C���^
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

  	if (m_nTimeCount == m_nTimeAnim)
	{
		m_nCounterAnim++;

		if (m_nCounterAnim % m_nGetCounterAnim == 0)
		{
			m_nCounterAnim = 0;
			m_nPatternAnim++;
			if (m_nPatternAnim % m_nGetPatternAnim == 0)
			{
				m_nPatternAnim = 0;
			}
		}

		// ���_����ݒ�
		pVtx[0].tex = D3DXVECTOR2((float)(1.0f / m_nGetCounterAnim)* m_nCounterAnim, (float)(1.0f / m_nGetPatternAnim)* m_nPatternAnim);
		pVtx[1].tex = D3DXVECTOR2((float)(1.0f / m_nGetCounterAnim)* (m_nCounterAnim + 1), (float)(1.0f / m_nGetPatternAnim)* m_nPatternAnim);
		pVtx[2].tex = D3DXVECTOR2((float)(1.0f / m_nGetCounterAnim)* m_nCounterAnim, (float)(1.0f / m_nGetPatternAnim)* (m_nPatternAnim + 1));
		pVtx[3].tex = D3DXVECTOR2((float)(1.0f / m_nGetCounterAnim)* (m_nCounterAnim + 1), (float)(1.0f / m_nGetPatternAnim)* (m_nPatternAnim + 1));

		m_nTimeCount = 0;
	}
	m_nTimeCount++;

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2), m_pos.y - (m_size.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y - (m_size.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);

	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();

	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �I�u�W�F�N�g�N���X�̔C�ӂŕς�����A�j���[�V�����̐ݒ�
//=============================================================================
void CScene2D::UpdateAnimationSelect()
{
	// VERTEX_2D�̃|�C���^
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (m_nTimeCount == m_nTimeAnim)
	{
		m_nCounterAnim++;

		if (m_nCounterAnim % m_nGetCounterAnim == 0)
		{
			m_nCounterAnim = 0;
		}

		// ���_����ݒ�
		pVtx[0].tex = D3DXVECTOR2((float)(1.0f / m_nGetCounterAnim)* m_nCounterAnim, (float)(1.0f / m_nGetPatternAnim)* m_nPatternAnim);
		pVtx[1].tex = D3DXVECTOR2((float)(1.0f / m_nGetCounterAnim)* (m_nCounterAnim + 1), (float)(1.0f / m_nGetPatternAnim)* m_nPatternAnim);
		pVtx[2].tex = D3DXVECTOR2((float)(1.0f / m_nGetCounterAnim)* m_nCounterAnim, (float)(1.0f / m_nGetPatternAnim)* (m_nPatternAnim + 1));
		pVtx[3].tex = D3DXVECTOR2((float)(1.0f / m_nGetCounterAnim)* (m_nCounterAnim + 1), (float)(1.0f / m_nGetPatternAnim)* (m_nPatternAnim + 1));
		
		m_nTimeCount = 0;
	}
	m_nTimeCount++;

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2), m_pos.y - (m_size.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y - (m_size.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);

	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();

	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �I�u�W�F�N�g�N���X�̃X�N���[���̐ݒ�
//=============================================================================
void CScene2D::UpdateScroll()
{
	// VERTEX_2D�̃|�C���^
	VERTEX_2D *pVtx;

	// �󂯎�������������Z
	m_fScrollX += m_fGetScrollMoveX;
	m_fScrollY += m_fGetScrollMoveY;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2), m_pos.y - (m_size.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y - (m_size.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);

	// ���_����ݒ�
	pVtx[0].tex = D3DXVECTOR2(m_fScrollX, m_fScrollY);
	pVtx[1].tex = D3DXVECTOR2(m_fScrollX + 1.0f, m_fScrollY);
	pVtx[2].tex = D3DXVECTOR2(m_fScrollX, m_fScrollY + 0.5f);
	pVtx[3].tex = D3DXVECTOR2(m_fScrollX + 1.0f, m_fScrollY + 0.5f);

	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �I�u�W�F�N�g�N���X�̓������̐ݒ�
//=============================================================================
void CScene2D::UpdateTransparency()
{
	// VERTEX_2D�̃|�C���^
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2), m_pos.y - (m_size.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y - (m_size.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);

	// �����ɂ���̂��g�����ǂ���
	if (m_bTransparencyUse)
	{
		// �����ɂ���
		if (!m_bTransparency)
		{
			// ���_�J���[�̐ݒ�(0�`255�͈̔͂Őݒ�)
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			m_bTransparency = true;
		}
		else if (m_bTransparency)
		{
			// ���_�J���[�̐ݒ�(0�`255�͈̔͂Őݒ�)
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 0);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 0);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 0);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 0);
			m_bTransparency = false;
		}
	}
	else if (!m_bTransparencyUse)
	{
		// ���_�J���[�̐ݒ�(0�`255�͈̔͂Őݒ�)
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �I�u�W�F�N�g�N���X�̐F�̐ݒ�
//=============================================================================
void CScene2D::UpdateColor()
{
	// VERTEX_2D�̃|�C���^
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2), m_pos.y - (m_size.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y - (m_size.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);

	// ���_�J���[�̐ݒ�(0�`255�͈̔͂Őݒ�)
	pVtx[0].col = D3DCOLOR_RGBA(m_nRed, m_nGreen, m_nBrue, m_nAlpha);
	pVtx[1].col = D3DCOLOR_RGBA(m_nRed, m_nGreen, m_nBrue, m_nAlpha);
	pVtx[2].col = D3DCOLOR_RGBA(m_nRed, m_nGreen, m_nBrue, m_nAlpha);
	pVtx[3].col = D3DCOLOR_RGBA(m_nRed, m_nGreen, m_nBrue, m_nAlpha);

	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();
}

