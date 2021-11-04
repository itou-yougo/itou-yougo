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
#include "collision.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define BOMBEXPLOSION_ANIMATION_COUNT (10)	// 爆発のアニメーションのカウント(横のテクスチャの分割数)
#define BOMBEXPLOSION_ANIMATION_PATTERN (2) // 爆発のアニメーションのパターン(縦のテクスチャの分割数)
#define BOMBEXPLOSION_SIZE_X (745.0f)			// 爆発の縦の長さ
#define BOMBEXPLOSION_SIZE_Y (1080.0f)			// 爆発の横の長さ

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
		pBombExplosion->SetBombexplosion(pos, nLife, bombexplosiontype, objType);

		// サイズのセット
		pBombExplosion->SetSize(D3DXVECTOR3(BOMBEXPLOSION_SIZE_X, BOMBEXPLOSION_SIZE_Y, 0.0f));

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

	// 敵のシーンの受け取り
	CScene *pScene = CScene::GetSceneTop(CScene::OBJTYPE_ENEMY);

	do
	{
		if (pScene != NULL)
		{
			// オブジェタイプの受け取り
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_ENEMY)
			{
				switch (m_BombExplosionType)
				{
					// プレイヤー1のボムの爆発
				case BOMBEXPLOSION_PLAYER:

					// 当たり判定
					if (CCollision::PRectangleCollision(m_pos, D3DXVECTOR3(BOMBEXPLOSION_SIZE_X, BOMBEXPLOSION_SIZE_Y, 0.0f), pScene) == true)
					{
						// 敵のダメージ
						((CEnemy*)pScene)->EnemyDamage(100, CEnemy::DAMAGE_TYPE_BULLET, CBullet::BULLET_TYPE_1P);
						break;
					}
					break;

					// プレイヤー2のボムの爆発
				case BOMBEXPLOSION_PLAYER2:

					// 当たり判定
					if (CCollision::PRectangleCollision(m_pos, D3DXVECTOR3(BOMBEXPLOSION_SIZE_X, BOMBEXPLOSION_SIZE_Y, 0.0f), pScene) == true)
					{
						// 敵のダメージ
						((CEnemy*)pScene)->EnemyDamage(100, CEnemy::DAMAGE_TYPE_BULLET, CBullet::BULLET_TYPE_2P);
						break;
					}
					break;

				default:
					break;
				}
			}
			pScene = pScene->GetSceneNext();
		}
	} while (pScene != NULL);

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