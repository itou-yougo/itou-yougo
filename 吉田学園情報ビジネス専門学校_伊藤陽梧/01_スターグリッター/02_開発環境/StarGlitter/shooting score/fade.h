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
	CFade();
	~CFade();

	static CFade *Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetFade(CManager::MODE modeNext);
	void SetFadeType(FADE fade) {
		m_fade = fade; SetObjType(OBJTYPE_FADE);
	}

	FADE GetFade(void);

private:
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff; //頂点バッファへのポインタ
	FADE m_fade;					//フェード状態
	CManager::MODE m_modeNext;   //次の画面(モード)
	D3DXCOLOR m_colorFade;          //フェード色
};

#endif
