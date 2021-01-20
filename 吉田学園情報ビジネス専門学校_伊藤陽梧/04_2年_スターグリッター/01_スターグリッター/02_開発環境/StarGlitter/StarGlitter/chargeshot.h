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

	CChargeshot();  // �R���X�g���N
	~CChargeshot();	// �f�X�g���N�^

	static HRESULT Load(void); // ���[�h
	static void Unload(void);  // �A�����[�h

	static CChargeshot *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CHARGESHOTTYPE chargeshottype, OBJTYPE objType); // �N���G�C�g
	void SetChargeShot(D3DXVECTOR3 pos, D3DXVECTOR3 size, CHARGESHOTTYPE chargeshottype, OBJTYPE objType) { // �`���[�W�V���b�g�̐ݒ�
		m_pos = pos; m_size = size;
		m_chargeshottype = chargeshottype; SetObjType(objType);
	}

	HRESULT Init();    // ����������
	void Uninit(void); // �I������
	void Update(void); // �X�V����
	void Draw(void);   // �`�揈��

	CGauge* GetGauge(void); // �Q�[�W�̃|�C���^��Ԃ�
	CCharge* GetCharge(void); // �`���[�W�̃|�C���^��Ԃ�
private:
	CGauge *pGauge;							  // �Q�[�W�̃|�C���^
	CCharge *pCharge;						  // �`���[�W�̃|�C���^
	static LPDIRECT3DTEXTURE9 m_pTexture;	  // �e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		  // ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;			  // ���̈ʒu
	D3DXVECTOR3				m_size;			  // ���̈ʒu
	CHARGESHOTTYPE			m_chargeshottype; // �`���[�W�V���b�g�̃^�C�v
};
#endif