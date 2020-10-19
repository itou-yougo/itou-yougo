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

	CChargeshot();
	~CChargeshot();

	static HRESULT Load(void);
	static void Unload(void);
	static CChargeshot *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, CHARGESHOTTYPE chargeshottype, OBJTYPE objType);
	void SetChargeShot(D3DXVECTOR3 pos, float fSizeX, float fSizeY, CHARGESHOTTYPE chargeshottype, OBJTYPE objType) {
		m_pos = pos; m_fSizeX = fSizeX; m_fSizeY = fSizeY;
		m_chargeshottype = chargeshottype; SetObjType(objType);
	}

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	CGauge* GetGauge(void);
	CCharge* GetCharge(void);
private:
	CGauge *pGauge;							  // ゲージのポインタ
	CCharge *pCharge;						  // チャージのポインタ
	static LPDIRECT3DTEXTURE9 m_pTexture;	  // テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		  // 頂点バッファへのポインタ
	D3DXVECTOR3				m_pos;			  // 球の位置
	float					m_fSizeX;		  // ポリゴンの横の大きさ
	float					m_fSizeY;		  // ポリゴンの縦の大きさ
	CHARGESHOTTYPE			m_chargeshottype; // チャージショットのタイプ
};
#endif