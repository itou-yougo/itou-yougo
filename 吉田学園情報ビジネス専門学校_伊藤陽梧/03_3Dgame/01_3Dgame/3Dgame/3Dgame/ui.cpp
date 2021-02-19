//=============================================================================
//
// uiの処理 [ui.cpp]
// Author : 伊藤陽梧
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "ui.h"
#include "player.h"
#include "game.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9 CUi::m_pTexture[TYPE_MAX] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CUi::CUi(int nPriority) :CScene2D(nPriority)

{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_type = TYPE_NONE;
}

//=============================================================================
// デストラクタ
//=============================================================================
CUi::~CUi()
{

}

//=============================================================================
// 生成処理
//=============================================================================
CUi *CUi::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	CUi *pUi;
	pUi = new CUi(OBJTYPE_UI);
	pUi->SetPosition(pos);
	pUi->SetSize(size);
	pUi->m_type = type;
	pUi->Init();
	return pUi;
}

//=============================================================================
// 読み込み処理
//=============================================================================
HRESULT CUi::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_TITLE,								// ファイルの名前
		&m_pTexture[TYPE_TITLE]);
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_TUTORIAL,								// ファイルの名前
		&m_pTexture[TYPE_TUTORIAL]);
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_GAMEOVER,								// ファイルの名前
		&m_pTexture[TYPE_GAMEOVER]);
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_RESULT,								// ファイルの名前
		&m_pTexture[TYPE_RESULT]);

	return S_OK;
}

//=============================================================================
// テクスチャの破棄
//=============================================================================
void CUi::Unload(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CUi::Init(void)
{
	CScene2D::Init();
	SetObjType(CScene::OBJTYPE_UI);
	BindTexture(m_pTexture[m_type]);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CUi::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CUi::Update(void)
{
	switch (m_type)
	{
	case TYPE_PLAYER_LIFE:
		CScene2D::SetLifebar((float)PLAYER_LIFE, (float)CGame::GetPlayer()->GetLife(), PLAYER_HP_COLOR);
		break;
	default:
		CScene2D::Update();
		break;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CUi::Draw(void)
{
	CScene2D::Draw();
}