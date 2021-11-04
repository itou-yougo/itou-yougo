//=============================================================================
//
// ボスアタックの処理 [bossattack.cpp]
// Author : 伊藤陽梧
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "bossattack.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "explosion.h"
#include "enemy.h"
#include "life.h"
#include "effect.h"
#include "bullet.h"
#include "collision.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define EXPLOSION_SIZE_X (100.0f)			// 爆発の縦の長さ
#define EXPLOSION_SIZE_Y (100.0f)			// 爆発の横の長さ

#define BOSSEXPLOSION_SIZE_X (200.0f)			// ボスの爆発の縦の長さ
#define BOSSEXPLOSION_SIZE_Y (200.0f)			// ボスの爆発の横の長さ

#define BOSSCREATEALPHA (100) 
#define BOSSMOVEALPHA (255)
#define BOSS_SIZE_EXTEND (5.0f)
#define BOSS_SPEED (5.0f)

#define BEAM_BOSS_STOPCOUNT (150)
#define BEAM_BOSS_MOVECOUNT (130)
#define BEAM_BOSS_SHOTCOUNT (50)

#define BEAM_POS (D3DXVECTOR3(m_pos.x, m_pos.y + (LASERBULLET_SIZE_Y / 2) + 50.0f, 0.0f))
#define BEAM_LIFE (80)
#define BEAM_DAMAGE (1)

#define BULLET_SPEED (-10.0f)
#define BULLET_LIFE (200)
#define BULLET_DAMAGE (1)
#define BULLET_BOSS_SHOTCOUNT (100)

#define CHARGEHIT_INCREDIBLE_TIME (40)
#define CHARGEHIT_DAMAGE (3)

#define BEAMHIT_INCREDIBLE_TIME (80)
#define BEAMHIT_DAMAGE (3)

#define BULLETHIT_DAMAGE (1)

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CBossattck::m_apTexture[MAX_BOSS_TEXTURE] = {};

//=============================================================================
// ボスアタッククラスのコンストラクタ
//=============================================================================
CBossattck::CBossattck() :CScene2D(OBJTYPE_BOSSATTACK)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, BOSS_SIZE_Y, 0.0f);
	m_nCount = 0;
	m_nInvincibleTime = 0;
	m_nCountBullet = 0;
	m_nCountStop = 0;
	m_nLife = 0;
	m_bStop = false;
	m_Player = BOSSATTCK_PLAYER_NONE;
	m_BossAttack = BOSSATTACK_BEAM;
}

//=============================================================================
// ボスアタッククラスのデストラクタ
//=============================================================================
CBossattck::~CBossattck()
{

}

//=============================================================================
// ボスアタッククラスのテクスチャの読み込み
//=============================================================================
HRESULT CBossattck::Load(void)
{
	// インスタンス生成したものを受け取る
	CRenderer *pRenderer = CManager::GetRenderer();

	// デバイスを受け取る
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BOSSMAHOU, &m_apTexture[BOSSATTACK_BULLET]); // ビームを撃つボスアタック
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BOSSKABOTYA, &m_apTexture[BOSSATTACK_BEAM]);	// たまを撃つボスアタック

	return S_OK;
}

//=============================================================================
// ボスアタッククラスのテクスチャの破棄
//=============================================================================
void CBossattck::Unload(void)
{
	for (int nCount = 0; nCount < BOSSATTACK_MAX; nCount++)
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
// ボスアタッククラスのインスタンス生成
//=============================================================================
CBossattck* CBossattck::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, PLAYER Player, BOSSATTACK BossAttack, OBJTYPE objType)
{
	// CBossattckのポインタ
	CBossattck *pBossattck = NULL;

	// メモリの確保
	pBossattck = new CBossattck;

	// pBossattckがNULLじゃないとき
	if (pBossattck != NULL)
	{
		pBossattck->SetBossAttack(pos, move, nLife, Player, BossAttack, objType);

		// 初期化処理
		pBossattck->Init();
	}

	// pBossattckを返す
 	return pBossattck;
}

//=============================================================================
// ボスアタッククラスの初期化処理
//=============================================================================
HRESULT CBossattck::Init()
{
	// CScene2Dの初期化処理
	CScene2D::Init();

	// テクスチャの設定
	BindTexture(m_apTexture[m_BossAttack]);

	srand((unsigned)time(NULL));

	return S_OK;
}

//=============================================================================
// ボスアタッククラスの終了処理
//=============================================================================
void CBossattck::Uninit(void)
{
	// CScene2Dの終了処理
	CScene2D::Uninit();
}

//=============================================================================
// ボスアタッククラスの更新処理
//=============================================================================
void CBossattck::Update(void)
{
	// CScene2Dの更新処理
	CScene2D::Update();

	// 座標と体力の受け取り
	m_pos = GetPosition();

	//　横のサイズがBOSS_SIZE_Xより小さかったら
	if (m_size.x < BOSS_SIZE_X)
	{
		SetColor(255, 255, 255, BOSSCREATEALPHA);
		m_size.x += BOSS_SIZE_EXTEND;
	}

	//　横のサイズがBOSS_SIZE_Xより大きくなったら
	if (m_size.x >= BOSS_SIZE_X)
	{
		m_size.x = BOSS_SIZE_X;
		SetColor(255, 255, 255, BOSSMOVEALPHA);
		
		// ライフが0より大きかったら
		if (m_nLife > 0)
		{
			switch (m_BossAttack)
			{
				// ビームを撃つボスアタック
			case BOSSATTACK_BEAM:
				BossBeam();
				break;

				// たまを撃つボスアタック
			case BOSSATTACK_BULLET:
				BossBullet();
				break;

			default:
				break;
			}
		}
	}

	// 当たるときの処理
	Hit();

	// ライフが0以下の時
	if (m_nLife <= 0)
	{
		// 移動量の加算
		m_pos.y += BOSS_SPEED;

		// カウントの加算
		m_nCount++;

		// カウントが10の時
		if (m_nCount == 10)
		{
			CExplosion::Create(m_pos + D3DXVECTOR3((float)(rand() % (int)BOSS_SIZE_X) - BOSS_SIZE_X / 2.0f, ((float)(rand() % (int)BOSS_SIZE_Y) - BOSS_SIZE_Y / 2.0f), 0.0f),
				D3DXVECTOR3(BOSSEXPLOSION_SIZE_X, BOSSEXPLOSION_SIZE_Y, 0.0f), CExplosion::EXPLOSIONTYPE_BOSS, CScene::OBJTYPE_EXPLOSION);
			m_nCount = 0;
		}
	}

	// 無敵時間のカウントの減算
	m_nInvincibleTime--;
	if (m_nInvincibleTime < 0)
	{
		m_nInvincibleTime = 0;
	}

	// 座標とサイズ、体力を渡す
	SetPosition(m_pos);
	SetSize(m_size);

	// 下に行ったらUninitする
	if (m_pos.y - (m_size.y / 2) > SCREEN_HEIGHT)
	{
		Uninit();
	}
}

//=============================================================================
// ボスアタッククラスの描画処理
//=============================================================================
void CBossattck::Draw(void)
{
	// CScene2Dの描画処理
	CScene2D::Draw();
}

//=============================================================================
// ボスアタッククラスのダメージを受けた時の処理
//=============================================================================
void CBossattck::BossAttackDamage(int nDamage)
{
	m_nLife -= nDamage;
}

//=============================================================================
// ボスアタッククラスのビームを撃つボスの処理
//=============================================================================
void CBossattck::BossBeam(void)
{
	switch (m_Player)
	{
		// プレイヤー1のボスアタック
	case BOSSATTCK_PLAYER1:
		BossAttackBeam();

		// 横の移動の制限
		if (m_pos.x - (m_size.x / 2) <= PLAYER2_MOVABLE_RANGE_S ||
			m_pos.x + (m_size.x / 2) >= PLAYER2_MOVABLE_RANGE_L)
		{
			// 移動の反転
			m_move *= -1.0f;
		}
		break;

		// プレイヤー2のボスアタック
	case BOSSATTCK_PLAYER2:
		BossAttackBeam();

		// 横の移動の制限
		if (m_pos.x - (m_size.x / 2) <= PLAYER_MOVABLE_RANGE_S ||
			m_pos.x + (m_size.x / 2) >= PLAYER_MOVABLE_RANGE_L)
		{
			// 移動の反転
			m_move *= -1.0f;
		}
		break;

	default:
		break;
	}
}

//=============================================================================
// ボスアタッククラスの弾を撃つボスの処理
//=============================================================================
void CBossattck::BossBullet(void)
{
	CScene *pScene = NULL;
	switch (m_Player)
	{
		// プレイヤー1のボスアタック
	case BOSSATTCK_PLAYER1:
		// ボスアタックの攻撃
		BossAttackBullet(CPlayer::PLAYER_2P);

		// 横の移動の制限
		if (m_pos.x - (m_size.x / 2) <= PLAYER2_MOVABLE_RANGE_S ||
			m_pos.x + (m_size.x / 2) >= PLAYER2_MOVABLE_RANGE_L)
		{
			// 横の移動の反転
			m_move *= -1.0f;
		}
		break;

		// プレイヤー2のボスアタック
	case BOSSATTCK_PLAYER2:
		// ボスアタックの攻撃
		BossAttackBullet(CPlayer::PLAYER_1P);

		// 横の移動の制限
		if (m_pos.x - (m_size.x / 2) <= PLAYER_MOVABLE_RANGE_S ||
			m_pos.x + (m_size.x / 2) >= PLAYER_MOVABLE_RANGE_L)
		{
			// 横の移動の反転
			m_move *= -1.0f;
		}
		break;

	default:
		break;
	}
}

//=============================================================================
// ボスアタッククラスのビームを撃つ処理
//=============================================================================
void CBossattck::BossAttackBeam(void)
{
	// 止まるときのカウントの加算
	m_nCountStop++;

	// 止まってないとき
	if (m_bStop == false)
	{
		m_pos += m_move;

		// 弾を撃つカウントが100以上になったら
		if (m_nCountStop >= BEAM_BOSS_STOPCOUNT)
		{
			m_bStop = true;
			m_nCountStop = 0;
		}
	}
	// 止まるとき
	else if (m_bStop == true)
	{
		// 弾を撃つカウントの加算
		m_nCountBullet++;

		// 弾を撃つカウントが50以上になったら
		if (m_nCountBullet == BEAM_BOSS_SHOTCOUNT)
		{
			CBullet::Create(BEAM_POS, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(LASERBULLET_SIZE_X, LASERBULLET_SIZE_Y, 0.0f), BEAM_LIFE, BEAM_DAMAGE, CBullet::BULLET_TYPE_BOSS,
				CBullet::CHARGEBULLET_TYPE_BOSSLASER, CScene::OBJTYPE_BULLET);
		}

		// 止まるときのカウントが90以上になったら
		if (m_nCountStop >= BEAM_BOSS_MOVECOUNT)
		{
			m_bStop = false;
			m_nCountStop = 0;
			m_nCountBullet = 0;
		}
	}
}

//=============================================================================
// ボスアタッククラスの弾を撃つ処理
//=============================================================================
void CBossattck::BossAttackBullet(CPlayer::PLAYERNUM PlayerNum)
{
	m_pos += m_move;

	// 弾を撃つカウントの加算
	m_nCountBullet++;

	// 弾を撃つカウントが100以上の時
	if (m_nCountBullet >= BULLET_BOSS_SHOTCOUNT)
	{
		// プレイヤーのシーンの受け取り
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
						// 角度の計算
						m_fAngle = atan2f(m_pos.x - ((CScene2D*)pScene)->GetPosition().x, m_pos.y - ((CScene2D*)pScene)->GetPosition().y);

						// 弾の生成
						CBullet::Create(m_pos, D3DXVECTOR3(sinf(m_fAngle) * BULLET_SPEED, cosf(m_fAngle) * BULLET_SPEED, 0.0f),
							D3DXVECTOR3(EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y, 0.0f), BULLET_LIFE, BULLET_DAMAGE,
							CBullet::BULLET_TYPE_BOSS, CBullet::CHARGEBULLET_TYPE_NOMAL, CScene::OBJTYPE_BULLET);

						m_nCountBullet = 0;
					}
				}
				pScene = pScene->GetSceneNext();
			}
		} while (pScene != NULL);
	}
}

//=============================================================================
// ボスアタッククラスの当たるときの処理
//=============================================================================
void CBossattck::Hit(void)
{
	// ライフが0より大きかったら
	if (m_nLife > 0)
	{
		switch (m_BossAttack)
		{
			// ビームを撃つボスアタック
		case BOSSATTACK_BEAM:
			switch (m_Player)
			{
				// プレイヤー1のボスアタック
			case BOSSATTCK_PLAYER1:
				HitDamage();
				break;

				// プレイヤー2のボスアタック
			case BOSSATTCK_PLAYER2:
				HitDamage();
				break;

			default:
				break;
			}
			break;

			// たまを撃つボスアタック
		case BOSSATTACK_BULLET:
			switch (m_Player)
			{
				// プレイヤー1のボスアタック
			case BOSSATTCK_PLAYER1:
				HitDamage();
				break;

				// プレイヤー2のボスアタック
			case BOSSATTCK_PLAYER2:
				HitDamage();
				break;

			default:
				break;
			}
			break;

		default:
			break;
		}
	}
}

//=============================================================================
// ボスアタッククラスの当たるときのダメージの処理
//=============================================================================
void CBossattck::HitDamage(void)
{
	// 弾のシーンの受け取り
	CScene *pScene = CScene::GetSceneTop(CScene::OBJTYPE_BULLET);
	do
	{
		if (pScene != NULL)
		{
			// オブジェタイプの受け取り
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_BULLET)
			{
				// 弾のタイプがボスの弾の時
				if (((CBullet*)pScene)->GetBulletType() != CBullet::BULLET_TYPE_BOSS)
				{
					switch (((CBullet*)pScene)->GetChargeBulletType())
					{
						// 普通の弾
					case CBullet::CHARGEBULLET_TYPE_NOMAL:
						// 当たり判定
						if (CCollision::PRectangleCollision(m_pos, m_size, pScene) == true)
						{
							// 弾の終了処理
							((CBullet*)pScene)->Uninit();

							// ボスアタックのダメージ
							BossAttackDamage(BULLETHIT_DAMAGE);

							// 爆発の生成
							CExplosion::Create(((CScene2D*)pScene)->GetPosition(), D3DXVECTOR3(EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y, 0.0f),
								CExplosion::EXPLOSIONTYPE_NOMAL, CScene::OBJTYPE_EXPLOSION);
							break;
						}
						break;

						// チャージした弾
					case CBullet::CHARGEBULLET_TYPE_CHARGE:
						// 当たったときのカウントが0の時
						if (m_nInvincibleTime == 0)
						{
							// 当たり判定
							if (CCollision::PRectangleCollision(m_pos, m_size, pScene) == true)
							{
								// ボスアタックのダメージ
								BossAttackDamage(CHARGEHIT_DAMAGE);

								// 爆発の生成
								CExplosion::Create(((CScene2D*)pScene)->GetPosition(), D3DXVECTOR3(EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y, 0.0f),
									CExplosion::EXPLOSIONTYPE_NOMAL, CScene::OBJTYPE_EXPLOSION);

								// カウントの代入
								m_nInvincibleTime = CHARGEHIT_INCREDIBLE_TIME;
								break;
							}
						}
						break;

						// チャージした弾
					case CBullet::CHARGEBULLET_TYPE_LASER:
						// 当たったときのカウントが0の時
						if (m_nInvincibleTime == 0)
						{
							// 当たり判定
							if (CCollision::PRectangleCollision(m_pos, m_size, pScene) == true)
							{
								// ボスアタックのダメージ
								BossAttackDamage(BEAMHIT_DAMAGE);

								// 爆発の生成
								CExplosion::Create(((CScene2D*)pScene)->GetPosition(), D3DXVECTOR3(EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y, 0.0f),
									CExplosion::EXPLOSIONTYPE_NOMAL, CScene::OBJTYPE_EXPLOSION);

								// カウントの代入
								m_nInvincibleTime = BEAMHIT_INCREDIBLE_TIME;
								break;
							}
						}
						break;

					default:
						break;
					}
				}
			}
			pScene = pScene->GetSceneNext();
		}
	} while (pScene != NULL);
}