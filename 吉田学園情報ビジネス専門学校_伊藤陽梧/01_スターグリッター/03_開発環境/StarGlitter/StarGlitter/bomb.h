//=============================================================================
//
// �{���̏��� [bomb.h]
// Author : �ɓ��z��
//
//=============================================================================
#ifndef _BOMB_H_
#define _BOMB_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// �{���N���X
//=============================================================================
class CBomb :public CScene2D
{
public:
	typedef enum
	{
		BOMB_TYPE_NONE = 0,
		BOMB_TYPE_PLAYER,  // �v���C���[1�̃{��
		BOMB_TYPE_PLAYER2, // �v���C���[2�̃{��
		BOMB_TYPE_MAX,
	}BOMBTTYPE;

	CBomb();  // �R���X�g���N
	~CBomb(); // �f�X�g���N�^

	static HRESULT Load(void); // ���[�h
	static void Unload(void);  // �A�����[�h
	static CBomb *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, BOMBTTYPE BombType, OBJTYPE objType); // �N���G�C�g

	HRESULT Init();    // ����������
	void Uninit(void); // �I������
	void Update(void); // �X�V����
	void Draw(void);   // �`�揈��

	void SetBomb(D3DXVECTOR3 pos, D3DXVECTOR3 size, BOMBTTYPE BombType, OBJTYPE objType) { // �{���̐ݒ�
		SetPosition(pos); SetSize(size);
		m_pos = pos; m_BombType = BombType;
		SetObjType(objType);
	}

	void UseBomb(void); // �{�����g���Ƃ��̏���
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;  // �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3	m_pos;					   // �{���̍��W
	D3DXVECTOR3 m_Getpos;				   // �󂯂��Ƃ������W
	bool	m_bUse;						   // �{�����g�������ǂ���
	BOMBTTYPE m_BombType;				   // �{���̃^�C�v
};
#endif