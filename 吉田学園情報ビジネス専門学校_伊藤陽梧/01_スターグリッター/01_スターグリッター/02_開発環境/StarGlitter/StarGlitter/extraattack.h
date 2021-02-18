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
	}EXTRAATTCKPLAYERNUM;

	typedef enum
	{
		EXTRAATTACK_BLINKING = 0,  // �`�J�`�J���Ȃ��瑊��̕��ɍs���G�N�X�g���A�^�b�N
		EXTRAATTACK_AIM,		   // �����_���G�N�X�g���A�^�b�N
		EXTRAATTACK_EXPLOSION,	   // ��������G�N�X�g���A�^�b�N
		EXTRAATTACK_LOCKET,		   // ��ɂ�����G�N�X�g���A�^�b�N
		EXTRAATTACK_MAX,
	}EXTRAATTACK;

	CExtraattck();  // �R���X�g���N
	~CExtraattck();	// �f�X�g���N�^

	static HRESULT Load(void); // ���[�h
	static void Unload(void);  // �A�����[�h
	static CExtraattck *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size,
		EXTRAATTCKPLAYERNUM Player, EXTRAATTACK Extraattack, OBJTYPE objType); // �N���G�C�g

	HRESULT Init();     // ����������
	void Uninit(void);  // �I������
	void Update(void);  // �X�V����
	void Draw(void);    // �`�揈��

	void SetExtraAttack(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size,
		EXTRAATTCKPLAYERNUM Player, EXTRAATTACK Extraattack, OBJTYPE objType) { //�G�N�X�g���A�^�b�N�̐ݒ�
		SetPosition(pos); SetSize(size);
		m_pos = pos; m_move = move; m_size = size;
		m_ExtraPlayerNum = Player; m_ExtraAttack = Extraattack;
		SetObjType(objType);
	}

	void Blinking(void);  // �`�J�`�J���鏈��
	void Aim(void);		  // �����_������
	void Explosion(void); // �������鏈��
	void Locket(void);	  // ��ɂ����鏈��
	EXTRAATTACK GetExtraAttack(void); // �G�N�X�g���A�^�b�N��Ԃ�����
	EXTRAATTCKPLAYERNUM GetExtraPlayerNum(void); // �G�N�X�g���A�^�b�N�̃v���C���[�̔ԍ���Ԃ�����
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_EXTRAATTACK_TEXTURE];  // �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3	m_pos;					   // ���W
	D3DXVECTOR3	m_move;					   // ����
	D3DXVECTOR3 m_Getpos;				   // �󂯎�������W
	D3DXVECTOR3	m_size;					   // �傫��
	float	m_fAngle;					   // �p�x
	int		m_nCountColor;				   // �F�̃J�E���g
	EXTRAATTCKPLAYERNUM m_ExtraPlayerNum;  // �ǂ̃v���C���[��
	EXTRAATTACK m_ExtraAttack;			   // �G�N�X�g���A�^�b�N�̃^�C�v
};
#endif