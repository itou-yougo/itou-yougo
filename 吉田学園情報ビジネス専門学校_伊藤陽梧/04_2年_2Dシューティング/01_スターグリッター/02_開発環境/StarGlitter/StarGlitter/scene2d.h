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
	CScene2D(int nPriority = 1);
	virtual~CScene2D();

	static CScene2D *Create();
	void BindTexture(LPDIRECT3DTEXTURE9	Texture);

	virtual HRESULT Init();
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	D3DXVECTOR3 GetPosition(void);
	float GetSizeX(void);
	float GetSizeY(void);

	void UpdateAnimation();
	void UpdateAnimationSelect();
	void UpdateScroll();
	void UpdateTransparency();
	void UpdateColor();

	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }

	void SetSize(float fSizeX, float fSizeY) {
		m_fSizeX = fSizeX; m_fSizeY = fSizeY;
	}

	void SetAnimation(int nCounterAnim, int nPatternAnim, int nTimeAnim) {
		m_nGetCounterAnim = nCounterAnim; m_nGetPatternAnim = nPatternAnim;
		m_nTimeAnim = nTimeAnim; m_nTimeCount = nTimeAnim;
		m_AnimationType = TYPE_ANIMATION;
	}

	void SetAnimationSelect(int nCounterAnim, int nPatternAnim, int nSetPatternAnim, int nTimeAnim) {
		m_nGetCounterAnim = nCounterAnim; m_nGetPatternAnim = nPatternAnim; m_nPatternAnim = nSetPatternAnim;
		m_nTimeAnim = nTimeAnim; m_nTimeCount = nTimeAnim;
		m_AnimationType = TYPE_ANIMATIONSELECT;
	}

	void SetScroll(float nGetScrollX, float nGetScrollY) {
		m_fGetScrollMoveX = nGetScrollX; m_fGetScrollMoveY = nGetScrollY;
		m_AnimationType = TYPE_SCROLL;
	}

	void SetTransparency(bool bUse) {
		m_bTransparencyUse = bUse;
		m_AnimationType = TYPE_TRANSPARENCY;
	}

	void SetColor(int nRed, int nGreen, int nBrue, int nAlpha) {
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
	float					m_fSizeX;		    // ポリゴンの横の大きさ
	float					m_fSizeY;		    // ポリゴンの縦の大きさ
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
