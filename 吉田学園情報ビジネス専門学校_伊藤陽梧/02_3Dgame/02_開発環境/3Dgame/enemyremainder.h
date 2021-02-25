//=============================================================================
//
// 倒す敵の数の処理 [enemyremainder.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _ENEMYREMAINDER_H_
#define _ENEMYREMAINDER_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "scene.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_ENEMY_NUM (50)												// 敵の最大数
#define MAX_NUMBER_CREATE (2)											// ナンバーの生成する数
#define ENEMYREMAINDER_POS (D3DXVECTOR3(1000.0f, 100.0f, 0.0f))			// 座標
#define ENEMYREMAINDER_SIZE (D3DXVECTOR3(422.5f, 65.5f, 0.0f))			// サイズ
#define ENEMYREMAINDER_POS_DISTANCE (D3DXVECTOR3(30.0f, 0.0f, 0.0f))	// 離す距離
#define ENEMYREMAINDER_NUM_SIZE (D3DXVECTOR3(70.0f, 95.5f, 0.0f))		// 数字のサイズ

//=============================================================================
// 前方宣言
//=============================================================================
class CNumber;

//=============================================================================
// エネミーリマインダークラス
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