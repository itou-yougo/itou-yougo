//=============================================================================
//
// ポリゴンの描画の処理 [bullet.cpp]
// Author : 伊藤陽梧
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include <time.h>
#include <stdlib.h>
#include "ojamaplayer.h"
#include "ojamaplayer2.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "explosion.h"
#include "enemy.h"
#include "life.h"
#include "effect.h"
#include "bullet.h"
#include "extraattack.h"
#include "enemyexplosion.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define EXPLOSION_SIZE_X (100.0f)			// 爆発の縦の長さ
#define EXPLOSION_SIZE_Y (100.0f)			// 爆発の横の長さ

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 COjamaplayer2::m_pTexture = NULL;

//=============================================================================
// おじゃまプレイヤー2クラスのコンストラクタ
//=============================================================================
COjamaplayer2::COjamaplayer2() :CScene2D(OBJTYPE_OJAMA2)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Getpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_middle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_GetposPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_accele = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fSizeX = 0.0f;
	m_fSizeY = 0.0f;
	m_fGetSizeX = 0.0f;
	m_fGetSizeY = 0.0f;
	m_fAngle = 0;
	m_nCount = 0;
	m_nOjamaCount = 0;
	m_bFirstmove = false;
	m_bSecondmove = false;
	m_OjamaType = OJAMA_TYPE_NONE;
}

//=============================================================================
// おじゃまプレイヤー2クラスのデストラクタ
//=============================================================================
COjamaplayer2::~COjamaplayer2()
{

}

//=============================================================================
// おじゃまプレイヤー2クラスのテクスチャの読み込み
//=============================================================================
HRESULT COjamaplayer2::Load(void)
{
	// インスタンス生成したものを受け取る
	CRenderer *pRenderer = CManager::GetRenderer();

	// デバイスを受け取る
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BULLET, &m_pTexture);

	return S_OK;
}

//=============================================================================
// おじゃまプレイヤー2クラスのテクスチャの破棄
//=============================================================================
void COjamaplayer2::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// おじゃまプレイヤー2クラスのインスタンス生成
//=============================================================================
COjamaplayer2* COjamaplayer2::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fSizeX, float fSizeY, int nCount, D3DXVECTOR3 Accele, OJAMATYPE OjamaType, OBJTYPE objType)
{
	// COjamaplayer2のポインタ
	COjamaplayer2 *pOjamaplayer2 = NULL;

	// メモリの確保
	pOjamaplayer2 = new COjamaplayer2;

	// pOjamaplayer2がNULLじゃないとき
	if (pOjamaplayer2 != NULL)
	{
		// おじゃまプレイヤー2のセット
		pOjamaplayer2->SetCOjama(pos, move, fSizeX, fSizeY, nCount, Accele, OjamaType, objType);

		// 初期化処理
		pOjamaplayer2->Init();
	}

	// pOjamaplayer2を返す
	return pOjamaplayer2;
}

//=============================================================================
// おじゃまプレイヤー2クラスの初期化処理
//=============================================================================
HRESULT COjamaplayer2::Init()
{
	// CScene2Dの初期化処理
	CScene2D::Init();

	// テクスチャの設定
	BindTexture(m_pTexture);

	// 色のセット
	SetColor(0, 0, 255, 255);

	for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
	{
		//PLAYER2のシーンのゲット
		CScene *pScene = GetScene(OBJTYPE_PLAYER, nCntScene);
		if (pScene != NULL)
		{
			OBJTYPE objType = pScene->GetObjType();

			// オブジェタイプがプレイヤーの時
			if (objType == OBJTYPE_PLAYER)
			{
				m_GetposPlayer = ((CScene2D*)pScene)->GetPosition();
			}
		}
	}

	switch (m_OjamaType)
	{
		// 曲がるおじゃま
	case OJAMA_TYPE_FALL:
		// 中心と角度の代入
		m_middle = D3DXVECTOR3(SCREEN_CENTER_X, 50.0f, 0.0f);
		m_fAngle = atan2f(m_middle.x - m_pos.x, m_middle.y - m_pos.y);
		break;

		// まっすぐ動くおじゃま
	case OJAMA_TYPE_CURVE:
		// 中心の代入
		m_middle = D3DXVECTOR3(SCREEN_CENTER_X, (float)(rand() % 455) + 125.0f, 0.0f);
		break;

		// 落ちるおじゃま
	case OJAMA_TYPE_THROUGH:
		// 角度の計算
		m_fAngle = atan2f(m_pos.x - m_GetposPlayer.x, m_pos.y - m_GetposPlayer.y);
		break;

	default:
		break;

	}
	srand((unsigned int)time(NULL));

	return S_OK;
}

//=============================================================================
// おじゃまプレイヤー2クラスの終了処理
//=============================================================================
void COjamaplayer2::Uninit(void)
{
	// CScene2Dの終了処理
	CScene2D::Uninit();
}

//=============================================================================
// おじゃまプレイヤー2クラスの更新処理
//=============================================================================
void COjamaplayer2::Update(void)
{
	// エフェクトのクリエイト
	CEffect::Create(m_pos, m_fSizeX + 5.0f, m_fSizeY + 5.0f, 10, 100, 255, 255, 255, CEffect::EFFECTTYPE_BULLET, OBJTYPE_EFFECT);

	// CScene2Dの更新処理
	CScene2D::Update();

	// 座標と体力の受け取り
	m_pos = GetPosition();

	switch (m_OjamaType)
	{
		// 落ちるおじゃま
	case OJAMA_TYPE_FALL:
		if (m_fAngle > D3DX_PI)
		{
			m_fAngle -= D3DX_PI * 2.0f;
		}
		if (m_fAngle < D3DX_PI)
		{
			m_fAngle += D3DX_PI * 2.0f;
		}

		// 一、二回目の動きがfalseの時
		if (m_bFirstmove == false && m_bSecondmove == false)
		{
			// 移動量の加算
			m_pos += D3DXVECTOR3(sinf(m_fAngle) * m_move.x, cosf(m_fAngle) * m_move.y, 0.0f);
		}

		// 中心より小さいとき
		if (m_middle.y >= m_pos.y)
		{
			// 一回目の動きをtrueにする
			m_bFirstmove = true;
			m_bSecondmove = false;

			// 落ちる座標を決める
			m_posPlayer.x = (float)(rand() % 400 - 200) + m_GetposPlayer.x;
			if (m_posPlayer.x < PLAYER_MOVABLE_RANGE_S)
			{
				m_posPlayer.x = PLAYER_MOVABLE_RANGE_S;
			}
			if (m_posPlayer.x > PLAYER_MOVABLE_RANGE_L)
			{
				m_posPlayer.x = PLAYER_MOVABLE_RANGE_L;
			}
		}

		// 一回目の動きがtrueの時
		if (m_bFirstmove == true)
		{
			m_pos.x += m_accele.x;

			// 落ちる座標より小さくなったら
			if (m_posPlayer.x >= m_pos.x)
			{
				// 一回目の動きをfalse、二回目の動きをtrueにする
				m_bFirstmove = false;
				m_bSecondmove = true;
			}
		}
		// 二回目の動きがtrueの時
		if (m_bSecondmove == true)
		{
			m_pos.y += m_accele.y;
		}
		break;

		// まっすぐ動くおじゃま
	case OJAMA_TYPE_THROUGH:

		if (m_fAngle > D3DX_PI)
		{
			m_fAngle -= D3DX_PI * 2.0f;
		}
		if (m_fAngle < -D3DX_PI)
		{
			m_fAngle += D3DX_PI * 2.0f;
		}

		// 移動量の加算
		m_pos += D3DXVECTOR3(sinf(m_fAngle) * m_move.x, cosf(m_fAngle) * m_move.y, 0.0f);
		break;

		// 曲がるおじゃま
	case OJAMA_TYPE_CURVE:
		// 中心より大きいとき
		if (m_pos.x > m_middle.x)
		{
			// 角度を決める
			m_fAngle = atan2f(m_pos.x - m_middle.x, m_pos.y - m_middle.y);
			if (m_fAngle > D3DX_PI)
			{
				m_fAngle -= D3DX_PI;
			}
			if (m_fAngle < -D3DX_PI)
			{
				m_fAngle += D3DX_PI;
			}

			// 決めた角度の方に動かす
			m_move.x = sinf(m_fAngle) * -10;
			m_move.y = cosf(m_fAngle) * -10;
		}
		// 中心より小さいとき
		else if (m_pos.x <= m_middle.x)
		{
			// 角度を決める
			m_fAngle = atan2f(m_middle.x - m_GetposPlayer.x, m_middle.y - m_GetposPlayer.y);

			if (m_fAngle > D3DX_PI)
			{
				m_fAngle -= D3DX_PI;
			}
			if (m_fAngle < -D3DX_PI)
			{
				m_fAngle += D3DX_PI;
			}

			// 決めた角度の方に動かす
			m_move.x = sinf(m_fAngle) * -10;
			m_move.y = cosf(m_fAngle) * -10;
		}
		m_pos += m_move;
		break;

	default:
		break;

	}

	// 座標とサイズ、体力を渡す
	SetPosition(m_pos);
	SetSize(m_fSizeX, m_fSizeY);

	for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
	{
		// 弾のシーンのゲット
		CScene *pScene = GetScene(OBJTYPE_BULLET, nCntScene);
		if (pScene != NULL)
		{
			OBJTYPE objType = pScene->GetObjType();

			// オブジェタイプが弾の時
			if (objType == OBJTYPE_BULLET)
			{
				// 座標やサイズの受け取り
				m_Getpos = ((CScene2D*)pScene)->GetPosition();
				m_fGetSizeX = ((CScene2D*)pScene)->GetSizeX();
				m_fGetSizeY = ((CScene2D*)pScene)->GetSizeY();

				// 当たり判定
				if (m_pos.x - (m_fSizeX / 2) <= m_Getpos.x + (m_fGetSizeX / 2) &&
					m_pos.x + (m_fSizeX / 2) >= m_Getpos.x - (m_fGetSizeX / 2) &&
					m_pos.y - (m_fSizeY / 2) <= m_Getpos.y + (m_fGetSizeY / 2) &&
					m_pos.y + (m_fSizeY / 2) >= m_Getpos.y - (m_fGetSizeY / 2))
				{
					// 受け取った弾のタイプがプレイヤーの時
					if (((CBullet*)pScene)->GetBulletType() == CBullet::BULLET_TYPE_PLAYER)
					{
						// プレイヤーに当てられたらプレイヤーのおじゃまをクリエイト(2回目はあれをクリエイト)
						if (m_nCount < 1)
						{
							m_nOjamaCount = rand() % 3;
							switch (m_nOjamaCount)
							{
							case 0:
								COjamaplayer::Create(m_pos, D3DXVECTOR3(-10.0f, -10.0f, 0.0f), 50.0f, 50.0f, m_nCount + 1, D3DXVECTOR3(2.0f, 2.0f, 0.0f), COjamaplayer::OJAMA_TYPE_THROUGH, OBJTYPE_OJAMA);
								break;

							case 1:
								COjamaplayer::Create(m_pos, D3DXVECTOR3(10.0f, -10.0f, 0.0f), 50.0f, 50.0f, m_nCount + 1, D3DXVECTOR3((float)(rand() % 3) + 2.0f, -2.0f, 0.0f), COjamaplayer::OJAMA_TYPE_CURVE, OBJTYPE_OJAMA);
								break;

							case 2:
								COjamaplayer::Create(m_pos, D3DXVECTOR3((float)(rand() % 10) - 15.0f, (float)(rand() % 10) - 15.0f, 0.0f), 50.0f, 50.0f, m_nCount + 1, D3DXVECTOR3((float)(rand() % 5) + 5.0f, 5.0f, 0.0f), COjamaplayer::OJAMA_TYPE_FALL, OBJTYPE_OJAMA);
								break;

							default:
								break;
							}
							//終了処理
							Uninit();
						}
						else
						{
							for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
							{
								// オブジェタイプがPLAYER2の時
								CScene *pScene = GetScene(OBJTYPE_PLAYER2, nCntScene);
								if (pScene != NULL)
								{
									OBJTYPE objType = pScene->GetObjType();

									// オブジェタイプがプレイヤー2の時
									if (objType == OBJTYPE_PLAYER2)
									{
										m_GetposPlayer = ((CScene2D*)pScene)->GetPosition();
									}
								}
							}
							// 角度を決める
							m_fAngle = atan2f(m_pos.x - m_GetposPlayer.x, m_pos.y - m_GetposPlayer.y);
							
							// エクストラアタックの生成
							CExtraattck::Create(m_pos, D3DXVECTOR3(sinf(m_fAngle) * -10.0f, cosf(m_fAngle) * -10.0f, 0.0f), 50.0f, 50.0f, CExtraattck::EXTRAATTCK_PLAYER2, CExtraattck::EXTRAATTACK_TIKATIKA, OBJTYPE_EXTRAATTACK);
							
							//終了処理
							Uninit();
						}
					}
					break;
				}
			}
		}
		// 敵の爆発のシーンのゲット
		pScene = GetScene(OBJTYPE_ENEMYEXPLOSION, nCntScene);
		if (pScene != NULL)
		{
			OBJTYPE objType = pScene->GetObjType();

			// オブジェタイプが弾の時
			if (objType == OBJTYPE_ENEMYEXPLOSION)
			{
				// オブジェタイプが弾の時
				m_Getpos = ((CScene2D*)pScene)->GetPosition();
				m_fGetSizeX = ((CScene2D*)pScene)->GetSizeX();
				m_fGetSizeY = ((CScene2D*)pScene)->GetSizeY();

				// 当たり判定
				if (m_pos.x - (m_fSizeX / 2) <= m_Getpos.x + (m_fGetSizeX / 2) &&
					m_pos.x + (m_fSizeX / 2) >= m_Getpos.x - (m_fGetSizeX / 2) &&
					m_pos.y - (m_fSizeY / 2) <= m_Getpos.y + (m_fGetSizeY / 2) &&
					m_pos.y + (m_fSizeY / 2) >= m_Getpos.y - (m_fGetSizeY / 2))
				{
					// 受け取った弾のタイプがプレイヤーの時
					if (((CEnemyexplosion*)pScene)->GetExplosionType() == CEnemyexplosion::EXPLOSIONTYPE_PLAYER)
					{
						// プレイヤーに当てられたらプレイヤーのおじゃまをクリエイト(2回目はあれをクリエイト)
						if (m_nCount < 1)
						{
							m_nOjamaCount = rand() % 3;
							switch (m_nOjamaCount)
							{
							case 0:
								COjamaplayer::Create(m_pos, D3DXVECTOR3(-10.0f, -10.0f, 0.0f), 50.0f, 50.0f, m_nCount + 1, D3DXVECTOR3(2.0f, 2.0f, 0.0f), COjamaplayer::OJAMA_TYPE_THROUGH, OBJTYPE_OJAMA);
								break;

							case 1:
								COjamaplayer::Create(m_pos, D3DXVECTOR3(10.0f, -10.0f, 0.0f), 50.0f, 50.0f, m_nCount + 1, D3DXVECTOR3((float)(rand() % 3) + 2.0f, -2.0f, 0.0f), COjamaplayer::OJAMA_TYPE_CURVE, OBJTYPE_OJAMA);
								break;

							case 2:
								COjamaplayer::Create(m_pos, D3DXVECTOR3((float)(rand() % 10) - 15.0f, (float)(rand() % 10) - 15.0f, 0.0f), 50.0f, 50.0f, m_nCount + 1, D3DXVECTOR3((float)(rand() % 5) + 5.0f, 5.0f, 0.0f), COjamaplayer::OJAMA_TYPE_FALL, OBJTYPE_OJAMA);
								break;

							default:
								break;
							}
							Uninit();
						}
						else
						{
							for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
							{
								CScene *pScene = GetScene(OBJTYPE_PLAYER, nCntScene);
								if (pScene != NULL)
								{
									OBJTYPE objType = pScene->GetObjType();

									// オブジェタイプがプレイヤー2の時
									if (objType == OBJTYPE_PLAYER)
									{
										m_GetposPlayer = ((CScene2D*)pScene)->GetPosition();
									}
								}
							}
							// 角度を決める
							m_fAngle = atan2f(m_pos.x - m_GetposPlayer.x, m_pos.y - m_GetposPlayer.y);
							
							// エクストラアタックの生成
							CExtraattck::Create(m_pos, D3DXVECTOR3(sinf(m_fAngle) * -10.0f, cosf(m_fAngle) * -10.0f, 0.0f), 50.0f, 50.0f, CExtraattck::EXTRAATTCK_PLAYER2, CExtraattck::EXTRAATTACK_TIKATIKA, OBJTYPE_EXTRAATTACK);
							
							//終了処理
							Uninit();
						}
					}
					break;
				}
			}
		}
	}

	// 画面外に出たら終了処理
	if (m_pos.y > SCREEN_HEIGHT + m_fSizeY)
	{
		Uninit();
	}
}

//=============================================================================
// おじゃまプレイヤー2クラスの描画処理
//=============================================================================
void COjamaplayer2::Draw(void)
{
	// CScene2Dの描画処理
	CScene2D::Draw();
}