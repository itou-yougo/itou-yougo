//=============================================================================
//
// �Q�[������ [game.h]
// Author : �ɓ��z��
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "mode.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_ENEMY_NUM (50) // �G�̍ő吔
#define MAX_NUMBER_CREATE (2) // �i���o�[�̐������鐔

//=============================================================================
// �O���錾
//=============================================================================
class CPlayer;
class CNumber;

//=============================================================================
// �Q�[���N���X
//=============================================================================
class CGame :public CMode
{
public:
	CGame();
	~CGame();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayer *GetPlayer(void);
	static void SubtractEnemy(void) { 
		m_nEnemyNum--; m_nEnemyDeathTotal++; }

	static int GetEnemyDeathTotal(void) { return m_nEnemyDeathTotal; }
private:
	static CPlayer *m_pPlayer;		// �v���C���[
	static int m_nEnemyNum;			// �G�̐�
	static int m_nEnemyDeathTotal;	// �G�|��������
	bool m_bEnemyCreate;			// �G�𐶐����邩�ǂ���
	int m_nEnemyCreateTime;			// �G�𐶐����鎞��
};
#endif