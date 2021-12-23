//=============================================================================
//
// トータルリザルトヘッダー [total_result.h]
// Author : 吉田 悠人
//
//=============================================================================
//二重インクルード防止
#ifndef _TOTAL_MANAGER_H_
#define _TOTAL_MANAGER_H_

//=============================
// インクルード
//=============================
#include "main.h"
#include "scene.h"
#include "game.h"

//=============================
// 前方宣言
//=============================
class CScene2d;
class CScoreKill;
class CPolygon;

//=============================
// クラス定義
//=============================

// マネージャークラス
class CTotalResult : public CScene
{
public:
	//============
	// 状態列挙
	//============

	//============
	// メンバ関数
	//============
	CTotalResult();
	~CTotalResult();
	static CTotalResult *Create(void); //クラス生成
	HRESULT Init(void);		// 初期化
	void	Uninit(void);	// 終了
	void	Update(void);	// 更新
	void	Draw(void);		// 描画

private:
	//============
	// メンバ変数
	//============
	CScene2d * m_pBg;						// 背景ポリゴン
	CScoreKill* m_pScoreKill;	// キルスコア
	D3DXVECTOR3 m_ScorePos[MAX_PLAYER];
	CPolygon * m_pBackGroundPolygon;

};


#endif