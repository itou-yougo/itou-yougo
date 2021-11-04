//=============================================================================
//
// 敵の爆発の処理 [enemyexplosion.h]
// Author : 伊藤陽梧
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "enemyexplosion.h"
#include "renderer.h"
#include "manager.h"
#include "enemy.h"
#include "sound.h"
#include "bullet.h"
#include "collision.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define EXPLOSION_ANIMATION_COUNT (6)	// 爆発のアニメーションのカウント(横のテクスチャの分割数)
#define EXPLOSION_ANIMATION_PATTERN (1) // 爆発のアニメーションのパターン(縦のテクスチャの分割数)
#define EXPLOSION_ANIMATION_TIME (10) // 爆発のアニメーションの時間
#define EXPLOSION_SIZE_X (100.0f)			// 爆発の縦の長さ
#define EXPLOSION_SIZE_Y (100.0f)			// 爆発の横の長さ

#define ENEMY_DAMAGE (5)

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CEnemyexplosion::m_apTexture[MAX_ENEMYEXPLOSION_TEXTURE] = {};

//=============================================================================
// 敵の爆発クラスのコンストラクタ
//=============================================================================
CEnemyexplosion::CEnemyexplosion() :CScene2D(OBJTYPE_ENEMYEXPLOSION)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	m_nTimeAnim = EXPLOSION_ANIMATION_TIME;
	m_ExplosionType = EXPLOSIONTYPE_NONE;
	m_ExplosionTexture = EXPLOSIONTEXTURE_1;
}

//=============================================================================
// 敵の爆発クラスのデストラクタ
//=============================================================================
CEnemyexplosion::~CEnemyexplosion()
{

}

//=============================================================================
// 敵の爆発クラスのテクスチャの読み込み
//=============================================================================
HRESULT CEnemyexplosion::Load(void)
{
	// インスタンス生成したものを受け取る
	CRenderer *pRenderer = CManager::GetRenderer();

	// デバイスを受け取る
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_ENEMYEXPLOSION1, &m_apTexture[EXPLOSIONTEXTURE_1]); // 弾に当たって倒されたときのテクスチャ
	D3DXCreateTextureFromFile(pDevice, TEXTURE_ENEMYEXPLOSION2, &m_apTexture[EXPLOSIONTEXTURE_2]); // 爆発に当たって倒されたときのテクスチャ

	return S_OK;
}

//=============================================================================
// 敵の爆発クラスのテクスチャの破棄
//=============================================================================
void CEnemyexplosion::Unload(void)
{
	for (int nCount = 0; nCount < MAX_ENEMYEXPLOSION_TEXTURE; nCount++)
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
// 敵の爆発クラスのインスタンス生成
//=============================================================================
CEnemyexplosion* CEnemyexplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, EXPLOSIONTYPE ExplosionType, EXPLOSIONTEXTURE ExplosionTexture, OBJTYPE objType)
{
	// CEnemyexplosionのポインタ
	CEnemyexplosion *pEnemyexplosion = NULL;

	// メモリの確保
	pEnemyexplosion = new CEnemyexplosion;

	CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_EXPLOSION_SE);

	// pEnemyexplosionがNULLじゃないとき
	if (pEnemyexplosion != NULL)
	{
		// 敵の爆発のセット
		pEnemyexplosion->SetExplosion(pos, size, ExplosionType, ExplosionTexture, objType);

		// 初期化処理
		pEnemyexplosion->Init();
	}

	// pEnemyexplosionを返す
	return pEnemyexplosion;
}

//=============================================================================
// 敵の爆発クラスの初期化処理
//=============================================================================
HRESULT CEnemyexplosion::Init()
{
	// CScene2Dの初期化処理
	CScene2D::Init();

	// テクスチャの設定
	BindTexture(m_apTexture[m_ExplosionTexture]);

	// アニメーションのセット
	CScene2D::SetAnimation(EXPLOSION_ANIMATION_COUNT, EXPLOSION_ANIMATION_PATTERN, EXPLOSION_ANIMATION_TIME);

	return S_OK;
}

//=============================================================================
// 敵の爆発クラスの終了処理
//=============================================================================
void CEnemyexplosion::Uninit(void)
{
	// CScene2Dの終了処理
	CScene2D::Uninit();
}

//=============================================================================
// 敵の爆発クラスの更新処理
//=============================================================================
void CEnemyexplosion::Update(void)
{
	// サイズの受け取り
	m_size = GetSize();

	// CScene2Dの更新処理
	CScene2D::Update();

	// サイズの加算
	m_size.x++;
	m_size.y++;

	// 敵に当たったとき
	Hit();

	// 座標とサイズを渡す
	SetPosition(m_pos);
	SetSize(m_size);
	
	// アニメーションが終わったら終了処理
	if (m_nTimeAnim == EXPLOSION_ANIMATION_TIME)
	{
		m_nCounterAnim++;

		if (m_nCounterAnim % EXPLOSION_ANIMATION_COUNT == 0)
		{
			Uninit();
		}
		m_nTimeAnim = 0;
	}
	m_nTimeAnim++;
}

//=============================================================================
// 敵の爆発クラスの描画処理
//=============================================================================
void CEnemyexplosion::Draw(void)
{
	// CScene2Dの描画処理
	CScene2D::Draw();
}

//=============================================================================
// 敵の爆発クラスの当たったときの処理
//=============================================================================
void CEnemyexplosion::Hit(void)
{
	// 敵のシーンを受け取る
	CScene *pScene = CScene::GetSceneTop(CScene::OBJTYPE_ENEMY);
	do
	{
		if (pScene != NULL)
		{
			// オブジェタイプの受け取り
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_ENEMY)
			{
				switch (m_ExplosionType)
				{
				case EXPLOSIONTYPE_PLAYER:
					// 当たり判定
					if (CCollision::PRectangleCollision(m_pos, m_size, pScene) == true)
					{
						// 敵のダメージ
						((CEnemy*)pScene)->EnemyDamage(ENEMY_DAMAGE, CEnemy::DAMAGE_TYPE_EXPLOSION, CBullet::BULLET_TYPE_1P);
					}
					break;

				case EXPLOSIONTYPE_PLAYER2:
					// 当たり判定
					if (CCollision::PRectangleCollision(m_pos, m_size, pScene) == true)
					{
						// 敵のダメージ
						((CEnemy*)pScene)->EnemyDamage(ENEMY_DAMAGE, CEnemy::DAMAGE_TYPE_EXPLOSION, CBullet::BULLET_TYPE_2P);
					}
					break;

				default:
					break;
				}
			}
			pScene = pScene->GetSceneNext();
		}
	} while (pScene != NULL);
}

//=============================================================================
// 敵の爆発クラスの爆発のタイプを渡す処理
//=============================================================================
CEnemyexplosion::EXPLOSIONTYPE CEnemyexplosion::GetExplosionType(void)
{
	return m_ExplosionType;
}

