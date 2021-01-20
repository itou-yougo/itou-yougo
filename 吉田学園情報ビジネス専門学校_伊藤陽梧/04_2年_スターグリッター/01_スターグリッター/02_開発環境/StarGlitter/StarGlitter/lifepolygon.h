//=============================================================================
//
// ライフポリゴンの処理 [lifepolygon.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _LIFEPOLYGON_H_
#define _LIFEPOLYGON_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// ライフポリゴンクラス
//=============================================================================
class CLifepolygon
{
public:

	CLifepolygon();  // コンストラク
	~CLifepolygon(); // デストラクタ

	static HRESULT Load(void); // ロード
	static void Unload(void);  // アンロード

	static CLifepolygon *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nDivide, int nCount); // クリエイト

	HRESULT Init(void); // 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理

	void SetLifePolygon(int nDivide, int nCount); // ライフのテクスチャの設定

	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; } // 座標の設定
	void SetSize(D3DXVECTOR3 size) { // サイズの設定
		m_size = size;
	}

private:
	static LPDIRECT3DTEXTURE9 m_pTexture; // テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	  // 頂点バッファへのポインタ
	D3DXVECTOR3				m_pos;		  // 座標
	D3DXVECTOR3				m_size;		  // 大きさ
};
#endif