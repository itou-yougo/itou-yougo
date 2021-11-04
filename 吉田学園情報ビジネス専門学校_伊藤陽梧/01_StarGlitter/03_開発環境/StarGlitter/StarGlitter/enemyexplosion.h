//=============================================================================
//
// �G�̔����̏��� [enemyexplosion.h]
// Author : �ɓ��z��
//
//=============================================================================
#ifndef _ENEMYEXPLOSION_H_
#define _ENEMYEXPLOSION_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_ENEMYEXPLOSION_TEXTURE (2)

//=============================================================================
// �O���錾
//=============================================================================
class CSound;

//=============================================================================
// �G�̔����N���X
//=============================================================================
class CEnemyexplosion :public CScene2D
{
public:
	typedef enum
	{
		EXPLOSIONTYPE_NONE = 0,
		EXPLOSIONTYPE_PLAYER,  // PLAYER1�̔���
		EXPLOSIONTYPE_PLAYER2, // PLAYER2�̔���
		EXPLOSIONTYPE_MAX,
	}EXPLOSIONTYPE;

	typedef enum
	{
		EXPLOSIONTEXTURE_1 = 0, // �e�ɓ������ē|���ꂽ�Ƃ��̃e�N�X�`��
		EXPLOSIONTEXTURE_2,		// �����ɓ������ē|���ꂽ�Ƃ��̃e�N�X�`��
	}EXPLOSIONTEXTURE;

	CEnemyexplosion();  // �R���X�g���N
	~CEnemyexplosion();	// �f�X�g���N�^

	static HRESULT Load(void); // ���[�h
	static void Unload(void);  // �A�����[�h
	static CEnemyexplosion *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, 
		EXPLOSIONTYPE ExplosionType, EXPLOSIONTEXTURE ExplosionTexture, OBJTYPE objType); // �N���G�C�g
	void SetExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 size, 
		EXPLOSIONTYPE ExplosionType, EXPLOSIONTEXTURE ExplosionTexture, OBJTYPE objType) { // �G�̔����̏���
		m_pos = pos; m_size = size;
		m_ExplosionType = ExplosionType; m_ExplosionTexture = ExplosionTexture;
		SetPosition(pos); SetSize(size);
		SetObjType(objType);
	}

	HRESULT Init();    // ����������
	void Uninit(void); // �I������
	void Update(void); // �X�V����
	void Draw(void);   // �`�揈��

	void Hit(void); // ���������Ƃ��̏���
	EXPLOSIONTYPE GetExplosionType(void); // �����̃^�C�v��Ԃ�
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_ENEMYEXPLOSION_TEXTURE]; // �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3		  m_pos;			  // ���W
	D3DXVECTOR3		  m_size;			  // �傫��
	int				  m_nCounterAnim;	  // �A�j���[�V�����̃J�E���g
	int				  m_nPatternAnim;	  // �A�j���[�V�����̃p�^�[��
	int				  m_nTimeAnim;		  // �A�j���[�V�����̎���
	EXPLOSIONTYPE	  m_ExplosionType;	  // �����̃^�C�v
	EXPLOSIONTEXTURE  m_ExplosionTexture; // �����̃e�N�X�`��
};
#endif