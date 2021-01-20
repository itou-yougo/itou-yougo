//=============================================================================
//
// おじゃまの処理 [ojama.cpp]
// Author : 伊藤陽梧
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "ojama.h"
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
#include "collision.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define EXPLOSION_SIZE_X (100.0f)			// 爆発の縦の長さ
#define EXPLOSION_SIZE_Y (100.0f)			// 爆発の横の長さ

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 COjama::m_pTexture = NULL;

//=============================================================================
// おじゃまプレイヤークラスのコンストラクタ
//=============================================================================
COjama::COjama() :CScene2D(OBJTYPE_OJAMA)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Getpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_GetSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Fallpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_middle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_accele = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCount = 0;
	m_nOjamaCount = 0;
	m_fAngle = 0.0f;
	m_bFirstmove = false;
	m_bSecondmove = false;
	m_OjamaType = OJAMA_TYPE_NONE;
}

//=============================================================================
// おじゃまプレイヤークラスのデストラクタ
//=============================================================================
COjama::~COjama()
{

}

//=============================================================================
// おじゃまプレイヤークラスのテクスチャの読み込み
//=============================================================================
HRESULT COjama::Load(void)
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
// おじゃまプレイヤークラスのテクスチャの破棄
//=============================================================================
void COjama::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// おじゃまプレイヤークラスのインスタンス生成
//=============================================================================
COjama* COjama::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nCount, D3DXVECTOR3 Accele, OJAMATYPE OjamaType, OJAMAPLAYERNUM OjamaPlayer, OBJTYPE objType)
{
	// COjamaのポインタ
	COjama *pOjamaplayer = NULL;

	// メモリの確保
	pOjamaplayer = new COjama;

	// pOjamaplayerがNULLじゃないとき
	if (pOjamaplayer != NULL)
	{
		// おじゃまプレイヤーのセット
		pOjamaplayer->SetCOjama(pos, move, size, nCount, Accele, OjamaType, OjamaPlayer, objType);

		// 初期化処理
		pOjamaplayer->Init();
	}

	// pOjamaplayerを返す
	return pOjamaplayer;
}

//=============================================================================
// おじゃまプレイヤークラスの初期化処理
//=============================================================================
HRESULT COjama::Init()
{
	// CScene2Dの初期化処理
	CScene2D::Init();

	// テクスチャの設定
	BindTexture(m_pTexture);

	//プレイヤーのシーンのゲット
	CScene *pScene = CScene::GetSceneTop(CScene::OBJTYPE_PLAYER);
	switch (m_OjamaPlayerNum)
	{
		// 1Pのおじゃま
	case OJAMAPLAYER_1P:
		// 色のセット
		SetColor(255, 0, 0, 255);

		do
		{
			if (pScene != NULL)
			{
				// オブジェタイプの受け取り
				OBJTYPE objType = pScene->GetObjType();
				if (objType == OBJTYPE_PLAYER)
				{
					// 2Pに当てたいからの座標をもらう
					if (((CPlayer*)pScene)->GetPlayerNum() == CPlayer::PLAYER_2P)
					{
						m_Getpos = ((CScene2D*)pScene)->GetPosition();
					}
				}
				pScene = pScene->GetSceneNext();
			}
		} while (pScene != NULL);

		switch (m_OjamaType)
		{
			// 曲がるおじゃま
		case OJAMA_TYPE_FALL:
			// 中心と角度の代入
			m_middle = D3DXVECTOR3(SCREEN_CENTER_X, 50.0f, 0.0f);
			m_fAngle = atan2f(m_pos.x - m_middle.x, m_pos.y - m_middle.y);
			break;

			// まっすぐ動くおじゃま
		case OJAMA_TYPE_CURVE:
			// 中心の代入
			m_middle = D3DXVECTOR3(SCREEN_CENTER_X, (float)(rand() % 455) + 125.0f, 0.0f);
			break;

			// 落ちるおじゃま
		case OJAMA_TYPE_THROUGH:
			// 角度の計算
			m_fAngle = atan2f(m_pos.x - m_Getpos.x, m_pos.y - m_Getpos.y);
			break;

		default:
			break;
		}
		break;

		// 2Pのおじゃま
	case OJAMAPLAYER_2P:
		// 色のセット
		SetColor(0, 0, 255, 255);
		do
		{
			if (pScene != NULL)
			{
				// オブジェタイプの受け取り
				OBJTYPE objType = pScene->GetObjType();
				if (objType == OBJTYPE_PLAYER)
				{
					// 1Pに当てたいからの座標をもらう
					if (((CPlayer*)pScene)->GetPlayerNum() == CPlayer::PLAYER_1P)
					{
						m_Getpos = ((CScene2D*)pScene)->GetPosition();
					}
				}
				pScene = pScene->GetSceneNext();
			}
		} while (pScene != NULL);

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
			m_fAngle = atan2f(m_pos.x - m_Getpos.x, m_pos.y - m_Getpos.y);
			break;

		default:
			break;
		}
		break;

	default:
		break;
	}

	return S_OK;
}

//=============================================================================
// おじゃまプレイヤークラスの終了処理
//=============================================================================
void COjama::Uninit(void)
{
	// CScene2Dの終了処理
	CScene2D::Uninit();
}

//=============================================================================
// おじゃまプレイヤークラスの更新処理
//=============================================================================
void COjama::Update(void)
{
	switch (m_OjamaPlayerNum)
	{
		// 1Pのおじゃま
	case OJAMAPLAYER_1P:
		// エフェクトのクリエイト
		CEffect::Create(m_pos, m_size + D3DXVECTOR3(5.0f, 5.0f, 0.0f), 10, 255, 100, 100, 255, CEffect::EFFECTTYPE_BULLET, OBJTYPE_EFFECT);
		break;

		// 2Pのおじゃま
	case OJAMAPLAYER_2P:	// エフェクトのクリエイト
		CEffect::Create(m_pos, m_size + D3DXVECTOR3(5.0f, 5.0f, 0.0f), 10, 100, 255, 255, 255, CEffect::EFFECTTYPE_BULLET, OBJTYPE_EFFECT);
		break;

	default:
		break;
	}
	// CScene2Dの更新処理
	CScene2D::Update();

	// 座標と体力の受け取り
	m_pos = GetPosition();

	switch (m_OjamaType)
	{
		// 落ちるおじゃま
	case OJAMA_TYPE_FALL:
		Fall();
		break;

		// まっすぐ動くおじゃま
	case OJAMA_TYPE_THROUGH:
		Through();
		break;

		// 曲がるおじゃま
	case OJAMA_TYPE_CURVE:
		Curve();
		break;

	default:
		break;

	}

	Hit();

	//m_pos += m_move;

	// 座標とサイズ、体力を渡す
	SetPosition(m_pos);
	SetSize(m_size);

	// 画面外に出たら終了処理
	if (m_pos.y > SCREEN_HEIGHT + m_size.y)
	{
		Uninit();
	}
}

//=============================================================================
// おじゃまプレイヤークラスの描画処理
//=============================================================================
void COjama::Draw(void)
{
	// CScene2Dの描画処理
	CScene2D::Draw();
}

//=============================================================================
// おじゃまクラスの曲がって動く処理
//=============================================================================
void COjama::Curve(void)
{
	switch (m_OjamaPlayerNum)
	{
		// 1Pのおじゃま
	case OJAMAPLAYER_1P:
		// 中心より小さいとき
		if (m_pos.x < m_middle.x)
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
		// 中心より大きいとき
		else if (m_pos.x >= m_middle.x)
		{
			// 角度を決める
			m_fAngle = atan2f(m_middle.x - m_Getpos.x, m_middle.y - m_Getpos.y);
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
		break;

		// 2Pのおじゃま
	case OJAMAPLAYER_2P:
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
			m_fAngle = atan2f(m_middle.x - m_Getpos.x, m_middle.y - m_Getpos.y);
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
		break;

	default:
		break;
	}
	m_pos += m_move;
}

//=============================================================================
// おじゃまクラスのまっすぐ動く処理
//=============================================================================
void COjama::Through(void)
{
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
}

//=============================================================================
// おじゃまクラスの落ちて動く処理
//=============================================================================
void COjama::Fall(void)
{
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

	switch (m_OjamaPlayerNum)
	{
		// 1Pのおじゃま
	case OJAMAPLAYER_1P:
		// 中心より小さいとき
		if (m_middle.y >= m_pos.y)
		{
			// 一回目の動きをtrueにする
			m_bFirstmove = true;
			m_bSecondmove = false;

			// 落ちる座標を決める
			m_Fallpos.x = (float)(rand() % 400 - 200) + m_Getpos.x;
			if (m_Fallpos.x < PLAYER2_MOVABLE_RANGE_S)
			{
				m_Fallpos.x = PLAYER2_MOVABLE_RANGE_S;
			}
			if (m_Fallpos.x > PLAYER2_MOVABLE_RANGE_L)
			{
				m_Fallpos.x = PLAYER2_MOVABLE_RANGE_L;
			}
		}

		// 一回目の動きがtrueの時
		if (m_bFirstmove == true)
		{
			m_pos.x += m_accele.x;

			// 落ちる座標より大きくなったら
			if (m_Fallpos.x <= m_pos.x)
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

		// 2Pのおじゃま
	case OJAMAPLAYER_2P:
		// 中心より小さいとき
		if (m_middle.y >= m_pos.y)
		{
			// 一回目の動きをtrueにする
			m_bFirstmove = true;
			m_bSecondmove = false;

			// 落ちる座標を決める
			m_Fallpos.x = (float)(rand() % 400 - 200) + m_Getpos.x;
			if (m_Fallpos.x < PLAYER_MOVABLE_RANGE_S)
			{
				m_Fallpos.x = PLAYER_MOVABLE_RANGE_S;
			}
			if (m_Fallpos.x > PLAYER_MOVABLE_RANGE_L)
			{
				m_Fallpos.x = PLAYER_MOVABLE_RANGE_L;
			}
		}

		// 一回目の動きがtrueの時
		if (m_bFirstmove == true)
		{
			m_pos.x += m_accele.x;

			// 落ちる座標より小さくなったら
			if (m_Fallpos.x >= m_pos.x)
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

	default:
		break;
	}
}

//=============================================================================
// おじゃまクラスの当たったときの処理
//=============================================================================
void COjama::Hit(void)
{
	// 弾のシーンを受け取る
	CScene *pScene = CScene::GetSceneTop(CScene::OBJTYPE_BULLET);
	do
	{
		if (pScene != NULL)
		{
			// オブジェタイプの受け取り
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_BULLET)
			{
				// 当たり判定
				if (CCollision::PRectangleCollision(m_pos, m_size, pScene) == true)
				{
					HitBullet(pScene);
				}
			}
			pScene = pScene->GetSceneNext();
		}
	} while (pScene != NULL);

	// 敵の爆発のシーンを受け取る
	pScene = CScene::GetSceneTop(CScene::OBJTYPE_ENEMYEXPLOSION);
	do
	{
		if (pScene != NULL)
		{
			// オブジェタイプの受け取り
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_ENEMYEXPLOSION)
			{
				// 当たり判定
				if (CCollision::PRectangleCollision(m_pos, m_size, pScene) == true)
				{
					HitExplosion(pScene);
				}
			}
			pScene = pScene->GetSceneNext();
		}
	} while (pScene != NULL);
}

//=============================================================================
// おじゃまクラスの弾に当たったときの処理
// pScene：爆発のシーンのポインタ
//=============================================================================
void COjama::HitBullet(CScene *pScene)
{
	// 受け取った弾のタイプが1Pの時
	if (((CBullet*)pScene)->GetBulletType() == CBullet::BULLET_TYPE_1P)
	{
		if (m_OjamaPlayerNum == OJAMAPLAYER_2P)
		{
			// プレイヤー2に当てられたらプレイヤー2のおじゃまをクリエイト(2回目はあれをクリエイト)
			if (m_nCount < 1)
			{
				m_nOjamaCount = rand() % 3;
				switch (m_nOjamaCount)
				{
				case 0:
					COjama::Create(m_pos, D3DXVECTOR3(-10.0f, -10.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f),
						m_nCount + 1, D3DXVECTOR3(2.0f, 2.0f, 0.0f), COjama::OJAMA_TYPE_THROUGH, COjama::OJAMAPLAYER_1P, OBJTYPE_OJAMA);
					break;

				case 1:
					COjama::Create(m_pos, D3DXVECTOR3(-10.0f, -10.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f),
						m_nCount + 1, D3DXVECTOR3(-(float)(rand() % 3) - 2.0f, -2.0f, 0.0f), COjama::OJAMA_TYPE_CURVE, COjama::OJAMAPLAYER_1P, OBJTYPE_OJAMA);
					break;

				case 2:
					COjama::Create(m_pos, D3DXVECTOR3(-(float)(rand() % 10) + 15.0f, -(float)(rand() % 10) + 15.0f, 0.0f),
						D3DXVECTOR3(50.0f, 50.0f, 0.0f), m_nCount + 1,
						D3DXVECTOR3(-(float)(rand() % 5) - 5.0f, 5.0f, 0.0f), COjama::OJAMA_TYPE_FALL, COjama::OJAMAPLAYER_1P, OBJTYPE_OJAMA);
					break;
				default:
					break;
				}

				//終了処理
				Uninit();
				return;
			}
			else
			{
				ExtraAttackCreate(CPlayer::PLAYER_1P);
			}
		}
	}
	// 受け取った弾のタイプが2Pの時
	if (((CBullet*)pScene)->GetBulletType() == CBullet::BULLET_TYPE_2P)
	{
		if (m_OjamaPlayerNum == OJAMAPLAYER_1P)
		{
			// プレイヤー2に当てられたらプレイヤー2のおじゃまをクリエイト(2回目はあれをクリエイト)
			if (m_nCount < 1)
			{
				m_nOjamaCount = rand() % 3;
				switch (m_nOjamaCount)
				{
				case 0:
					COjama::Create(m_pos, D3DXVECTOR3(-10.0f, -10.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f),
						m_nCount + 1, D3DXVECTOR3(2.0f, 2.0f, 0.0f), COjama::OJAMA_TYPE_THROUGH, COjama::OJAMAPLAYER_2P, OBJTYPE_OJAMA);
					break;

				case 1:
					COjama::Create(m_pos, D3DXVECTOR3(-10.0f, -10.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f),
						m_nCount + 1, D3DXVECTOR3(-(float)(rand() % 3) - 2.0f, -2.0f, 0.0f), COjama::OJAMA_TYPE_CURVE, COjama::OJAMAPLAYER_2P, OBJTYPE_OJAMA);
					break;

				case 2:
					COjama::Create(m_pos, D3DXVECTOR3(-(float)(rand() % 10) + 15.0f, -(float)(rand() % 10) + 15.0f, 0.0f),
						D3DXVECTOR3(50.0f, 50.0f, 0.0f), m_nCount + 1,
						D3DXVECTOR3(-(float)(rand() % 5) - 5.0f, 5.0f, 0.0f), COjama::OJAMA_TYPE_FALL, COjama::OJAMAPLAYER_2P, OBJTYPE_OJAMA);
					break;

				default:
					break;
				}
				//終了処理
				Uninit();
				return;
			}
			else
			{
				ExtraAttackCreate(CPlayer::PLAYER_2P);
			}
		}
	}
}

//=============================================================================
// おじゃまクラスの爆発に当たったときの処理
// pScene：爆発のシーンのポインタ
//=============================================================================
void COjama::HitExplosion(CScene *pScene)
{
	// 受け取った弾のタイプが1Pの時
	if (((CBullet*)pScene)->GetBulletType() == CBullet::BULLET_TYPE_1P)
	{
		// プレイヤーに当てられたらプレイヤーのおじゃまをクリエイト(2回目はあれをクリエイト)
		if (m_nCount < 1)
		{
			m_nOjamaCount = rand() % 3;
			switch (m_nOjamaCount)
			{
			case 0:
				COjama::Create(m_pos, D3DXVECTOR3(-10.0f, -10.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f),
					m_nCount + 1, D3DXVECTOR3(2.0f, 2.0f, 0.0f), COjama::OJAMA_TYPE_THROUGH, COjama::OJAMAPLAYER_1P, OBJTYPE_OJAMA);
				break;

			case 1:
				COjama::Create(m_pos, D3DXVECTOR3(10.0f, -10.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f),
					m_nCount + 1, D3DXVECTOR3((float)(rand() % 3) + 2.0f, -2.0f, 0.0f), COjama::OJAMA_TYPE_CURVE, COjama::OJAMAPLAYER_1P, OBJTYPE_OJAMA);
				break;

			case 2:
				COjama::Create(m_pos, D3DXVECTOR3((float)(rand() % 10) - 15.0f, (float)(rand() % 10) - 15.0f, 0.0f),
					D3DXVECTOR3(50.0f, 50.0f, 0.0f), m_nCount + 1,
					D3DXVECTOR3((float)(rand() % 5) + 5.0f, 5.0f, 0.0f), COjama::OJAMA_TYPE_FALL, COjama::OJAMAPLAYER_1P, OBJTYPE_OJAMA);
				break;

			default:
				break;
			}
			//終了処理
			Uninit();
		}
		else
		{
			ExtraAttackCreate(CPlayer::PLAYER_2P);
		}
	}

	// 受け取った弾のタイプが2Pの時
	if (((CBullet*)pScene)->GetBulletType() == CBullet::BULLET_TYPE_2P)
	{
		// プレイヤーに当てられたらプレイヤーのおじゃまをクリエイト(2回目はあれをクリエイト)
		if (m_nCount < 1)
		{
			m_nOjamaCount = rand() % 3;
			switch (m_nOjamaCount)
			{
			case 0:
				COjama::Create(m_pos, D3DXVECTOR3(-10.0f, -10.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f),
					m_nCount + 1, D3DXVECTOR3(2.0f, 2.0f, 0.0f), COjama::OJAMA_TYPE_THROUGH, COjama::OJAMAPLAYER_2P, OBJTYPE_OJAMA);
				break;

			case 1:
				COjama::Create(m_pos, D3DXVECTOR3(-10.0f, -10.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f),
					m_nCount + 1, D3DXVECTOR3(-(float)(rand() % 3) - 2.0f, -2.0f, 0.0f), COjama::OJAMA_TYPE_CURVE, COjama::OJAMAPLAYER_2P, OBJTYPE_OJAMA);
				break;

			case 2:
				COjama::Create(m_pos, D3DXVECTOR3(-(float)(rand() % 10) + 15.0f, -(float)(rand() % 10) + 15.0f, 0.0f),
					D3DXVECTOR3(50.0f, 50.0f, 0.0f), m_nCount + 1,
					D3DXVECTOR3(-(float)(rand() % 5) - 5.0f, 5.0f, 0.0f), COjama::OJAMA_TYPE_FALL, COjama::OJAMAPLAYER_2P, OBJTYPE_OJAMA);
				break;

			default:
				break;
			}
			Uninit();
			return;
		}
		else
		{
			ExtraAttackCreate(CPlayer::PLAYER_1P);
		}
	}
}

//=============================================================================
// おじゃまクラスのエクストラアタックを作る処理
// PlayerNum：プレイヤーの番号
//=============================================================================
void COjama::ExtraAttackCreate(CPlayer::PLAYERNUM PlayerNum)
{
	//プレイヤーのシーンのゲット
	CScene *pScene = CScene::GetSceneTop(CScene::OBJTYPE_PLAYER);
	do
	{
		if (pScene != NULL)
		{
			OBJTYPE objType = pScene->GetObjType();

			// オブジェタイプがプレイヤーの時
			if (objType == OBJTYPE_PLAYER)
			{
				switch (PlayerNum)
				{
				case CPlayer::PLAYER_1P:
					if (((CPlayer*)pScene)->GetPlayerNum() == PlayerNum)
					{
						// 角度を決める
						m_fAngle = atan2f(m_pos.x - ((CScene2D*)pScene)->GetPosition().x, m_pos.y - ((CScene2D*)pScene)->GetPosition().y);

						// エクストラアタックの生成
						CExtraattck::Create(m_pos, D3DXVECTOR3(sinf(m_fAngle) * -10.0f, cosf(m_fAngle) * -10.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f),
							CExtraattck::EXTRAATTCK_PLAYER1, CExtraattck::EXTRAATTACK_BLINKING, OBJTYPE_EXTRAATTACK);

						//終了処理
						Uninit();
						return;
					}

					break;

				case CPlayer::PLAYER_2P:
					if (((CPlayer*)pScene)->GetPlayerNum() == PlayerNum)
					{
						// 角度を決める
						m_fAngle = atan2f(m_pos.x - ((CScene2D*)pScene)->GetPosition().x, m_pos.y - ((CScene2D*)pScene)->GetPosition().y);

						// エクストラアタックの生成
						CExtraattck::Create(m_pos, D3DXVECTOR3(sinf(m_fAngle) * -10.0f, cosf(m_fAngle) * -10.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f),
							CExtraattck::EXTRAATTCK_PLAYER2, CExtraattck::EXTRAATTACK_AIM, OBJTYPE_EXTRAATTACK);

						//終了処理
						Uninit();
						return;
					}
					break;

				default:
					break;
				}
			}
			pScene = pScene->GetSceneNext();
		}
	} while (true);
}

//=============================================================================
// おじゃまクラスのプレイヤーの番号を返す処理
//=============================================================================
COjama::OJAMAPLAYERNUM COjama::GetOjamaPlayerNum(void)
{
	return m_OjamaPlayerNum;
}


