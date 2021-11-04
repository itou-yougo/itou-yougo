//=============================================================================
//
// タイトルロゴの処理 [titlelogo.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _TITLELOGO_H_
#define _TITLELOGO_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_LOGO_TEXTURE (3)

//=============================================================================
// 前方宣言
//=============================================================================
class CFade;

//=============================================================================
// タイトルロゴクラス
//=============================================================================
class CTitleLogo :public CScene2D
{
public:
	typedef enum
	{
		LOGOTYPE_NONE = 0,
		LOGOTYPE_SIROHAIKEI, // 白い背景
		LOGOTYPE_TITLE,		 // タイトル
		LOGOTYPE_PRESSENTER, // プレスエンター
		LOGOTYPE_MAX,
	}LOGOTYPE;

	CTitleLogo();  // コンストラク
	~CTitleLogo(); // デストラクタ

	static HRESULT Load(void); // ロード
	static void Unload(void);  // アンロード

	static CTitleLogo *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, LOGOTYPE logoType); // クリエイト

	HRESULT Init(void); // 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理

	void SetTitleLogo(D3DXVECTOR3 pos, D3DXVECTOR3 size, LOGOTYPE logoType) { // タイトルロゴの設定
		m_pos = pos; m_size = size; m_LogoType = logoType;
		SetPosition(pos); SetSize(size);
	}

	void TitleLogo(void); // タイトルロゴの処理
	void PlessEnter(void); // プレスエンターの処理
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_LOGO_TEXTURE]; // テクスチャへのポインタ
	D3DXVECTOR3				  m_pos;	  // 座標
	D3DXVECTOR3				  m_size;	  // 大きさ
	int						  m_nCount;	  // カウント
	int						  m_nAlpha;	  // 透明度
	bool					  m_bUse;	  // 使用可能かの判定
	LOGOTYPE				  m_LogoType; // ロゴのタイプ
};
#endif