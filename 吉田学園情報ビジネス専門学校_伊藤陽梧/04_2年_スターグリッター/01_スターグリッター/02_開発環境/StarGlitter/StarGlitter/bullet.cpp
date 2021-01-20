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
#include "explosion.h"
#include "enemy.h"
#include "life.h"
#include "effect.h"
#include "bossattack.h"
#include "collision.h"

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
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nLife, int nDamage, BULLETTYPE BulletType, CHARGEBULLETTYPE ChargeBulletType, OBJTYPE objType)
{
	// pBulletのポインタ
	CBullet *pBullet = NULL;

	// メモリの確保
	pBullet = new CBullet;

	// pBulletがNULLじゃないとき
	if (pBullet != NULL)
	{
		// 弾のセット
		pBullet->SetBullet(pos, move, size, nLife, nDamage, BulletType, ChargeBulletType, objType);

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
	case BULLET_TYPE_1P:
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
	case BULLET_TYPE_2P:
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

	// 弾を動かす処理
	Move();

	switch (m_BulletType)
	{
		// PLAYER1の弾
	case BULLET_TYPE_1P:
		if (m_ChargeBulletType == CHARGEBULLET_TYPE_NOMAL)
		{
			CEffect::Create(m_pos, m_size + D3DXVECTOR3(5.0f, 5.0f, 0.0f) ,
				10, 255, 100, 100, 255, CEffect::EFFECTTYPE_BULLET, OBJTYPE_EFFECT);
		}

		// 弾の処理
		BulletNomal(BULLET_TYPE_1P);
		// チャージ弾の処理
		BulletCharge(BULLET_TYPE_1P);
		// レーザー弾の処理
		BulletLaser(CPlayer::PLAYER_1P, BULLET_TYPE_1P);

		break;

		// PLAYER2の弾
	case BULLET_TYPE_2P:
		if (m_ChargeBulletType == CHARGEBULLET_TYPE_NOMAL)
		{
			CEffect::Create(m_pos, m_size + D3DXVECTOR3(5.0f, 5.0f, 0.0f),
				10, 100, 255, 255, 255, CEffect::EFFECTTYPE_BULLET, OBJTYPE_EFFECT);
		}

		// 弾の処理
		BulletNomal(BULLET_TYPE_2P);
		// チャージ弾の処理
		BulletCharge(BULLET_TYPE_2P);
		// レーザー弾の処理
		BulletLaser(CPlayer::PLAYER_2P, BULLET_TYPE_2P);
		break;

		// ボスの弾
	case BULLET_TYPE_BOSS:
		// ボスのレーザー弾の処理
		BulletBossLaser();
		break;

	default:
		break;
	}

	// 座標とサイズ、体力を渡す
	SetPosition(m_pos);
	SetSize(m_size);
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
// バレットクラスの弾を動かす処理
//=============================================================================
void CBullet::Move(void)
{
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
	if (m_pos.y + m_size.y <= 0.0f)
	{
		Uninit();
		return;
	}
}

//=============================================================================
// バレットクラスの弾の処理
// BulletType：誰が撃った弾なのか
//=============================================================================
void CBullet::BulletNomal(BULLETTYPE BulletType)
{
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
				// チャージ弾のタイプが普通の弾の時
				if (m_ChargeBulletType == CHARGEBULLET_TYPE_NOMAL)
				{
					// 当たり判定
					if (CCollision::PRectangleCollision(m_pos, m_size, pScene) == true)
					{
						// 敵のダメージ
						((CEnemy*)pScene)->EnemyDamage(m_nDamage, CEnemy::DAMAGE_TYPE_BULLET, BulletType);

						// 爆発の生成
						CExplosion::Create(m_pos, D3DXVECTOR3(EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y, 0.0f),
							CExplosion::EXPLOSIONTYPE_NOMAL, CScene::OBJTYPE_EXPLOSION);

						// 終了処理
						Uninit();
						return;
					}
				}
			}
			pScene = pScene->GetSceneNext();
		}
	} while (pScene != NULL);
}

//=============================================================================
// バレットクラスのチャージ弾の処理
// BulletType：誰が撃った弾なのか
//=============================================================================
void CBullet::BulletCharge(BULLETTYPE BulletType)
{
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
				// チャージ弾のタイプがチャージした弾の時
				if (m_ChargeBulletType == CHARGEBULLET_TYPE_CHARGE)
				{
					// 当たり判定
					if (CCollision::PRectangleCollision(m_pos, m_size, pScene) == true)
					{
						// 敵のダメージ
						((CEnemy*)pScene)->EnemyDamage(m_nDamage, CEnemy::DAMAGE_TYPE_BULLET, BulletType);

						// 爆発の生成
						CExplosion::Create(m_pos, D3DXVECTOR3(EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y, 0.0f),
							CExplosion::EXPLOSIONTYPE_NOMAL, CScene::OBJTYPE_EXPLOSION);
					}
				}
			}
			pScene = pScene->GetSceneNext();
		}
	} while (pScene != NULL);
}

//=============================================================================
// バレットクラスのレーザー弾の処理
// PlayerNum：誰が撃った弾なのか
//=============================================================================
void CBullet::BulletLaser(CPlayer::PLAYERNUM PlayerNum, BULLETTYPE BulletType)
{
	// チャージ弾のタイプがレーザー弾の時
	if (m_ChargeBulletType == CHARGEBULLET_TYPE_LASER)
	{
		// PLAYERのシーンの受け取り
		CScene *pScene = CScene::GetSceneTop(CScene::OBJTYPE_PLAYER);
		do
		{
			if (pScene != NULL)
			{
				// オブジェタイプの受け取り
				OBJTYPE objType = pScene->GetObjType();
				if (objType == OBJTYPE_PLAYER)
				{
					if (((CPlayer*)pScene)->GetPlayerNum() == PlayerNum)
					{
						// 座標の受け取りと代入
						m_pos = ((CScene2D*)pScene)->GetPosition();

						// LASERBULLET_SIZE_Y分縦の座標を下げる
						m_pos.y = m_pos.y - (LASERBULLET_SIZE_Y / 2);
					}
				}
				pScene = pScene->GetSceneNext();
			}
		} while (pScene != NULL);

		// 敵のシーンの受け取り
		pScene = CScene::GetSceneTop(CScene::OBJTYPE_ENEMY);
		do
		{
			if (pScene != NULL)
			{
				// オブジェタイプの受け取り
				OBJTYPE objType = pScene->GetObjType();
				if (objType == OBJTYPE_ENEMY)
				{
					// チャージ弾のタイプがチャージした弾の時
					if (m_ChargeBulletType == CHARGEBULLET_TYPE_LASER)
					{
						// 当たり判定
						if (CCollision::PRectangleCollision(m_pos, m_size, pScene) == true)
						{
							// 敵のダメージ
							((CEnemy*)pScene)->EnemyDamage(m_nDamage, CEnemy::DAMAGE_TYPE_BULLET, BulletType);

							// 爆発の生成
							CExplosion::Create(m_pos, D3DXVECTOR3(EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y, 0.0f),
								CExplosion::EXPLOSIONTYPE_NOMAL, CScene::OBJTYPE_EXPLOSION);
						}
					}
				}
				pScene = pScene->GetSceneNext();
			}
		} while (pScene != NULL);
	}
}

//=============================================================================
// バレットクラスのボスのレーザー弾の処理
//=============================================================================
void CBullet::BulletBossLaser(void)
{
	if (m_ChargeBulletType == CHARGEBULLET_TYPE_NOMAL)
	{
		// エフェクトの生成
		CEffect::Create(m_pos, m_size + D3DXVECTOR3(5.0f, 5.0f, 0.0f),
			10, 100, 255, 255, 255, CEffect::EFFECTTYPE_BULLET, OBJTYPE_EFFECT);

		// 画面外に出た時
		if (m_pos.y + m_size.y <= 0.0f || m_pos.x - m_size.x <= SCREEN_CENTER_X)
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


