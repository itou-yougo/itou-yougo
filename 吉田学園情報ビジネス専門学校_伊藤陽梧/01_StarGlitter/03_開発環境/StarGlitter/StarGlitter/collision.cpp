//=============================================================================
//
// �����蔻��̏��� [collision.cpp]
// Author : �ɓ��z��
//
//=============================================================================
#include "collision.h"
#include "scene2d.h"

//=============================================================================
// ��`�̓����蔻��
// pos1   : �����鑤�̈ʒu
// size1  : �����鑤�̃T�C�Y
// pos2   : ���Ă��鑤�̈ʒu
// size2  : ���Ă��鑤�̃T�C�Y
// �߂�l : �����������ǂ�����Ԃ�
//=============================================================================
bool CCollision::RectangleCollision(D3DXVECTOR3 pos1, D3DXVECTOR3 size1,
	D3DXVECTOR3 pos2, D3DXVECTOR3 size2)
{
	bool bHit = false;

	D3DXVECTOR3 box1Max = D3DXVECTOR3(size1.x / 2, size1.y / 2, size1.z / 2) + pos1;          //�Ԃ��鑤�̍ő�l
	D3DXVECTOR3 box1Min = D3DXVECTOR3(-size1.x / 2, -size1.y / 2, -size1.z / 2) + pos1;       //�Ԃ��鑤�̍ŏ��l
	D3DXVECTOR3 box2Max = D3DXVECTOR3(size2.x / 2, size2.y / 2, size2.z / 2) + pos2;      //�Ԃ����鑤�̍ő�l
	D3DXVECTOR3 box2Min = D3DXVECTOR3(-size2.x / 2, -size2.y / 2, -size2.z / 2) + pos2;   //�Ԃ����鑤�̍ŏ��l

	if (box1Max.y > box2Min.y&&
		box1Min.y < box2Max.y&&
		box1Max.x > box2Min.x&&
		box1Min.x < box2Max.x&&
		box1Max.z > box2Min.z&&
		box1Min.z < box2Max.z)
	{
		bHit = true;
	}

	// �����������ǂ�����Ԃ�
	return bHit;
}

//=============================================================================
// ���̓����蔻��
// pos1   : �Ԃ��鑤�̈ʒu
// size1  : �Ԃ��鑤�̃T�C�Y
// pos2   : �Ԃ����鑤�̈ʒu
// size2  : �Ԃ����鑤�̃T�C�Y
// �߂�l : �Ԃ��鑤���~�̒��ɓ����Ă��邩�ǂ���
//=============================================================================
bool CCollision::SphereCollision(D3DXVECTOR3 pos1, float size1, D3DXVECTOR3 pos2, float size2)
{
	float distance = powf(pos1.x - pos2.x, 2.0f) + powf(pos1.y - pos2.y, 2.0f) + powf(pos1.z - pos2.z, 2.0f); //�ʒu
	float radius = powf(size1 + size2, 2.0f); // ���a

	// �����������ǂ�����Ԃ�
	return (distance <= radius);
}

//=============================================================================
// ��`�̓����蔻��(�V�[���̃|�C���^���g��)
// pos    : �����鑤�̈ʒu
// size   : �����鑤�̃T�C�Y
// pScene : ���Ă��鑤�̃|�C���^
// �߂�l : �����������ǂ�����Ԃ�
//=============================================================================
bool CCollision::PRectangleCollision(D3DXVECTOR3 pos, D3DXVECTOR3 size, CScene *pScene)
{
	D3DXVECTOR3 Getpos = ((CScene2D*)pScene)->GetPosition();
	D3DXVECTOR3 GetSize = ((CScene2D*)pScene)->GetSize();

	bool bHit = false;

	D3DXVECTOR3 box1Max = D3DXVECTOR3(size.x / 2, size.y / 2, size.z / 2) + pos;					//�Ԃ��鑤�̍ő�l
	D3DXVECTOR3 box1Min = D3DXVECTOR3(-size.x / 2, -size.y / 2, -size.z / 2) + pos;					//�Ԃ��鑤�̍ŏ��l
	D3DXVECTOR3 box2Max = D3DXVECTOR3(GetSize.x / 2, GetSize.y / 2, GetSize.z / 2) + Getpos;	//�Ԃ����鑤�̍ő�l
	D3DXVECTOR3 box2Min = D3DXVECTOR3(-GetSize.x / 2, -GetSize.y / 2, -GetSize.z / 2) + Getpos; //�Ԃ����鑤�̍ŏ��l

	if (box1Max.y > box2Min.y&&
		box1Min.y < box2Max.y&&
		box1Max.x > box2Min.x&&
		box1Min.x < box2Max.x)
	{
		bHit = true;
	}

	// �����������ǂ�����Ԃ�
	return bHit;
}