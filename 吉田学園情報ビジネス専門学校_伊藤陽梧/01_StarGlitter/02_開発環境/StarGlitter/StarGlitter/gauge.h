//=============================================================================
//
// ゲージの処理 [gauge.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _GAUGE_H_
#define _GAUGE_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_GAUGE_TEXTURE (3)
#define MAX_GAUGE_EXTEND (276.0f)

//=============================================================================
// ゲージクラス
//=============================================================================
class CGauge
{
public:
	CGauge();  // コンストラク
	~CGauge(); // デストラクタ

	static HRESULT Load(void); // ロード
	static void Unload(void);  // アンロード

	static CGauge *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size); // クリエイト
	void SetGauge(D3DXVECTOR3 pos, D3DXVECTOR3 size) {		  // 座標とサイズの設定
		m_pos = pos; m_size = size;
	}

	HRESULT Init();    // 初期化処理
	void Uninit(void); // 終了処理
	void Update(void); // 更新処理
	void Draw(void);   // 描画処理

	void SetExtend(float fExtendX, float fExtendY) { // 長さをセットする処理
		m_fMaxExtendX += fExtendX; m_fMaxExtendY += fExtendY;
	}
	float GetMaxExtend(void); // 長さの最大値を返す
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;  // テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	   // 頂点バッファへのポインタ
	D3DXVECTOR3				m_pos;		   // 座標
	D3DXVECTOR3				m_size;		   // 座標
	float					m_fExtendX;	   // テクスチャを横に伸ばす
	float					m_fExtendY;	   // テクスチャを縦に伸ばす
	float					m_fMaxExtendX; // テクスチャを横に伸ばす最大値
	float					m_fMaxExtendY; // テクスチャを縦に伸ばす最大値
};
#endif