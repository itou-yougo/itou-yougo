//=============================================================================
//
// アイテムの処理 [Item.h]
// Author : 西潟栞那汰
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "model.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CCollision;
class CPlayer;
class CShadow;

//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// クラス宣言
//=============================================================================
class CItem : public CModel
{
public:
	//アイテム効果
	typedef enum
	{
		ITEM_EFFECT_DASH = 0,	//加速
		ITEM_EFFECT_REVERSE,	//操作逆転
		ITEM_EFFECT_MAX
	}ITEM_EFFECT;

	CItem();	// コンストラクタ
	~CItem();	// デストラクタ

	static CItem * Create(D3DXVECTOR3 pos, ITEM_EFFECT effect);	// 生成処理

	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void MoveUpdate(void);	//移動更新
	void RotUpdate(void);	//角度更新

	void CollisionItem(void);		// 当たり判定
	virtual void ItemEffect(CPlayer*pPlayer);	// アイテム効果

	void SetItemEffect(ITEM_EFFECT ItemState) { m_ItemEffect = ItemState; }
	ITEM_EFFECT GetItemState(void) { return m_ItemEffect; }
private:
	//=============================================================================
	// メンバ変数宣言
	//=============================================================================
	D3DXVECTOR3 m_size;		//大きさ
	D3DXVECTOR3 m_rot;		//角度
	D3DXVECTOR3 m_move;		//移動

	ITEM_EFFECT m_ItemEffect;	//アイテムステータス
	CCollision *m_pCollision;	//コリジョンのポインタ
	CPlayer *m_pPlayer;			//プレイヤーのポインタ
	CShadow *m_pShadow;			//影のポインタ
	int m_nPlayerNum;			//プレイヤーナンバー
	int m_nItemCnt;				//取得後のタイマー

	bool m_bUp;				//上限判定
	bool m_bGet;			//取得フラグ
	bool m_bDeath;			//死亡フラグ
};

#endif // !_ITEM_H_
