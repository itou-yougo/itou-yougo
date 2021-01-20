//=============================================================================
//
// ポリゴンの描画の処理 [scene2d.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include"main.h"
#include"scene.h"

//=============================================================================
// オブジェクトクラス
//=============================================================================
class CScene2D :public CScene
{
public:
	CScene2D(int nPriority = 1); // コンストラク
	virtual~CScene2D();			 // デストラクタ

	static CScene2D *Create(); // クリエイト
	void BindTexture(LPDIRECT3DTEXTURE9	Texture); // テクスチャのバインド

	virtual HRESULT Init();    // 初期化処理
	virtual void Uninit(void); // 終了処理
	virtual void Update(void); // 更新処理
	virtual void Draw(void);   // 描画処理

	D3DXVECTOR3 GetPosition(void); // 座標を返す
	D3DXVECTOR3 GetSize(void);	   // サイズを返す

	void UpdateAnimation(); // アニメーションの処理
	void UpdateAnimationSelect(); // 任意で変えられるアニメーションの処理
	void UpdateScroll(); // スクロールの処理
	void UpdateTransparency(); // 透明化の処理
	void UpdateColor(); // 色の処理

	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }

	void SetSize(D3DXVECTOR3 size) { m_size = size; }

	void SetAnimation(int nCounterAnim, int nPatternAnim, int nTimeAnim) { // アニメーションの設定
		m_nGetCounterAnim = nCounterAnim; m_nGetPatternAnim = nPatternAnim;
		m_nTimeAnim = nTimeAnim; m_nTimeCount = nTimeAnim;
		m_AnimationType = TYPE_ANIMATION;
	}

	void SetAnimationSelect(int nCounterAnim, int nPatternAnim, int nSetPatternAnim, int nTimeAnim) { // 任意で変えられるアニメーションの設定
		m_nGetCounterAnim = nCounterAnim; m_nGetPatternAnim = nPatternAnim; m_nPatternAnim = nSetPatternAnim;
		m_nTimeAnim = nTimeAnim; m_nTimeCount = nTimeAnim;
		m_AnimationType = TYPE_ANIMATIONSELECT;
	}

	void SetScroll(float nGetScrollX, float nGetScrollY) { // スクロールの設定
		m_fGetScrollMoveX = nGetScrollX; m_fGetScrollMoveY = nGetScrollY;
		m_AnimationType = TYPE_SCROLL;
	}

	void SetTransparency(bool bUse) { // 透明化の設定
		m_bTransparencyUse = bUse;
		m_AnimationType = TYPE_TRANSPARENCY;
	}

	void SetColor(int nRed, int nGreen, int nBrue, int nAlpha) { // 色の設定
		m_nRed = nRed; m_nGreen = nGreen;
		m_nBrue = nBrue; m_nAlpha = nAlpha;
		m_AnimationType = TYPE_COLOR;
	}

private:
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_ANIMATION,		  // アニメーション
		TYPE_ANIMATIONSELECT, // 任意で変えられるアニメーション
		TYPE_SCROLL,		  // ずらしていくアニメーション
		TYPE_TRANSPARENCY,	  // 透明にさせるのと戻すのを繰り返す
		TYPE_COLOR,			  // 色を設定できる
		TYPE_MAX,
	}ANIMATIONTYPE;

	LPDIRECT3DTEXTURE9		m_pTexture;		    // テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		    // 頂点バッファへのポインタ
	D3DXVECTOR3				m_pos;			    // ポリゴンの位置
	D3DXVECTOR3				m_size;			    // ポリゴンの位置
	float					m_fScrollX;		    // スクロールの横の移動
	float					m_fScrollY;		    // スクロールの縦の移動
	float					m_fGetScrollMoveX;  // スクロールの横の速さの受け取り
	float					m_fGetScrollMoveY;  // スクロールの縦の速さの受け取り
	float					m_fExtendX;		    // テクスチャを横に伸ばす
	float					m_fExtendY;		    // テクスチャを縦に伸ばす
	int						m_nCounterAnim;	    // アニメーションのカウント
	int						m_nPatternAnim;     // アニメーションのパターン
	int						m_nGetCounterAnim;  // アニメーションのカウントの受け取り
	int						m_nGetPatternAnim;  // アニメーションのパターンの受け取り
	int						m_nTimeAnim;	    // アニメーションの時間
	int						m_nTimeCount;	    // アニメーションの時間のカウント
	int						m_nRed;			    // 赤
	int						m_nGreen;		    // 緑
	int						m_nBrue;		    // 青
	int						m_nAlpha;		    // 透明度
	bool					m_bTransparency;    // 透明にするカウント
	bool					m_bTransparencyUse; // 透明にするかどうか


	ANIMATIONTYPE m_AnimationType;
};
#endif
