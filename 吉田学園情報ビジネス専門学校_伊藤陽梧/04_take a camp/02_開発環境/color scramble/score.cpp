//===================================================
//
// スコア表示処理 [score.cpp]
//    Author : 吉田 悠人
//
//====================================================

//**********************************
//インクルード
//**********************************
#include "number.h"
#include "chara_select.h"
#include "score.h"
#include "color_tile.h"

//**********************************
//インクルード
//**********************************
#define SCORE_SIZE		(D3DXVECTOR3(40.0f, 30.0f, 0.0f))
#define CREATE_POS_Y	(400.0f)
#define SCORE_SPACE		(SCREEN_WIDTH/4)

//==================================
// コンストラクタ
//==================================
CScore::CScore()
{
	//初期化
	memset(m_apNumber, 0, sizeof(m_apNumber));	// ナンバーのクリア
	memset(m_pos, 0, sizeof(m_pos));			// 位置
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// カラー
	m_nPlayerNum = 0;
}

//==================================
// デストラクタ
//==================================
CScore::~CScore()
{
}

//==================================
// クリエイト
//==================================
CScore * CScore::Create(D3DXVECTOR3 pos, D3DXCOLOR col, int nScore)
{
	// メモリの確保
	CScore *pScorePaint = NULL;
	pScorePaint = new CScore;

	//NULLチェック
	if (pScorePaint != NULL)
	{
		// 位置設定
		pScorePaint->m_pos = pos;
		// カラー設定
		pScorePaint->m_col = col;
		// 初期化処理
		pScorePaint->Init();
		//スコアセット
		pScorePaint->SetPaintScore(nScore);
		// オブジェクトタイプの設定
		pScorePaint->SetPriority(OBJTYPE_UI_2);
	}
	return pScorePaint;
}

//==================================
// 初期化処理
//==================================
HRESULT CScore::Init(void)
{
	//数値生成
	for (int nCntDigit = 0; nCntDigit < MAX_SCORE_DIGIT; nCntDigit++)
	{
		m_apNumber[nCntDigit] = CNumber::Create(0,
			D3DXVECTOR3((float)(m_pos.x - (nCntDigit-1) * (SCORE_SIZE.x)), m_pos.y, 0.0f),
			SCORE_SIZE,
			m_col);
	}

	return S_OK;
}

//==================================
// 終了処理
//==================================
void CScore::Uninit(void)
{
	for (int nCntDigit = 0; nCntDigit < MAX_SCORE_DIGIT; nCntDigit++)
	{
		if (m_apNumber[nCntDigit] != NULL)
		{
			m_apNumber[nCntDigit]->Uninit();
			delete m_apNumber[nCntDigit];
			m_apNumber[nCntDigit] = NULL;
		}
	}

	// 開放処理
	Release();
}

//==================================
// 更新処理
//==================================
void CScore::Update(void)
{
	for (int nCntDigit = 0; nCntDigit < MAX_SCORE_DIGIT; nCntDigit++)
	{
		//NULLチェック
		if (m_apNumber[nCntDigit] != NULL)
		{
			m_apNumber[nCntDigit]->Update();

		}
	}
}

//==================================
// 描画処理
//==================================
void CScore::Draw(void)
{
	for (int nCntDigit = 0; nCntDigit < MAX_SCORE_DIGIT; nCntDigit++)
	{
		//NULLチェック
		if (m_apNumber[nCntDigit] != NULL)
		{
			m_apNumber[nCntDigit]->Draw();
		}
	}
}

//=============================
// スコア計算処理
//=============================
void CScore::SetPaintScore(int nScore)
{
	int nInteger = 0;//計算用変数

	for (int nCntDigit = 0; nCntDigit < MAX_SCORE_DIGIT; nCntDigit++)
	{
		nInteger = int(nScore / pow(10, nCntDigit + 1)); //1の位以下を切り捨てる
		nInteger = int(nInteger * pow(10, nCntDigit + 1));
		m_apNumber[nCntDigit]->SetNumber(int((nScore - nInteger) / pow(10, nCntDigit)));
	}
}
