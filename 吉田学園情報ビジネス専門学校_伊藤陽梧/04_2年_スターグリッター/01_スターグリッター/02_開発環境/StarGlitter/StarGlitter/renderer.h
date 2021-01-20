//=============================================================================
//
// レンダラーの処理 [renderer.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include"main.h"

//=============================================================================
// レンダリングクラス
//=============================================================================
class CRenderer
{
public:
	CRenderer();  // コンストラク
	~CRenderer(); // デストラクタ

	HRESULT Init(HWND hWnd, bool bWindow); // 初期化処理
	void Uninit(void);					   // 終了処理
	void Update(void);					   // 更新処理
	void Draw(void);					   // 描画処理
	void SetNumFPS(int nCountFPS) { m_nCountFPS = nCountFPS; } // FPSの設定

	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; } // デバイスを返す

private:
	void DrawFPS(void);
	LPDIRECT3D9				m_pD3D;			// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9		m_pD3DDevice;	// Deviceオブジェクト(描画に必要)
	int						m_nCountFPS;	// FPSの値
#ifdef _DEBUG
	LPD3DXFONT				m_pFont;			// フォントへのポインタ
#endif

};
#endif