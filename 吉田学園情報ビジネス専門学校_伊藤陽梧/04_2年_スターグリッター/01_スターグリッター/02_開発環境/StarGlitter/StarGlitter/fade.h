#pragma once
//=============================================================================
//
// フェードの処理 [fade.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene.h"
#include "manager.h"

//=============================================================================
// フェードクラス
//=============================================================================
class CFade :public CScene
{
public:
	typedef enum
	{
		FADE_NOME = 0,  //何もない状態
		FADE_IN,      //フェードイン処理
		FADE_OUT,     //フェードアウト処理
		FADE_MAX
	}FADE;

	CFade();  // コンストラク
	~CFade(); // デストラクタ

	static CFade *Create(void); // クリエイト

	HRESULT Init(void); // 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理

	void SetFade(CManager::MODE modeNext); // フェードの設定
	void SetFadeType(FADE fade) { // タイプの設定
		m_fade = fade; SetObjType(OBJTYPE_FADE);
	}

	FADE GetFade(void); // フェードの状態の受け取り

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;  //頂点バッファへのポインタ
	FADE					m_fade;		 //フェード状態
	CManager::MODE			m_modeNext;	 //次の画面(モード)
	D3DXCOLOR				m_colorFade; //フェード色
};

#endif
