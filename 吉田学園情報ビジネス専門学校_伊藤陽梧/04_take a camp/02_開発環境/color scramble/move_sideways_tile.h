//=============================================================================
//
// 横移動に動く床 ヘッダー [move_sideways_tile.h]
// Author : 吉田 悠人
//
//=============================================================================

//二重インクルード防止
#ifndef _MOVE_SIDEWAYS_TILE_H_
#define _MOVE_SIDEWAYS_TILE_H_

//*****************************
// インクルード
//*****************************
#include "move_tile.h"

//*****************************
//前方宣言
//*****************************
class CModel;

//*****************************
//マクロ定義
//*****************************

//*****************************
// クラス定義
//*****************************
class CSidewaysTile : public CMoveTile
{
public:

	//メンバ関数
	CSidewaysTile();
	~CSidewaysTile();

	static void	Create(D3DXVECTOR3 pos, D3DXCOLOR col = TILE_DEFAULT_COLOR);
	void		MoveRot(bool bReversal);
	void		TileCheck(void);
private:
};

#endif