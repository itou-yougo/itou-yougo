//=============================================================================
//
// 弾の処理 [Bullet.h]
// Author : 佐藤颯紀
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "model.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CPlayer;
class CCollision;
class CPeintCollision;
//=============================================================================
// マクロ定義
//=============================================================================
#define BULLET_MOVE 5		// 弾の移動量
#define MAX_PEINT 5			// 攻撃でぬれる最大マス

//=============================================================================
// クラス宣言
//=============================================================================
class CBullet : public CModel
{
public:
	CBullet();	// コンストラクタ
	~CBullet();	// デストラクタ

	static CBullet * Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nPlayerNum);	// 生成処理

	HRESULT Init(void);		// 初期化処理

	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void CollisionPlayer(void);	// 当たり判定
	void KillCount(void);

	CCollision* GetCollision(void) { return m_pCollision; }
private:
	//=============================================================================
	// メンバ変数宣言
	//=============================================================================
	D3DXVECTOR3 m_move;			// 移動量
	D3DXVECTOR3 m_size;			// 大きさ
	D3DXCOLOR	m_color;		// 色
	int m_nLife;				// ライフ
	float m_fSpeed;				// 速さ
	CCollision * m_pCollision;	// 当たり判定
	CPeintCollision* m_pPeintCollision[MAX_PEINT];	//マス目の当たり判定
	int m_nPlayerNum;			// プレイヤーナンバー
	static D3DXVECTOR3 m_PeintPos[MAX_PEINT];	//塗る用の当たり判定位置
};

#endif // !_BULLET_H_
