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
	CSelect();
	~CSelect();

	static HRESULT Load(void);
	static void Unload(void);
	static CSelect *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, SELECTTYPE SelectType);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetText(D3DXVECTOR3 pos, float fSizeX, float fSizeY, SELECTTYPE SelectType) {
		m_pos = pos; m_fSizeX = fSizeX; m_fSizeY = fSizeY; m_pSelectType = SelectType;
		SetPosition(pos); SetSize(fSizeX, fSizeY);
	}

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_SELECT_TEXTURE]; // テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9   m_pVtxBuff;				 // 頂点バッファへのポインタ
	D3DXVECTOR3				  m_pos;					 // ポリゴンの位置
	int						  m_nCount;					 // カウント
	int						  m_nCountSelect;			 // 選んだ時のカウント
	float					  m_fSizeX;					 // ポリゴンの横の大きさ
	float					  m_fSizeY;					 // ポリゴンの縦の大きさ
	bool					  m_bButtonPress;			 // ボタンを押したかどうか
	CText*					  m_pText[MAX_TEXT]; // テキストのポインタ
	SELECTTYPE				  m_pSelectType;			 // セレクトのタイプ
};
#endif