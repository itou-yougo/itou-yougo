//=============================================================================
//
// 2Dポリゴンの処理 [scene3d.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "scene.h"

//=============================================================================
// CScene2Dクラス
//=============================================================================
class CScene2D :public CScene
{
public:
	CScene2D(int nPriority = OBJTYPE_NONE);
	~CScene2D();

	static CScene2D *Create(float nPosX, float nPosY);

	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void);	//描画処理

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }		// 位置
	void SetSize(D3DXVECTOR3 size) { m_size = size; }		// サイズ
	void SetColor(D3DXCOLOR color) { m_color = color;}		// カラー
	void SetLifebar(float fMaxHp, float fCur, D3DXCOLOR col);	// HPバーの設定

	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXCOLOR GetColor(void) { return m_color; }

private:
	LPDIRECT3DTEXTURE9		m_pTexture;				// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;				// 頂点バッファへのポインタ
	D3DXVECTOR3				m_pos;					// ポリゴンの位置
	D3DXVECTOR3				m_size;
	D3DXCOLOR				m_color;
};

#endif // !_SCENE2D_H_
