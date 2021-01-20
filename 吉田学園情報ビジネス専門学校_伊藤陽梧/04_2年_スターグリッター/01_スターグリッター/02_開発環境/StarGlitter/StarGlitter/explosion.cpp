//=============================================================================
//
// ポリゴンの描画の処理 [explosion.h]
// Author : 伊藤陽梧
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "explosion.h"
#include "renderer.h"
#include "manager.h"
#include "enemy.h"
#include "sound.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define EXPLOSION_ANIMATION_COUNT (7)		// 爆発のアニメーションのカウント(横のテクスチャの分割数)
#define EXPLOSION_ANIMATION_PATTERN (1)		// 爆発のアニメーションのパターン(縦のテクスチャの分割数)
#define BOSSEXPLOSION_ANIMATION_COUNT (7)	// 爆発のアニメーションのカウント(横のテクスチャの分割数)
#define BOSSEXPLOSION_ANIMATION_PATTERN (1) // 爆発のアニメーションのパターン(縦のテクスチャの分割数)
#define EXPLOSION_SIZE_X (100.0f)			// 爆発の縦の長さ
#define EXPLOSION_SIZE_Y (100.0f)			// 爆発の横の長さ

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture[MAX_EXPLOSION_TEXTUTE] = {};

//=============================================================================
// バレットクラスのコンストラクタ
//=============================================================================
CExplosion::CExplosion() :CScene2D(OBJTYPE_EXPLOSION)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCounterAnim = 0;
	m_ExplosionType = EXPLOSIONTYPE_NOMAL;
}

//=============================================================================
// バレットクラスのデストラクタ
//=============================================================================
CExplosion::~CExplosion()
{

}

//=============================================================================
// バレットクラスのテクスチャの読み込み
//=============================================================================
HRESULT CExplosion::Load(void)
{
	// インスタンス生成したものを受け取る
	CRenderer *pRenderer = CManager::GetRenderer();

	// デバイスを受け取る
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_EXPLOSION, &m_pTexture[0]);	   // 弾の爆発
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BOSSEXPLOSION, &m_pTexture[1]); // ボスアタックの爆発

	return S_OK;
}

//=============================================================================
// バレットクラスのテクスチャの破棄
//=============================================================================
void CExplosion::Unload(void)
{
	for (int nCount = 0; nCount < MAX_EXPLOSION_TEXTUTE; nCount++)
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
// バレットクラスのインスタンス生成
//=============================================================================
CExplosion* CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, EXPLOSIONTYPE ExplosionType, OBJTYPE objType)
{
	// CExplosionのポインタ
	CExplosion *pExplosion = NULL;

	// メモリの確保
	pExplosion = new CExplosion;

	// サウンドの再生
	CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_EXPLOSION_SE);

	// pExplosionがNULLじゃないとき
	if (pExplosion != NULL)
	{
		// 爆発のセット
		pExplosion->SetExplosion(pos, size, ExplosionType, objType);

		// 初期化処理
		pExplosion->Init();
	}

	// pExplosionを返す
	return pExplosion;
}

//=============================================================================
// バレットクラスの初期化処理
//=============================================================================
HRESULT CExplosion::Init()
{
	m_nCounterAnim = 0;

	// CScene2Dの初期化処理
	CScene2D::Init();

	switch (m_ExplosionType)
	{
		// 弾の爆発
	case EXPLOSIONTYPE_NOMAL:
		// テクスチャの設定
		BindTexture(m_pTexture[0]);

		// アニメーションのセット
		CScene2D::SetAnimation(EXPLOSION_ANIMATION_COUNT, EXPLOSION_ANIMATION_PATTERN, 1);

		break;

		// ボスアタックの爆発
	case EXPLOSIONTYPE_BOSS:
		// テクスチャの設定
		BindTexture(m_pTexture[1]);

		// アニメーションのセット
   		CScene2D::SetAnimation(BOSSEXPLOSION_ANIMATION_COUNT, BOSSEXPLOSION_ANIMATION_PATTERN, 1);
		break;

	default:
		break;
	}
	
	return S_OK;
}

//=============================================================================
// バレットクラスの終了処理
//=============================================================================
void CExplosion::Uninit(void)
{
	// CScene2Dの終了処理
	CScene2D::Uninit();
}

//=============================================================================
// バレットクラスの更新処理
//=============================================================================
void CExplosion::Update(void)
{
	// サイズの受け取り
	m_size = GetSize();

	// アニメーションのカウント
	m_nCounterAnim++;

	// CScene2Dの更新処理
	CScene2D::Update();

	// m_posを渡す
	SetPosition(m_pos);
	SetSize(m_size);

	switch (m_ExplosionType)
	{
	case EXPLOSIONTYPE_NOMAL:
		if (m_nCounterAnim % EXPLOSION_ANIMATION_COUNT == 0)
		{
			Uninit();
		}
		break;

	case EXPLOSIONTYPE_BOSS:
		if (m_nCounterAnim % BOSSEXPLOSION_ANIMATION_COUNT == 0)
		{
			Uninit();
		}
		break;

	default:
		break;
	}
}

//=============================================================================
// バレットクラスの描画処理
//=============================================================================
void CExplosion::Draw(void)
{
	// CScene2Dの描画処理
	CScene2D::Draw();
}

