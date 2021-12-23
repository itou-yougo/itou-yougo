//=============================================================================
//
// インゲームのテキスト処理 [ingame_text.cpp]
// Author : 佐藤颯紀
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "ingame_text.h"
#include "manager.h"
#include "polygon.h"
#include "resource_texture.h"
#include "number.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define REMAINING_TEXT_SIZE D3DXVECTOR3(460.0f,120.0f,0.0f)	// サイズ
#define REMAINING_TIME (60)		// 表示タイム
#define NUMBER_SIZE (D3DXVECTOR3(60, 60, 0))				// 数値サイズ
#define TEXT_MOVE_BASIC (D3DXVECTOR3(20.0f, 0.0f, 0.0f))	// 基本移動量
#define TEXT_MOVE_SLOW	(D3DXVECTOR3(3.0f, 0.0f, 0.0f))		// 遅いときの移動量
#define SLOW_POS		(740)								// 遅くさせる場所
#define SPEED_POS		(640)								// 加速させる場所

//=============================================================================
// コンストラクタ
//=============================================================================
CInGameText::CInGameText() :CScene2d(OBJTYPE_UI_2)
{
	memset(&m_apNumber,0,sizeof(m_apNumber));
	m_pos = VEC3_ZERO;							// 位置情報
	m_size = VEC3_ZERO;							// サイズ
	m_move = VEC3_ZERO;
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	// 色情報
	m_nCount = 0;								// カウンター
	m_nTime = REMAINING_TIME;	// 残り時間
}

//=============================================================================
// デストラクタ
//=============================================================================
CInGameText::~CInGameText()
{

}

//=============================================================================
// 生成処理
//=============================================================================
CInGameText * CInGameText::Create(D3DXVECTOR3 pos)
{
	CInGameText *pInGameText = NULL;

	// メモリの確保
	pInGameText = new CInGameText; 
	
	// NULLチェック
	if (pInGameText != NULL)
	{
		// 初期化処理呼び出し
		pInGameText->Init();
		// 位置設定
		pInGameText->SetPos(pos);
		// テクスチャの設定
		pInGameText->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_SECONDS));
		// オブジェクトタイプ
		pInGameText->SetPriority(OBJTYPE_UI_2);
	}

	return pInGameText;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CInGameText::Init(void)
{
	// 初期化処理
	CScene2d::Init();

	// 色設定
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// サイズ設定
	SetSize(REMAINING_TEXT_SIZE);

	// 移動量
	m_move = TEXT_MOVE_BASIC;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CInGameText::Uninit(void)
{
	// 終了処理
	CScene2d::Uninit();
	
	// 桁分回す
	for (int nCntDigit = 0; nCntDigit < MAX_DIGIT; nCntDigit++)
	{
		// NULLチェック
		if (m_apNumber[nCntDigit] != NULL)
		{
			// 終了処理
			m_apNumber[nCntDigit]->Uninit();
			delete m_apNumber[nCntDigit];
			m_apNumber[nCntDigit] = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CInGameText::Update(void)
{
	// 更新処理
	CScene2d::Update();

	// 位置情報の取得
	D3DXVECTOR3 TextPos = GetPos();

	// 桁分回す
	for (int nCntDigit = 0; nCntDigit < MAX_DIGIT; nCntDigit++)
	{
		//nullチェック
		if (m_apNumber[nCntDigit] == nullptr)
		{
			// ナンバー生成処理
			m_apNumber[nCntDigit] = CNumber::Create(0,
				D3DXVECTOR3((float)(GetPos().x + nCntDigit * NUMBER_SIZE.x), GetPos().y, 0.0f),
				NUMBER_SIZE,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			// ナンバーの配置
			m_apNumber[nCntDigit]->SetNumber((int)((m_nTime % (int)(powf(10.0f, (MAX_DIGIT - nCntDigit)))) / (float)(powf(10, (MAX_DIGIT - nCntDigit - 1)))));
		}

	}


	// 位置情報に移動量を加算する
	TextPos.x -= m_move.x;

	// 一定値に達すると減速させる
	if (TextPos.x <= SLOW_POS&& TextPos.x > SPEED_POS)
	{
		m_move.x = TEXT_MOVE_SLOW.x;
	}

	// 一定値に達すると加速させる
	if (TextPos.x <= SPEED_POS&&TextPos.x > 0.0f)
	{
		m_move.x = TEXT_MOVE_BASIC.x;
	}

	// カウントが一定数になったら
	if (TextPos.x <= -REMAINING_TEXT_SIZE.x / 2)
	{
		// 終了処理
		Uninit();
		return;
	}

	// 位置情報設定
	SetPos(TextPos);


	// 回数分回す
	for (int nCntDigit = 0; nCntDigit < MAX_DIGIT; nCntDigit++)
	{
		// 更新処理
		m_apNumber[nCntDigit]->Update();

		// 位置の設定
		m_apNumber[nCntDigit]->SetPos(D3DXVECTOR3((float)( GetPos().x+ nCntDigit * 75), GetPos().y, 0.0f));
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CInGameText::Draw(void)
{
	// 描画処理
	CScene2d::Draw();

	// 回数分回す
	for (int nCntDigit = 0; nCntDigit < MAX_DIGIT; nCntDigit++)
	{
		//NULLチェック
		if (m_apNumber[nCntDigit] != nullptr)
		{
			// 描画処理
			m_apNumber[nCntDigit]->Draw();
	
		}
	}
}