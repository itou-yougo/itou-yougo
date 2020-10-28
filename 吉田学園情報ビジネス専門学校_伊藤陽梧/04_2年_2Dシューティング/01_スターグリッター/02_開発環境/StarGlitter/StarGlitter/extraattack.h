//=============================================================================
//
// �G�N�X�g���A�^�b�N�̏��� [extraattack.h]
// Author : �ɓ��z��
//
//=============================================================================
#ifndef _EXTRAATTACK_H_
#define _EXTRAATTACK_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2d.h"
#include "bullet.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_EXTRAATTACK_TEXTURE (4) //�e�N�X�`���̍ő吔

//=============================================================================
// �G�N�X�g���A�^�b�N�N���X
//=============================================================================
class CExtraattck :public CScene2D
{
public:
	typedef enum
	{
		EXTRAATTCK_PLAYER_NONE = 0,
		EXTRAATTCK_PLAYER1,		    // �v���C���[1�̃G�N�X�g���A�^�b�N
		EXTRAATTCK_PLAYER2,		    // �v���C���[2�̃G�N�X�g���A�^�b�N
		EXTRAATTCK_PLAYER_MAX,
	}PLAYER;

	typedef enum
	{
		EXTRAATTACK_NONE = 0,
		EXTRAATTACK_TIKATIKA,  // �`�J�`�J���Ȃ��瑊��̕��ɍs���G�N�X�g���A�^�b�N
		EXTRAATTACK_NERAU,	   // �����_���G�N�X�g���A�^�b�N
		EXTRAATTACK_EXPLOSION, // ��������G�N�X�g���A�^�b�N
		EXTRAATTACK_LOCKET,	   // ��ɂ�����G�N�X�g���A�^�b�N
		EXTRAATTACK_MAX,
	}EXTRAATTACK;

	CExtraattck();
	~CExtraattck();

	static HRESULT Load(void);
	static void Unload(void);
	static CExtraattck *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fSizeX, float fSizeY, PLAYER Player, EXTRAATTACK Extraattack, OBJTYPE objType);

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetExtraAttack(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fSizeX, float fSizeY, PLAYER Player, EXTRAATTACK Extraattack, OBJTYPE objType) {
		SetPosition(pos); SetSize(fSizeX, fSizeY);
		m_pos = pos; m_move = move;
		m_fSizeX = fSizeX; m_fSizeY = fSizeY;
		m_Player = Player; m_ExtraAttack = Extraattack;
		SetObjType(objType);
	}

	EXTRAATTACK GetExtraAttack(void);
private:
	CBullet::BULLETTYPE m_BulletType;	   // �e�̃^�C�v
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_EXTRAATTACK_TEXTURE];  // �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3	m_pos;					   // ���W
	D3DXVECTOR3	m_move;					   // ����
	D3DXVECTOR3 m_Getpos;				   // �󂯎�������W
	float	m_fSizeX;					   // ���̑傫��
	float	m_fSizeY;					   // �c�̑傫��
	float	m_fAngle;					   // �p�x
	int		m_nCountColor;				   // �F�̃J�E���g
	PLAYER m_Player;					   // �ǂ̃v���C���[��
	EXTRAATTACK m_ExtraAttack;			   // �G�N�X�g���A�^�b�N�̃^�C�v
};
#endif