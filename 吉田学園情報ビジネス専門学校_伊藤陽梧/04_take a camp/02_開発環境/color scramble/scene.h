//=============================================================================
//
// sceneヘッダ [scene.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _SCENE_H_
#define _SCENE_H_

//インクルード
#include "main.h"

//***********************************
//マクロ定義
//***********************************
#define MAX_SCENE 12800   // ポリゴンの最大数
#define PRIORITY_NUM OBJTYPE_MAX

//=============================
//クラス定義
//=============================

//シーンクラス
class CScene
{
public:
	//============
	// 構造体定義
	//============

	//============
	// 状態列挙
	//============
	// オブジェクトタイプ列挙
	// 更新・描画順
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_BG,            // 背景
		OBJTYPE_TILE,          // タイル
		OBJTYPE_COLOR_TILE,    // 色付きタイル
		OBJTYPE_PLAYER,        // プレイヤー
		OBJTYPE_DUMMY,         // ダミー
		OBJTYPE_BULLET,        // 弾
		OBJTYPE_PEINT,		   // 塗り判定用
		OBJTYPE_ITEM,          // アイテム
		OBJTYPE_MAP,           // マップ
		OBJTYPE_BULDING,       // マップ
		OBJTYPE_EFFECT,        // エフェクト
		OBJTYPE_PARTICLE,      // パーティクル
		OBJTYPE_MOTION,        // モーション
		OBJTYPE_UI_1,          // UI
		OBJTYPE_UI_2,          // UI
        OBJTYPE_EFFECT_2,      // UIより前に出すエフェクト
		OBJTYPE_ACT_RANGE,	   // 行動範囲
		OBJTYPE_COLLISION,     // コリジョン
		OBJTYPE_SYSTEM,        // システム
		OBJTYPE_MAX,           // タイプの最大数
	}OBJTYPE;

	//============
	// メンバ関数
	//============
	CScene(int nPriority = OBJTYPE_NONE);
	virtual ~CScene();
	static void ReleaseAll(void);                   // すべて解放
	static void UpdateAll(void);                    // すべて更新
	static void DrawAll(void);                      // すべて描画
	static int GetNumAll(void) { return m_nIDAll; } // これまで生成されたオブジェクトの数
	 
	void SetPriority(const int  nPriority);   // プライオリティの設定
	int GetType(void) { return m_nPriority; }  // オブジェクトタイプの取得
	int GetID(void) { return m_nNumID; }      // 配列番号の取得

	static CScene*GetTop(int nIndex) { return m_pTop[nIndex]; }  // リスト構造トップの取得
	static CScene*GetCur(int nIndex) { return m_pCur[nIndex]; }  // リスト構造カレントの取得
	CScene*GetNext(void) { return m_pNext; }                     // リスト構造ネクストの取得
	CScene*GetPrev(void) { return m_pPrev; }                     // リスト構造プレビューの取得

	// 純粋仮想関数
	virtual HRESULT Init(void) = 0; // 初期化
	virtual void Uninit(void) = 0;  // 終了
	virtual void Update(void) = 0;  // 更新
	virtual void Draw(void) = 0;    // 描画

	void OutList(void); // リスト構造から自身を消してつなぎなおす
protected:
	void Release(void);      // 解放処理
private:
	

	//============
	// メンバ変数
	//============
	static int m_nIDAll;                   // 生成したポリゴン数
	int     m_nNumID;                      // 生成したポリゴンの配列
	int     m_nPriority;                   // プライオリティ
	bool    m_bReleasFlag;                 // 削除フラグ

	// リスト構造
	static CScene * m_pTop[PRIORITY_NUM];  // 先頭
	static CScene * m_pCur[PRIORITY_NUM];  // 最後
	CScene * m_pNext;                      // 次 
	CScene * m_pPrev;                      // 前
};

#endif