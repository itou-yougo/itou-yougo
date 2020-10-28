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
#define GATTYANN_SPEED (10.0f)
#define GATTYANN_OPEN_SPEED (15)

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

	CGattyann();
	~CGattyann();

	static HRESULT Load(void);
	static void Unload(void);
	static CGattyann *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, GATTYANNTYPE GattyannType);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetGattyann(D3DXVECTOR3 pos, float fSizeX, float fSizeY, GATTYANNTYPE GattyannType) {
		m_pos = pos; m_fSizeX = fSizeX; m_fSizeY = fSizeY; m_GattyannType = GattyannType;
		SetPosition(pos); SetSize(fSizeX, fSizeY);
	}

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_GATTYANN_TEXTURE]; // テクスチャへのポインタ
	D3DXVECTOR3				  m_pos;		  // 座標
	float					  m_fSizeX;		  // 横の大きさ
	float					  m_fSizeY;		  // 縦の大きさ
	int						  m_nCount;		  // カウント
	GATTYANNTYPE			  m_GattyannType; // 何枚目か
};
#endif