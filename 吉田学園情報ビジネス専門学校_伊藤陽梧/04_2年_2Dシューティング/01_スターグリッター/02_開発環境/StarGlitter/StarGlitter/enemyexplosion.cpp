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

//=============================================================================
// マクロ定義
//=============================================================================
#define EXPLOSION_ANIMATION_COUNT (6)	// 爆発のアニメーションのカウント(横のテクスチャの分割数)
#define EXPLOSION_ANIMATION_PATTERN (1) // 爆発のアニメーションのパターン(縦のテクスチャの分割数)
#define EXPLOSION_ANIMATION_TIME (10) // 爆発のアニメーションの時間
#define EXPLOSION_SIZE_X (100.0f)			// 爆発の縦の長さ
#define EXPLOSION_SIZE_Y (100.0f)			// 爆発の横の長さ

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
	m_Getpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fSizeX = 0.0f;
	m_fSizeY = 0.0f;
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
CEnemyexplosion* CEnemyexplosion::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, EXPLOSIONTYPE ExplosionType, EXPLOSIONTEXTURE ExplosionTexture, OBJTYPE objType)
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
		pEnemyexplosion->SetExplosion(pos, fSizeX, fSizeY, ExplosionType, ExplosionTexture, objType);

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
	m_fSizeX = GetSizeX();
	m_fSizeY = GetSizeY();

	// CScene2Dの更新処理
	CScene2D::Update();

	// サイズの加算
	m_fSizeX++;
	m_fSizeY++;

	switch (m_ExplosionType)
	{
	case EXPLOSIONTYPE_PLAYER:
		for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
		{
			// 敵のシーンの受け取り
			CScene *pScene = GetScene(OBJTYPE_ENEMY, nCntScene);
			if (pScene != NULL)
			{
				// オブジェタイプの受け取り
				OBJTYPE objType = pScene->GetObjType();
				if (objType == OBJTYPE_ENEMY)
				{
					// 座標の受け取り
					m_Getpos = ((CScene2D*)pScene)->GetPosition();

					// 当たり判定
					if (m_pos.x - (m_fSizeX / 2) <= m_Getpos.x + (ENEMY_SIZE_X / 2) &&
						m_pos.x + (m_fSizeX / 2) >= m_Getpos.x - (ENEMY_SIZE_X / 2) &&
						m_pos.y - (m_fSizeY / 2) <= m_Getpos.y + (ENEMY_SIZE_Y / 2) &&
						m_pos.y + (m_fSizeY / 2) >= m_Getpos.y - (ENEMY_SIZE_Y / 2))
					{
						// 敵のダメージ
						((CEnemy*)pScene)->EnemyDamage(5, CEnemy::DAMAGE_TYPE_EXPLOSION, CBullet::BULLET_TYPE_PLAYER);
						break;
					}
				}
			}
		}
		break;

	case EXPLOSIONTYPE_PLAYER2:
		for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
		{
			// 敵のシーンの受け取り
			CScene *pScene = GetScene(OBJTYPE_ENEMY, nCntScene);
			if (pScene != NULL)
			{
				// オブジェタイプの受け取り
				OBJTYPE objType = pScene->GetObjType();
				if (objType == OBJTYPE_ENEMY)
				{
					// 座標の受け取り
					m_Getpos = ((CScene2D*)pScene)->GetPosition();

					// 当たり判定
					if (m_pos.x - (m_fSizeX / 2) <= m_Getpos.x + (PLAYER_SIZE_X / 2) &&
						m_pos.x + (m_fSizeX / 2) >= m_Getpos.x - (PLAYER_SIZE_X / 2) &&
						m_pos.y - (m_fSizeY / 2) <= m_Getpos.y + (PLAYER_SIZE_Y / 2) &&
						m_pos.y + (m_fSizeY / 2) >= m_Getpos.y - (PLAYER_SIZE_Y / 2))
					{
						// 敵のダメージ
						((CEnemy*)pScene)->EnemyDamage(5, CEnemy::DAMAGE_TYPE_EXPLOSION, CBullet::BULLET_TYPE_PLAYER2);
						break;
					}
				}
			}
		}
		break;

	default:
		break;
	}


	// 座標とサイズを渡す
	SetPosition(m_pos);
	SetSize(m_fSizeX, m_fSizeY);
	
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
// 敵の爆発クラスの爆発のタイプを渡す処理
//=============================================================================
CEnemyexplosion::EXPLOSIONTYPE CEnemyexplosion::GetExplosionType(void)
{
	return m_ExplosionType;
}

