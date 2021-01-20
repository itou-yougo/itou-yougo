//=============================================================================
//
// 敵の処理 [enemy.h]
// Author : 伊藤陽梧
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "enemy.h"
#include "renderer.h"
#include "manager.h"
#include "bullet.h"
#include "sound.h"
#include "enemyexplosion.h"
#include "ojama.h"
#include "chargeshot.h"
#include "gauge.h"
#include "player.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CEnemy::m_pTexture = NULL;

//=============================================================================
// エネミークラスのコンストラクタ
//=============================================================================
CEnemy::CEnemy() :CScene2D(OBJTYPE_ENEMY)
{
	m_pGauge = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_nOjamaCount = 0;
	m_DamageType = DAMAGE_TYPE_NONE;
}

//=============================================================================
// エネミークラスのデストラクタ
//=============================================================================
CEnemy::~CEnemy()
{

}

//=============================================================================
// エネミークラスのテクスチャの読み込み
//=============================================================================
HRESULT CEnemy::Load(void)
{
	// インスタンス生成したものを受け取る
	CRenderer *pRenderer = CManager::GetRenderer();

	// デバイスを受け取る
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_ENEMY1, &m_pTexture);

	return S_OK;
}

//=============================================================================
// エネミークラスのテクスチャの破棄
//=============================================================================
void CEnemy::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// エネミークラスのインスタンス生成
//=============================================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nLife, OBJTYPE objType)
{
	// CEnemyのポインタ
	CEnemy *pEnemy = NULL;

	// メモリの確保
	pEnemy = new CEnemy;

	// pEnemyがNULLじゃないとき
	if (pEnemy != NULL)
	{
		// 敵の設定
		pEnemy->SetEnemy(pos, move, size, nLife, objType);

		// 初期化処理
		pEnemy->Init();
	}

	// pEnemyを返す
	return pEnemy;
}

//=============================================================================
// エネミークラスの初期化処理
//=============================================================================
HRESULT CEnemy::Init()
{
	//m_pBarrier = CBarrier::Create(m_pos, BARRIER_SIZE_X, BARRIER_SIZE_Y, 1, CBarrier::BARRIER_TYPE_BRUE, OBJTYPE_BARRIER);

	// CScene2Dの初期化処理
	CScene2D::Init();

	// テクスチャの設定
	BindTexture(m_pTexture);

	// アニメーションのセット
	SetAnimationSelect(3, 5, m_nLife - 1, 5);

	srand((unsigned int)time(NULL));

	return S_OK;
}

//=============================================================================
// エネミークラスの終了処理
//=============================================================================
void CEnemy::Uninit(void)
{
	// CScene2Dの終了処理
	CScene2D::Uninit();
}

//=============================================================================
// エネミークラスの更新処理
//=============================================================================
void CEnemy::Update(void)
{
	// CScene2Dの更新処理
	CScene2D::Update();

	// CInputのポインタのインスタンス生成の受け取り
	CInputKeyboard *pInput = CManager::GetInputKeyboard();

	// 座標と体力を受け取る
	m_pos = GetPosition();

	m_pos += m_move;

	// 倒されたときの処理
	Death();

	// 座標とサイズ、体力を渡す
	SetPosition(m_pos);
	SetSize(m_size);

	// 移動できる範囲の制限
	if (m_pos.y > SCREEN_HEIGHT + (ENEMY_SIZE_X / 2))
	{
		Uninit();
		return;
	}
}

//=============================================================================
// エネミークラスの描画処理
//=============================================================================
void CEnemy::Draw(void)
{
	// CScene2Dの描画処理
	CScene2D::Draw();
}

//=============================================================================
// エネミークラスの倒されたときの処理
//=============================================================================
void CEnemy::Death(void)
{
	// 体力が0以下になったとき
	if (m_nLife <= 0)
	{
		// おじゃまを作る処理
		OjamanCreate();

		// ゲージの最大値を伸ばす処理
		GaugeUp();

		// 終了処理
		Uninit();
		return;
	}
}

//=============================================================================
// エネミークラスのおじゃまを作る処理
//=============================================================================
void CEnemy::OjamanCreate(void)
{
	// 爆発のダメージで死んだとき
	if (m_DamageType == DAMAGE_TYPE_EXPLOSION)
	{
		// どっちのプレイヤーの攻撃か判別してランダムでおじゃまを出す
		switch (m_BulletType)
		{
			// PLAYER1の弾
		case CBullet::BULLET_TYPE_1P:
			switch (rand() % 3)
			{
			case 0:
				COjama::Create(m_pos, D3DXVECTOR3(-10.0f, -10.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f),
					0, D3DXVECTOR3(2.0f, 2.0f, 0.0f), COjama::OJAMA_TYPE_THROUGH, COjama::OJAMAPLAYER_1P, OBJTYPE_OJAMA);
				break;

			case 1:
				COjama::Create(m_pos, D3DXVECTOR3(10.0f, -10.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), 0,
					D3DXVECTOR3((float)(rand() % 3) + 2.0f, -2.0f, 0.0f), COjama::OJAMA_TYPE_CURVE, COjama::OJAMAPLAYER_1P, OBJTYPE_OJAMA);
				break;

			case 2:
				COjama::Create(m_pos, D3DXVECTOR3((float)(rand() % 10) - 15.0f, (float)(rand() % 10) - 15.0f, 0.0f),
					D3DXVECTOR3(50.0f, 50.0f, 0.0f), 0, D3DXVECTOR3((float)(rand() % 5) + 5.0f, 5.0f, 0.0f),
					COjama::OJAMA_TYPE_FALL, COjama::OJAMAPLAYER_1P, OBJTYPE_OJAMA);
				break;

			default:
				break;
			}

			// 敵の爆発を出す処理
			EnemyExplosionCreate(CEnemyexplosion::EXPLOSIONTEXTURE_2);
			break;

			// PLAYER2の弾
		case CBullet::BULLET_TYPE_2P:
			switch (rand() % 3)
			{
			case 0:
				COjama::Create(m_pos, D3DXVECTOR3(-10.0f, -10.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), 0,
					D3DXVECTOR3(2.0f, 2.0f, 0.0f), COjama::OJAMA_TYPE_THROUGH, COjama::OJAMAPLAYER_2P, OBJTYPE_OJAMA);
				break;

			case 1:
				COjama::Create(m_pos, D3DXVECTOR3(-10.0f, -10.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), 0,
					D3DXVECTOR3(-(float)(rand() % 3) - 2.0f, -2.0f, 0.0f), COjama::OJAMA_TYPE_CURVE, COjama::OJAMAPLAYER_2P, OBJTYPE_OJAMA);
				break;

			case 2:
				COjama::Create(m_pos, D3DXVECTOR3(-(float)(rand() % 10) + 15.0f, -(float)(rand() % 10) + 15.0f, 0.0f),
					D3DXVECTOR3(50.0f, 50.0f, 0.0f), 0, D3DXVECTOR3(-(float)(rand() % 5) - 5.0f, 5.0f, 0.0f),
					COjama::OJAMA_TYPE_FALL, COjama::OJAMAPLAYER_2P, OBJTYPE_OJAMA);
				break;
			default:
				break;
			}

			// 敵の爆発を出す処理
			EnemyExplosionCreate(CEnemyexplosion::EXPLOSIONTEXTURE_2);
			break;

		default:
			break;
		}
	}
	else
	{
		// 敵の爆発を出す処理
		EnemyExplosionCreate(CEnemyexplosion::EXPLOSIONTEXTURE_1);
	}
}

//=============================================================================
// エネミークラスの敵の爆発を出す処理
// ExplosionTexture：テクスチャの番号
//=============================================================================
void CEnemy::EnemyExplosionCreate(CEnemyexplosion::EXPLOSIONTEXTURE ExplosionTexture)
{
	// どっちのプレイヤーの攻撃か判別して爆発を起こす
	switch (m_BulletType)
	{
		// PLAYER1の弾
	case CBullet::BULLET_TYPE_1P:
		// 敵の爆発の生成
		CEnemyexplosion::Create(m_pos, D3DXVECTOR3(100.0f, 100.0f, 0.0f), CEnemyexplosion::EXPLOSIONTYPE_PLAYER,
			ExplosionTexture, OBJTYPE_ENEMYEXPLOSION);
		break;

		// PLAYER2の弾
	case CBullet::BULLET_TYPE_2P:
		// 敵の爆発の生成
		CEnemyexplosion::Create(m_pos, D3DXVECTOR3(100.0f, 100.0f, 0.0f), CEnemyexplosion::EXPLOSIONTYPE_PLAYER2,
			ExplosionTexture, OBJTYPE_ENEMYEXPLOSION);
		break;
	}
}

//=============================================================================
// エネミークラスのゲージの最大値を伸ばす処理
//=============================================================================
void CEnemy::GaugeUp(void)
{
	// プレイヤーのシーンを受け取る
	CScene *pScene = CScene::GetSceneTop(CScene::OBJTYPE_PLAYER);
	do
	{
		if (pScene != NULL)
		{
			// オブジェクトの受け取り
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_PLAYER)
			{
				switch (m_BulletType)
				{
					// プレイヤー1のこうげきで倒されたら
				case CBullet::BULLET_TYPE_1P:
					if (((CPlayer*)pScene)->GetPlayerNum() == CPlayer::PLAYER_1P)
					{
						// PLAYERのチャージショットのゲージの最大値を伸ばす
						((((CPlayer*)pScene)->GetChargeShot())->GetGauge())->SetExtend(5.0f, 0.0f);
					}
					break;

					// プレイヤー2のこうげきで倒されたら
				case CBullet::BULLET_TYPE_2P:
					if (((CPlayer*)pScene)->GetPlayerNum() == CPlayer::PLAYER_2P)
					{
						// PLAYER2のチャージショットのゲージの最大値を伸ばす
						((((CPlayer*)pScene)->GetChargeShot())->GetGauge())->SetExtend(5.0f, 0.0f);
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
// エネミークラスのダメージの処理
//=============================================================================
void CEnemy::EnemyDamage(int nDamage, DAMAGETYPE DamageType, CBullet::BULLETTYPE BulletType)
{
	// ダメージと弾のタイプを受け取る
	m_DamageType = DamageType;
	m_BulletType = BulletType;

	// nDamage分ライフを減らす
	m_nLife = m_nLife - nDamage;

	// アニメーションのセット
	SetAnimationSelect(3, 5, m_nLife - 1, 5);
}