//=============================================================================
//
// ポリゴンの描画の処理 [bg.h]
// Author : 伊藤陽梧
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "bg.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "explosion.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define BG1_SCROLL_SPEED (-0.001f)			// 背景を動かす速さ

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CBg::m_apTexture[MAX_BG_TEXTURE];

//=============================================================================
// 背景クラスのコンストラクタ
//=============================================================================
CBg::CBg() :CScene(OBJTYPE_BG)
{
	for (int nCount = 0; nCount < MAX_BG_TEXTURE; nCount++)
	{
		m_apScene[nCount] = NULL;
	}
	m_BgType = BGTYPE_GAME;
}

//=============================================================================
// 背景クラスのデストラクタ
//=============================================================================
CBg::~CBg()
{

}

//=============================================================================
// 背景クラスのテクスチャ読み込み
//=============================================================================
HRESULT CBg::Load(void)
{
	// インスタンス生成したものを受け取る
	CRenderer *pRenderer = CManager::GetRenderer();

	// デバイスを受け取る
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BG1, &m_apTexture[BGTYPE_GAME]);			   // ゲームの背景
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BG4, &m_apTexture[BGTYPE_FRAME]);		   // ゲームの枠
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BGTUTORIAL, &m_apTexture[BGTYPE_TUTORIAL]); // チュートリアルの背景
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BGRESULT, &m_apTexture[BGTYPE_RESULT]);	   // リザルトの背景

	return S_OK;
}

//=============================================================================
// 背景クラスのテクスチャ破棄
//=============================================================================
void CBg::Unload(void)
{
	for (int nCount = 0; nCount < MAX_BG_TEXTURE; nCount++)
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
// 背景クラスのインスタンス生成
//=============================================================================
CBg *CBg::Create(BGTYPE bgtype, OBJTYPE objType)
{
	// pBgのポインタ
	CBg *pBg = NULL;

	// メモリの確保
	pBg = new CBg;

	// pBgがNULLじゃないとき
	if (pBg != NULL)
	{
		pBg->SetBG(bgtype, objType);

		// 初期化処理
		pBg->Init();
	}

	// pBgを返す
	return pBg;
}

//=============================================================================
// 背景クラスの初期化処理
//=============================================================================
HRESULT CBg::Init()
{
	switch (m_BgType)
	{
		// チュートリアルの背景
	case BGTYPE_TUTORIAL:
		BgCreate(m_BgType);
		break;

		// ゲームの背景
	case BGTYPE_GAME:
		BgCreate(m_BgType);

		// bgのアニメーションのセット
		m_apScene[m_BgType]->SetScroll(0.0f, BG1_SCROLL_SPEED);
		break;

		// ゲームの枠
	case BGTYPE_FRAME:
		BgCreate(m_BgType);
		break;

		// リザルトの背景
	case BGTYPE_RESULT:
		BgCreate(m_BgType);
		break;

	default:
		break;
	}
	
	return S_OK;
}

//=============================================================================
// 背景クラスの終了処理
//=============================================================================
void CBg::Uninit(void)
{
	switch (m_BgType)
	{
		// チュートリアルの背景
	case BGTYPE_TUTORIAL:
		if (m_apScene[m_BgType] != NULL)
		{
			// CScene2Dの終了処理
			m_apScene[m_BgType]->Uninit();
		}
		break;

		// ゲームの背景
	case BGTYPE_GAME:
		if (m_apScene[m_BgType] != NULL)
		{
			// CScene2Dの終了処理
			m_apScene[m_BgType]->Uninit();
		}
		break;

		// ゲームの枠
	case BGTYPE_FRAME:
		if (m_apScene[m_BgType] != NULL)
		{
			// CScene2Dの終了処理
			m_apScene[m_BgType]->Uninit();
		}
		break;

		// リザルトの背景
	case BGTYPE_RESULT:
		if (m_apScene[m_BgType] != NULL)
		{
			// CScene2Dの終了処理
			m_apScene[m_BgType]->Uninit();
		}
		break;

	default:
		break;
	}

	Release();
}

//=============================================================================
// 背景クラスの更新処理
//=============================================================================
void CBg::Update(void)
{
	for (int nCount = 0; nCount < MAX_BG_TEXTURE; nCount++)
	{
		// CScene2Dの更新処理
		if (m_apScene[nCount] != NULL)
		{
			m_apScene[nCount]->Update();
		}
	}
}

//=============================================================================
// 背景クラスの描画処理
//=============================================================================
void CBg::Draw(void)
{
	for (int nCount = 0; nCount < MAX_BG_TEXTURE; nCount++)
	{
		// CScene2Dの描画処理
		if (m_apScene[nCount] != NULL)
		{
			m_apScene[nCount]->Draw();
		}
	}
}

//=============================================================================
// 背景クラスのポリゴンを作る処理
//=============================================================================
void CBg::BgCreate(BGTYPE BgType)
{
	m_apScene[BgType] = CScene2D::Create();

	// CScene2Dの初期化処理
	m_apScene[BgType]->Init();

	m_apScene[BgType]->SetObjType(OBJTYPE_SCENE);

	// テクスチャの設定
	m_apScene[BgType]->BindTexture(m_apTexture[m_BgType]);

	// 座標と縦と横の長さを渡す
	m_apScene[BgType]->SetPosition(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f));
	m_apScene[BgType]->SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
}
