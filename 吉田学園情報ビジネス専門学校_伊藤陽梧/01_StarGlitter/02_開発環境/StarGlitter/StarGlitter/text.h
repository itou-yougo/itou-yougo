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

	CText();  // コンストラク
	~CText(); // デストラクタ

	static HRESULT Load(void); // ロード
	static void Unload(void);  // アンロード
	static CText *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TEXTTYPE TextType); // クリエイト

	HRESULT Init(void); // 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理

	void SetText(D3DXVECTOR3 pos, D3DXVECTOR3 size, TEXTTYPE TextType) { // テキストの設定
		m_pos = pos; m_size = size; m_TextType = TextType;
		SetPosition(pos); SetSize(size);
	}

	void Ready(void); // Readyの文字の処理
	void Go(void);	  // Goの文字の処理
	void Ko(void);	  // Koの文字の処理
	void Won(void);   // Wonの文字の処理
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_TEXT_TEXTURE]; // テクスチャへのポインタ
	D3DXVECTOR3				  m_pos;	  // 座標
	D3DXVECTOR3				  m_size;	  // 大きさ
	int						  m_nAlpha;   // 透明度
	int						  m_nCount;   // カウント
	bool					  m_bUse;	  // 使っているかの判定
	TEXTTYPE				  m_TextType; // テキストのタイプ
};
#endif