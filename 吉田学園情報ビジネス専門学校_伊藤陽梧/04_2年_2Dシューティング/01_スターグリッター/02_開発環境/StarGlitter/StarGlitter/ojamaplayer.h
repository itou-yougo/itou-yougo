//=============================================================================
//
// ������܃v���C���[�̏��� [ojamaplayer.h]
// Author : �ɓ��z��
//
//=============================================================================
#ifndef _OJAMAPLAYER_H_
#define _OJAMAPLAYER_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2d.h"
#include "bullet.h"

//=============================================================================
// ������܃v���C���[�N���X
//=============================================================================
class COjamaplayer :public CScene2D
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

	COjamaplayer();
	~COjamaplayer();

	static HRESULT Load(void);
	static void Unload(void);
	static COjamaplayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fSizeX, float fSizeY, int nCount, D3DXVECTOR3 Accele, OJAMATYPE OjamaType, OBJTYPE objType);

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetCOjama(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fSizeX, float fSizeY, int nCount, D3DXVECTOR3 Accele, OJAMATYPE OjamaType, OBJTYPE objType) {
		SetPosition(pos); SetSize(fSizeX, fSizeY);
		m_pos = pos; m_move = move;
		m_fSizeX = fSizeX; m_fSizeY = fSizeY;
		m_nCount = nCount; m_accele = Accele;
		m_OjamaType = OjamaType; SetObjType(objType);
	}

private:
	static LPDIRECT3DTEXTURE9 m_pTexture; // �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3	m_pos;					  // ���W
	D3DXVECTOR3	m_move;					  // ����
	D3DXVECTOR3 m_Getpos;				  // �󂯎�������W
	D3DXVECTOR3	m_middle;				  // ���S�̍��W
	D3DXVECTOR3 m_posPlayer2;			  // �v���C���[2�̍��W
	D3DXVECTOR3 m_GetposPlayer2;		  // �v���C���[2�̎󂯎�������W
	D3DXVECTOR3	m_accele;				  // �����x
	float	m_fSizeX;					  // ���̑傫��
	float	m_fSizeY;					  // �c�̑傫��
	float	m_fGetSizeX;				  // �󂯎�������̑傫��
	float	m_fGetSizeY;				  // �󂯎�����c�̑傫��
	float	m_fAngle;					  // �p�x
	int		m_nCount;					  // ����ڂ̃N���G�C�g���̃J�E���g
	int		m_nOjamaCount;				  // ������܂̃J�E���g
	bool	m_bFirstmove;				  // ���ڂ̓��������锻��
	bool	m_bSecondmove;				  // ���ڂ̓��������锻��
	OJAMATYPE m_OjamaType;				  // ������܂̃^�C�v
};
#endif