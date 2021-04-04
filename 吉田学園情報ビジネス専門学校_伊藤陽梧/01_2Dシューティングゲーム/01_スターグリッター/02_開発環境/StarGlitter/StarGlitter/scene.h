//=============================================================================
//
// ポリゴンの描画の処理 [scene.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include"main.h"

//=============================================================================
// オブジェクトクラス
//=============================================================================
class CScene
{
public:
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_BG,				// 背景
		OBJTYPE_SCENE,			// シーン
		OBJTYPE_BOSSATTACK,		// ボスアタック
		OBJTYPE_EXPLOSION,		// 爆発
		OBJTYPE_LIFE,			// 体力
		OBJTYPE_GAUGE,			// ゲージ
		OBJTYPE_EFFECT,			// エフェクト
		OBJTYPE_BULLET,			// 弾
		OBJTYPE_PLAYER,			// プレイヤー
		OBJTYPE_ENEMY,			// 敵
		OBJTYPE_ENEMYEXPLOSION, // 敵の爆発
		OBJTYPE_EXTRAATTACK,	// エクストラアタック
		OBJTYPE_OJAMA,			// おじゃま
		OBJTYPE_TEXT,			// テキスト
		OBJTYPE_GATTYANN,		// ガッチャン
		OBJTYPE_FADE,			// フェード
		OBJTYPE_MAX,
	}OBJTYPE;

	CScene(int nPriority = 2); // コンストラク
	virtual ~CScene();		   // デストラクタ

	virtual HRESULT Init() = 0;    // 初期化処理
	virtual void Uninit(void) = 0; // 終了処理
	virtual void Update(void) = 0; // 更新処理
	virtual void Draw(void) = 0;   // 描画処理

	static void UpdateAll(void);  // すべての更新処理
	static void DrawAll(void);	  // すべての描画処理
	static void ReleaseAll(void); // すべてのフラグ建設

	static void NotFadeReleaseAll(void); // フェード以外のフラグ建設



	static void SetPause(bool bPause){ // ポーズの設定
		m_bPause = bPause;
	}
	static bool GetPause(void); // ポーズの状態を返す

	void ConnectionList(void); // データのつなぎなおし

	void SetObjType(OBJTYPE objType) { // オブジェタイプの設定
		m_objType = objType;
	};

	OBJTYPE GetObjType(void); // オブジェタイプを返す
	static CScene *GetSceneTop(int nPriority) { return m_pTop[nPriority]; } // シーンのデータを返す
	CScene * GetSceneNext(void) { return m_pNext; } // シーンのネクストのデータを返す
protected:
	void Release(void); // フラグ建設

private:
	static int m_nNumAll;				// オブジェクトの総数
	static bool m_bPause;				// ポーズの状態
	static int m_nNext;					// 次へ行かせるカウント
	int		m_nPriority;				// 描画の優先順位数
	bool	m_bDeath;					// オブジェクトが死んだときのフラグ
	OBJTYPE m_objType;					// オブジェクトの種類

	static CScene *m_pTop[OBJTYPE_MAX]; // 先頭のオブジェクトへのポインタ
	static CScene *m_pCur[OBJTYPE_MAX]; // 現在のオブジェクトへのポインタ
	CScene *m_pPrev;					// 前のオブジェクトへのポインタ
	CScene *m_pNext;					// 次のオブジェクトへのポインタ
};
#endif
