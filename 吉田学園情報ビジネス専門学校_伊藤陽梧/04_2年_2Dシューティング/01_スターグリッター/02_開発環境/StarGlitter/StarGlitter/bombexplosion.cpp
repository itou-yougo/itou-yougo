//=============================================================================
//
// ボムの爆発の処理 [bombexplosion.cpp]
// Author : 伊藤陽梧
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "bombexplosion.h"
#include "renderer.h"
#include "manager.h"
#include "enemy.h"
#include "sound.h"
#include "bullet.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CBombexplosion::m_pTexture = NULL;

//=============================================================================
// ボムの爆発クラスのコンストラクタ
//=============================================================================
CBombexplosion::CBombexplosion() :CScene2D(OBJTYPE_EXPLOSION)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Getpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fSizeX = 0.0f;
	m_fSizeY = 0.0f;
	m_fGetSizeX = 0.0f;
	m_fGetSizeY = 0.0f;
	m_nLife = 0;
	m_BombExplosionType = BOMBEXPLOSION_NONE;
}

//=============================================================================
// ボムの爆発クラスのデストラクタ
//=============================================================================
CBombexplosion::~CBombexplosion()
{

}

//=============================================================================
// ボムの爆発クラスのテクスチャの読み込み
//=============================================================================
HRESULT CBombexplosion::Load(void)
{
	// インスタンス生成したものを受け取る
	CRenderer *pRenderer = CManager::GetRenderer();

	// デバイスを受け取る
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BOMBEXPLOSION, &m_pTexture);

	return S_OK;
}

//=============================================================================
// ボムの爆発クラスのテクスチャの破棄
//=============================================================================
void CBombexplosion::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// ボムの爆発クラスのインスタンス生成
//=============================================================================
CBombexplosion* CBombexplosion::Create(D3DXVECTOR3 pos, int nLife, BOMBEXPLOSIONTYPE bombexplosiontype, OBJTYPE objType)
{
	// CBombexplosionのポインタ
	CBombexplosion *pBombExplosion = NULL;

	// メモリの確保
	pBombExplosion = new CBombexplosion;

	// サウンドの開始
	CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_EXPLOSION_SE);

	// pBombExplosionがNULLじゃないとき
	if (pBombExplosion != NULL)
	{
		// ボムの爆発のセット
		pBombExplosion->SetExplosion(pos, nLife, bombexplosiontype, objType);

		// 初期化処理
		pBombExplosion->Init();
	}

	// pBombExplosionを返す
	return pBombExplosion;
}

//=============================================================================
// ボムの爆発クラスの初期化処理
//=============================================================================
HRESULT CBombexplosion::Init()
{
	// CScene2Dの初期化処理
	CScene2D::Init();

	// テクスチャの設定
	BindTexture(m_pTexture);

	// アニメーションのセット
	CScene2D::SetAnimation(BOMBEXPLOSION_ANIMATION_COUNT, BOMBEXPLOSION_ANIMATION_PATTERN, 4);

	return S_OK;
}

//=============================================================================
// ボムの爆発クラスの終了処理
//=============================================================================
void CBombexplosion::Uninit(void)
{
	// CScene2Dの終了処理
	CScene2D::Uninit();
}

//=============================================================================
// ボムの爆発クラスの更新処理
//=============================================================================
void CBombexplosion::Update(void)
{
	// 体力の減算
	m_nLife--;

	// CScene2Dの更新処理
	CScene2D::Update();

	switch (m_BombExplosionType)
	{
		// プレイヤー1のボムの爆発
	case BOMBEXPLOSION_PLAYER:
		for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
		{
			// シーンの受け取り
			CScene *pScene = GetScene(OBJTYPE_ENEMY, nCntScene);
			if (pScene != NULL)
			{
				// オブジェタイプの受け取り
				OBJTYPE objType = pScene->GetObjType();
				if (objType == OBJTYPE_ENEMY)
				{
					// 座標やサイズの受け取り
					m_Getpos = ((CScene2D*)pScene)->GetPosition();
					m_fGetSizeX = ((CScene2D*)pScene)->GetSizeX();
					m_fGetSizeY = ((CScene2D*)pScene)->GetSizeY();
					if (m_Getpos.y + m_fGetSizeY >= 0)
					{
						// 当たり判定
						if (m_pos.x - (BOMBEXPLOSION_SIZE_X / 2) <= m_Getpos.x + (m_fGetSizeX / 2) &&
							m_pos.x + (BOMBEXPLOSION_SIZE_X / 2) >= m_Getpos.x - (m_fGetSizeX / 2) &&
							m_pos.y - (BOMBEXPLOSION_SIZE_Y / 2) <= m_Getpos.y + (m_fGetSizeY / 2) &&
							m_pos.y + (BOMBEXPLOSION_SIZE_Y / 2) >= m_Getpos.y - (m_fGetSizeY / 2))
						{
							// 敵のダメージ
							((CEnemy*)pScene)->EnemyDamage(100, CEnemy::DAMAGE_TYPE_BULLET, CBullet::BULLET_TYPE_PLAYER);
							break;
						}
					}
				}
			}
		}
		break;

		// プレイヤー2のボムの爆発
	case BOMBEXPLOSION_PLAYER2:
		for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
		{
			// シーンの受け取り
			CScene *pScene = GetScene(OBJTYPE_ENEMY, nCntScene);
			if (pScene != NULL)
			{
				// オブジェタイプの受け取り
				OBJTYPE objType = pScene->GetObjType();
				if (objType == OBJTYPE_ENEMY)
				{
					// 座標やサイズの受け取り
					m_Getpos = ((CScene2D*)pScene)->GetPosition();
					m_fGetSizeX = ((CScene2D*)pScene)->GetSizeX();
					m_fGetSizeY = ((CScene2D*)pScene)->GetSizeY();
					if (m_Getpos.y + m_fGetSizeY >= 0)
					{
						// 当たり判定
						if (m_pos.x - (BOMBEXPLOSION_SIZE_X / 2) <= m_Getpos.x + (m_fGetSizeX / 2) &&
							m_pos.x + (BOMBEXPLOSION_SIZE_X / 2) >= m_Getpos.x - (m_fGetSizeX / 2) &&
							m_pos.y - (BOMBEXPLOSION_SIZE_Y / 2) <= m_Getpos.y + (m_fGetSizeY / 2) &&
							m_pos.y + (BOMBEXPLOSION_SIZE_Y / 2) >= m_Getpos.y - (m_fGetSizeY / 2))
						{
							// 敵のダメージ
							((CEnemy*)pScene)->EnemyDamage(100, CEnemy::DAMAGE_TYPE_BULLET, CBullet::BULLET_TYPE_PLAYER2);
							break;
						}
					}
				}
			}
		}
		break;

	default:
		break;
	}

	// 体力が0以下になったら終了
	if (m_nLife <= 0)
	{
		Uninit();
	}
}

//=============================================================================
// ボムの爆発クラスの描画処理
//=============================================================================
void CBombexplosion::Draw(void)
{
	// CScene2Dの描画処理
	CScene2D::Draw();
}

