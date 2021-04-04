//=============================================================================
//
// エクストラアタックの処理 [extraattack.cpp]
// Author : 伊藤陽梧
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "extraattack.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "explosion.h"
#include "enemy.h"
#include "life.h"
#include "effect.h"
#include "bullet.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define EXPLOSION_SIZE_X (100.0f)			// 爆発の縦の長さ
#define EXPLOSION_SIZE_Y (100.0f)			// 爆発の横の長さ

#define EXTRAATTACK_BLINKING_POS (D3DXVECTOR3(745.0f,1000.0f,0.0f))
#define EXTRAATTACK_BLINKING_MOVE (10.0f)

#define EXTRAATTACK_AIM_COUNTERANIM (4)
#define EXTRAATTACK_AIM_PATTERNANIM (1)
#define EXTRAATTACK_AIM_TIMEANIM (10)
#define EXTRAATTACK_AIM_MOVE (10.0f)

#define EXTRAATTACK_EXPLOSION_COUNTERANIM (2)
#define EXTRAATTACK_EXPLOSION_PATTERNANIM (1)
#define EXTRAATTACK_EXPLOSION_TIMEANIM (1)
#define EXTRAATTACK_EXPLOSION_SIZE (D3DXVECTOR3(100.0f, 100.0f, 0.0f))
#define EXTRAATTACK_EXPLOSION_ADDSIZE (2.0f)
#define EXTRAATTACK_EXPLOSION_MAX_SIZE (200.0f)

#define EXTRAATTACK_LOCKET_COUNTERANIM (3)
#define EXTRAATTACK_LOCKET_PATTERNANIM (1)
#define EXTRAATTACK_LOCKET_TIMEANIM (10)
#define EXTRAATTACK_LOCKET_MOVE (D3DXVECTOR3(0.0f, -5.0f, 0.0f))
#define EXTRAATTACK_LOCKET_SIZE (D3DXVECTOR3(100.0f, 100.0f, 0.0f))

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CExtraattck::m_pTexture[MAX_EXTRAATTACK_TEXTURE] = {};

//=============================================================================
// エクストラアタッククラスのコンストラクタ
//=============================================================================
CExtraattck::CExtraattck() :CScene2D(OBJTYPE_EXTRAATTACK)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Getpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCountColor = 0;
	m_ExtraPlayerNum = EXTRAATTCK_PLAYER_NONE;
	m_ExtraAttack = EXTRAATTACK_BLINKING;
}

//=============================================================================
// エクストラアタッククラスのデストラクタ
//=============================================================================
CExtraattck::~CExtraattck()
{

}

//=============================================================================
// エクストラアタッククラスのテクスチャの読み込み
//=============================================================================
HRESULT CExtraattck::Load(void)
{
	// インスタンス生成したものを受け取る
	CRenderer *pRenderer = CManager::GetRenderer();

	// デバイスを受け取る
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_TIKATIKA, &m_pTexture[EXTRAATTACK_BLINKING]);		// チカチカしながら相手の方に行くエクストラアタック
	D3DXCreateTextureFromFile(pDevice, TEXTURE_OBAKE, &m_pTexture[EXTRAATTACK_AIM]);			// 相手を狙うエクストラアタック
	D3DXCreateTextureFromFile(pDevice, TEXTURE_EXTRAEXPLOSION, &m_pTexture[EXTRAATTACK_EXPLOSION]);	// 爆発するエクストラアタック
	D3DXCreateTextureFromFile(pDevice, TEXTURE_HONE, &m_pTexture[EXTRAATTACK_LOCKET]);			// 上にあがるエクストラアタック

	return S_OK;
}

//=============================================================================
// エクストラアタッククラスのテクスチャの破棄
//=============================================================================
void CExtraattck::Unload(void)
{
	for (int nCount = 0; nCount < MAX_EXTRAATTACK_TEXTURE; nCount++)
	{
		// テクスチャの破棄
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
// エクストラアタッククラスのインスタンス生成
//=============================================================================
CExtraattck* CExtraattck::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, EXTRAATTCKPLAYERNUM Player, EXTRAATTACK Extraattack, OBJTYPE objType)
{
	// CExtraattckのポインタ
	CExtraattck *pExtraattck = NULL;

	// メモリの確保
	pExtraattck = new CExtraattck;

	// pExtraattckがNULLじゃないとき
	if (pExtraattck != NULL)
	{
		// エクストラアタックのセット
		pExtraattck->SetExtraAttack(pos, move, size, Player, Extraattack, objType);

		// 初期化処理
		pExtraattck->Init();
	}

	// pExtraattckを返す
	return pExtraattck;
}

//=============================================================================
// エクストラアタッククラスの初期化処理
//=============================================================================
HRESULT CExtraattck::Init()
{
	// CScene2Dの初期化処理
	CScene2D::Init();

	//プレイヤーのシーンのゲット
	CScene *pScene = CScene::GetSceneTop(CScene::OBJTYPE_PLAYER);

	switch (m_ExtraAttack)
	{
		// チカチカしながら相手の方に行くエクストラアタック
	case EXTRAATTACK_BLINKING:
		// テクスチャの設定
		BindTexture(m_pTexture[EXTRAATTACK_BLINKING]);

		// プレイヤー1のエクストラアタックの時
		if (m_ExtraPlayerNum == EXTRAATTCK_PLAYER1)
		{
			// 座標の設定
			m_Getpos.x = (float)(rand() % (int)EXTRAATTACK_BLINKING_POS.x) + PLAYER2_MOVABLE_RANGE_S;
			m_Getpos.y = EXTRAATTACK_BLINKING_POS.y;
		}
		// プレイヤー2のエクストラアタックの時
		if (m_ExtraPlayerNum == EXTRAATTCK_PLAYER2)
		{
			// 座標の設定
			m_Getpos.x = (float)(rand() % (int)EXTRAATTACK_BLINKING_POS.x) + PLAYER_MOVABLE_RANGE_S;
			m_Getpos.y = EXTRAATTACK_BLINKING_POS.y;
		}
		break;

		// 相手を狙うエクストラアタック
	case EXTRAATTACK_AIM:
		// テクスチャの設定
		BindTexture(m_pTexture[EXTRAATTACK_AIM]);
		// アニメーションのセット
		SetAnimation(EXTRAATTACK_AIM_COUNTERANIM, EXTRAATTACK_AIM_PATTERNANIM, EXTRAATTACK_AIM_TIMEANIM);
		do
		{
			if (pScene != NULL)
			{
				OBJTYPE objType = pScene->GetObjType();
				if (objType == OBJTYPE_PLAYER)
				{
					switch (m_ExtraPlayerNum)
					{
					case EXTRAATTCK_PLAYER1:
						// 2Pの座標が欲しい
						if (((CPlayer*)pScene)->GetPlayerNum() == CPlayer::PLAYER_2P)
						{
							// 座標を受け取る
							m_Getpos = ((CScene2D*)pScene)->GetPosition();
						}
						break;

					case EXTRAATTCK_PLAYER2:

						// 1Pの座標が欲しい
						if (((CPlayer*)pScene)->GetPlayerNum() == CPlayer::PLAYER_1P)
						{
							// 座標を受け取る
							m_Getpos = ((CScene2D*)pScene)->GetPosition();
						}
						break;

					default:
						break;
					}

				}
				pScene = pScene->GetSceneNext();
			}
		} while (pScene != NULL);
		break;

		// 爆発するエクストラアタック
	case EXTRAATTACK_EXPLOSION:
		// テクスチャの設定
		BindTexture(m_pTexture[EXTRAATTACK_EXPLOSION]);
		// アニメーションのセット
		SetAnimation(EXTRAATTACK_EXPLOSION_COUNTERANIM, EXTRAATTACK_EXPLOSION_PATTERNANIM, EXTRAATTACK_EXPLOSION_TIMEANIM);
		break;

		// 上にあがるエクストラアタック
	case EXTRAATTACK_LOCKET:
		// テクスチャの設定
		BindTexture(m_pTexture[EXTRAATTACK_LOCKET]);
		// アニメーションのセット
		SetAnimation(EXTRAATTACK_LOCKET_COUNTERANIM, EXTRAATTACK_LOCKET_PATTERNANIM, EXTRAATTACK_LOCKET_TIMEANIM);
		break;

	default:
		break;
	}

	return S_OK;
}

//=============================================================================
// エクストラアタッククラスの終了処理
//=============================================================================
void CExtraattck::Uninit(void)
{
	// CScene2Dの終了処理
	CScene2D::Uninit();
}

//=============================================================================
// エクストラアタッククラスの更新処理
//=============================================================================
void CExtraattck::Update(void)
{
	// CScene2Dの更新処理
	CScene2D::Update();

	// 座標と体力の受け取り
	m_pos = GetPosition();

	switch (m_ExtraAttack)
	{
		// チカチカしながら相手の方に行くエクストラアタック
	case EXTRAATTACK_BLINKING:
		Blinking();
		break;

		// 相手を狙うエクストラアタック
	case EXTRAATTACK_AIM:
		Aim();
		break;

		// 爆発するエクストラアタック
	case EXTRAATTACK_EXPLOSION:
		Explosion();
		break;

		// 上にあがるエクストラアタック
	case EXTRAATTACK_LOCKET:
		Locket();
		break;

	default:
		break;
	}

	// 座標とサイズ、体力を渡す
	SetPosition(m_pos);
	SetSize(m_size);
}

//=============================================================================
// エクストラアタッククラスの描画処理
//=============================================================================
void CExtraattck::Draw(void)
{
	// CScene2Dの描画処理
	CScene2D::Draw();
}

//=============================================================================
// エクストラアタッククラスのチカチカするエクストラアタックの処理
//=============================================================================
void CExtraattck::Blinking(void)
{
	// 移動量の加算
	m_pos += m_move;

	// 角度の計算
	m_fAngle = atan2f(m_pos.x - m_Getpos.x, m_pos.y - m_Getpos.y);

	// 決めた角度の方に飛ばす
	m_move.x = sinf(m_fAngle) * -EXTRAATTACK_BLINKING_MOVE;
	m_move.y = cosf(m_fAngle) * -EXTRAATTACK_BLINKING_MOVE;

	// 色のカウントが0の時
	if (m_nCountColor == 0)
	{
		// 色のセット
		SetColor(0, 0, 255, 255);
		m_nCountColor++;
	}
	// 色のカウントが1の時
	else if (m_nCountColor == 1)
	{
		// 色のセット
		SetColor(255, 255, 255, 255);
		m_nCountColor = 0;
	}

	switch (m_ExtraPlayerNum)
	{
		// プレイヤー1のエクストラアタック
	case EXTRAATTCK_PLAYER1:
		if (m_pos.x >= m_Getpos.x)
		{
			// エクストラアタックの生成
			Create(m_pos, EXTRAATTACK_LOCKET_MOVE, EXTRAATTACK_LOCKET_SIZE,
				EXTRAATTCK_PLAYER1, EXTRAATTACK_LOCKET, OBJTYPE_EXTRAATTACK);

			// 終了処理
			Uninit();
			return;
		}
		break;

		// プレイヤー2のエクストラアタック
	case EXTRAATTCK_PLAYER2:
		if (m_pos.x <= m_Getpos.x)
		{
			// エクストラアタックの生成
			Create(m_pos, EXTRAATTACK_LOCKET_MOVE, EXTRAATTACK_LOCKET_SIZE,
				EXTRAATTCK_PLAYER2, EXTRAATTACK_LOCKET, OBJTYPE_EXTRAATTACK);

			// 終了処理
			Uninit();
			return;
		}
		break;

	default:
		break;
	}
}

//=============================================================================
// エクストラアタッククラスの相手を狙うエクストラアタックの処理
//=============================================================================
void CExtraattck::Aim(void)
{
	// 移動量の加算
	m_pos += m_move;

	// 角度の計算
	m_fAngle = atan2f(m_pos.x - m_Getpos.x, m_pos.y - m_Getpos.y);

	// 決めた角度の方に飛ばす
	m_move.x = sinf(m_fAngle) * -EXTRAATTACK_AIM_MOVE;
	m_move.y = cosf(m_fAngle) * -EXTRAATTACK_AIM_MOVE;

	switch (m_ExtraPlayerNum)
	{
		// プレイヤー1のエクストラアタック
	case EXTRAATTCK_PLAYER1:
		if (m_pos.x >= m_Getpos.x)
		{
			// エクストラアタックの生成
			Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), EXTRAATTACK_EXPLOSION_SIZE,
				EXTRAATTCK_PLAYER1, EXTRAATTACK_EXPLOSION, OBJTYPE_EXTRAATTACK);

			// 終了処理
			Uninit();
			return;
		}
		break;

		// プレイヤー2のエクストラアタック
	case EXTRAATTCK_PLAYER2:
		if (m_pos.x <= m_Getpos.x)
		{
			// エクストラアタックの生成
			Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), EXTRAATTACK_EXPLOSION_SIZE,
				EXTRAATTCK_PLAYER2, EXTRAATTACK_EXPLOSION, OBJTYPE_EXTRAATTACK);

			// 終了処理
			Uninit();
			return;
		}
		break;

	default:
		break;
	}
}

//=============================================================================
// エクストラアタッククラスの爆発するエクストラアタックの処理
//=============================================================================
void CExtraattck::Explosion(void)
{
	// サイズの加算
	m_size.x += EXTRAATTACK_EXPLOSION_ADDSIZE;
	m_size.y += EXTRAATTACK_EXPLOSION_ADDSIZE;

	// サイズが200.0f以上なら終了処理をする
	if (m_size.x >= EXTRAATTACK_EXPLOSION_MAX_SIZE && m_size.y >= EXTRAATTACK_EXPLOSION_MAX_SIZE)
	{
		// 終了処理
		Uninit();
		return;
	}
}

//=============================================================================
// エクストラアタッククラスの上にあがるエクストラアタックの処理
//=============================================================================
void CExtraattck::Locket(void)
{
	m_pos += m_move;

	// 画面外に出たら終了処理をする
	if (m_pos.y < -(m_size.y / 2))
	{
		// 終了処理
		Uninit();
		return;
	}
}

//=============================================================================
// エクストラアタッククラスのエクストラアタックのタイプを渡す処理
//=============================================================================
CExtraattck::EXTRAATTACK CExtraattck::GetExtraAttack(void)
{
	return m_ExtraAttack;
}

CExtraattck::EXTRAATTCKPLAYERNUM CExtraattck::GetExtraPlayerNum(void)
{
	return m_ExtraPlayerNum;
}


