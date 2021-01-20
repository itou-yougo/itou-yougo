//=============================================================================
//
// エフェクトの処理 [effect.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_EFFECT_TEXTURE (2)

//=============================================================================
// エフェクトクラス
//=============================================================================
class CEffect :public CScene2D
{
public:
	typedef enum
	{
		EFFECTTYPE_BULLET = 0,  // 弾のエフェクト
		EFFECTTYPE_CHARGESTATE, // チャージのエフェクト
	}EFFECTTYPE;

	CEffect();  // コンストラク
	~CEffect();	// デストラクタ

	static HRESULT Load(void); // ロード
	static void Unload(void);  // アンロード
	static CEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,
		int nLife, int nRed, int nGreen, int nBrue, int nAlpha, EFFECTTYPE EffectType, OBJTYPE objType); // クリエイト

	HRESULT Init(void); // 初期化処理
	void Uninit(void);  // 終了処理
	void Update(void);  // 更新処理
	void Draw(void);    // 描画処理

	void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 size,
		int nLife, int nRed, int nGreen, int nBrue, int nAlpha, EFFECTTYPE EffectType, OBJTYPE objType) { // エフェクトの設定
		m_pos = pos; m_size = size;
		m_nLife = nLife; m_nRed = nRed; m_nGreen = nGreen;
		m_nBrue = nBrue; m_nAlpha = nAlpha;
		m_EffectType = EffectType;
		SetPosition(pos); SetSize(size);
		SetObjType(objType);
	}

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_EFFECT_TEXTURE]; // テクスチャへのポインタ
	D3DXVECTOR3				  m_pos;	  // 座標
	D3DXVECTOR3				  m_size;	  // 大きさ
	int						  m_nLife;	  // 体力
	int						  m_nRed;	  // 赤
	int						  m_nGreen;	  // 緑
	int						  m_nBrue;	  // 青
	int						  m_nAlpha;	  // 透明度
	EFFECTTYPE m_EffectType;
};
#endif