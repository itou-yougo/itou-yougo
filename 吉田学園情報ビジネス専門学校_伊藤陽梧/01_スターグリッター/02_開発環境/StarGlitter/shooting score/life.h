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

	CLife();
	~CLife();

	static CLife *Create(int nLife, LIFETYPE LifeType, OBJTYPE objType);

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	int GetLife(void);

	void Damage();
	void Cure();
	//void Damage(int nDamage) {
	//	m_nLife -= nDamage;
	//}

	void SetLife(int nLife) {
		m_nLife = nLife;
	}

	void SetType(LIFETYPE LifeType, OBJTYPE objType) {
		m_LifeType = LifeType;
		SetObjType(objType);
	}

private:
	CLifepolygon* m_pLifepolygon[MAX_LIFEPOLYGON]; // CLifepolygonのポインタ
	int     m_nLife;							   // 体力
	LIFETYPE m_LifeType;						   // 体力のタイプ
};
#endif