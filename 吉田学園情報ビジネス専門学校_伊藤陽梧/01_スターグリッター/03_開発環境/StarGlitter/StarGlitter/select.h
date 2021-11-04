//=============================================================================
//
// セレクトの処理 [select.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _SELECT_H_
#define _SELECT_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_SELECT_TEXTURE (2) // セレクトのテクスチャの最大数
#define MAX_TEXT (2) // テキストの最大数

//=============================================================================
// 前方宣言
//=============================================================================
class CText;

//=============================================================================
// セレクトクラス
//=============================================================================
class CSelect :public CScene2D
{
public:
	typedef enum
	{
		SELECTTYPE_KUROHAIKEI = 0, // 黒い背景
		SELECTTYPE_MENU,		   // メニュー
	}SELECTTYPE;

	CSelect();  // コンストラク
	~CSelect();	// デストラクタ

	static HRESULT Load(void); // ロード
	static void Unload(void);  // アンロード
	static CSelect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, SELECTTYPE SelectType); // クリエイト

	HRESULT Init(void); // 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理

	void SetSelect(D3DXVECTOR3 pos, D3DXVECTOR3 size, SELECTTYPE SelectType) { // セレクトの設定
		m_pos = pos; m_size = size; m_pSelectType = SelectType;
		SetPosition(pos); SetSize(size);
	}

	void Menu(void);	 // メニューの処理
	void Select(void);	 // 選ぶ処理
	void Decision(void); // 決定の処理
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_SELECT_TEXTURE]; // テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9   m_pVtxBuff;				 // 頂点バッファへのポインタ
	D3DXVECTOR3				  m_pos;					 // ポリゴンの位置
	D3DXVECTOR3				  m_size;					 // 大きさ
	int						  m_nCount;					 // カウント
	int						  m_nCountSelect;			 // 選んだ時のカウント
	bool					  m_bButtonPress;			 // ボタンを押したかどうか
	CText*					  m_pText[MAX_TEXT]; // テキストのポインタ
	SELECTTYPE				  m_pSelectType;			 // セレクトのタイプ
};
#endif