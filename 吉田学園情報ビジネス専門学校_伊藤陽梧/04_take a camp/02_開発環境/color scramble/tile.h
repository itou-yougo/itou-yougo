//=============================================================================
//
// tileヘッダ [tile.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _TILE_H_
#define _TILE_H_

//*****************************
// インクルード
//*****************************
#include "main.h"
#include "model.h"
#include "color_manager.h"

//*****************************
//前方宣言
//*****************************
class CCollision;
class CScene3d;
class CBullet;
class CPlayer;
class CPeintCollision;
class CAttackArea;

//*****************************
//マクロ定義
//*****************************
#define TILE_ONE_SIDE		(20.0f)			// タイルのサイズ*一辺
#define TILE_SIZE_Y			(TILE_ONE_SIDE/2)
#define TILE_SIZE			(D3DXVECTOR3(TILE_ONE_SIDE,TILE_SIZE_Y,TILE_ONE_SIDE))  // タイルのサイズ
#define MAX_TILE_COLOR_NUM	(16)
#define TILE_DEFAULT_COLOR	(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))
#define TILE_POS_Y			(-TILE_SIZE_Y/2)

//*****************************
// クラス定義
//*****************************

// タイルクラス
class CTile : public CModel
{
public:

	// 関数ポインタ
	typedef void(*CTile::SENTENCE_FUNC)(D3DXVECTOR3, D3DXCOLOR);

	//メンバ関数
	CTile();
	~CTile();

	static void Create(D3DXVECTOR3 pos, D3DXCOLOR col = TILE_DEFAULT_COLOR);
	static CTile*GetHitTile(D3DXVECTOR3 pos);

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	//セット・取得
	// 色
	void SetColor(D3DXCOLOR col) { m_color = col; }
	D3DXCOLOR GetColor(void) { return m_color; }
	// Y座標の目標値
	void SetDistPosY(float fDistY) { m_fDistPosY = fDistY; }
	float GetDistPosY(void) { return m_fDistPosY; }
	// Y座標の係数
	void SetDistPosYRate(float fDistYRate) { m_fDistPosYRate = fDistYRate; }
	float GetDistPosYRate(void) { return m_fDistPosYRate; }
	// コリジョンの取得
	CCollision*GetCollision(void) { return m_pCollison; }
	static void CreateSentence0() { return ; }
	// ヒットフラグ
	bool GetHitPlayerFlag(void) { return m_bHitPlayer; }
	bool GetHitBulletFlag(void) { return m_bHitBullet; }
	// タイルリストの取得
	static std::vector<CTile*>GetTileList(void) { return m_aTileList; }
	// タイルリストのクリア
	static void ResetTileList(void) { m_aTileList.clear(); }
	// タイルを使えるかのフラグ取得
	void SetRide(bool bRide) { m_bRide = bRide; }
	bool GetRide(void) { return m_bRide; }

private:
	void DrawModel(void);
	void SetShaderVariable(LPD3DXEFFECT pEffect, CResourceModel::Model * pModelData); // シェーダに値を送る

	bool CollisionPlayer(void);								// プレイヤーとの当たり判定
	virtual void HitPlayerAction(CPlayer * pPlayer);        // 弾と当たったときのアクション*プレス
	virtual void HitPlayerActionTrigger(CPlayer * pPlayer); // 弾と当たったときのアクション*トリガー
	virtual void HitPlayerActionRelease(void); // 弾と当たったときのアクション*リリース


	bool CollisionBullet(void);								// 弾との当たり判定
	virtual void HitBulletAction(CBullet * pBullet);		// 弾と当たったときのアクション
	bool CollisionPeint(void);								// 塗り判定に当たった時
	virtual void HItPeint(CPeintCollision * pPeint);		// 塗り判定と当たった時のアクション

	// メンバ変数
	static std::vector<CTile*> m_aTileList;
	D3DXCOLOR m_color;			// カラー
	CCollision * m_pCollison;	// 当たり判定
	float m_fDistPosY;			// 座標Yの目標値
	float m_fDistPosYRate;		// 座標Yの変更時の係数
	bool m_bHitOld;				// 一個前のフレームで当たっていたか保存するよう
	bool m_bHitPlayer;			// プレイヤーが当たっているフラグ
	bool m_bHitBullet;			// 弾が当たっているフラグ
	bool m_bRide;				// 乗れかのフラグ
};



#endif