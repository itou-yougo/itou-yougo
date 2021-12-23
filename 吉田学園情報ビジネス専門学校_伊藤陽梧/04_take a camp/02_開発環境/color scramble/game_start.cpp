//=============================================================================
//
// ゲーム開始の処理 [game_start.cpp]
// Author : 佐藤颯紀
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "game_start.h"
#include "polygon.h"
#include "resource_texture.h"
#include "player.h"
#include "time.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TEXT_SIZE D3DXVECTOR3(520.0f,180.0f,0.0f)	// サイズ
#define SIZE_X		(120.0f)
#define SIZE_Y_UP	(300.0f)
#define SIZE_Y_DOWN (420.0f)
#define COUNT		(60)
//=============================================================================
// コンストラクタ
//=============================================================================
CGameStart::CGameStart()
{
	m_pPolygon = NULL;							// ポリゴン情報
	m_pos = VEC3_ZERO;							// 位置情報
	m_size = VEC3_ZERO;
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	// 色情報
	m_nCount = 0;								// カウンター
	m_type = START_TYPE_READEY;					// タイプ
	m_bStart = false;							// スタート使用してるかしてないか
}

//=============================================================================
// デストラクタ
//=============================================================================
CGameStart::~CGameStart()
{

}

//=============================================================================
// 生成処理
//=============================================================================
CGameStart * CGameStart::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CGameStart *pStart = NULL;

	// メモリの確保
	pStart = new CGameStart;

	// NULLチェック
	if (pStart != NULL)
	{
		// 位置設定
		pStart->m_pos = pos;
		// サイズ設定
		pStart->m_size = size;
		// 初期化処理呼び出し
		pStart->Init();

		// オブジェクトタイプ
		pStart->SetPriority(OBJTYPE_UI_2);
	}

	return pStart;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGameStart::Init(void)
{
	// 色設定
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ポリゴンの生成
	m_pPolygon = CPolygon::Create(
		m_pos,
		m_size,
		m_col);

	// readyなら
	if (m_type == START_TYPE_READEY)
	{
		// テクスチャーの設定
		m_pPolygon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_READEY));
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CGameStart::Uninit(void)
{
	if (m_pPolygon != NULL)
	{
		// ポリゴンの終了処理
		m_pPolygon->Uninit();

		// メモリの解放
		delete m_pPolygon;
		m_pPolygon = NULL;
	}

	// 開放処理
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CGameStart::Update(void)
{
	// ポリゴンの更新処理
	m_pPolygon->Update();

	// 毎フレームごとにカウントを増やしていく
	m_nCount++;

	switch (m_type)
	{
	case START_TYPE_READEY:
		// readyなら
		GoChange();
		break;
	case START_TYPE_GO:
		// GOなら
		PlayChange();
		break;

	case START_TYPE_PLAY:
		// プレイ状態にはいったら
		Uninit();
		return;
		break;
	default:
		break;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CGameStart::Draw(void)
{
	// ポリゴンの描画処理
	m_pPolygon->Draw();
}

//=============================================================================
// 画像や大きさ変更処理
//=============================================================================
void CGameStart::GoChange(void)
{
	// カウントが一定値になったら
	if (m_nCount == COUNT)
	{
		// goへ
		m_type = START_TYPE_GO;
		// テクスチャー変更
		m_pPolygon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_GO));

		// 頂点座標の設定
		D3DXVECTOR3 vtxPos[NUM_VERTEX];

		vtxPos[0] = D3DXVECTOR3(SCREEN_WIDTH / 2.0f - SIZE_X, SIZE_Y_UP, 0.0f);
		vtxPos[1] = D3DXVECTOR3(SCREEN_WIDTH / 2.0f + SIZE_X, SIZE_Y_UP, 0.0f);
		vtxPos[2] = D3DXVECTOR3(SCREEN_WIDTH / 2.0f - SIZE_X, SIZE_Y_DOWN, 0.0f);
		vtxPos[3] = D3DXVECTOR3(SCREEN_WIDTH / 2.0f + SIZE_X, SIZE_Y_DOWN, 0.0f);

		// 頂点座標の設定
		m_pPolygon->SetVertexPos(vtxPos);

		// タイムを使用状態にする
		CTime::Create();

		// カウントの初期化
		m_nCount = 0;
	}
}

//=============================================================================
// プレイモードに状態変更
//=============================================================================
void CGameStart::PlayChange(void)
{
	// カウントが一定値になったら
	if (m_nCount == COUNT)
	{
		// プレイヤーの状態を通常状態に
		StartPlayer();
		// プレイタイプへ
		m_type = START_TYPE_PLAY;
	}
}

//=============================================================================
// プレイヤーを動けるようにする
//=============================================================================
void CGameStart::StartPlayer(void)
{
	CPlayer*pPlayer = (CPlayer*)GetTop(OBJTYPE_PLAYER);

	while (pPlayer != NULL)
	{
		pPlayer->SetUpdateFlag(true);

		pPlayer = (CPlayer*)pPlayer->GetNext();
	}
}
