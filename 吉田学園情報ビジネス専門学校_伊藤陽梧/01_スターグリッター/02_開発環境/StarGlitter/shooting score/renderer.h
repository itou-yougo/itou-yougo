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
	CRenderer();
	~CRenderer();

	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetNumFPS(int nCountFPS) { m_nCountFPS = nCountFPS; }

	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }

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