//=============================================================================
//
// ガッチャンの処理 [gattyann..h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _GATTYANN_H_
#define _GATTYANN_H_

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_GATTYANN_TEXTURE (8)
#define GATTYANN_SPEED (15.0f)
#define GATTYANN_OPEN_SPEED (15.0f) // 開く速さ

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// ガッチャンクラス
//=============================================================================
class CGattyann :public CScene2D
{
public:
	typedef enum
	{
		GATTYANN_1 = 0, // 1枚目
		GATTYANN_2,		// 2枚目
		GATTYANN_3,		// 3枚目
		GATTYANN_4,		// 4枚目
		GATTYANN_5,		// 5枚目
		GATTYANN_6,		// 6枚目
		GATTYANN_7,		// 7枚目
		GATTYANN_8,		// 8枚目
	}GATTYANNTYPE;

	CGattyann();  // コンストラク
	~CGattyann(); // デストラクタ

	static HRESULT Load(void);
	static void Unload(void);
	static CGattyann *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, GATTYANNTYPE GattyannType); // クリエイト

	HRESULT Init(void); // 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理

	void SetGattyann(D3DXVECTOR3 pos, D3DXVECTOR3 size, GATTYANNTYPE GattyannType) { // ガッチャンの設定
		m_pos = pos; m_size = size; m_GattyannType = GattyannType;
		SetPosition(pos); SetSize(size);
	}
	
	void CloseMove(void); // 閉じる処理
	void OpenMove(void);  // 開く処理
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_GATTYANN_TEXTURE]; // テクスチャへのポインタ
	D3DXVECTOR3				  m_pos;		  // 座標
	D3DXVECTOR3				  m_size;		  // 大きさ
	int						  m_nCount;		  // カウント
	GATTYANNTYPE			  m_GattyannType; // 何枚目か
};
#endif