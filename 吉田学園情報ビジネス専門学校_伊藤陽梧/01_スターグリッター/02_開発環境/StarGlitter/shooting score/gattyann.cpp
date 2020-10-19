//=============================================================================
//
// ガッチャンの処理 [gattyann.cpp]
// Author : 伊藤陽梧
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "gattyann.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "fade.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CGattyann::m_pTexture[MAX_GATTYANN_TEXTURE] = {};

//=============================================================================
// ガッチャンクラスのコンストラクタ
//=============================================================================
CGattyann::CGattyann() :CScene2D(OBJTYPE_GATTYANN)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fSizeX = 0.0f;
	m_fSizeY = 0.0f;
	m_nCount = 0;
	m_GattyannType = GATTYANN_1;
}

//=============================================================================
// ガッチャンクラスのデストラクタ
//=============================================================================
CGattyann::~CGattyann()
{

}

//=============================================================================
// ガッチャンクラスのテクスチャ読み込み
//=============================================================================
HRESULT CGattyann::Load(void)
{
	// インスタンス生成したものを受け取る
	CRenderer *pRenderer = CManager::GetRenderer();

	// デバイスを受け取る
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_GATTYANN1, &m_pTexture[GATTYANN_1]); // 1枚目
	D3DXCreateTextureFromFile(pDevice, TEXTURE_GATTYANN2, &m_pTexture[GATTYANN_2]); // 2枚目
	D3DXCreateTextureFromFile(pDevice, TEXTURE_GATTYANN3, &m_pTexture[GATTYANN_3]); // 3枚目
	D3DXCreateTextureFromFile(pDevice, TEXTURE_GATTYANN4, &m_pTexture[GATTYANN_4]); // 4枚目
	D3DXCreateTextureFromFile(pDevice, TEXTURE_GATTYANN5, &m_pTexture[GATTYANN_5]); // 5枚目
	D3DXCreateTextureFromFile(pDevice, TEXTURE_GATTYANN6, &m_pTexture[GATTYANN_6]); // 6枚目
	D3DXCreateTextureFromFile(pDevice, TEXTURE_GATTYANN7, &m_pTexture[GATTYANN_7]); // 7枚目
	D3DXCreateTextureFromFile(pDevice, TEXTURE_GATTYANN8, &m_pTexture[GATTYANN_8]); // 8枚目

	return S_OK;
}

//=============================================================================
// ガッチャンクラスのテクスチャ破棄
//=============================================================================
void CGattyann::Unload(void)
{
	for (int nCount = 0; nCount < MAX_GATTYANN_TEXTURE; nCount++)
	{
		// テクスチャの破棄
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
// ガッチャンクラスのインスタンス生成
//=============================================================================
CGattyann * CGattyann::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, GATTYANNTYPE GattyannType)
{
	// CGattyannのポインタ
	CGattyann *pText = NULL;

	// メモリの確保
	pText = new CGattyann;

	// pTextがNULLじゃないとき
	if (pText != NULL)
	{
		// 座標やサイズのセット
		pText->SetGattyann(pos, fSizeX, fSizeY, GattyannType);

		// 初期化処理
		pText->Init();
	}

	// pNumberを返す
	return pText;
}

//=============================================================================
// ガッチャンクラスの初期化処理
//=============================================================================
HRESULT CGattyann::Init()
{
	// CScene2Dの初期化処理
	CScene2D::Init();

	// m_apTextureがNULLじゃないとき
	if (m_pTexture[m_GattyannType] != NULL)
	{
		//　テクスチャの設定
		BindTexture(m_pTexture[m_GattyannType]);
	}

	return S_OK;
}

//=============================================================================
// ガッチャンクラスの終了処理
//=============================================================================
void CGattyann::Uninit(void)
{
	// CScene2Dの終了処理
	CScene2D::Uninit();
}

//=============================================================================
// ガッチャンクラスの更新処理
//=============================================================================
void CGattyann::Update(void)
{
	// CScene2Dの更新処理
	CScene2D::Update();

	m_pos = GetPosition();

	switch (m_GattyannType)
	{
		// 1枚目
	case GATTYANN_1:
		// カウントの加算
		m_nCount++;
		if (m_nCount >= GATTYANN_OPEN_SPEED)
		{
			// GATTYANN_SPEED分加算
			m_pos.y += -GATTYANN_SPEED;
			if (m_pos.y <= -m_fSizeY)
			{
				Uninit();
			}
		}
		break;

		// 2枚目
	case GATTYANN_2:
		// カウントの加算
		m_nCount++;
		if (m_nCount >= GATTYANN_OPEN_SPEED)
		{
			// GATTYANN_SPEED分加算
			m_pos.x += (GATTYANN_SPEED + 5.0f);
			if (m_fSizeX >= m_fSizeX + SCREEN_WIDTH)
			{
				Uninit();
			}
		}
		break;

		// 3枚目
	case GATTYANN_3:
		// カウントの加算
		m_nCount++;
		if (m_nCount >= GATTYANN_OPEN_SPEED)
		{
			// GATTYANN_SPEED分加算
			m_pos.x += -(GATTYANN_SPEED + 5.0f);
			if (m_pos.x <= -m_fSizeX)
			{
				Uninit();
			}
		}
		break;

		// 4枚目
	case GATTYANN_4:
		// カウントの加算
		m_nCount++;
		if (m_nCount >= GATTYANN_OPEN_SPEED)
		{
			// GATTYANN_SPEED分加算
			m_pos.y += GATTYANN_SPEED;
			if (m_fSizeY >= m_fSizeY + SCREEN_HEIGHT)
			{
				Uninit();
			}
		}
		break;

		// 5枚目
	case GATTYANN_5:
		// GATTYANN_SPEED分加算
		m_pos.y += -GATTYANN_SPEED;
		if (m_pos.y <= SCREEN_CENTER_Y)
		{
			m_pos.y = SCREEN_CENTER_Y;

			// カウントの加算
			m_nCount++;

			if (m_nCount == GATTYANN_OPEN_SPEED * 2)
			{
				// モードのセット
				CManager::SetMode(CManager::MODE_GAME);

				// 次の四枚を生成
				Create(D3DXVECTOR3(SCREEN_CENTER_X / 2, SCREEN_CENTER_Y / 2, 0.0f), 864.0f, 540.0f, GATTYANN_1);
				Create(D3DXVECTOR3(SCREEN_WIDTH - SCREEN_CENTER_X / 2, SCREEN_CENTER_Y / 2, 0.0f), 864.0f, 540.0f, GATTYANN_2);
				Create(D3DXVECTOR3(SCREEN_CENTER_X / 2, SCREEN_HEIGHT - SCREEN_CENTER_Y / 2, 0.0f), 864.0f, 540.0f, GATTYANN_3);
				Create(D3DXVECTOR3(SCREEN_WIDTH - SCREEN_CENTER_X / 2, SCREEN_HEIGHT - SCREEN_CENTER_Y / 2, 0.0f), 864.0f, 540.0f, GATTYANN_4);
				m_nCount = 0;
			}
		}
		break;

		// 5枚目
	case GATTYANN_6:
		// GATTYANN_SPEED分加算
		m_pos.y += GATTYANN_SPEED;
		if (m_pos.y >= SCREEN_CENTER_Y)
		{
			m_pos.y = SCREEN_CENTER_Y;

			// カウントの加算
			m_nCount++;
		}
		break;

		// 6枚目
	case GATTYANN_7:
		// GATTYANN_SPEED分加算
		m_pos.y += -GATTYANN_SPEED;
		if (m_pos.y <= SCREEN_CENTER_Y)
		{
			m_pos.y = SCREEN_CENTER_Y;

			// カウントの加算
			m_nCount++;
		}
		break;

		// 7枚目
	case GATTYANN_8:
		// GATTYANN_SPEED分加算
		m_pos.y += GATTYANN_SPEED;
		if (m_pos.y >= SCREEN_CENTER_Y)
		{
			m_pos.y = SCREEN_CENTER_Y;

			// カウントの加算
			m_nCount++;
		}
		break;

	default:
		break;
	}

	// 座標のセット
	SetPosition(m_pos);
}

//=============================================================================
// ガッチャンクラスの描画処理
//=============================================================================
void CGattyann::Draw(void)
{
	// CScene2Dの描画処理
	CScene2D::Draw();
}