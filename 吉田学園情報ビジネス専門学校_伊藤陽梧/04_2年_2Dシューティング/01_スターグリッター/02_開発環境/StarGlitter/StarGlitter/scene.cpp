//=============================================================================
//
// �|���S���̕`��̏��� [scene.cpp]
// Author : �ɓ��z��
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include"main.h"
#include"scene.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CScene *CScene::m_apScene[MAX_DRAWORDER][MAX_POLYGON] = {};
int CScene::m_nNumAll = 0;
bool CScene::m_bPause = false;

//=============================================================================
// �I�u�W�F�N�g�N���X�̃R���X�g���N�^
//=============================================================================
CScene::CScene(int nPriority)
{
	m_objType = OBJTYPE_NONE;
	for (int nCount = 0; nCount < MAX_POLYGON; nCount++)
	{
		if (m_apScene[nPriority][nCount] == NULL)
		{
			// CScene2D�ŃC���X�^���X�����������̂��Ԃ�����
			m_apScene[nPriority][nCount] = this;
			m_nID = nCount;
			m_nPriority = nPriority;
			m_nNumAll++;
			break;
		}
	}
}

//=============================================================================
// �I�u�W�F�N�g�N���X�̃f�X�g���N�^
//=============================================================================
CScene::~CScene()
{

}

//=============================================================================
// �I�u�W�F�N�g�N���X�̍X�V����
//=============================================================================
void CScene::UpdateAll(void)
{
	// �|�[�Y��Ԃ���Ȃ��Ƃ�
	if (m_bPause == false)
	{
		for (int nPriority = 0; nPriority < MAX_DRAWORDER; nPriority++)
		{
			for (int nCount = 0; nCount < MAX_POLYGON; nCount++)
			{
				if (m_apScene[nPriority][nCount] != NULL)
				{
					// �X�V����
					m_apScene[nPriority][nCount]->Update();
				}
			}
		}

		for (int nCount = 0; nCount < MAX_POLYGON; nCount++)
		{
			if (m_apScene[OBJTYPE_GATTYANN][nCount] != NULL)
			{
				// �X�V����
				m_apScene[OBJTYPE_GATTYANN][nCount]->Update();
			}
		}
	}

	// �|�[�Y��Ԃ̎�
	if (m_bPause == true)
	{
		for (int nPriority = 0; nPriority < MAX_DRAWORDER; nPriority++)
		{
			for (int nCount = 0; nCount < MAX_POLYGON; nCount++)
			{
				if (m_apScene[nPriority][nCount] != NULL && m_apScene[nPriority][nCount]->GetObjType() == OBJTYPE_TEXT)
				{
					// �X�V����
					m_apScene[nPriority][nCount]->Update();
				}
			}
		}
	}
}

//=============================================================================
// �I�u�W�F�N�g�N���X�̕`�揈��
//=============================================================================
void CScene::DrawAll(void)
{
	for (int nPriority = 0; nPriority < MAX_DRAWORDER; nPriority++)
	{
		for (int nCount = 0; nCount < MAX_POLYGON; nCount++)
		{
			if (m_apScene[nPriority][nCount] != NULL)
			{
				// �`�揈��
				m_apScene[nPriority][nCount]->Draw();
			}
		}
	}
}

//=============================================================================
// �I�u�W�F�N�g�N���X�̏I������
//=============================================================================
void CScene::ReleaseAll(void)
{
	for (int nPriority = 0; nPriority < MAX_DRAWORDER; nPriority++)
	{
		for (int nCount = 0; nCount < MAX_POLYGON; nCount++)
		{
			//pEnemy��NULL����Ȃ��Ƃ�
			if (m_apScene[nPriority][nCount] != NULL)
			{
				//�I������
				m_apScene[nPriority][nCount]->Uninit();
			}
		}
	}
}

//=============================================================================
// �I�u�W�F�N�g�N���X�̃t�F�[�h�𔲂����I������
//=============================================================================
void CScene::NotFadeReleaseAll(void)
{
	for (int nPriority = 0; nPriority < MAX_DRAWORDER; nPriority++)
	{
		for (int nCount = 0; nCount < MAX_POLYGON; nCount++)
		{
			//pEnemy��NULL����Ȃ��Ƃ�
			if (m_apScene[nPriority][nCount] != NULL && m_apScene[nPriority][nCount]->m_objType != OBJTYPE_FADE)
			{
				//�I������
				m_apScene[nPriority][nCount]->Uninit();
			}
		}
	}
}

//=============================================================================
// �I�u�W�F�N�g�N���X�̃|�[�Y��n������
//=============================================================================
bool CScene::GetPause(void)
{
	return m_bPause;
}

//=============================================================================
// �I�u�W�F�N�g�N���X�̃^�C�v��n������
//=============================================================================
CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_objType;
}

//=============================================================================
// �I�u�W�F�N�g�N���X�̃V�[����n������
//=============================================================================
CScene * CScene::GetScene(int nPriority, int nCount)
{
	return m_apScene[nPriority][nCount];
}

//=============================================================================
// �I�u�W�F�N�g�N���X�̃������̊J��
//=============================================================================
void CScene::Release(void)
{
	//apEnemy��NULL����Ȃ��Ƃ�
	if (m_apScene[m_nPriority][m_nID] != NULL)
	{
		int nID = m_nID;
		int nPriority = m_nPriority;

		//�������̊J��
		delete m_apScene[nPriority][nID];
		m_apScene[nPriority][nID] = NULL;
  		m_nNumAll--;
	}
}