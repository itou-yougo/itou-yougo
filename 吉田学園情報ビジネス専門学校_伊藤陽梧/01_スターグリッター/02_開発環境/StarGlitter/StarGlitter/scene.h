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
		OBJTYPE_PLAYER,			// プレイヤー1
		OBJTYPE_PLAYER2,		// プレイヤー2
		OBJTYPE_ENEMY,			// 敵
		OBJTYPE_ENEMYEXPLOSION, // 敵の爆発
		OBJTYPE_EXTRAATTACK,	// エクストラアタック
		OBJTYPE_OJAMA,			// おじゃま
		OBJTYPE_OJAMA2,			// おじゃま2
		OBJTYPE_TEXT,			// テキスト
		OBJTYPE_GATTYANN,		// ガッチャン
		OBJTYPE_FADE,			// フェード
		OBJTYPE_MAX,
	}OBJTYPE;

	CScene(int nPriority = 2);
	virtual ~CScene();

	virtual HRESULT Init() = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static void UpdateAll(void);
	static void DrawAll(void);
	static void ReleaseAll(void);

	static void NotFadeReleaseAll(void);

	void SetObjType(OBJTYPE objType) {
		m_objType = objType;
	};

	static void SetPause(bool bPause){
		m_bPause = bPause;
	}

	static bool GetPause(void);

	OBJTYPE GetObjType(void);
	static CScene *GetScene(int nPriority, int nCount);
protected:
	void Release(void);

private:
	static CScene *m_apScene[MAX_DRAWORDER][MAX_POLYGON]; //シーンクラスのポインタ
	static int m_nNumAll; // 総数
	static bool m_bPause; // ポーズ状態
	int	    m_nID;		  // オブジェクトのID
	int	    m_nPriority;  // 描画の番号
	OBJTYPE m_objType;	  // オブジェクトの種類
};
#endif
