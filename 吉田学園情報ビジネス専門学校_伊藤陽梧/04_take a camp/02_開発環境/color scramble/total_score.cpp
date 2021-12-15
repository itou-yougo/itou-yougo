//===================================================
//
// 塗りスコア表示処理 [score_paint.cpp]
//    Author : 吉田 悠人
//
//====================================================

//**********************************
//インクルード
//**********************************
#include "total_score.h"
#include "color_manager.h"
#include "chara_select.h"
#include "score.h"
#include "color_tile.h"
#include "kill_count.h"
#include "scene2d.h"
#include "resource_texture.h"
#include "character_polygon.h"

//**********************************
//インクルード
//**********************************
#define PAINT_POS_Y		(500.0f)
#define KILL_POS_Y		(600.0f)
#define SCORE_SPACE		(SCREEN_WIDTH/4)
#define TOTAL_BG_SIZE	(D3DXVECTOR3(320.0f,650.0f,0.0f))
#define CHARACTER_POLYGON_POS_Y 320.0f
//==================================
// コンストラクタ
//==================================
CTotalScore::CTotalScore()
{
	m_pBg		= NULL;
	m_pKillUi	= NULL;
	m_pTileUI	= NULL;
}

//==================================
// デストラクタ
//==================================
CTotalScore::~CTotalScore()
{
}

//==================================
// クリエイト
//==================================
CTotalScore * CTotalScore::Create(void)
{
	// メモリの確保
	CTotalScore *pTotalScore = NULL;
	pTotalScore = new CTotalScore;

	//NULLチェック
	if (pTotalScore != NULL)
	{
		// 初期化処理
		pTotalScore->Init();
		// オブジェクトタイプの設定
		pTotalScore->SetPriority(OBJTYPE_UI_2);
	}
	return pTotalScore;
}

//==================================
// 初期化処理
//==================================
HRESULT CTotalScore::Init(void)
{
	//カラーデータ取得
	CColorManager* pColor = CColorManager::GetColorManager();

	// プレイヤー人数取得
	int nPlayerNum = CCharaSelect::GetEntryPlayerNum();

	// X軸生成用変数
	float fPosX = (SCREEN_WIDTH / 2) - (((float)(nPlayerNum - 1) * SCORE_SPACE) / 2);
	
	//テクスチャ番号
	CResourceTexture::TEXTURE_TYPE nTexture[CResourceCharacter::CHARACTER_MAX] =
	{
		CResourceTexture::TEXTURE_RESULT_KNIGHT,
		CResourceTexture::TEXTURE_RESULT_LANCER,
		CResourceTexture::TEXTURE_RESULT_WIZARD,
		CResourceTexture::TEXTURE_RESULT_KNIGHT,
		CResourceTexture::TEXTURE_RESULT_LANCER,
		CResourceTexture::TEXTURE_RESULT_ARCHER,
	};

	// 最大桁数分ループ
	for (int nPlayer = 0; nPlayer<MAX_PLAYER; nPlayer++)
	{
		//プレイ人数分生成
		if (CCharaSelect::GetEntryData(nPlayer).bEntry)
		{
			//それぞれ生成
			
			//背景
			m_pBg = CScene2d::Create();
			m_pBg->SetPos(D3DXVECTOR3(fPosX, SCREEN_HEIGHT / 2.0f, 0.0f));
			m_pBg->SetSize(TOTAL_BG_SIZE);
			m_pBg->SetColor(pColor->GetIconColor(CCharaSelect::GetEntryData(nPlayer).nColorNum));
			m_pBg->BindTexture(CResourceTexture::GetTexture(nTexture[(int)CCharaSelect::GetEntryData(nPlayer).charaType]));
			m_pBg->SetPriority(OBJTYPE_BG);

			// キャラポリゴンの生成
			CCharacterPolygon*pCharaPolygon = CCharacterPolygon::Create(D3DXVECTOR3(fPosX, CHARACTER_POLYGON_POS_Y, 0.0f));
			pCharaPolygon->SetCharaType(CCharaSelect::GetEntryData(nPlayer).charaType);
			pCharaPolygon->SetRimColor(pColor->GetStepColor(CCharaSelect::GetEntryData(nPlayer).nColorNum, 1));

			//キル用UI
			m_pTileUI = CScene2d::Create();
			m_pTileUI->SetPos(D3DXVECTOR3(fPosX - 80.0f, PAINT_POS_Y, 0.0f));
			m_pTileUI->SetSize(D3DXVECTOR3(80.0f, 80.0f, 0.0f));
			m_pTileUI->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_RESULT_TILE));
			m_pTileUI->SetPriority(OBJTYPE_UI_2);

			//塗りスコア
			CScore::Create(D3DXVECTOR3(fPosX+50.0f, PAINT_POS_Y, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CColorTile::GetTileNum(nPlayer));
			
			//キル用UI
			m_pKillUi = CScene2d::Create();
			m_pKillUi->SetPos(D3DXVECTOR3(fPosX - 80.0f, KILL_POS_Y, 0.0f));
			m_pKillUi->SetSize(D3DXVECTOR3(80.0f, 80.0f, 0.0f));
			m_pKillUi->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_RESULT_KILL));
			m_pKillUi->SetPriority(OBJTYPE_UI_2);

			//キルスコア
			CScore::Create(D3DXVECTOR3(fPosX+50.0f, KILL_POS_Y, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CKillCount::GetTotalKill(nPlayer));

			fPosX += SCORE_SPACE;
		}
	}


	return S_OK;
}

//==================================
// 終了処理
//==================================
void CTotalScore::Uninit(void)
{

	// 開放処理
	Release();
}

//==================================
// 更新処理
//==================================
void CTotalScore::Update(void)
{
}

//==================================
// 描画処理
//==================================
void CTotalScore::Draw(void)
{
}
