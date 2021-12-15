//=============================================================================
//
// 塗りスコア表示処理 [score.h]
// Author : 吉田 悠人
//
//=============================================================================

//二重インクルード防止
#ifndef _SCORE_H_
#define _SCORE_H_

//*****************************
//インクルード
//*****************************
#include "main.h"
#include "scene.h"
#include "game.h"

//*****************************
//前方宣言
//*****************************
class CNumber;

//*****************************
//マクロ定義
//*****************************
#define MAX_SCORE_DIGIT (3)  // スコアの最大桁数

//*****************************
//クラス定義
//*****************************

//スコアクラス
class CScore : public CScene
{
public:
	//============
	// メンバ関数
	//============
	CScore();
	~CScore();

	static CScore *Create(D3DXVECTOR3 pos, D3DXCOLOR col, int nScore); // クラス生成

	HRESULT Init(void);		// 初期化
	void	Uninit(void);	// 終了
	void	Update(void);	// 更新
	void	Draw(void);		// 描画
	void	SetPaintScore(int nScore);	// スコア

private:
	//============
	// メンバ変数
	//============
	CNumber* m_apNumber[MAX_SCORE_DIGIT];	// ナンバーポリゴン
	int			m_nPaintScore;					// スコア
	D3DXVECTOR3 m_pos;							// 位置
	D3DXCOLOR	m_col;							// カラー
	int			m_nPlayerNum;					// プレイヤー人数取得用変数
};

#endif