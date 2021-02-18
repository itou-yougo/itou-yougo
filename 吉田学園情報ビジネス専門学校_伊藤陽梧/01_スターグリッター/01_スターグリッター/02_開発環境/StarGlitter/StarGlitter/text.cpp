//=============================================================================
//
// テキストの処理 [text.cpp]
// Author : 伊藤陽梧
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "text.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "select.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_SIZE_Y (190.0f) // 縦の大きさの最大値
#define MAX_TIME (60)		// 時間の最大値

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CText::m_apTexture[MAX_TEXT_TEXTURE] = {};

//=============================================================================
// テキストのコンストラクタ
//=============================================================================
CText::CText() :CScene2D(OBJTYPE_TEXT)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nAlpha = 255;
	m_nCount = 0;
	m_bUse = true;
	m_TextType = TEXTTYPE_MAX;
}

//=============================================================================
// テキストのデストラクタ
//=============================================================================
CText::~CText()
{

}

//=============================================================================
// テキストのテクスチャ読み込み
//=============================================================================
HRESULT CText::Load(void)
{
	// インスタンス生成したものを受け取る
	CRenderer *pRenderer = CManager::GetRenderer();

	// デバイスを受け取る
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_RESTART, &m_apTexture[TEXTTYPE_RESTART]);    // もう一度始める
	D3DXCreateTextureFromFile(pDevice, TEXTURE_TITLEMODORU, &m_apTexture[TEXTTYPE_MODORU]);	// タイトルに戻る
	D3DXCreateTextureFromFile(pDevice, TEXTURE_READY, &m_apTexture[TEXTTYPE_READY]);		// READYの文字
	D3DXCreateTextureFromFile(pDevice, TEXTURE_GO, &m_apTexture[TEXTTYPE_GO]);				// GOの文字
	D3DXCreateTextureFromFile(pDevice, TEXTURE_KO, &m_apTexture[TEXTTYPE_KO]);				// KOの文字
	D3DXCreateTextureFromFile(pDevice, TEXTURE_WON, &m_apTexture[TEXTTYPE_WON]);			// WONの文字
	D3DXCreateTextureFromFile(pDevice, TEXTURE_LOST, &m_apTexture[TEXTTYPE_LOST]);			// LOSTの文字

	return S_OK;
}

//=============================================================================
// テキストのテクスチャ破棄
//=============================================================================
void CText::Unload(void)
{
	for (int nCount = 0; nCount < MAX_TEXT_TEXTURE; nCount++)
	{
		// テクスチャの破棄
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
// テキストのインスタンス生成
//=============================================================================
CText * CText::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TEXTTYPE TextType)
{
	// CTextのポインタ
	CText *pText = NULL;

	// メモリの確保
	pText = new CText;

	// pTextがNULLじゃないとき
	if (pText != NULL)
	{
		// 座標やサイズのセット
		pText->SetText(pos, size, TextType);

		// 初期化処理
		pText->Init();
	}

	// pNumberを返す
	return pText;
}

//=============================================================================
// テキストの初期化処理
//=============================================================================
HRESULT CText::Init()
{
	// CScene2Dの初期化処理
	CScene2D::Init();
	
	// m_apTextureがNULLじゃないとき
	if (m_apTexture[m_TextType] != NULL)
	{
		//　テクスチャの設定
		BindTexture(m_apTexture[m_TextType]);
	}

	// オブジェタイプのセット
	SetObjType(OBJTYPE_TEXT);

	switch (m_TextType)
	{
		// GOの文字
	case TEXTTYPE_GO:
		// チカチカさせる
		SetTransparency(true);
		break;

	default:
		break;
	}

	return S_OK;
}

//=============================================================================
// テキストの終了処理
//=============================================================================
void CText::Uninit(void)
{
	// CScene2Dの終了処理
	CScene2D::Uninit();
}

//=============================================================================
// テキストの更新処理
//=============================================================================
void CText::Update(void)
{
	// CScene2Dの更新処理
	CScene2D::Update();

	// サイズの受け取り
	m_size = GetSize();

	switch (m_TextType)
	{
		// READYの文字
	case TEXTTYPE_READY:
		// Readyの文字の処理
		Ready();
		break;

		// GOの文字
	case TEXTTYPE_GO:
		// Goの文字の処理
		Go();
		break;

		// KOの文字
	case TEXTTYPE_KO:
		// Koの文字の処理
		Ko();
		break;

	case TEXTTYPE_WON:
		// Wonの文字の処理
		Won();
		break;

	default:
		break;
	}

	// サイズのセット
	SetSize(m_size);
}

//=============================================================================
// テキストの描画処理
//=============================================================================
void CText::Draw(void)
{
	// CScene2Dの描画処理
	CScene2D::Draw();
}

//=============================================================================
// Readyの文字の処理
//=============================================================================
void CText::Ready(void)
{
	// m_bUseが使用状態の時
	if (m_bUse == true)
	{
		m_size.y += 3.0f;

		// サイズがMAX_SIZE_Yより大きくなったら
		if (m_size.y >= MAX_SIZE_Y)
		{
			// m_bUseを使用しない状態にする
			m_bUse = false;
		}
	}
	// m_bUseが使用しない状態の時
	else if (m_bUse == false)
	{
		m_size.y -= 3.0f;

		// サイズがMAX_SIZE_Yより小さくなったら
		if (m_size.y <= 0.0f)
		{
			// GOのクリエイト
			Create(m_pos, D3DXVECTOR3(632.0f, 232.0f, 0.0f), TEXTTYPE_GO);;

			// 終了処理
			Uninit();
			return;
		}
	}
}

//=============================================================================
// Goの文字の処理
//=============================================================================
void CText::Go(void)
{
	m_nCount++;

	// m_nCountがMAX_TIMEより大きいとき
	if (m_nCount >= MAX_TIME)
	{
		//ゲームの状態をGAMESTATE_STARTにする
		CGame::SetGameState(CGame::GAMESTATE_START);

		// 終了処理
		Uninit();
		return;
	}
}

//=============================================================================
// Koの文字の処理
//=============================================================================
void CText::Ko(void)
{
	m_nCount++;

	// m_nCountがMAX_TIMEより大きいとき
	if (m_nCount >= MAX_TIME)
	{
		// m_bUseが使用状態の時
		if (m_bUse == true)
		{
			// プレイヤーのシーンの受け取り
			CScene *pScene = CScene::GetSceneTop(CScene::OBJTYPE_PLAYER);
			do
			{
				if (pScene != NULL)
				{
					// オブジェタイプの受け取り
					CScene::OBJTYPE objType = pScene->GetObjType();
					if (objType == CScene::OBJTYPE_PLAYER)
					{
						switch (((CPlayer*)pScene)->GetPlayerNum())
						{
						case CPlayer::PLAYER_1P:
							//PLAYER1がPLAYERSTATE_LOSEだったら
							if (((CPlayer*)pScene)->GetPlayerState() == CPlayer::PLAYERSTATE_LOSE)
							{
								// LOSTのテキストの生成
								CText::Create(D3DXVECTOR3(PLAYER_START_POS, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(652.0f, 232.0f, 0.0f), CText::TEXTTYPE_LOST);
							}
							else
							{
								// WONのテキストの生成
								CText::Create(D3DXVECTOR3(PLAYER_START_POS, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(592.0f, 232.0f, 0.0f), CText::TEXTTYPE_WON);
							}
							break;

						case CPlayer::PLAYER_2P:
							//PLAYER2がPLAYERSTATE_LOSEだったら
							if (((CPlayer*)pScene)->GetPlayerState() == CPlayer::PLAYERSTATE_LOSE)
							{
								// LOSTのテキストの生成
								CText::Create(D3DXVECTOR3(PLAYER2_START_POS, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(652.0f, 232.0f, 0.0f), CText::TEXTTYPE_LOST);
							}
							else
							{
								// WONのテキストの生成
								CText::Create(D3DXVECTOR3(PLAYER2_START_POS, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(592.0f, 232.0f, 0.0f), CText::TEXTTYPE_WON);
							}
							break;

						default:
							break;
						}
					}
					pScene = pScene->GetSceneNext();
				}
			} while (pScene != NULL);

			// m_bUseを使用しない状態にする
			m_bUse = false;

			// 終了処理
			Uninit();
			return;
		}
	}
}

//=============================================================================
// Wonの文字の処理
//=============================================================================
void CText::Won(void)
{
	m_nCount++;
	if (m_nCount >= 120)
	{
		if (m_bUse == true)
		{
			CSelect::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CSelect::SELECTTYPE_KUROHAIKEI);
			CSelect::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(850.0f, 625.0f, 0.0f), CSelect::SELECTTYPE_MENU);
			m_bUse = false;
		}
	}
}
