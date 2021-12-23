//=============================================================================
//
// ワープ床ヘッダー [warp_tile.h]
// Author : 吉田 悠人
//
//=============================================================================

//二重インクルード防止
#ifndef _WARP_TILE_H_
#define _WARP_TILE_H_

//*****************************
// インクルード
//*****************************
#include "tile.h"
#include "map.h"
#include <vector>
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
class CWarpTile : public CTile
{
public:
	//*****************************
	// 列挙
	//*****************************
	// ステート
	typedef enum
	{
		WARP_TILE_NORMAL = 0,	//通常状態
		WARP_TILE_WARP,			//ワープ状態
		WARP_TILE_WARP_AFTER,	//ワープ先の状態
		WARP_TILE_STOP			//停止状態
	}WARP_TILE_STATE;

	//識別用タイプ
	typedef enum
	{
		WARP_TILE_TYPE_NONE = -1,//なし
		WARP_TILE_TYPE_1,		//タイプ1
		WARP_TILE_TYPE_2,		//タイプ2
		WARP_TILE_TYPE_MAX
	}WARP_TILE_TYPE;

	//*****************************
	//メンバ関数
	//*****************************
	CWarpTile();
	~CWarpTile();

	static void Create_1(D3DXVECTOR3 pos, D3DXCOLOR col);	//生成処理（識別番号1）
	static void Create_2(D3DXVECTOR3 pos, D3DXCOLOR col);	//生成処理（識別番号2）

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:
	void HitPlayerAction(CPlayer*pPlayer);	// プレイヤーが乗っているか
	void HitPlayerActionRelease(void);		// プレイヤーが降りたか

	//*****************************
	// メンバ変数
	//*****************************
	int				m_nLyncTile;								// つながっているタイル
	WARP_TILE_STATE m_WarpState;								// 状態変数
	WARP_TILE_TYPE	m_WarpType;									// ワープ床の識別用変数
	static std::vector<std::vector<CWarpTile*>> m_pWarpTile;	// ワープ床のポインタ動的配列
	static int m_nTotalWarpTile;								// 総数
};

#endif