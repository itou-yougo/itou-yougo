//=============================================================================
//
// �|���S���̕`��̏��� [scene.h]
// Author : �ɓ��z��
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include"main.h"

//=============================================================================
// �I�u�W�F�N�g�N���X
//=============================================================================
class CScene
{
public:
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_BG,				// �w�i
		OBJTYPE_SCENE,			// �V�[��
		OBJTYPE_BOSSATTACK,		// �{�X�A�^�b�N
		OBJTYPE_EXPLOSION,		// ����
		OBJTYPE_LIFE,			// �̗�
		OBJTYPE_GAUGE,			// �Q�[�W
		OBJTYPE_EFFECT,			// �G�t�F�N�g
		OBJTYPE_BULLET,			// �e
		OBJTYPE_PLAYER,			// �v���C���[
		OBJTYPE_ENEMY,			// �G
		OBJTYPE_ENEMYEXPLOSION, // �G�̔���
		OBJTYPE_EXTRAATTACK,	// �G�N�X�g���A�^�b�N
		OBJTYPE_OJAMA,			// �������
		OBJTYPE_TEXT,			// �e�L�X�g
		OBJTYPE_GATTYANN,		// �K�b�`����
		OBJTYPE_FADE,			// �t�F�[�h
		OBJTYPE_MAX,
	}OBJTYPE;

	CScene(int nPriority = 2); // �R���X�g���N
	virtual ~CScene();		   // �f�X�g���N�^

	virtual HRESULT Init() = 0;    // ����������
	virtual void Uninit(void) = 0; // �I������
	virtual void Update(void) = 0; // �X�V����
	virtual void Draw(void) = 0;   // �`�揈��

	static void UpdateAll(void);  // ���ׂĂ̍X�V����
	static void DrawAll(void);	  // ���ׂĂ̕`�揈��
	static void ReleaseAll(void); // ���ׂẴt���O����

	static void NotFadeReleaseAll(void); // �t�F�[�h�ȊO�̃t���O����



	static void SetPause(bool bPause){ // �|�[�Y�̐ݒ�
		m_bPause = bPause;
	}
	static bool GetPause(void); // �|�[�Y�̏�Ԃ�Ԃ�

	void ConnectionList(void); // �f�[�^�̂Ȃ��Ȃ���

	void SetObjType(OBJTYPE objType) { // �I�u�W�F�^�C�v�̐ݒ�
		m_objType = objType;
	};

	OBJTYPE GetObjType(void); // �I�u�W�F�^�C�v��Ԃ�
	static CScene *GetSceneTop(int nPriority) { return m_pTop[nPriority]; } // �V�[���̃f�[�^��Ԃ�
	CScene * GetSceneNext(void) { return m_pNext; } // �V�[���̃l�N�X�g�̃f�[�^��Ԃ�
protected:
	void Release(void); // �t���O����

private:
	static int m_nNumAll;				// �I�u�W�F�N�g�̑���
	static bool m_bPause;				// �|�[�Y�̏��
	static int m_nNext;					// ���֍s������J�E���g
	int		m_nPriority;				// �`��̗D�揇�ʐ�
	bool	m_bDeath;					// �I�u�W�F�N�g�����񂾂Ƃ��̃t���O
	OBJTYPE m_objType;					// �I�u�W�F�N�g�̎��

	static CScene *m_pTop[OBJTYPE_MAX]; // �擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CScene *m_pCur[OBJTYPE_MAX]; // ���݂̃I�u�W�F�N�g�ւ̃|�C���^
	CScene *m_pPrev;					// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CScene *m_pNext;					// ���̃I�u�W�F�N�g�ւ̃|�C���^
};
#endif
