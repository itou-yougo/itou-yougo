//=============================================================================
//
// 弾の処理 [bullet.cpp]
// Author : 伊藤陽梧
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "bullet.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "player2.h"
#include "explosion.h"
#include "enemy.h"
#include "life.h"
#include "effect.h"
#include "bossattack.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define EXPLOSION_SIZE_X (75.0f)			// 爆発の縦の長さ
#define EXPLOSION_SIZE_Y (75.0f)			// 爆発の横の長さ

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CBullet::m_apTexture[MAX_BULLET_TEXTURE] = {};

//=============================================================================
// バレットクラスのコンストラクタ
//=============================================================================
CBullet::CBullet() :CScene2D(OBJTYPE_BULLET)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Getpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fSizeX = 0.0f;
	m_fSizeY = 0.0f;
	m_fGetSizeX = 0.0f;
	m_fGetSizeY = 0.0f;
	m_nLife = 0;
	m_nGetLife = 0;
	m_nDamage = 0;
	m_BulletType = BULLET_TYPE_NONE;
}

//=============================================================================
// バレットクラスのデストラクタ
//=============================================================================
CBullet::~CBullet()
{

}

//=============================================================================
// バレットクラスのテクスチャの読み込み
//=============================================================================
HRESULT CBullet::Load(void)
{
	// インスタンス生成したものを受け取る
	CRenderer *pRenderer = CManager::GetRenderer();

	// デバイスを受け取る
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BULLET, &m_apTexture[CHARGEBULLET_TYPE_NONE]);				// なし
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BULLET, &m_apTexture[CHARGEBULLET_TYPE_NOMAL]);				// 普通の弾
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BULLETCHARGE, &m_apTexture[CHARGEBULLET_TYPE_CHARGE]);		// チャージした弾
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BULLETLASER, &m_apTexture[CHARGEBULLET_TYPE_LASER]);			// レーザー弾
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BULLETBOSSLASER, &m_apTexture[CHARGEBULLET_TYPE_BOSSLASER]); // ボスのレーザー弾

	return S_OK;
}

//=============================================================================
// バレットクラスのテクスチャの破棄
//=============================================================================
void CBullet::Unload(void)
{
	for (int nCount = 0; nCount < MAX_BULLET_TEXTURE; nCount++)
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
// バレットクラスのインスタンス生成
//=============================================================================
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fSizeX, float fSizeY, int nLife, int nDamage, BULLETTYPE BulletType, CHARGEBULLETTYPE ChargeBulletType, OBJTYPE objType)
{
	// pBulletのポインタ
	CBullet *pBullet = NULL;

	// メモリの確保
	pBullet = new CBullet;

	// pBulletがNULLじゃないとき
	if (pBullet != NULL)
	{
		// 弾のセット
		pBullet->SetBullet(pos, move, fSizeX, fSizeY, nLife, nDamage, BulletType, ChargeBulletType, objType);

		// 初期化処理
		pBullet->Init();
	}

	// pBulletを返す
	return pBullet;
}

//=============================================================================
// バレットクラスの初期化処理
//=============================================================================
HRESULT CBullet::Init()
{
	// CScene2Dの初期化処理
	CScene2D::Init();

	// テクスチャの設定
	BindTexture(m_apTexture[m_ChargeBulletType]);

	switch (m_BulletType)
	{
		// PLAYER1の弾
	case BULLET_TYPE_PLAYER:
		// 普通の弾
		if (m_ChargeBulletType == CHARGEBULLET_TYPE_NOMAL)
		{
			// 色のセット
			SetColor(255, 0, 0, 255);
		}
		// チャージした弾
		if (m_ChargeBulletType == CHARGEBULLET_TYPE_CHARGE)
		{
			// アニメーションのセット
			SetAnimation(2, 1, 4);
		}
		break;

		// PLAYER2の弾
	case BULLET_TYPE_PLAYER2:
		// 普通の弾
		if (m_ChargeBulletType == CHARGEBULLET_TYPE_NOMAL)
		{
			// 色のセット
			SetColor(0, 0, 255, 255);
		}
		// チャージした弾
		if (m_ChargeBulletType == CHARGEBULLET_TYPE_LASER)
		{
			// アニメーションのセット
			SetAnimation(2, 1, 4);
		}
		break;

		// ボスの弾
	case BULLET_TYPE_BOSS:
		// 普通の弾
		if (m_ChargeBulletType == CHARGEBULLET_TYPE_NOMAL)
		{
			// 色のセット
			SetColor(255, 0, 0, 255);
		}
		// ボスのレーザー弾
		if (m_ChargeBulletType == CHARGEBULLET_TYPE_BOSSLASER)
		{
			// アニメーションのセット
			SetAnimation(2, 1, 4);
		}
		break;

	default:
		break;
	}

	
	return S_OK;   
}

//=============================================================================
// バレットクラスの終了処理
//=============================================================================
void CBullet::Uninit(void)
{
	// CScene2Dの終了処理
	CScene2D::Uninit();
}

//=============================================================================
// バレットクラスの更新処理
//=============================================================================
void CBullet::Update(void)
{
	// CScene2Dの更新処理
	CScene2D::Update();

	switch (m_BulletType)
	{
		// PLAYER1の弾
	case BULLET_TYPE_PLAYER:
		if (m_ChargeBulletType == CHARGEBULLET_TYPE_NOMAL)
		{
			CEffect::Create(m_pos, m_fSizeX + 5.0f, m_fSizeY + 5.0f, 10, 255, 100, 100, 255, CEffect::EFFECTTYPE_BULLET, OBJTYPE_EFFECT);
		}

		// 座標と体力の受け取り
		m_pos = GetPosition();

		// 移動量の加算
		m_pos += m_move;
		m_nLife--;

		// 体力がなくなったとき
		if (m_nLife <= 0)
		{
			Uninit();
			return;
		}

		// 画面外に出た時
		if (m_pos.y + m_fSizeY <= 0.0f)
		{
			Uninit();
			return;
		}

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
					// 座標やサイズの受け取り
					m_Getpos = ((CScene2D*)pScene)->GetPosition();
					m_fGetSizeX = ((CScene2D*)pScene)->GetSizeX();
					m_fGetSizeY = ((CScene2D*)pScene)->GetSizeY();
					if (m_Getpos.y + m_fGetSizeY >= 0)
					{
						// チャージ弾のタイプが普通の弾の時
						if (m_ChargeBulletType == CHARGEBULLET_TYPE_NOMAL)
						{
							// 当たり判定
							if (m_pos.x - (m_fSizeX / 2) <= m_Getpos.x + (ENEMY_SIZE_X / 2) &&
								m_pos.x + (m_fSizeX / 2) >= m_Getpos.x - (ENEMY_SIZE_X / 2) &&
								m_pos.y - (m_fSizeY / 2) <= m_Getpos.y + (ENEMY_SIZE_Y / 2) &&
								m_pos.y + (m_fSizeY / 2) >= m_Getpos.y - (ENEMY_SIZE_Y / 2))
							{
								// 敵のダメージ
								((CEnemy*)pScene)->EnemyDamage(m_nDamage, CEnemy::DAMAGE_TYPE_BULLET, BULLET_TYPE_PLAYER);

								// 爆発の生成
								CExplosion::Create(m_pos, EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y, CExplosion::EXPLOSIONTYPE_NOMAL, CScene::OBJTYPE_EXPLOSION);

								// 終了処理
								Uninit();
								break;
							}
						}
						// チャージ弾のタイプがチャージした弾の時
						if (m_ChargeBulletType == CHARGEBULLET_TYPE_CHARGE)
						{
							// 当たり判定
							if (m_pos.x - (m_fSizeX / 2) <= m_Getpos.x + (ENEMY_SIZE_X / 2) &&
								m_pos.x + (m_fSizeX / 2) >= m_Getpos.x - (ENEMY_SIZE_X / 2) &&
								m_pos.y - (m_fSizeY / 2) <= m_Getpos.y + (ENEMY_SIZE_Y / 2) &&
								m_pos.y + (m_fSizeY / 2) >= m_Getpos.y - (ENEMY_SIZE_Y / 2))
							{
								// 敵のダメージ
								((CEnemy*)pScene)->EnemyDamage(m_nDamage, CEnemy::DAMAGE_TYPE_BULLET, BULLET_TYPE_PLAYER);

								// 爆発の生成
								CExplosion::Create(m_pos, EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y, CExplosion::EXPLOSIONTYPE_NOMAL, CScene::OBJTYPE_EXPLOSION);
								break;
							}
						}
					}
				}
			}
		}

		// 座標とサイズ、体力を渡す
		SetPosition(m_pos);
		SetSize(m_fSizeX, m_fSizeY);
		break;

		// PLAYER2の弾
	case BULLET_TYPE_PLAYER2:
		if (m_ChargeBulletType == CHARGEBULLET_TYPE_NOMAL)
		{
			CEffect::Create(m_pos, m_fSizeX + 5.0f, m_fSizeY + 5.0f, 10, 100, 255, 255, 255, CEffect::EFFECTTYPE_BULLET, OBJTYPE_EFFECT);
		}

		// 座標と体力の受け取り
		m_pos = GetPosition();

		// 移動量の加算
		m_pos += m_move;
		m_nLife--;

		// 体力がなくなったとき
		if (m_nLife <= 0)
		{
			Uninit();
			return;
		}

		// 画面外に出た時
		if (m_pos.y + m_fSizeY <= 0.0f)
		{
			Uninit();
			return;
		}

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
					// 座標やサイズの受け取り
					m_Getpos = ((CScene2D*)pScene)->GetPosition();
					m_fGetSizeX = ((CScene2D*)pScene)->GetSizeX();
					m_fGetSizeY = ((CScene2D*)pScene)->GetSizeY();
					if (m_Getpos.y + m_fGetSizeY >= 0)
					{
						// チャージ弾のタイプが普通の弾の時
						if (m_ChargeBulletType == CHARGEBULLET_TYPE_NOMAL)
						{
							if (m_pos.x - (m_fSizeX / 2) <= m_Getpos.x + (m_fGetSizeX / 2) &&
								m_pos.x + (m_fSizeX / 2) >= m_Getpos.x - (m_fGetSizeX / 2) &&
								m_pos.y - (m_fSizeY / 2) <= m_Getpos.y + (m_fGetSizeY / 2) &&
								m_pos.y + (m_fSizeY / 2) >= m_Getpos.y - (m_fGetSizeY / 2))
							{
								// 敵のダメージ
								((CEnemy*)pScene)->EnemyDamage(m_nDamage, CEnemy::DAMAGE_TYPE_BULLET, BULLET_TYPE_PLAYER2);

								// 爆発の生成
								CExplosion::Create(m_pos, EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y, CExplosion::EXPLOSIONTYPE_NOMAL, CScene::OBJTYPE_EXPLOSION);

								// 終了処理
								Uninit();
								break;
							}
						}
						// チャージ弾のタイプがレーザー弾の時
						if (m_ChargeBulletType == CHARGEBULLET_TYPE_LASER)
						{
							if (m_pos.x - (m_fSizeX / 2) <= m_Getpos.x + (m_fGetSizeX / 2) &&
								m_pos.x + (m_fSizeX / 2) >= m_Getpos.x - (m_fGetSizeX / 2) &&
								m_pos.y - (m_fSizeY / 2) <= m_Getpos.y + (m_fGetSizeY / 2) &&
								m_pos.y + (m_fSizeY / 2) >= m_Getpos.y - (m_fGetSizeY / 2))
							{
								// 敵のダメージ
								((CEnemy*)pScene)->EnemyDamage(m_nDamage, CEnemy::DAMAGE_TYPE_BULLET, BULLET_TYPE_PLAYER2);

								// 爆発の生成
								CExplosion::Create(m_pos, EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y, CExplosion::EXPLOSIONTYPE_NOMAL, CScene::OBJTYPE_EXPLOSION);
								break;
							}
						}
					}
				}
			}

			// チャージ弾のタイプがレーザー弾の時
			if (m_ChargeBulletType == CHARGEBULLET_TYPE_LASER)
			{
				// PLAYER2のシーンの受け取り
				pScene = GetScene(OBJTYPE_PLAYER2, nCntScene);
				if (pScene != NULL)
				{
					// オブジェタイプの受け取り
					OBJTYPE objType = pScene->GetObjType();
					if (objType == OBJTYPE_PLAYER2)
					{
						// 座標の受け取りと代入
						m_pos = ((CScene2D*)pScene)->GetPosition();

						// LASERBULLET_SIZE_Y分縦の座標を下げる
						m_pos.y = m_pos.y - (LASERBULLET_SIZE_Y / 2);
					}
				}
			}
		}

		// 座標とサイズ、体力を渡す
		SetPosition(m_pos);
		SetSize(m_fSizeX, m_fSizeY);
		break;

		// ボスの弾
	case BULLET_TYPE_BOSS:
		if (m_ChargeBulletType == CHARGEBULLET_TYPE_NOMAL)
		{
			// エフェクトの生成
			CEffect::Create(m_pos, m_fSizeX + 5.0f, m_fSizeY + 5.0f, 10, 100, 255, 255, 255, CEffect::EFFECTTYPE_BULLET, OBJTYPE_EFFECT);

			// 画面外に出た時
			if (m_pos.y + m_fSizeY <= 0.0f || m_pos.x - m_fSizeX <= SCREEN_CENTER_X)
			{
				// 終了処理
				Uninit();
				return;
			}
		}

		// 座標と体力の受け取り
		m_pos = GetPosition();

		// 移動量の加算
		m_pos += m_move;
		m_nLife--;

		// 体力がなくなったとき
		if (m_nLife <= 0)
		{
			Uninit();
			return;
		}

		// 座標とサイズ、体力を渡す
		SetPosition(m_pos);
		SetSize(m_fSizeX, m_fSizeY);
		break;

	default:
		break;
	}
	
}

//=============================================================================
// バレットクラスの描画処理
//=============================================================================
void CBullet::Draw(void)
{
	// CScene2Dの描画処理
	CScene2D::Draw();
}

//=============================================================================
// バレットクラスの弾のタイプを渡す処理
//=============================================================================
CBullet::BULLETTYPE CBullet::GetBulletType(void)
{
	return m_BulletType;
}

//=============================================================================
// バレットクラスのチャージ弾のタイプを渡す処理
//=============================================================================
CBullet::CHARGEBULLETTYPE CBullet::GetChargeBulletType(void)
{
	return m_ChargeBulletType;
}


