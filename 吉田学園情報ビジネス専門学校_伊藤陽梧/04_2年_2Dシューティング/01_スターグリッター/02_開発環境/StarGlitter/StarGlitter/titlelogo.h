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

	CTitleLogo();
	~CTitleLogo();

	static HRESULT Load(void);
	static void Unload(void);
	static CTitleLogo *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, LOGOTYPE logoType);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetText(D3DXVECTOR3 pos, float fSizeX, float fSizeY, LOGOTYPE logoType) {
		m_pos = pos; m_fSizeX = fSizeX; m_fSizeY = fSizeY; m_LogoType = logoType;
		SetPosition(pos); SetSize(fSizeX, fSizeY);
	}

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_LOGO_TEXTURE]; // テクスチャへのポインタ
	D3DXVECTOR3				  m_pos;	  // 座標
	float					  m_fSizeX;   // 横の大きさ
	float					  m_fSizeY;   // 縦の大きさ
	int						  m_nCount;	  // カウント
	int						  m_nAlpha;	  // 透明度
	bool					  m_bUse;	  // 使用可能かの判定
	LOGOTYPE				  m_LogoType; // ロゴのタイプ
};
#endif