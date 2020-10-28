//=============================================================================
//
// ポリゴンの描画の処理 [player2.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _PLAYER2_H_
#define _PLAYER2_H_


//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CSound;
class CLife;
class CChargeshot;
class CBomb;
class CEffect;

//=============================================================================
// マクロ定義
//=============================================================================
#define PLAYER_SPEED (10.0f)			 // 自機の速さ
#define PLAYER2_MOVABLE_RANGE_S (915.0f)  // 自機の移動できる範囲(短いほう)
#define PLAYER2_MOVABLE_RANGE_L (1658.0f) // 自機の移動できる範囲(長いほう)
#define PLAYER2_BOMB_MAX (2)				// 自機のボムの最大数

//=============================================================================
// プレイヤークラス
//=============================================================================
class CPlayer2 :public CScene2D
{
public:
	typedef enum
	{
		PLAYERSTATE_NONE = 0,
		PLAYERSTATE_NOMAL,  // ノーマル状態
		PLAYERSTATE_DAMAGE, // ダメージを受けた状態
		PLAYERSTATE_LOSE,	// 負けた時の状態
		PLAYERSTATE_MAX,
	}PLAYERSTATE;

	CPlayer2();
	~CPlayer2();

	static HRESULT Load(void);
	static void Unload(void);
	static CPlayer2 *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fSizeX, float fSizeY, int nLife, OBJTYPE objType);

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPlayer2(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fSizeX, float fSizeY, int nLife, OBJTYPE objType) {
		SetPosition(pos); m_pos = pos; m_move = move;
		m_fSizeX = fSizeX; m_fSizeY = fSizeY;
		m_nLife = nLife; SetObjType(objType);
	}

	void PlayerDamage2(int nDamage);
	void PlayerAddLife2(int nLife);
	CChargeshot* GetChargeShot(void);
	PLAYERSTATE GetPlayer2State(void);
private:
	CLife*					  m_pLife;					 // 体力のポインタ
	CChargeshot*			  m_pChargeShot;			 // チャージショットのポインタ
	CBomb*					  m_pBomb[PLAYER2_BOMB_MAX]; // ボムのポインタ
	CEffect*				  m_pEffect;				 // エフェクトのポインタ
	static LPDIRECT3DTEXTURE9 m_pTexture;				 // テクスチャへのポインタ
	static int				  m_nDamage;				 // 受けたダメージの値
	D3DXVECTOR3				  m_pos;					 // 位置
	D3DXVECTOR3				  m_Getpos;					 // 敵の位置
	D3DXVECTOR3				  m_move;					 // 速さ
	float					  m_fSizeX;					 // 横の大きさ
	float					  m_fSizeY;					 // 縦の大きさ
	float					  m_fGetSizeX;				 // 受け取った横の大きさ
	float					  m_fGetSizeY;				 // 受け取った縦の大きさ
	float					  m_fAngle;					 // 角度
	int						  m_nLife;					 // 自機の体力
	int						  m_nBulletShotCount; 		 // 弾を撃つ間隔
	int						  m_nHitCount;		 		 // 次に敵に当たるカウント
	int						  m_nExtraAttackCount;		 // エクストラアタックのカウント
	int						  m_nPressTime;				 // ボタンを押す時間
	bool					  m_bExtraAttack;			 // エクストラアタックをするフラグ
	bool					  m_bEffectCreate;			 // エフェクトを出すフラグ
	PLAYERSTATE				  m_PlayerState;			 // プレイヤーの状態
};
#endif