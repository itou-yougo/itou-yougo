//=============================================================================
//
// 必殺技のエフェクトの処理 [spesialattackeffect.cpp]
// Author : 伊藤陽梧
//
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "billboard.h"
#include "particle.h"
#include "spesialattackeffect.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CSpesialattackeffect::CSpesialattackeffect()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CSpesialattackeffect::~CSpesialattackeffect()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CSpesialattackeffect * CSpesialattackeffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, int Life)
{
	// CSpesialattackeffectクラスのポインタ
	CSpesialattackeffect *pSpesialattackeffect;

	// メモリ確保
	pSpesialattackeffect = new CSpesialattackeffect;

	// 位置座標設定
	pSpesialattackeffect->SetPos(pos);

	// サイズ設定
	pSpesialattackeffect->SetSize(size);

	// カラー設定
	pSpesialattackeffect->SetColor(col);

	// カラー設定
	pSpesialattackeffect->SetLife(Life);

	// アニメーションの設定
	pSpesialattackeffect->SetAnimation(SPESIALATTACKEFFECT_COUNTANIM, SPESIALATTACKEFFECT_PATTERNANIM, SPESIALATTACKEFFECT_TIMEANIM);

	// 初期化
	pSpesialattackeffect->Init();

	// CSparkクラスのポインタを返す
	return pSpesialattackeffect;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CSpesialattackeffect::Init()
{
	// CParticleクラスのInit
	CParticle::Init(TEX_TYPE_SPESIALATTACK);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CSpesialattackeffect::Uninit(void)
{
	// 終了
	CParticle::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CSpesialattackeffect::Update(void)
{
	// 更新
	CParticle::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CSpesialattackeffect::Draw(void)
{
	// 加算合成のフラグ
	SetAdditiveSynthesis();

	// 描画
	CParticle::Draw();
}