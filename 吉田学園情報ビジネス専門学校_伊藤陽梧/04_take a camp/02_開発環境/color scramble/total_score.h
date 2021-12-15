//=============================================================================
//
// トータルスコア表示処理 [total_score.h]
// Author : 吉田 悠人
//
//=============================================================================

//二重インクルード防止
#ifndef _TOTAL_SCORE_H_
#define _TOTAL_SCORE_H_

//*****************************
//インクルード
//*****************************
#include "main.h"
#include "scene.h"
#include "game.h"
//*****************************
// 前方宣言
//*****************************
class CScene2d;

//*****************************
//クラス定義
//*****************************
//スコアクラス
class CTotalScore : public CScene
{
public:
	//============
	// メンバ関数
	//============
	CTotalScore();
	~CTotalScore();

	static CTotalScore *Create(void); // クラス生成

	HRESULT Init(void);		// 初期化
	void	Uninit(void);	// 終了
	void	Update(void);	// 更新
	void	Draw(void);		// 描画

private:
	//============
	// メンバ変数
	//============
	CScene2d* m_pBg;	// 背景用ポインタ
	CScene2d* m_pKillUi;// キルUI用ポインタ
	CScene2d* m_pTileUI;// タイルUI用ポインタ
};

#endif