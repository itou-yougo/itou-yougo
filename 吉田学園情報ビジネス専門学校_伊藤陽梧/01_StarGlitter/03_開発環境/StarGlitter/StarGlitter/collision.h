//=============================================================================
//
// 当たり判定の処理 [collision.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _COLLISION_H_
#define _COLLISION_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene.h"

//=============================================================================
// コリジョンクラス
//=============================================================================
class CCollision
{
public:
	static bool RectangleCollision(D3DXVECTOR3 pPos1, D3DXVECTOR3 size1, D3DXVECTOR3 pPos2, D3DXVECTOR3 size2); // 矩形の当たり判定
	static bool SphereCollision(D3DXVECTOR3 pos1, float size1, D3DXVECTOR3 pos2, float size2); // 球の当たり判定
	static bool PRectangleCollision(D3DXVECTOR3 pos, D3DXVECTOR3 size, CScene *pScene); // 矩形の当たり判定(シーンのポインタを使う)
private:

};
#endif
