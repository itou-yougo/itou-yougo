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

	CBomb();
	~CBomb();

	static HRESULT Load(void);
	static void Unload(void);
	static CBomb *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, BOMBTTYPE BombType, OBJTYPE objType);

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetBomb(D3DXVECTOR3 pos, float fSizeX, float fSizeY, BOMBTTYPE BombType, OBJTYPE objType) {
		SetPosition(pos); SetSize(fSizeX, fSizeY);
		m_pos = pos; m_BombType = BombType;
		SetObjType(objType);
	}

	void UseBomb(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;  // �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3	m_pos;					   // �{���̍��W
	D3DXVECTOR3 m_Getpos;				   // �󂯂��Ƃ������W
	bool	m_bUse;						   // �{�����g�������ǂ���
	BOMBTTYPE m_BombType;				   // �{���̃^�C�v
};
#endif