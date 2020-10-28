//=============================================================================
//
// 文字の描画の処理 [text.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _TEXT_H_
#define _TEXT_H_

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_TEXT_TEXTURE (6)

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// プレイヤークラス
//=============================================================================
class CText :public CScene2D
{
public:
	typedef enum
	{
		TEXTTYPE_RESTART = 0, // もう一度始める
		TEXTTYPE_MODORU,	  // タイトルに戻る
		TEXTTYPE_READY,		  // READYの文字
		TEXTTYPE_GO,		  // GOの文字
		TEXTTYPE_KO,		  // KOの文字
		TEXTTYPE_WON,		  // WONの文字
		TEXTTYPE_LOST,		  // LOSTの文字
		TEXTTYPE_MAX,
	}TEXTTYPE;

	CText();
	~CText();

	static HRESULT Load(void);
	static void Unload(void);
	static CText *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, TEXTTYPE TextType);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetText(D3DXVECTOR3 pos, float fSizeX, float fSizeY, TEXTTYPE TextType) {
		m_pos = pos; m_fSizeX = fSizeX; m_fSizeY = fSizeY; m_TextType = TextType;
		SetPosition(pos); SetSize(fSizeX, fSizeY);
	}

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_TEXT_TEXTURE]; // テクスチャへのポインタ
	D3DXVECTOR3				  m_pos;	  // 座標
	int						  m_nAlpha;   // 透明度
	int						  m_nCount;   // カウント
	float					  m_fSizeX;   // 横の大きさ
	float					  m_fSizeY;   // 縦の大きさ
	bool					  m_bUse;	  // 使っているかの判定
	TEXTTYPE				  m_TextType; // テキストのタイプ
};
#endif