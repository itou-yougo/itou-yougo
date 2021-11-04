//=============================================================================
//
// ライフの処理 [hp.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _HP_H_
#define _HP_H_

//=============================================================================
// 前方宣言
//=============================================================================
class CLifepolygon;

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene.h"

//=============================================================================
// ライフクラス
//=============================================================================
class CLife : public CScene
{
public:
	typedef enum
	{
		LIFE_TYPE_NONE = 0,
		LIFE_TYPE_PLAYER,  // PLAYER1の体力
		LIFE_TYPE_PLAYER2, // PLAYER2の体力
		LIFE_TYPE_MAX,
	}LIFETYPE;

	CLife();  // コンストラク
	~CLife(); // デストラクタ

	static CLife *Create(int nLife, LIFETYPE LifeType, OBJTYPE objType); // クリエイト

	HRESULT Init();    // 初期化処理
	void Uninit(void); // 終了処理
	void Update(void); // 更新処理
	void Draw(void);   // 描画処理

	int GetLife(void); // 体力を返す

	void Damage(); // ダメージの処理
	void Cure(); // 回復の処理
	//void Damage(int nDamage) {
	//	m_nLife -= nDamage;
	//}

	void SetLife(int nLife) { // 体力の設定
		m_nLife = nLife;
	}

	void SetType(LIFETYPE LifeType, OBJTYPE objType) { // 体力の処理
		m_LifeType = LifeType;
		SetObjType(objType);
	}

private:
	CLifepolygon* m_pLifepolygon[MAX_LIFEPOLYGON]; // CLifepolygonのポインタ
	int     m_nLife;							   // 体力
	LIFETYPE m_LifeType;						   // 体力のタイプ
};
#endif