//=============================================================================
//
// チャージショットの処理 [chargeshot.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _CHARGESHOT_H_
#define _CHARGESHOT_H_

//=============================================================================
// 前方宣言
//=============================================================================
class CGauge;
class CCharge;

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene.h"

//=============================================================================
// チャージショットクラス
//=============================================================================
class CChargeshot : public CScene
{
public:
	typedef enum
	{
		CHARGESHOTTYPE_NONE = 0,
		CHARGESHOTTYPE_PLAYER,  // PLAYER1のチャージショット
		CHARGESHOTTYPE_PLAYER2, // PLAYER2のチャージショット
	}CHARGESHOTTYPE;

	CChargeshot();  // コンストラク
	~CChargeshot();	// デストラクタ

	static HRESULT Load(void); // ロード
	static void Unload(void);  // アンロード

	static CChargeshot *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CHARGESHOTTYPE chargeshottype, OBJTYPE objType); // クリエイト
	void SetChargeShot(D3DXVECTOR3 pos, D3DXVECTOR3 size, CHARGESHOTTYPE chargeshottype, OBJTYPE objType) { // チャージショットの設定
		m_pos = pos; m_size = size;
		m_chargeshottype = chargeshottype; SetObjType(objType);
	}

	HRESULT Init();    // 初期化処理
	void Uninit(void); // 終了処理
	void Update(void); // 更新処理
	void Draw(void);   // 描画処理

	CGauge* GetGauge(void); // ゲージのポインタを返す
	CCharge* GetCharge(void); // チャージのポインタを返す
private:
	CGauge *pGauge;							  // ゲージのポインタ
	CCharge *pCharge;						  // チャージのポインタ
	static LPDIRECT3DTEXTURE9 m_pTexture;	  // テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		  // 頂点バッファへのポインタ
	D3DXVECTOR3				m_pos;			  // 球の位置
	D3DXVECTOR3				m_size;			  // 球の位置
	CHARGESHOTTYPE			m_chargeshottype; // チャージショットのタイプ
};
#endif