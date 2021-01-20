//=============================================================================
//
// エフェクトの処理 [effect.cpp]
// Author : 伊藤陽梧
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "effect.h"
#include "renderer.h"
#include "manager.h"
#include "life.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CEffect::m_apTexture[MAX_EFFECT_TEXTURE] = {};

//=============================================================================
// エフェクトクラスのコンストラクタ
//=============================================================================
CEffect::CEffect() :CScene2D(OBJTYPE_EFFECT)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_nRed = 0;
	m_nGreen = 0;
	m_nBrue = 0;
	m_nAlpha = 0;
	m_EffectType = EFFECTTYPE_BULLET;
}

//=============================================================================
// エフェクトクラスのデストラクタ
//=============================================================================
CEffect::~CEffect()
{

}

//=============================================================================
// エフェクトクラスのテクスチャ読み込み
//=============================================================================
HRESULT CEffect::Load(void)
{
	// インスタンス生成したものを受け取る
	CRenderer *pRenderer = CManager::GetRenderer();

	// デバイスを受け取る
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの読み込み
	HRESULT hr = D3DXCreateTextureFromFile(pDevice, TEXTURE_EFFECT_BULLET, &m_apTexture[0]);
	hr = D3DXCreateTextureFromFile(pDevice, TEXTURE_EFFECT_CHARGE, &m_apTexture[1]);

	return S_OK;
}

//=============================================================================
// エフェクトクラスのテクスチャ破棄
//=============================================================================
void CEffect::Unload(void)
{
	for (int nCount = 0; nCount < MAX_EFFECT_TEXTURE; nCount++)
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
// エフェクトクラスのインスタンス生成
//=============================================================================
CEffect * CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nLife, int nRed, int nGreen, int nBrue, int nAlpha, EFFECTTYPE EffectType, OBJTYPE objType)
{
	// CDiceのポインタ
	CEffect *Effect = NULL;

	// メモリの確保
	Effect = new CEffect;

	// EffectがNULLじゃないとき
	if (Effect != NULL)
	{
		Effect->SetEffect(pos, size, nLife, nRed, nGreen, nBrue, nAlpha, EffectType, objType);
		
		// 初期化処理
		Effect->Init();
	}

	// Effectを返す
	return Effect;
}

//=============================================================================
// エフェクトクラスの初期化処理
//=============================================================================
HRESULT CEffect::Init()
{
	// CScene2Dの初期化処理
	CScene2D::Init();

	switch (m_EffectType)
	{
	case EFFECTTYPE_BULLET:
		// テクスチャの設定
		BindTexture(m_apTexture[m_EffectType]);
		break;

	case EFFECTTYPE_CHARGESTATE:
		// テクスチャの設定
		BindTexture(m_apTexture[m_EffectType]);

		// アニメーションのセット
		SetAnimationSelect(3, 3, 0, 10);
		break;

	default:
		break;
	}
	
	return S_OK;
}

//=============================================================================
// エフェクトクラスの終了処理
//=============================================================================
void CEffect::Uninit(void)
{
	// CScene2Dの終了処理
	CScene2D::Uninit();
}

//=============================================================================
// エフェクトクラスの更新処理
//=============================================================================
void CEffect::Update(void)
{
	// CScene2Dの更新処理
	CScene2D::Update();
	SetColor(m_nRed, m_nGreen, m_nBrue, m_nAlpha);

	// 座標とサイズを受け取る
	m_pos = GetPosition();
	m_size = GetSize();

	switch (m_EffectType)
	{
		// 弾のエフェクト
	case EFFECTTYPE_BULLET:
		// サイズを小さくしていく
		m_size -= D3DXVECTOR3(1.0f, 1.0f, 0.0f);

		// サイズが0.0fより小さくなったら
		if (m_size < D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		{
			m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}

		// 体力と透明度の減算
		m_nLife--;
		m_nAlpha--;

		// 体力が0以下になったら
		if (m_nLife <= 0)
		{
			Uninit();
		}
		break;

	default:
		break;
	}
	
	// 座標とサイズを渡す
	SetPosition(m_pos);
	SetSize(m_size);
}

//=============================================================================
// エフェクトクラスの描画処理
//=============================================================================
void CEffect::Draw(void)
{
	// インスタンス生成したものを受け取る
	CRenderer *pRenderer = CManager::GetRenderer();

	// デバイスを受け取る
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	
	// CScene2Dの描画処理
	CScene2D::Draw();

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}