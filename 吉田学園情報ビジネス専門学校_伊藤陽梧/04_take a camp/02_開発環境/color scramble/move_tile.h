//=============================================================================
//
// 動く床のヘッダー [move_tile.h]
// Author : 吉田 悠人
//
//=============================================================================

//二重インクルード防止
#ifndef _MOVE_TILE_H_
#define _MOVE_TILE_H_

//*****************************
// インクルード
//*****************************
#include "tile.h"
#include "map.h"

//*****************************
//前方宣言
//*****************************
class CModel;

//*****************************
//マクロ定義
//*****************************

//*****************************
// クラス定義
//*****************************
class CMoveTile : public CTile
{
public:
	// ステート
	typedef enum
	{
		MOVE_STATE_NORMAL = 0,	//通常状態
		MOVE_STATE_MOVE,		//移動状態
		MOVE_STATE_STOP,		//停止状態
	}MOVE_STATE;

	//メンバ関数
	CMoveTile();
	~CMoveTile();

	HRESULT Init(void);
	void Update(void);

	//変数の取得設定
	
	// ステート
	void SetState(MOVE_STATE state) { m_MoveState = state; }
	MOVE_STATE GetState(void) { return m_MoveState; }
	// 移動量
	void SetMove(D3DXVECTOR3 move) { m_Move = move; }
	D3DXVECTOR3 GetMove(void) { return m_Move; }
	//移動方向
	bool GetReversal(void) { return m_bReversal; }
	void SetReversal(bool Reversal) { m_bReversal = Reversal; }
	virtual void MoveRot(bool bReversal) = 0;
	virtual void TileCheck(void) = 0;
	void HitTile(void);						// 他のタイルとの当たり判定

private:
	void HitPlayerAction(CPlayer*pPlayer);	// プレイヤーが乗っているか
	void HitPlayerActionRelease(void);		// プレイヤーが降りたか

	void Move(void);						// 移動処理

	// メンバ変数
	bool			m_bStep;		// 載っているフラグ
	MOVE_STATE		m_MoveState;	// タイルのステート
	D3DXVECTOR3		m_Move;			// 移動量
	int				m_nMoveCount;	// 移動カウント
	bool			m_bReversal;	// 反転フラグ(trueなら-)
};

#endif