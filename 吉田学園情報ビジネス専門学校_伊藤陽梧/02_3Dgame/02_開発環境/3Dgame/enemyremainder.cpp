//=============================================================================
//
// �|���G�̐��̏��� [enemyremainder.cpp]
// Author : �ɓ��z��
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "enemyremainder.h"
#include "number.h"
#include "game.h"
#include "ui.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemyremainder::CEnemyremainder(int nPriority)
{
	memset(m_apNumber, 0, sizeof(m_apNumber));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemyremainder::~CEnemyremainder()
{
}

//=============================================================================
// ��������
//=============================================================================
CEnemyremainder * CEnemyremainder::Create(D3DXVECTOR3 pos)
{
	CEnemyremainder *pEnemyremainder;
	pEnemyremainder = new CEnemyremainder;
	pEnemyremainder->m_pos = pos;
	pEnemyremainder->Init();
	return pEnemyremainder;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CEnemyremainder::Init(void)
{
	// ���Ɖ��̂̔z�u
	CUi::Create(m_pos, D3DXVECTOR3(422.5f, 65.5f, 0.0f), CUi::TYPE_ENEMYREMAINDER);

	// �����̔z�u
	m_apNumber[0] = CNumber::Create(m_pos - D3DXVECTOR3(30.0f, 0.0f, 0.0f), D3DXVECTOR3(70.0f, 95.5f, 0.0f));
	m_apNumber[1] = CNumber::Create(m_pos + D3DXVECTOR3(30.0f, 0.0f, 0.0f), D3DXVECTOR3(70.0f, 95.5f, 0.0f));
	return E_NOTIMPL;
}

//=============================================================================
// �I������
//=============================================================================
void CEnemyremainder::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER_CREATE; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			// �I������
			m_apNumber[nCount]->Uninit();

			// ������NULL�ɂ���
			delete m_apNumber[nCount];
			m_apNumber[nCount] = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CEnemyremainder::Update(void)
{
	// �����̐ݒ�
	for (int nCount = 0; nCount < MAX_NUMBER_CREATE; nCount++)
	{
		int nScore = (int)pow(10.0f, MAX_NUMBER_CREATE - nCount);
		int nScore2 = (int)pow(10.0f, MAX_NUMBER_CREATE - nCount - 1);
		int nAnswer = (MAX_ENEMY_NUM - CGame::GetEnemyDeathTotal()) % nScore / nScore2;

		m_apNumber[nCount]->SetNumber(nAnswer);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CEnemyremainder::Draw(void)
{
	// �`�揈��
	for (int nCount = 0; nCount < MAX_NUMBER_CREATE; nCount++)
	{
		m_apNumber[nCount]->Draw();
	}
}