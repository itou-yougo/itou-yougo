//=============================================================================
//
// dynamic_tectureヘッダ [dynamic_tecture.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _DYNAMIC_TEXTURE_H_
#define _DYNAMIC_TEXTURE_H_

//*****************************
// インクルード
//*****************************
#include "main.h"

//*****************************
// クラス定義
//*****************************

//動的テクスチャクラス
class CDynamicTexture
{
public:
	//============
	// メンバ関数
	//============
	CDynamicTexture();
	~CDynamicTexture();

	// static
	static CDynamicTexture *Create(D3DXVECTOR2 size);  // クラス生成

	virtual HRESULT Init(D3DXVECTOR2 size);   // 初期化
	virtual void Uninit(void);	  // 終了
	void Begin(void);     // 開始
	void End(void);       // 終了

	LPDIRECT3DTEXTURE9 GetTexture(void) { return m_pTexture; } // テクスチャの取得処理

private:
	//============
	// メンバ変数
	//============

	LPDIRECT3DTEXTURE9		m_pTexture;		//テクスチャ
	LPDIRECT3DSURFACE9		m_pTexz;		//テクスチャの深度バッファ
	LPDIRECT3DSURFACE9		m_pTexSurface;	//テクスチャへアクセスする為のインターフェース
	LPDIRECT3DSURFACE9		m_pBackz;		//バックバッファの深度バッファ
	LPDIRECT3DSURFACE9		m_pBackSurface;	//バックバッファへアクセスする為の
	D3DXMATRIX	m_proj;		// 射影行列
	D3DXMATRIX	m_view;		// 行列
	D3DVIEWPORT9 m_saveViewport; // 保存用ビューポート
	D3DXVECTOR2 m_size;     // サイズ

};

#endif