//====================================================
//
// tutorialヘッダ [tutorial.h]
// Author : 伊藤陽梧
//
//====================================================

//二重インクルード防止
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//=============================
//インクルード
//=============================
#include "main.h"
#include "scene.h"

//=============================
// 前方宣言
//=============================
class CMap;
class CPolygon;
class CText;

//=============================
//クラス定義
//=============================

//チュートリアルクラス
class CTutorial : public CScene
{
public:
	enum TUTORIALPHASE
	{
		PHASE_PAINT = 0,
		PHASE_OVERPAINT,
		PHASE_ATTACK,
		PHASE_FINALATTACK,
		PHASE_FINISH,
	};

	//============
	// メンバ関数
	//===========
	CTutorial();
	~CTutorial();
	static CTutorial *Create(void); // クラス生成

	HRESULT Init(void); // 初期化
	void Uninit(void);  // 終了
	void Update(void);  // 更新
	void Draw(void);    // 描画

	TUTORIALPHASE GetTutorialPhase(void) { return m_Tutorialphase; }	// チュートリアルの状態の取得
private:
	//============
	// メンバ関数
	//===========
	void CheckTaskClear(const int nCurTaskNum, const int nTargetNum, const int nPlayernum);
	void UpdateText(void);
	void NextPhase(void);
	void StartPlayer(bool bUpdate);
	void Max_Playergauge(void);
	void DummyCreate(void);
	void SetTextWindow(void);

	//============
	// メンバ変数
	//===========
	CMap *m_pMap;										// マップのポインタ
	CPolygon *m_pTextWindow;								// ポリゴンのポインタ
	CText *m_pText;										// テキストのポインタ
	TUTORIALPHASE m_Tutorialphase;						// チュートリアルの状態
	bool m_bTask[MAX_PLAYER];							// プレイヤーごとのタスクを完了したか
	int m_nTextNum;										// テキストの数
	bool m_bNextText;									// 次のテキストに行くかいかないか
	bool m_bTextEnd;									// テキストを表示し終わったか
	int m_nCurTaskNum[MAX_PLAYER];						// 現在のタスクごとの数
	int m_nOldCurTaskNum[MAX_PLAYER];					// 1フレーム前のタスクごとの数
};

#endif