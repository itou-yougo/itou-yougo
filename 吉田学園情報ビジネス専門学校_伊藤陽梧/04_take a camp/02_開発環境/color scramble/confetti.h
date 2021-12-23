//=============================================================================
//
// confettiヘッダ [confetti.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _CONFETTI_H_
#define _CONFETTI_H_

//*****************************
//インクルード
//*****************************
#include "scene2d.h"

//*****************************
//クラス定義
//*****************************

// 紙吹雪クラス
class CConfetti : public CScene2d
{
public:
	//============
	// メンバ関数
	//============
	CConfetti();
	~CConfetti();

	static CConfetti *Create(D3DXVECTOR3 pos , D3DXCOLOR col,float fMoveAngle = 0.0f); // クラス生成

	HRESULT Init(void); // 初期化
	void Update(void);  // 更新

private:
	//============
	// メンバ変数
	//============
	int m_nLife;
	float m_fMoveAngle;
	float m_fMoveRate;
	D3DXVECTOR3 m_move;
};

#endif