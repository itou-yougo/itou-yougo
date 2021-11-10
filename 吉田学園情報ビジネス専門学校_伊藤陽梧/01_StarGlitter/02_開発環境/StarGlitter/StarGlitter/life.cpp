//=============================================================================
//
// ���C�t�̏��� [life.cpp]
// Author : �ɓ��z��
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "life.h"
#include "lifepolygon.h"

//=============================================================================
// ���C�t�N���X�̃R���X�g���N�^
//=============================================================================
CLife::CLife() :CScene(OBJTYPE_LIFE)
{
	for (int nCount = 0; nCount < MAX_LIFEPOLYGON; nCount++)
	{
		m_pLifepolygon[nCount] = NULL;
	}
	m_nLife = 0;
	m_LifeType = LIFE_TYPE_NONE;
}

//=============================================================================
// ���C�t�N���X�̃f�X�g���N�^
//=============================================================================
CLife::~CLife()
{

}

//=============================================================================
// ���C�t�N���X�̃C���X�^���X����
//=============================================================================
CLife * CLife::Create(int nLife, LIFETYPE LifeType, OBJTYPE objType)
{
	// pHp�̃|�C���^
	CLife *pHp = NULL;

	// �������̊m��
	pHp = new CLife;

	// pHp��NULL����Ȃ��Ƃ�
	if (pHp != NULL)
	{
		pHp->SetLife(nLife);
		pHp->SetType(LifeType, objType);

		// ����������
		pHp->Init();
	}

	// pHp��Ԃ�
	return pHp;
}

//=============================================================================
// ���C�t�N���X�̏���������
//=============================================================================
HRESULT CLife::Init()
{
	switch (m_LifeType)
	{
		// PLAYER1�̗̑�
	case LIFE_TYPE_PLAYER:
		for (int nCount = 0; nCount < m_nLife; nCount++)
		{
			// ���C�t�|���S���̃N���G�C�g
			m_pLifepolygon[nCount] = m_pLifepolygon[nCount]->Create(
				D3DXVECTOR3((LIFEPOLYGON_SIZE_X * 2) + (50.0f * nCount), 50.0f, 0.0f), 
				D3DXVECTOR3(LIFEPOLYGON_SIZE_X, LIFEPOLYGON_SIZE_Y, 0.0f), 1, 0);
		}
		break;

		// PLAYER2�̗̑�
	case LIFE_TYPE_PLAYER2:
		for (int nCount = 0; nCount < m_nLife; nCount++)
		{
			// ���C�t�|���S���̃N���G�C�g
			m_pLifepolygon[nCount] = m_pLifepolygon[nCount]->Create(
				D3DXVECTOR3(SCREEN_WIDTH - (LIFEPOLYGON_SIZE_X * 2) - (50.0f * nCount), 50.0f, 0.0f), 
				D3DXVECTOR3(LIFEPOLYGON_SIZE_X, LIFEPOLYGON_SIZE_Y, 0.0f), 1, 0);
		}
		break;
	default:
		break;
	}

	return S_OK;
}

//=============================================================================
// ���C�t�N���X�̏I������
//=============================================================================
void CLife::Uninit(void)
{
	switch (m_LifeType)
	{
		// PLAYER1�̗̑�
	case LIFE_TYPE_PLAYER:
		for (int nCount = 0; nCount < m_nLife; nCount++)
		{
			// ���C�t�|���S���̏I������
			m_pLifepolygon[nCount]->Uninit();

			delete m_pLifepolygon[nCount];
			m_pLifepolygon[nCount] = NULL;
		}
		break;
		
		// PLAYER2�̗̑�
	case LIFE_TYPE_PLAYER2:
		for (int nCount = 0; nCount < m_nLife; nCount++)
		{
			// ���C�t�|���S���̏I������
			m_pLifepolygon[nCount]->Uninit();

			delete m_pLifepolygon[nCount];
			m_pLifepolygon[nCount] = NULL;
		}
		break;

	default:
		break;
	}

	Release();
}

//=============================================================================
// ���C�t�N���X�̍X�V����
//=============================================================================
void CLife::Update(void)
{
	switch (m_LifeType)
	{
		// PLAYER1�̗̑�
	case LIFE_TYPE_PLAYER:
		for (int nCount = 0; nCount < m_nLife; nCount++)
		{
			// ���C�t�|���S���̍X�V����
			m_pLifepolygon[nCount]->Update();
		}
		break;

		// PLAYER2�̗̑�
	case LIFE_TYPE_PLAYER2:
		for (int nCount = 0; nCount < m_nLife; nCount++)
		{
			// ���C�t�|���S���̍X�V����
			m_pLifepolygon[nCount]->Update();
		}
		break;

	default:
		break;
	}
}

//=============================================================================
// ���C�t�N���X�̕`�揈��
//=============================================================================
void CLife::Draw(void)
{
	switch (m_LifeType)
	{
		// PLAYER1�̗̑�
	case LIFE_TYPE_PLAYER:
		for (int nCount = 0; nCount < m_nLife; nCount++)
		{
			// ���C�t�|���S���̕`�揈��
			m_pLifepolygon[nCount]->Draw();
		}
		break;

		// PLAYER2�̗̑�
	case LIFE_TYPE_PLAYER2:
		for (int nCount = 0; nCount < m_nLife; nCount++)
		{
			// ���C�t�|���S���̕`�揈��
			m_pLifepolygon[nCount]->Draw();
		}
		break;

	default:
		break;
	}
}

//=============================================================================
// ���C�t�N���X�̃��C�t��Ԃ�����
//=============================================================================
int CLife::GetLife(void)
{
	return m_nLife;
}

//=============================================================================
// ���C�t�N���X�̃_���[�W���󂯂����̏���
//=============================================================================
void CLife::Damage()
{
	if (m_nLife < 0)
	{
		m_nLife = 0;
	}

	switch (m_LifeType)
	{
		// PLAYER1�̗̑�
	case LIFE_TYPE_PLAYER:
		// m_pLifepolygon��NULL����Ȃ��Ƃ�
		if (m_pLifepolygon[m_nLife] != NULL)
		{
			// ���C�t�|���S���̏I������
			m_pLifepolygon[m_nLife]->Uninit();
			m_pLifepolygon[m_nLife] = NULL;
		}
		break;

		// PLAYER2�̗̑�
	case LIFE_TYPE_PLAYER2:
		// m_pLifepolygon��NULL����Ȃ��Ƃ�
		if (m_pLifepolygon[m_nLife] != NULL)
		{
			// ���C�t�|���S���̏I������
			m_pLifepolygon[m_nLife]->Uninit();
			m_pLifepolygon[m_nLife] = NULL;
		}
		break;

	default:
		break;
	}
}

//=============================================================================
// ���C�t�N���X�̉񕜂����Ƃ��̏���
//=============================================================================
void CLife::Cure()
{
	switch (m_LifeType)
	{
	case LIFE_TYPE_PLAYER:
		if (m_nLife - 1 < PLAYER_LIFE)
		{
			// ���C�t�|���S���̐���
			m_pLifepolygon[m_nLife - 1] = m_pLifepolygon[m_nLife - 1]->Create(
				D3DXVECTOR3((LIFEPOLYGON_SIZE_X * 2) + (50.0f * (m_nLife - 1)), 50.0f, 0.0f), 
				D3DXVECTOR3(LIFEPOLYGON_SIZE_X, LIFEPOLYGON_SIZE_Y, 0.0f), 1, 0);
		}
		break;

	case LIFE_TYPE_PLAYER2:
		if (m_nLife < PLAYER_LIFE + 1)
		{
			// ���C�t�|���S���̐���
			m_pLifepolygon[m_nLife - 1] = m_pLifepolygon[m_nLife - 1]->Create(
				D3DXVECTOR3(SCREEN_WIDTH - (LIFEPOLYGON_SIZE_X * 2) - (50.0f * (m_nLife - 1)), 50.0f, 0.0f), 
				D3DXVECTOR3(LIFEPOLYGON_SIZE_X, LIFEPOLYGON_SIZE_Y, 0.0f), 1, 0);
		}
		break;

	default:
		break;
	}
}
