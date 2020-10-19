//=============================================================================
//
// �`���[�W�V���b�g�̏��� [chargeshot.h]
// Author : �ɓ��z��
//
//=============================================================================
#ifndef _CHARGESHOT_H_
#define _CHARGESHOT_H_

//=============================================================================
// �O���錾
//=============================================================================
class CGauge;
class CCharge;

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene.h"

//=============================================================================
// �`���[�W�V���b�g�N���X
//=============================================================================
class CChargeshot : public CScene
{
public:
	typedef enum
	{
		CHARGESHOTTYPE_NONE = 0,
		CHARGESHOTTYPE_PLAYER,  // PLAYER1�̃`���[�W�V���b�g
		CHARGESHOTTYPE_PLAYER2, // PLAYER2�̃`���[�W�V���b�g
	}CHARGESHOTTYPE;

	CChargeshot();
	~CChargeshot();

	static HRESULT Load(void);
	static void Unload(void);
	static CChargeshot *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, CHARGESHOTTYPE chargeshottype, OBJTYPE objType);
	void SetChargeShot(D3DXVECTOR3 pos, float fSizeX, float fSizeY, CHARGESHOTTYPE chargeshottype, OBJTYPE objType) {
		m_pos = pos; m_fSizeX = fSizeX; m_fSizeY = fSizeY;
		m_chargeshottype = chargeshottype; SetObjType(objType);
	}

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	CGauge* GetGauge(void);
	CCharge* GetCharge(void);
private:
	CGauge *pGauge;							  // �Q�[�W�̃|�C���^
	CCharge *pCharge;						  // �`���[�W�̃|�C���^
	static LPDIRECT3DTEXTURE9 m_pTexture;	  // �e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		  // ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;			  // ���̈ʒu
	float					m_fSizeX;		  // �|���S���̉��̑傫��
	float					m_fSizeY;		  // �|���S���̏c�̑傫��
	CHARGESHOTTYPE			m_chargeshottype; // �`���[�W�V���b�g�̃^�C�v
};
#endif