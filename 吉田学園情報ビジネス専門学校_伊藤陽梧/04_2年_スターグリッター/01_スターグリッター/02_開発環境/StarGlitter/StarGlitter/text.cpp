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
#include "player2.h"
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
	m_nAlpha = 255;
	m_nCount = 0;
	m_fSizeX = 0.0f;
	m_fSizeY = 0.0f;
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
CText * CText::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, TEXTTYPE TextType)
{
	// CTextのポインタ
	CText *pText = NULL;

	// メモリの確保
	pText = new CText;

	// pTextがNULLじゃないとき
	if (pText != NULL)
	{
		// 座標やサイズのセット
		pText->SetText(pos, fSizeX, fSizeY, TextType);

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
	m_fSizeY = GetSizeY();

	switch (m_TextType)
	{
		// READYの文字
	case TEXTTYPE_READY:
		// m_bUseが使用状態の時
		if (m_bUse == true)
		{
			m_fSizeY += 3.0f;

			// サイズがMAX_SIZE_Yより大きくなったら
			if (m_fSizeY >= MAX_SIZE_Y)
			{
				// m_bUseを使用しない状態にする
				m_bUse = false;
			}
		}
		// m_bUseが使用しない状態の時
		else if (m_bUse == false)
		{
			m_fSizeY -= 3.0f;

			// サイズがMAX_SIZE_Yより小さくなったら
			if (m_fSizeY <= 0.0f)
			{
				// GOのクリエイト
				Create(m_pos, 632.0f, 232.0f, TEXTTYPE_GO);

				// 終了処理
				Uninit();
				return;
			}
		}
		break;

		// GOの文字
	case TEXTTYPE_GO:
		m_nCount++;

		// m_nCountがMAX_TIMEより大きいとき
		if (m_nCount >= MAX_TIME)
		{
			//ゲームの状態をGAMESTATE_STARTにする
			CGame::SetGameState(CGame::GAMESTATE_START);

			// 終了処理
			Uninit();
		}
		break;

		// KOの文字
	case TEXTTYPE_KO:
		m_nCount++;

		// m_nCountがMAX_TIMEより大きいとき
		if (m_nCount >= MAX_TIME)
		{
			// m_bUseが使用状態の時
			if (m_bUse == true)
			{
				for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
				{
					// PLAYERのシーンの受け取り
					CScene *pScene = CScene::GetScene(CScene::OBJTYPE_PLAYER, nCntScene);
					if (pScene != NULL)
					{
						// オブジェタイプの受け取り
						CScene::OBJTYPE objType = pScene->GetObjType();
						if (objType == CScene::OBJTYPE_PLAYER)
						{
							//PLAYER1がPLAYERSTATE_LOSEだったら
							if (((CPlayer*)pScene)->GetPlayerState() == CPlayer::PLAYERSTATE_LOSE)
							{
								// LOSTのテキストの生成
								CText::Create(D3DXVECTOR3(PLAYER_START_POS, SCREEN_CENTER_Y, 0.0f), 652.0f, 232.0f, CText::TEXTTYPE_LOST);
							}
							else
							{
								// WONのテキストの生成
								CText::Create(D3DXVECTOR3(PLAYER_START_POS, SCREEN_CENTER_Y, 0.0f), 592.0f, 232.0f, CText::TEXTTYPE_WON);
							}
						}
					}

					// PLAYER2のシーンの受け取り
					pScene = CScene::GetScene(CScene::OBJTYPE_PLAYER2, nCntScene);
					if (pScene != NULL)
					{
						// オブジェタイプの受け取り
						CScene::OBJTYPE objType = pScene->GetObjType();
						if (objType == CScene::OBJTYPE_PLAYER2)
						{
							//PLAYER2がPLAYERSTATE_LOSEだったら
							if (((CPlayer2*)pScene)->GetPlayer2State() == CPlayer2::PLAYERSTATE_LOSE)
							{
								// LOSTのテキストの生成
								CText::Create(D3DXVECTOR3(PLAYER2_START_POS, SCREEN_CENTER_Y, 0.0f), 652.0f, 232.0f, CText::TEXTTYPE_LOST);
							}
							else
							{
								// WONのテキストの生成
								CText::Create(D3DXVECTOR3(PLAYER2_START_POS, SCREEN_CENTER_Y, 0.0f), 592.0f, 232.0f, CText::TEXTTYPE_WON);
							}
						}
					}
				}

				// m_bUseを使用しない状態にする
				m_bUse = false;

				// 終了処理
				Uninit();
			}
		}
		break;

	case TEXTTYPE_WON:
		m_nCount++;
		// カウントがMAX_TIMEの２倍の値より大きいとき
		if (m_nCount >= MAX_TIME * 2)
		{
			// m_bUseが使用状態の時
			if (m_bUse == true)
			{
				// 黒い背景とメニューの生成
				CSelect::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, CSelect::SELECTTYPE_KUROHAIKEI);
				CSelect::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), 850.0f, 625.0f, CSelect::SELECTTYPE_MENU);

				// m_bUseを使用しない状態にする
				m_bUse = false;
			}
		}
		break;

	default:
		break;
	}

	// サイズのセット
	SetSize(m_fSizeX, m_fSizeY);
}

//=============================================================================
// テキストの描画処理
//=============================================================================
void CText::Draw(void)
{
	// CScene2Dの描画処理
	CScene2D::Draw();
}