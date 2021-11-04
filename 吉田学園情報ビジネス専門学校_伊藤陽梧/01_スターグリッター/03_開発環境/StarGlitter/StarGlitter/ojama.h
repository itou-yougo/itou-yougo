//=============================================================================
//
// ������܂̏��� [ojama.h]
// Author : �ɓ��z��
//
//=============================================================================
#ifndef _OJAMA_H_
#define _OJAMA_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2d.h"
#include "player.h"

//=============================================================================
// ������܃v���C���[�N���X
//=============================================================================
class COjama :public CScene2D
{
public:
	typedef enum
	{
		OJAMA_TYPE_NONE = 0,
		OJAMA_TYPE_CURVE,   // �Ȃ��邨�����
		OJAMA_TYPE_THROUGH, // �܂����������������
		OJAMA_TYPE_FALL,	// �����邨�����
		OJAMA_TYPE_MAX,
	}OJAMATYPE;

	typedef enum
	{
		OJAMAPLAYER_1P, // 1P�̂������
		OJAMAPLAYER_2P, // 2P�̂������
		OJAMAPLAYER_MAX,
	}OJAMAPLAYERNUM;

	COjama();  // �R���X�g���N
	~COjama(); // �f�X�g���N�^

	static HRESULT Load(void); // ���[�h
	static void Unload(void);  // �A�����[�h
	static COjama *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size,
		int nCount, D3DXVECTOR3 Accele, OJAMATYPE OjamaType,
		OJAMAPLAYERNUM OjamaPlayer, OBJTYPE objType); // �N���G�C�g

	HRESULT Init();    // ����������
	void Uninit(void); // �I������
	void Update(void); // �X�V����
	void Draw(void);   // �`�揈��

	void SetCOjama(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, 
		int nCount, D3DXVECTOR3 Accele, OJAMATYPE OjamaType, 
		OJAMAPLAYERNUM OjamaPlayer, OBJTYPE objType) { // ������܂̐ݒ�
		SetPosition(pos); SetSize(size);
		m_pos = pos; m_move = move; m_size = size;
		m_nCount = nCount; m_accele = Accele;
		m_OjamaType = OjamaType; m_OjamaPlayerNum = OjamaPlayer;
		SetObjType(objType);
	}

	void Curve(void);   // �Ȃ����ē�������
	void Through(void); // �܂�������������
	void Fall(void);    // �����ē�������

	void Hit(void); // ���������Ƃ�����
	void HitBullet(CScene *pScene); // �e�ɓ��������Ƃ�����
	void HitExplosion(CScene *pScene); // �����ɓ��������Ƃ�����
	void ExtraAttackCreate(CPlayer::PLAYERNUM PlayerNum); // �G�N�X�g���A�^�b�N����鏈��

	OJAMAPLAYERNUM GetOjamaPlayerNum(void); // ������܂̃v���C���[�̔ԍ���Ԃ�
private:
	static LPDIRECT3DTEXTURE9 m_pTexture; // �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3	m_pos;					  // ���W
	D3DXVECTOR3	m_move;					  // ����
	D3DXVECTOR3 m_Getpos;				  // �󂯎�������W
	D3DXVECTOR3 m_Fallpos;				  // ��������W
	D3DXVECTOR3	m_middle;				  // ���S�̍��W
	D3DXVECTOR3	m_accele;				  // �����x
	D3DXVECTOR3	m_size;					  // �傫��
	D3DXVECTOR3 m_GetSize;				  // �󂯎�����傫��
	float	m_fAngle;					  // �p�x
	int		m_nCount;					  // ����ڂ̃N���G�C�g���̃J�E���g
	int		m_nOjamaCount;				  // ������܂̃J�E���g
	bool	m_bFirstmove;				  // ���ڂ̓��������锻��
	bool	m_bSecondmove;				  // ���ڂ̓��������锻��
	OJAMATYPE m_OjamaType;				  // ������܂̃^�C�v
	OJAMAPLAYERNUM m_OjamaPlayerNum;	  // ������܂̃v���C���[�̔ԍ�
};
#endif