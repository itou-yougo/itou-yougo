//=============================================================================
//
// �|���S���̕`��̏��� [bg.h]
// Author : �ɓ��z��
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene.h"

//=============================================================================
// �O���錾
//=============================================================================
class CScene2D;

//=============================================================================
// �w�i�N���X
//=============================================================================
class CBg :public CScene
{
public:
	typedef enum
	{
		BGTYPE_GAME = 0, // �Q�[���̔w�i
		BGTYPE_FRAME,	 // �Q�[���̘g
		BGTYPE_TUTORIAL, // �`���[�g���A���̔w�i
		BGTYPE_RESULT,	 // ���U���g�̔w�i
	}BGTYPE;

	CBg();  // �R���X�g���N
	~CBg();	// �f�X�g���N�^

	static HRESULT Load(void); // ���[�h
	static void Unload(void);  // �A�����[�h
	static CBg *Create(BGTYPE bgtype, OBJTYPE objType); // �N���G�C�g

	HRESULT Init();    // ����������
	void Uninit(void); // �I������
	void Update(void); // �X�V����
	void Draw(void);   // �`�揈��

	void SetBG(BGTYPE bgtype, OBJTYPE objType) { // �w�i�̐ݒ�
		m_BgType = bgtype; SetObjType(objType);
	}
	void BgCreate(BGTYPE BgType); // �w�i�̃|���S������鏈��
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BG_TEXTURE]; // �e�N�X�`���̃|�C���^
	CScene2D *m_apScene[MAX_BG_TEXTURE];				   // CScene2D�̃|�C���^
	BGTYPE m_BgType;									   // �w�i�̎��
};
#endif