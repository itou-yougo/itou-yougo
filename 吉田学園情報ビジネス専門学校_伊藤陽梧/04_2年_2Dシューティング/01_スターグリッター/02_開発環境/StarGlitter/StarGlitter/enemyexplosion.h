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

	CEnemyexplosion();
	~CEnemyexplosion();

	static HRESULT Load(void);
	static void Unload(void);
	static CEnemyexplosion *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, EXPLOSIONTYPE ExplosionType, EXPLOSIONTEXTURE ExplosionTexture, OBJTYPE objType);
	void SetExplosion(D3DXVECTOR3 pos, float fSizeX, float fSizeY, EXPLOSIONTYPE ExplosionType, EXPLOSIONTEXTURE ExplosionTexture, OBJTYPE objType) {
		m_pos = pos; m_fSizeX = fSizeX; m_fSizeY = fSizeY;
		m_ExplosionType = ExplosionType; m_ExplosionTexture = ExplosionTexture;
		SetPosition(pos); SetSize(fSizeX, fSizeY);
		SetObjType(objType);
	}

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	EXPLOSIONTYPE GetExplosionType(void);
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_ENEMYEXPLOSION_TEXTURE]; // �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3		  m_pos;			  // ���W
	D3DXVECTOR3		  m_Getpos;			  // �󂯎�������W
	float			  m_fSizeX;			  // ���̑傫��
	float			  m_fSizeY;			  // �c�̑傫��
	int				  m_nCounterAnim;	  // �A�j���[�V�����̃J�E���g
	int				  m_nPatternAnim;	  // �A�j���[�V�����̃p�^�[��
	int				  m_nTimeAnim;		  // �A�j���[�V�����̎���
	EXPLOSIONTYPE	  m_ExplosionType;	  // �����̃^�C�v
	EXPLOSIONTEXTURE  m_ExplosionTexture; // �����̃e�N�X�`��
};
#endif