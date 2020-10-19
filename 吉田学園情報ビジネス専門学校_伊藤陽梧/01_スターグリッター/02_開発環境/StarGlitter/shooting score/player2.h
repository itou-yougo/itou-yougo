//=============================================================================
//
// �|���S���̕`��̏��� [player2.h]
// Author : �ɓ��z��
//
//=============================================================================
#ifndef _PLAYER2_H_
#define _PLAYER2_H_


//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// �O���錾
//=============================================================================
class CSound;
class CLife;
class CChargeshot;
class CBomb;
class CEffect;

//=============================================================================
// �}�N����`
//=============================================================================
#define PLAYER_SPEED (10.0f)			 // ���@�̑���
#define PLAYER2_MOVABLE_RANGE_S (915.0f)  // ���@�̈ړ��ł���͈�(�Z���ق�)
#define PLAYER2_MOVABLE_RANGE_L (1658.0f) // ���@�̈ړ��ł���͈�(�����ق�)
#define PLAYER2_BOMB_MAX (2)				// ���@�̃{���̍ő吔

//=============================================================================
// �v���C���[�N���X
//=============================================================================
class CPlayer2 :public CScene2D
{
public:
	typedef enum
	{
		PLAYERSTATE_NONE = 0,
		PLAYERSTATE_NOMAL,  // �m�[�}�����
		PLAYERSTATE_DAMAGE, // �_���[�W���󂯂����
		PLAYERSTATE_LOSE,	// ���������̏��
		PLAYERSTATE_MAX,
	}PLAYERSTATE;

	CPlayer2();
	~CPlayer2();

	static HRESULT Load(void);
	static void Unload(void);
	static CPlayer2 *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fSizeX, float fSizeY, int nLife, OBJTYPE objType);

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPlayer2(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fSizeX, float fSizeY, int nLife, OBJTYPE objType) {
		SetPosition(pos); m_pos = pos; m_move = move;
		m_fSizeX = fSizeX; m_fSizeY = fSizeY;
		m_nLife = nLife; SetObjType(objType);
	}

	void PlayerDamage2(int nDamage);
	void PlayerAddLife2(int nLife);
	CChargeshot* GetChargeShot(void);
	PLAYERSTATE GetPlayer2State(void);
private:
	CLife*					  m_pLife;					 // �̗͂̃|�C���^
	CChargeshot*			  m_pChargeShot;			 // �`���[�W�V���b�g�̃|�C���^
	CBomb*					  m_pBomb[PLAYER2_BOMB_MAX]; // �{���̃|�C���^
	CEffect*				  m_pEffect;				 // �G�t�F�N�g�̃|�C���^
	static LPDIRECT3DTEXTURE9 m_pTexture;				 // �e�N�X�`���ւ̃|�C���^
	static int				  m_nDamage;				 // �󂯂��_���[�W�̒l
	D3DXVECTOR3				  m_pos;					 // �ʒu
	D3DXVECTOR3				  m_Getpos;					 // �G�̈ʒu
	D3DXVECTOR3				  m_move;					 // ����
	float					  m_fSizeX;					 // ���̑傫��
	float					  m_fSizeY;					 // �c�̑傫��
	float					  m_fGetSizeX;				 // �󂯎�������̑傫��
	float					  m_fGetSizeY;				 // �󂯎�����c�̑傫��
	float					  m_fAngle;					 // �p�x
	int						  m_nLife;					 // ���@�̗̑�
	int						  m_nBulletShotCount; 		 // �e�����Ԋu
	int						  m_nHitCount;		 		 // ���ɓG�ɓ�����J�E���g
	int						  m_nExtraAttackCount;		 // �G�N�X�g���A�^�b�N�̃J�E���g
	int						  m_nPressTime;				 // �{�^������������
	bool					  m_bExtraAttack;			 // �G�N�X�g���A�^�b�N������t���O
	bool					  m_bEffectCreate;			 // �G�t�F�N�g���o���t���O
	PLAYERSTATE				  m_PlayerState;			 // �v���C���[�̏��
};
#endif