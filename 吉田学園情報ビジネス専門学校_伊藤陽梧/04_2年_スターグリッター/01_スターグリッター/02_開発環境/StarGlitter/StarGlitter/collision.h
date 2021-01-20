//=============================================================================
//
// �����蔻��̏��� [collision.h]
// Author : �ɓ��z��
//
//=============================================================================
#ifndef _COLLISION_H_
#define _COLLISION_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene.h"

//=============================================================================
// �R���W�����N���X
//=============================================================================
class CCollision
{
public:
	static bool RectangleCollision(D3DXVECTOR3 pPos1, D3DXVECTOR3 size1, D3DXVECTOR3 pPos2, D3DXVECTOR3 size2); // ��`�̓����蔻��
	static bool SphereCollision(D3DXVECTOR3 pos1, float size1, D3DXVECTOR3 pos2, float size2); // ���̓����蔻��
	static bool PRectangleCollision(D3DXVECTOR3 pos, D3DXVECTOR3 size, CScene *pScene); // ��`�̓����蔻��(�V�[���̃|�C���^���g��)
private:

};
#endif
