//=============================================================================
//
// �V�[���̏��� [scene.cpp]
// Author : �ɓ��z��
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "scene.h"
#include "scene2d.h"

//=============================================================================
//�ÓI�����o�ϐ�
//=============================================================================
CScene *CScene::m_pTop[OBJTYPE_MAX] = {};
CScene *CScene::m_pCur[OBJTYPE_MAX] = {};
int CScene::m_nNumAll = 0;
int CScene::m_nCount = 0;
int CScene::m_nNext = 0;
bool CScene::m_bUpdateStop = false;

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CScene::CScene(int nPriority)
{
	m_pNext = NULL;
	m_pPrev = NULL;
	//�g�b�v��NULL�̎�
	if (m_pTop[nPriority] == NULL)
	{
		m_pTop[nPriority] = this;
	}
	// ���݂̃I�u�W�F�N�g(m_pCur)�����݂��Ȃ��ꍇ
	if (m_pCur[nPriority] == NULL)
	{
		m_pCur[nPriority] = this;
	}

	// ���݂̃I�u�W�F�N�g(m_pCur)�̎��̃I�u�W�F�N�g�������ɂ���
	m_pCur[nPriority]->m_pNext = this;

	if (this == m_pCur[nPriority])
	{
		this->m_pPrev = NULL;
	}
	else
	{
		this->m_pPrev = m_pCur[nPriority];
	}

	// ���݂̃I�u�W�F�N�g(m_pCur)�������ɂ���
	m_pCur[nPriority] = this;

	// �����̎��̃I�u�W�F�N�g��NULL�ɂ���
	this->m_pNext = NULL;

	m_objType = OBJTYPE_NONE;
	m_nPriority = nPriority;
	m_bDeath = false;

}

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CScene::~CScene()
{

}

//=============================================================================
// �I�u�W�F�N�g�^�C�v�ݒ�
//=============================================================================
void CScene::SetObjType(OBJTYPE objType)
{
	m_objType = objType;
}

//=============================================================================
// �����[�X����
//=============================================================================
void CScene::ReleaseAll(void)
{
	for (int nCount = 0; nCount < OBJTYPE_MAX; nCount++)
	{
		CScene *pScene = m_pTop[nCount];

		while (pScene != NULL)
		{
			//�I������
			CScene *pSave = pScene->m_pNext;
			pScene->Release();
			pScene = pSave;
		}
	}
}

void CScene::DesignationReleaseAll(OBJTYPE type)
{
	for (int nCount = 0; nCount < OBJTYPE_MAX; nCount++)
	{
		if (nCount != type)
		{
			CScene *pScene = m_pTop[nCount];

			while (pScene != NULL)
			{
				//�I������
				CScene *pSave = pScene->m_pNext;
				pScene->Release();
				pScene = pSave;
			}
		}
	}

	for (int nCount = 0; nCount < OBJTYPE_MAX; nCount++)
	{
		CScene *pScene = m_pTop[nCount];

		while (pScene != NULL)
		{
			CScene *pSave = pScene->m_pNext;

			if (pScene->m_bDeath == true)
			{
				if (pScene->m_pPrev != NULL)
				{
					pScene->m_pPrev->m_pNext = pScene->m_pNext;
				}

				if (pScene->m_pNext != NULL)
				{
					pScene->m_pNext->m_pPrev = pScene->m_pPrev;
				}

				if (m_pTop[nCount] == pScene)
				{
					m_pTop[nCount] = pScene->m_pNext;
				}

				if (m_pCur[nCount] == pScene)
				{
					m_pCur[nCount] = pScene->m_pPrev;
				}

				//�I�u�W�F�N�g��j��
				delete pScene;
			}

			pScene = pSave;
		}
	}
}

void CScene::SetUpdateStop(bool bUpdateStop)
{
	m_bUpdateStop = bUpdateStop;
}

//=============================================================================
// �X�V����
//=============================================================================
void CScene::UpdateAll(void)
{
	if (m_bUpdateStop == false)
	{
		// OBJTYPE�̐�����
		for (int nCount = 0; nCount < OBJTYPE_MAX; nCount++)
		{
			// Top�̏��̕ێ�
			CScene *pScene = m_pTop[nCount];
			while (pScene != NULL)
			{
				// Next�̏��̕ێ�
				CScene *pSave = pScene->m_pNext;

				// ���S�t���O�������ĂȂ��Ƃ�
				if (pScene->m_bDeath == false)
				{
					//�X�V����
					pScene->Update();
				}
				// Next�̏���pScene�ɓ����
				pScene = pSave;
			}
		}
	}
	else
	{
		CScene *pScene = m_pTop[OBJTYPE_FADE];
		while (pScene != NULL)
		{
			CScene *pSave = pScene->m_pNext;
			if (pScene->m_bDeath == false)
			{
				//�X�V����
				pScene->Update();
			}
			pScene = pSave;
		}
	}

	for (int nCount = 0; nCount < OBJTYPE_MAX; nCount++)
	{
		CScene *pScene = m_pTop[nCount];
		while (pScene != NULL)
		{
			CScene *pSave = pScene->m_pNext;
			if (pScene->m_bDeath == true)
			{
				// ���X�g�̂Ȃ��Ȃ��������ď���
				pScene->ConnectionList();
				//�I�u�W�F�N�g��j��
				delete pScene;
			}
			pScene = pSave;
		}
	}
}

//=============================================================================
// �I�u�W�F�N�g�N���X�̃��X�g�̂Ȃ��Ȃ���
//=============================================================================
void CScene::ConnectionList(void)
{
	// �O�̏��������Ă���Ƃ�
	if (m_pPrev != NULL)
	{
		m_pPrev->m_pNext = m_pNext;
	}

	// ���̏��������Ă���Ƃ�
	if (m_pNext != NULL)
	{
		m_pNext->m_pPrev = m_pPrev;
	}

	// �������擪�ƌ��݂̃I�u�W�F�N�g�������Ƃ�
	if (this == m_pTop[m_nPriority] && this == m_pCur[m_nPriority])
	{
		m_pTop[m_nPriority] = NULL;
		m_pCur[m_nPriority] = NULL;
	}

	// �������擪�̃I�u�W�F�N�g�������Ƃ�
	if (this == m_pTop[m_nPriority])
	{
		m_pTop[m_nPriority] = m_pNext;
	}

	// ���������݂̃I�u�W�F�N�g�������Ƃ�
	if (this == m_pCur[m_nPriority])
	{
		m_pCur[m_nPriority] = m_pPrev;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CScene::DrawAll(void)
{
	for (int nCountpriority = 0; nCountpriority < OBJTYPE_MAX; nCountpriority++)
	{
		// Top�̏��̕ێ�
		CScene*pScene = m_pTop[nCountpriority];

		while (pScene != NULL)
		{
			// Next�̏��̕ێ�
			CScene *pSceneNext = pScene->m_pNext;

			if (pScene->m_bDeath != true)
			{
				pScene->Draw();
				pScene = pSceneNext;
			}
		}
	}
}

//=============================================================================
// �����[�X����
//=============================================================================
void CScene::Release(void)
{
	//���S�t���O�𗧂Ă�
	m_bDeath = true;
}