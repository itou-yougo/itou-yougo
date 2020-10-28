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

	CBg();
	~CBg();

	static HRESULT Load(void);
	static void Unload(void);
	static CBg *Create(BGTYPE bgtype, OBJTYPE objType);

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetBG(BGTYPE bgtype, OBJTYPE objType) {
		m_bgtype = bgtype; SetObjType(objType);
	}
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BG_TEXTURE]; // �e�N�X�`���̃|�C���^
	CScene2D *m_apScene[MAX_BG_TEXTURE];				   // CScene2D�̃|�C���^
	BGTYPE m_bgtype;									   // �w�i�̎��
};
#endif