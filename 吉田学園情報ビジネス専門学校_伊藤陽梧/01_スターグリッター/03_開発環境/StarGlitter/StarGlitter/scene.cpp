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
int CScene::m_nNumAll = 0;
int CScene::m_nNext = 0;
bool CScene::m_bPause = false;
CScene *CScene::m_pTop[OBJTYPE_MAX] = {}; // �擪�̃I�u�W�F�N�g�ւ̃|�C���^
CScene *CScene::m_pCur[OBJTYPE_MAX] = {}; // ���݂̃I�u�W�F�N�g�ւ̃|�C���^

//=============================================================================
// �I�u�W�F�N�g�N���X�̃R���X�g���N�^
//=============================================================================
CScene::CScene(int nPriority)
{
	m_objType = OBJTYPE_NONE;
	m_bDeath = true;

	// ���X�g�̐擪�����݂��Ȃ��ꍇ
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

	m_nPriority = nPriority;
	m_nNumAll++;

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
	// �|�[�Y�̏�Ԃ���Ȃ��Ƃ�
	if (m_bPause == false)
	{
		// OBJTYPE�̐�����
		for (int nPriority = 0; nPriority < OBJTYPE_MAX; nPriority++)
		{
			// Top�̏��̕ێ�
			CScene *pScene = m_pTop[nPriority];
			while (pScene != NULL)
			{
				// Next�̏��̕ێ�
				CScene *pSceneNext = pScene->m_pNext;

				// ���S�t���O�������ĂȂ��Ƃ�
				if (pScene->m_bDeath != false)
				{
					pScene->Update();
				}

				// Next�̏���pScene�ɓ����
				pScene = pSceneNext;
			}
		}

		for (int nPriority = 0; nPriority < OBJTYPE_MAX; nPriority++)
		{
			// Top�̏��̕ێ�
			CScene *pScene = m_pTop[nPriority];
			while (pScene != NULL)
			{
				// Next�̏��̕ێ�
				CScene *pSceneNext = pScene->m_pNext;

				// ���S�t���O�������Ă�Ƃ�
				if (pScene->m_bDeath == false)
				{
					// ���X�g�̂Ȃ��Ȃ��������ď���
					pScene->ConnectionList();
					delete pScene;
				}

				// Next�̏���pScene�ɓ����
				pScene = pSceneNext;
			}
		}
	}

	// �|�[�Y�̏�Ԃ̂Ƃ�
	if (m_bPause == true)
	{
		// OBJTYPE�̐�����
		for (int nPriority = 0; nPriority < OBJTYPE_MAX; nPriority++)
		{
			// Top�̏��̕ێ�
			CScene *pScene = m_pTop[nPriority];
			while (pScene != NULL && pScene->GetObjType() == OBJTYPE_TEXT)
			{
				// Next�̏��̕ێ�
				CScene *pSceneNext = pScene->m_pNext;

				// ���S�t���O�������ĂȂ��Ƃ�
				if (pScene->m_bDeath != false)
				{
					pScene->Update();
				}

				// Next�̏���pScene�ɓ����
				pScene = pSceneNext;
			}
		}

		for (int nPriority = 0; nPriority < OBJTYPE_MAX; nPriority++)
		{
			// Top�̏��̕ێ�
			CScene *pScene = m_pTop[nPriority];
			while (pScene != NULL)
			{
				// Next�̏��̕ێ�
				CScene *pSceneNext = pScene->m_pNext;

				// ���S�t���O�������Ă�Ƃ�
				if (pScene->m_bDeath == false)
				{
					// ���X�g�̂Ȃ��Ȃ��������ď���
					pScene->ConnectionList();
					delete pScene;
				}

				// Next�̏���pScene�ɓ����
				pScene = pSceneNext;
			}
		}
	}
}

//=============================================================================
// �I�u�W�F�N�g�N���X�̕`�揈��
//=============================================================================
void CScene::DrawAll(void)
{
	// OBJTYPE�̐�����
	for (int nPriority = 0; nPriority < OBJTYPE_MAX; nPriority++)
	{
		// Top�̏��̕ێ�
		CScene *pScene = m_pTop[nPriority];
		while (pScene != NULL)
		{
			// Next�̏��̕ێ�
			CScene *pSceneNext = pScene->m_pNext;

			// ���S�t���O�������ĂȂ��Ƃ�
			if (pScene->m_bDeath != false)
			{
				pScene->Draw();
			}

			// Next�̏���pScene�ɓ����
			pScene = pSceneNext;
		}
	}
}

//=============================================================================
// �I�u�W�F�N�g�N���X�̏I������
//=============================================================================
void CScene::ReleaseAll(void)
{
	// OBJTYPE�̐�����
	for (int nPriority = 0; nPriority < OBJTYPE_MAX; nPriority++)
	{
		// Top�̏��̕ێ�
		CScene *pScene = m_pTop[nPriority];
		while (pScene != NULL)
		{
			// Next�̏��̕ێ�
			CScene *pSceneNext = pScene->m_pNext;

			// ���S�t���O�𗧂Ă�
			pScene->Release();

			// Next�̏���pScene�ɓ����
			pScene = pSceneNext;
		}
	}
}

//=============================================================================
// �I�u�W�F�N�g�N���X�̃t�F�[�h�𔲂����I������
//=============================================================================
void CScene::NotFadeReleaseAll(void)
{
	// OBJTYPE�̐�����
	for (int nPriority = 0; nPriority < OBJTYPE_MAX; nPriority++)
	{
		// Top�̏��̕ێ�
		CScene *pScene = m_pTop[nPriority];
		while (pScene != NULL && pScene->m_objType != OBJTYPE_FADE)
		{
			// Next�̏��̕ێ�
			CScene *pSceneNext = pScene->m_pNext;

			// ���S�t���O�𗧂Ă�
			pScene->Release();

			// Next�̏���pScene�ɓ����
			pScene = pSceneNext;
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
// �I�u�W�F�N�g�N���X�̃������̊J��
//=============================================================================
void CScene::Release(void)
{
	// ���S�t���O�𗧂Ă�
	m_bDeath = false;

	// �I�u�W�F�N�g�̑����̌��Z
	m_nNumAll--;
}