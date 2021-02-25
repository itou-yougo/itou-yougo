//=============================================================================
//
// �|���G�̐��̏��� [enemyremainder.h]
// Author : �ɓ��z��
//
//=============================================================================
#ifndef _ENEMYREMAINDER_H_
#define _ENEMYREMAINDER_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "scene.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_ENEMY_NUM (50)												// �G�̍ő吔
#define MAX_NUMBER_CREATE (2)											// �i���o�[�̐������鐔
#define ENEMYREMAINDER_POS (D3DXVECTOR3(1000.0f, 100.0f, 0.0f))			// ���W
#define ENEMYREMAINDER_SIZE (D3DXVECTOR3(422.5f, 65.5f, 0.0f))			// �T�C�Y
#define ENEMYREMAINDER_POS_DISTANCE (D3DXVECTOR3(30.0f, 0.0f, 0.0f))	// ��������
#define ENEMYREMAINDER_NUM_SIZE (D3DXVECTOR3(70.0f, 95.5f, 0.0f))		// �����̃T�C�Y

//=============================================================================
// �O���錾
//=============================================================================
class CNumber;

//=============================================================================
// �G�l�~�[���}�C���_�[�N���X
//=============================================================================
class CEnemyremainder : public CScene
{
public:

	CEnemyremainder(int nPriority = OBJTYPE_UI);
	~CEnemyremainder();

	static CEnemyremainder * Create(D3DXVECTOR3 pos);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	D3DXVECTOR3 m_pos;
	CNumber* m_apNumber[MAX_NUMBER_CREATE];
};
#endif // !_SCORE_H_