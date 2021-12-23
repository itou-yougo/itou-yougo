//=============================================================================
//
// dummyヘッダ [dummy.h]
// Author : 伊藤陽梧
//
//=============================================================================

//二重インクルード防止
#ifndef _DUMMY_H_
#define _DUMMY_H_

//=============================
// インクルード
//=============================
#include "main.h"
#include "model.h"

//=============================
// 前方宣言
//=============================
class CCollision;

//=============================
// マクロ定義
//=============================

//=============================
// クラス定義
//=============================

// プレイヤークラス
class CDummy : public CModel
{
public:
	//*****************************
	// 列挙
	//*****************************

	// ステート
	typedef enum
	{
		DUMMY_STATE_NORMAL = 0,	//通常状態
		DUMMY_STATE_DEATH			//死亡状態
	}DUMMY_STATE;


	//============
	// メンバ関数
	//===========
	CDummy();
	~CDummy();
	static CDummy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Death(void);		// 死亡処理関数

	//*****************************
	//セッター・ゲッター
	//*****************************
	// カラー番号取得
	int GetColorNumber(void) { return m_nColor; }

	// プレイヤー状態
	void SetState(DUMMY_STATE PlayerState) { m_DummyState = PlayerState; }
	DUMMY_STATE GetState(void) { return m_DummyState; }

	// 当たり判定取得
	CCollision * GetCollision(void) { return  m_pCollision; }
private:
	void Respawn(void);			// リスポーン処理

	//*****************************
	// メンバ変数
	//*****************************
	DUMMY_STATE m_DummyState;	// プレイヤーステータス
	D3DXCOLOR m_color;			// 色
	int m_nColor;				// 色ナンバー
	int	m_nRespawnCount;		// リスポーンまでのカウント
	D3DXVECTOR3  m_RespawnPos;	// リスポーン位置
	CCollision * m_pCollision;	// 当たり判定
};

#endif