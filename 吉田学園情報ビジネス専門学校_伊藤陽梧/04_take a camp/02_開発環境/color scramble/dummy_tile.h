//====================================================
//
// dummy_tileヘッダ [dummy_tile.h]
// Author : 伊藤陽梧
//
//====================================================

//二重インクルード防止
#ifndef _DUMMY_TILE_H_
#define _DUMMY_TILE_H_

//=============================
// インクルード
//=============================
#include "tile.h"

//=============================
//前方宣言
//=============================
class CScene3d;

//=============================
// クラス定義
//=============================

// ダミータイルクラス
class CDummyTile : public CTile
{
public:
	//============
	// メンバ関数
	//===========
	CDummyTile();
	~CDummyTile();

	static void Create(D3DXVECTOR3 pos, D3DXCOLOR col = TILE_DEFAULT_COLOR);

	HRESULT Init(void);
	void Uninit(void);
private:

	//============
	// メンバ変数
	//===========
	CScene3d *m_pCrossPolygon;        // マーク
};

#endif