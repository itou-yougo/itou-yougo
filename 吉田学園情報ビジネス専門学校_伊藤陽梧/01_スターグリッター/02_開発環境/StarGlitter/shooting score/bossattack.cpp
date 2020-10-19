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
#include "player2.h"
#include "explosion.h"
#include "enemy.h"
#include "life.h"
#include "effect.h"
#include "bullet.h"
#include "ojamaplayer2.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define EXPLOSION_SIZE_X (100.0f)			// 爆発の縦の長さ
#define EXPLOSION_SIZE_Y (100.0f)			// 爆発の横の長さ
#define BOSSEXPLOSION_SIZE_X (200.0f)			// ボスの爆発の縦の長さ
#define BOSSEXPLOSION_SIZE_Y (200.0f)			// ボスの爆発の横の長さ

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
	m_Getpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fSizeX = 0.0f;
	m_fSizeY = BOSS_SIZE_Y;
	m_fGetSizeX = 0.0f;
	m_fGetSizeY = 0.0f;
	m_nCount = 0;
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
	for (int nCount = 0; nCount < 2; nCount++)
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
		pBossattck->SetExtraAttack(pos, move, nLife, Player, BossAttack, objType);

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
	if (m_fSizeX < BOSS_SIZE_X)
	{
		SetColor(255, 255, 255, 100);
		m_fSizeX += 5.0f;
	}

	//　横のサイズがBOSS_SIZE_Xより大きくなったら
	if (m_fSizeX >= BOSS_SIZE_X)
	{
		m_fSizeX = BOSS_SIZE_X;
		SetColor(255, 255, 255, 255);
		
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

					// 弾を撃つカウントの加算
					m_nCountBullet++;

					// 止まってないとき
					if (m_bStop == false)
					{
						m_pos += m_move;

						// 弾を撃つカウントが100以上になったら
						if (m_nCountBullet >= 100)
						{
							m_bStop = true;
							m_nCountBullet = 0;
						}
					}
					// 止まるとき
					else if (m_bStop == true)
					{
						// 止まるときのカウントの加算
						m_nCountStop++;

						// 弾を撃つカウントが50以上になったら
						if (m_nCountBullet >= 50)
						{
							CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - LASERBULLET_SIZE_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), LASERBULLET_SIZE_X, LASERBULLET_SIZE_Y, 40, 10, CBullet::BULLET_TYPE_BOSS, CBullet::CHARGEBULLET_TYPE_LASER, CScene::OBJTYPE_BULLET);
							m_nCountBullet = 0;
						}

						// 止まるときのカウントが100以上になったら
						if (m_nCountStop >= 90)
						{
							m_bStop = false;
							m_nCountStop = 0;
						}
					}

					for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
					{
						// 弾のシーンの受け取り
						CScene *pScene = GetScene(OBJTYPE_BULLET, nCntScene);
						if (pScene != NULL)
						{
							// オブジェタイプの受け取り
							OBJTYPE objType = pScene->GetObjType();
							if (objType == OBJTYPE_BULLET)
							{
								// 座標やサイズの受け取り
								m_Getpos = ((CScene2D*)pScene)->GetPosition();
								m_fGetSizeX = ((CScene2D*)pScene)->GetSizeX();
								m_fGetSizeY = ((CScene2D*)pScene)->GetSizeY();

								// 弾のタイプがボスの弾の時
								if (((CBullet*)pScene)->GetBulletType() != CBullet::BULLET_TYPE_BOSS)
								{
									switch (((CBullet*)pScene)->GetChargeBulletType())
									{
										// 普通の弾
									case CBullet::CHARGEBULLET_TYPE_NOMAL:
										// 当たり判定
										if (m_pos.x - (m_fSizeX / 2) <= m_Getpos.x + (m_fGetSizeX / 2) &&
											m_pos.x + (m_fSizeX / 2) >= m_Getpos.x - (m_fGetSizeX / 2) &&
											m_pos.y - (m_fSizeY / 2) <= m_Getpos.y + (m_fGetSizeY / 2) &&
											m_pos.y + (m_fSizeY / 2) >= m_Getpos.y - (m_fGetSizeY / 2))
										{
											// 弾の終了処理
											((CBullet*)pScene)->Uninit();

											// ボスアタックのダメージ
											BossAttackDamage(1);

											// 爆発の生成
											CExplosion::Create(m_Getpos, EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y, CExplosion::EXPLOSIONTYPE_NOMAL, CScene::OBJTYPE_EXPLOSION);
											break;
										}
										break;

										// チャージした弾
									case CBullet::CHARGEBULLET_TYPE_CHARGE:
										// 当たったときのカウントが0の時
										if (m_nCount == 0)
										{
											// 当たり判定
											if (m_pos.x - (m_fSizeX / 2) <= m_Getpos.x + (m_fGetSizeX / 2) &&
												m_pos.x + (m_fSizeX / 2) >= m_Getpos.x - (m_fGetSizeX / 2) &&
												m_pos.y - (m_fSizeY / 2) <= m_Getpos.y + (m_fGetSizeY / 2) &&
												m_pos.y + (m_fSizeY / 2) >= m_Getpos.y - (m_fGetSizeY / 2))
											{
												// ボスアタックのダメージ
												BossAttackDamage(1);

												// 爆発の生成
												CExplosion::Create(m_Getpos, EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y, CExplosion::EXPLOSIONTYPE_NOMAL, CScene::OBJTYPE_EXPLOSION);

												// カウントの代入
												m_nCount = 40;
												break;
											}
										}
										break;

									default:
										break;
									}
								}
							}
						}

						// カウントの減算
						m_nCount--;
						if (m_nCount < 0)
						{
							m_nCount = 0;
						}
					}

					// 横の移動の制限
					if (m_pos.x - (m_fSizeX / 2) <= PLAYER2_MOVABLE_RANGE_S ||
						m_pos.x + (m_fSizeX / 2) >= PLAYER2_MOVABLE_RANGE_L)
					{
						// 移動の反転
						m_move *= -1.0f;
					}
					break;

					// プレイヤー2のボスアタック
				case BOSSATTCK_PLAYER2:
					// 弾を撃つカウントの加算
					m_nCountBullet++;

					// 止まってないとき
					if (m_bStop == false)
					{
						m_pos += m_move;
						// 弾を撃つカウントが150以上になったら
						if (m_nCountBullet >= 150)
						{
							m_bStop = true;
							m_nCountBullet = 0;
						}
					}
					// 止まるとき
					else if (m_bStop == true)
					{
						// 止まるときのカウントの加算
						m_nCountStop++;

						// 弾を撃つカウントが50以上になったら
						if (m_nCountBullet >= 50)
						{
							CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + (LASERBULLET_SIZE_Y / 2) + 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), LASERBULLET_SIZE_X, LASERBULLET_SIZE_Y, 40, 1, CBullet::BULLET_TYPE_BOSS, CBullet::CHARGEBULLET_TYPE_BOSSLASER, CScene::OBJTYPE_BULLET);
							m_nCountBullet = 0;
						}

						// 止まるときのカウントが100以上になったら
						if (m_nCountStop >= 90)
						{
							m_bStop = false;
							m_nCountStop = 0;
						}
					}

					for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
					{
						// シーンの受け取り
						CScene *pScene = GetScene(OBJTYPE_BULLET, nCntScene);
						if (pScene != NULL)
						{
							// オブジェタイプの受け取り
							OBJTYPE objType = pScene->GetObjType();
							if (objType == OBJTYPE_BULLET)
							{
								// 座標やサイズの受け取り
								m_Getpos = ((CScene2D*)pScene)->GetPosition();
								m_fGetSizeX = ((CScene2D*)pScene)->GetSizeX();
								m_fGetSizeY = ((CScene2D*)pScene)->GetSizeY();

								// 弾のタイプがボスの弾の時
								if (((CBullet*)pScene)->GetBulletType() != CBullet::BULLET_TYPE_BOSS)
								{
									switch (((CBullet*)pScene)->GetChargeBulletType())
									{
										// 普通の弾
									case CBullet::CHARGEBULLET_TYPE_NOMAL:
										// 当たり判定
										if (m_pos.x - (m_fSizeX / 2) <= m_Getpos.x + (m_fGetSizeX / 2) &&
											m_pos.x + (m_fSizeX / 2) >= m_Getpos.x - (m_fGetSizeX / 2) &&
											m_pos.y - (m_fSizeY / 2) <= m_Getpos.y + (m_fGetSizeY / 2) &&
											m_pos.y + (m_fSizeY / 2) >= m_Getpos.y - (m_fGetSizeY / 2))
										{
											// 弾の終了処理
											((CBullet*)pScene)->Uninit();

											// ボスアタックのダメージ
											BossAttackDamage(1);

											// 爆発の生成
											CExplosion::Create(m_Getpos, EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y, CExplosion::EXPLOSIONTYPE_NOMAL, CScene::OBJTYPE_EXPLOSION);
											break;
										}
										break;

										// チャージした弾
									case CBullet::CHARGEBULLET_TYPE_CHARGE:
										// 当たったときのカウントが0の時
										if (m_nCount == 0)
										{
											if (m_pos.x - (m_fSizeX / 2) <= m_Getpos.x + (m_fGetSizeX / 2) &&
												m_pos.x + (m_fSizeX / 2) >= m_Getpos.x - (m_fGetSizeX / 2) &&
												m_pos.y - (m_fSizeY / 2) <= m_Getpos.y + (m_fGetSizeY / 2) &&
												m_pos.y + (m_fSizeY / 2) >= m_Getpos.y - (m_fGetSizeY / 2))
											{
												// ボスアタックのダメージ
												BossAttackDamage(1);

												// 爆発の生成
												CExplosion::Create(m_Getpos, EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y, CExplosion::EXPLOSIONTYPE_NOMAL, CScene::OBJTYPE_EXPLOSION);

												// カウントの代入
												m_nCount = 40;
												break;
											}
										}
										break;

									default:
										break;
									}
								}
							}
						}
					}

					// 横の移動の制限
					if (m_pos.x - (m_fSizeX / 2) <= PLAYER_MOVABLE_RANGE_S ||
						m_pos.x + (m_fSizeX / 2) >= PLAYER_MOVABLE_RANGE_L)
					{
						// 移動の反転
						m_move *= -1.0f;
					}
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
					m_pos += m_move;
					for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
					{
						// シーンの受け取り
						CScene *pScene = GetScene(OBJTYPE_BULLET, nCntScene);
						if (pScene != NULL)
						{
							// オブジェタイプの受け取り
							OBJTYPE objType = pScene->GetObjType();
							if (objType == OBJTYPE_BULLET)
							{
								// 座標やサイズの受け取り
								m_Getpos = ((CScene2D*)pScene)->GetPosition();
								m_fGetSizeX = ((CScene2D*)pScene)->GetSizeX();
								m_fGetSizeY = ((CScene2D*)pScene)->GetSizeY();

								// 弾のタイプがボスの弾の時
								if (((CBullet*)pScene)->GetBulletType() != CBullet::BULLET_TYPE_BOSS)
								{
									switch (((CBullet*)pScene)->GetChargeBulletType())
									{
										// 普通の弾
									case CBullet::CHARGEBULLET_TYPE_NOMAL:
										// 当たり判定
										if (m_pos.x - (m_fSizeX / 2) <= m_Getpos.x + (m_fGetSizeX / 2) &&
											m_pos.x + (m_fSizeX / 2) >= m_Getpos.x - (m_fGetSizeX / 2) &&
											m_pos.y - (m_fSizeY / 2) <= m_Getpos.y + (m_fGetSizeY / 2) &&
											m_pos.y + (m_fSizeY / 2) >= m_Getpos.y - (m_fGetSizeY / 2))
										{
											// 弾の終了処理
											((CBullet*)pScene)->Uninit();

											// ボスアタックのダメージ
											BossAttackDamage(1);

											// 爆発の生成
											CExplosion::Create(m_Getpos, EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y, CExplosion::EXPLOSIONTYPE_NOMAL, CScene::OBJTYPE_EXPLOSION);
											break;
										}
										break;

									case CBullet::CHARGEBULLET_TYPE_CHARGE:
										if (m_nCount == 0)
										{
											if (m_pos.x - (m_fSizeX / 2) <= m_Getpos.x + (m_fGetSizeX / 2) &&
												m_pos.x + (m_fSizeX / 2) >= m_Getpos.x - (m_fGetSizeX / 2) &&
												m_pos.y - (m_fSizeY / 2) <= m_Getpos.y + (m_fGetSizeY / 2) &&
												m_pos.y + (m_fSizeY / 2) >= m_Getpos.y - (m_fGetSizeY / 2))
											{

												// ボスアタックのダメージ
												BossAttackDamage(1);

												// 爆発の生成
												CExplosion::Create(m_Getpos, EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y, CExplosion::EXPLOSIONTYPE_NOMAL, CScene::OBJTYPE_EXPLOSION);

												// カウントの代入
												m_nCount = 40;
												break;
											}
										}
										break;

									default:
										break;
									}
								}
							}
						}

						// カウントの減算
						m_nCount--;
						if (m_nCount < 0)
						{
							m_nCount = 0;
						}
					}
					// 弾を撃つカウントの加算
					m_nCountBullet++;

					// 弾を撃つカウントが100以上の時
					if (m_nCountBullet >= 200)
					{
						for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
						{
							// シーンの受け取り
							CScene *pScene = GetScene(OBJTYPE_PLAYER2, nCntScene);
							if (pScene != NULL)
							{
								// オブジェタイプの受け取り
								OBJTYPE objType = pScene->GetObjType();
								if (objType == OBJTYPE_PLAYER2)
								{
									// 座標の受け取り
									m_Getpos = ((CScene2D*)pScene)->GetPosition();

									// 角度の計算
									m_fAngle = atan2f(m_pos.x - m_Getpos.x, m_pos.y - m_Getpos.y);

									// 弾の生成
									CBullet::Create(m_pos - D3DXVECTOR3(125.0f, 125.0f, 0) , D3DXVECTOR3(sinf(m_fAngle) * -10.0f, cosf(m_fAngle) * -10.0f, 0.0f), BOSSBULLET_SIZE_X, BOSSBULLET_SIZE_Y, 100, 1, CBullet::BULLET_TYPE_BOSS, CBullet::CHARGEBULLET_TYPE_NOMAL, CScene::OBJTYPE_BULLET);
									
									m_nCountBullet = 0;
								}
							}
						}
					}

					// 横の移動の制限
					if (m_pos.x - (m_fSizeX / 2) <= PLAYER2_MOVABLE_RANGE_S ||
						m_pos.x + (m_fSizeX / 2) >= PLAYER2_MOVABLE_RANGE_L)
					{
						// 横の移動の反転
						m_move *= -1.0f;
					}
					break;

					// プレイヤー2のボスアタック
				case BOSSATTCK_PLAYER2:
					m_pos += m_move;
					for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
					{
						CScene *pScene = GetScene(OBJTYPE_BULLET, nCntScene);
						if (pScene != NULL)
						{
							OBJTYPE objType = pScene->GetObjType();
							if (objType == OBJTYPE_BULLET)
							{
								m_Getpos = ((CScene2D*)pScene)->GetPosition();
								m_fGetSizeX = ((CScene2D*)pScene)->GetSizeX();
								m_fGetSizeY = ((CScene2D*)pScene)->GetSizeY();
								if (((CBullet*)pScene)->GetBulletType() != CBullet::BULLET_TYPE_BOSS)
								{
									switch (((CBullet*)pScene)->GetChargeBulletType())
									{
									case CBullet::CHARGEBULLET_TYPE_NOMAL:
										if (m_pos.x - (m_fSizeX / 2) <= m_Getpos.x + (m_fGetSizeX / 2) &&
											m_pos.x + (m_fSizeX / 2) >= m_Getpos.x - (m_fGetSizeX / 2) &&
											m_pos.y - (m_fSizeY / 2) <= m_Getpos.y + (m_fGetSizeY / 2) &&
											m_pos.y + (m_fSizeY / 2) >= m_Getpos.y - (m_fGetSizeY / 2))
										{
											// 弾の終了処理
											((CBullet*)pScene)->Uninit();

											// ボスアタックのダメージ
											BossAttackDamage(1);

											// 爆発の生成
											CExplosion::Create(m_Getpos, EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y, CExplosion::EXPLOSIONTYPE_NOMAL, CScene::OBJTYPE_EXPLOSION);
											break;
										}
										break;

									case CBullet::CHARGEBULLET_TYPE_CHARGE:
										if (m_nCount == 0)
										{
											if (m_pos.x - (m_fSizeX / 2) <= m_Getpos.x + (m_fGetSizeX / 2) &&
												m_pos.x + (m_fSizeX / 2) >= m_Getpos.x - (m_fGetSizeX / 2) &&
												m_pos.y - (m_fSizeY / 2) <= m_Getpos.y + (m_fGetSizeY / 2) &&
												m_pos.y + (m_fSizeY / 2) >= m_Getpos.y - (m_fGetSizeY / 2))
											{
												BossAttackDamage(1);
												CExplosion::Create(m_Getpos, EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y, CExplosion::EXPLOSIONTYPE_NOMAL, CScene::OBJTYPE_EXPLOSION);
												m_nCount = 40;
												break;
											}
										}
										break;

									default:
										break;
									}
								}
							}
						}
					}
					// 弾を撃つカウントが100以上の時
					if (m_nCountBullet >= 100)
					{
						for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
						{
							// シーンの受け取り
							CScene *pScene = GetScene(OBJTYPE_PLAYER, nCntScene);
							if (pScene != NULL)
							{
								// オブジェタイプの受け取り
								OBJTYPE objType = pScene->GetObjType();
								if (objType == OBJTYPE_PLAYER)
								{
									// 座標の受け取り
									m_Getpos = ((CScene2D*)pScene)->GetPosition();

									// 角度の計算
									m_fAngle = atan2f(m_pos.x - m_Getpos.x, m_pos.y - m_Getpos.y);

									// 弾の生成
									CBullet::Create(m_pos, D3DXVECTOR3(sinf(m_fAngle) * -10.0f, cosf(m_fAngle) * -10.0f, 0.0f), BOSSBULLET_SIZE_X, BOSSBULLET_SIZE_Y, 100, 1, CBullet::BULLET_TYPE_BOSS, CBullet::CHARGEBULLET_TYPE_NOMAL, CScene::OBJTYPE_BULLET);
									
									m_nCountBullet = 0;
								}
							}
						}
					}

					// 横の移動の制限
					if (m_pos.x - (m_fSizeX / 2) <= PLAYER_MOVABLE_RANGE_S ||
						m_pos.x + (m_fSizeX / 2) >= PLAYER_MOVABLE_RANGE_L)
					{
						// 横の移動の反転
						m_move *= -1.0f;
					}
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

	// ライフが0以下の時
	if (m_nLife <= 0)
	{
		// 移動量の加算
		m_pos.y += 5.0f;

		// カウントの加算
		m_nCount++;

		// カウントが10の時
		if (m_nCount == 10)
		{
			CExplosion::Create(m_pos + D3DXVECTOR3((float)(rand() % (int)BOSS_SIZE_X) - BOSS_SIZE_X / 2.0f, ((float)(rand() % (int)BOSS_SIZE_Y) - BOSS_SIZE_Y / 2.0f), 0.0f), BOSSEXPLOSION_SIZE_X, BOSSEXPLOSION_SIZE_Y, CExplosion::EXPLOSIONTYPE_BOSS, CScene::OBJTYPE_EXPLOSION);
			m_nCount = 0;
		}
	}

	// 座標とサイズ、体力を渡す
	SetPosition(m_pos);
	SetSize(m_fSizeX, m_fSizeY);

	// 下に行ったらUninitする
	if (m_pos.y - (m_fSizeY / 2) > SCREEN_HEIGHT)
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
