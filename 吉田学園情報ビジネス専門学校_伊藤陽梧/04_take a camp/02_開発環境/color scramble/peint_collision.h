//=============================================================================
//
// 塗り処理 [peint_collision.h]
// Author : 吉田 悠人
//
//=============================================================================
#ifndef _PEINT_COLLISION_
#define _PEINT_COLLISION_
//=============================================================================
// インクルードファイル
//=============================================================================
#include "scene.h"


//=============================================================================
// 前方宣言
//=============================================================================
class CCollision;

//=============================================================================
// クラス宣言
//=============================================================================
class CPeintCollision :public CScene
{
public:
	CPeintCollision();	// コンストラクタ
	~CPeintCollision();	// デストラクタ
	static CPeintCollision * Create(D3DXVECTOR3 pos, int nPlayerNum);	// 生成処理

	HRESULT Init(void);		// 初期化処理
	void	Uninit(void);	// 終了処理
	void	Update(void);	// 更新処理
	void	Draw(void);		// 描画処理
	void	ColorLoad(void);// カラー番号読み込み

	int		GetPlayerNum(void) { return m_nPlayerNum; }//プレイヤーナンバーゲッター
	int		GetColorNumber(void) { return m_nColorNumber; }
	CCollision* GetCollision(void) { return m_pCollision; }
	void	Death();
private:
	//==============1===============================================================
	// メンバ変数宣言
	//=============================================================================
	D3DXVECTOR3 m_pos;				// 位置
	D3DXVECTOR3 m_size;				// サイズ
	CCollision * m_pCollision;		// 当たり判定
	int m_nLife;					// ライフ
	int m_nPlayerNum;				// プレイヤーの番号
	int m_nColorNumber;				// カラー設定
	bool m_bDeath;					// 死亡フラグ
};

#endif