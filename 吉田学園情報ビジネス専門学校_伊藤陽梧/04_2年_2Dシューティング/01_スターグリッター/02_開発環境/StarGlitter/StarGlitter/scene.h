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
		OBJTYPE_PLAYER,			// �v���C���[1
		OBJTYPE_PLAYER2,		// �v���C���[2
		OBJTYPE_ENEMY,			// �G
		OBJTYPE_ENEMYEXPLOSION, // �G�̔���
		OBJTYPE_EXTRAATTACK,	// �G�N�X�g���A�^�b�N
		OBJTYPE_OJAMA,			// �������
		OBJTYPE_OJAMA2,			// �������2
		OBJTYPE_TEXT,			// �e�L�X�g
		OBJTYPE_GATTYANN,		// �K�b�`����
		OBJTYPE_FADE,			// �t�F�[�h
		OBJTYPE_MAX,
	}OBJTYPE;

	CScene(int nPriority = 2);
	virtual ~CScene();

	virtual HRESULT Init() = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static void UpdateAll(void);
	static void DrawAll(void);
	static void ReleaseAll(void);

	static void NotFadeReleaseAll(void);

	void SetObjType(OBJTYPE objType) {
		m_objType = objType;
	};

	static void SetPause(bool bPause){
		m_bPause = bPause;
	}

	static bool GetPause(void);

	OBJTYPE GetObjType(void);
	static CScene *GetScene(int nPriority, int nCount);
protected:
	void Release(void);

private:
	static CScene *m_apScene[MAX_DRAWORDER][MAX_POLYGON]; //�V�[���N���X�̃|�C���^
	static int m_nNumAll; // ����
	static bool m_bPause; // �|�[�Y���
	int	    m_nID;		  // �I�u�W�F�N�g��ID
	int	    m_nPriority;  // �`��̔ԍ�
	OBJTYPE m_objType;	  // �I�u�W�F�N�g�̎��
};
#endif
