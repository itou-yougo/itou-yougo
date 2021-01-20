//=============================================================================
//
// チャージの処理 [charge.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _CHARGE_H_
#define _CHARGE_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// チャージクラス
//=============================================================================
class CCharge
{
public:
	typedef enum
	{
		CHARGETYPE_NONE = 0,
		CHARGETYPE_1, // チャージの1段階目
		CHARGETYPE_2, // チャージの2段階目
		CHARGETYPE_3, // チャージの3段階目
		CHARGETYPE_MAX,
	}CHARGETYPE;

	CCharge();  // コンストラク
	~CCharge();	// デストラクタ 

	static HRESULT Load(void); // ロード
	static void Unload(void);  // アンロード

	static CCharge *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size); // クリエイト
	void SetCharge(D3DXVECTOR3 pos, D3DXVECTOR3 size) {		   // 座標とサイズの設定
		m_pos = pos; m_size = size;
	}

	void SetExtend(float fExtendX, float fMaxExtendX, float fExtendY, float fMaxExtendY) { // 長さをセットする処理
		m_fExtendX += fExtendX; m_fMaxExtendX = fMaxExtendX;
		m_fExtendY += fExtendY; m_fMaxExtendY = fMaxExtendY;
	}

	HRESULT Init();	   // 初期化処理
	void Uninit(void); // 終了処理
	void Update(void); // 更新処理
	void Draw(void);   // 描画処理

	void ChangeColor(void);			// 色と長さを変える処理
	CHARGETYPE GetChargeType(void); // チャージの段階を返す
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;  // テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	   // 頂点バッファへのポインタ
	D3DXVECTOR3				m_pos;		   // 座標
	D3DXVECTOR3				m_size;		   // 大きさ
	int						m_nCountColor; // 色を変えるカウント
	float					m_fExtendX;	   // テクスチャを横に伸ばす
	float					m_fExtendY;	   // テクスチャを縦に伸ばす
	float					m_fMaxExtendX; // テクスチャを横に伸ばす最大値
	float					m_fMaxExtendY; // テクスチャを縦に伸ばす最大値
	CHARGETYPE				m_chargetye;   // チャージの段階
};
#endif