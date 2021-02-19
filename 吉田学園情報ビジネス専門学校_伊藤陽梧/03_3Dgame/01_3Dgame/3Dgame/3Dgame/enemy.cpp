//=============================================================================
//
// 敵の処理 [enemy.cpp]
// Author : 伊藤陽梧
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "joystick.h"
#include "enemy.h"
#include "motion.h"
#include "model.h"
#include "player.h"
#include "game.h"
#include "map.h"
#include "sound.h"
#include "collision.h"
#include "debugcollision.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CEnemy::CEnemy(int nPriority) :CCharacter(nPriority)
{
	m_nCntFrame = 0;
	m_nCntAttack = 0;
	m_bHit = false;
	m_bAttack = false;
	m_EnemyState = ENEMYSTATE_NOMAL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CEnemy::~CEnemy()
{

}

//=============================================================================
// 生成処理
//=============================================================================
CEnemy * CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, ENEMYSTATE EnemyState)
{
    CEnemy *pEnemy;
    pEnemy = new CEnemy;
    pEnemy->SetEnemy(pos, rot, size, EnemyState);
    pEnemy->Init();
    return pEnemy;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CEnemy::Init(void)
{
	SetObjType(OBJTYPE_ENEMY);
	SetType(CHARACTERTYPE_ENEMY);
	LoadInitialPosition(MOTION_ENEMY_TEXT);
	CCharacter::Init();
    return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CEnemy::Uninit(void)
{
	CCharacter::Uninit();

	// リリース
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CEnemy::Update(void)
{
	CCharacter::Update();

	// 敵の状態
	switch (m_EnemyState)
	{
	case ENEMYSTATE_NOMAL:
		if (CGame::GetPlayer != NULL)
		{
			//プレイヤーの場所の取得
			D3DXVECTOR3 PlayerPos = CGame::GetPlayer()->GetPos();

			D3DXVECTOR3 pos = GetPos();
			D3DXVECTOR3 rot = GetRot();
			
			float fDistance = sqrtf(
				powf(PlayerPos.x - pos.x, 2.0f) +
				powf(PlayerPos.z - pos.z, 2.0f));

			if (fDistance <= ENEMY_DISTANCE_PLAYER)
			{
				m_bChase = false;
			}
			else
			{
				m_bChase = true;
			}

			if (m_bChase == true)
			{
				//方向の計算
				float angle = (float)atan2(PlayerPos.x - pos.x, PlayerPos.z - pos.z);
				rot.y = angle - D3DXToRadian(180);

				//向いている方向にrot
				pos.x += -sinf(rot.y) * ENEMY_MOVE_SPEED;
				pos.z += -cosf(rot.y) * ENEMY_MOVE_SPEED;
			}
			SetPos(pos);
			SetRot(rot);

			EnemyCollision();
		}
		break;

	default:
		break;
	}

#ifdef _DEBUG
	// 当たり判定の可視化
	CDebugCollision::Create(GetPos(), GetSize(), CDebugCollision::TYPE_SQUARE);
#endif
}

//=============================================================================
// 描画処理
//=============================================================================
void CEnemy::Draw(void)
{
	CCharacter::Draw();
}

//=============================================================================
// ヒット処理
//=============================================================================
void CEnemy::HitDamage(int nDamage)
{
	if (m_EnemyState == ENEMYSTATE_NOMAL)
	{
		int nLife = GetLife();
		if (m_bHit == false)
		{
			//m_bHit = true;
			nLife -= nDamage;
			SetLife(nLife);
		}
		if (nLife <= 0)
		{
			//サウンドの再生
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_ZOMBIE_DEATH);
			CGame::SubtractEnemy();
			Uninit();
		}
		else
		{
			//サウンドの再生
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_ZOMBIE_DAMAGE);
		}
	}
}


//=============================================================================
// 敵同士の当たり判定の処理
//=============================================================================
void CEnemy::EnemyCollision(void)
{
	// ゲット
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	D3DXVECTOR3 size = GetSize();

	CScene *pScene = GetSceneTop(OBJTYPE_ENEMY);
	do
	{
		if (pScene != NULL)
		{
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_ENEMY)
			{
				// 座標とサイズの受け取り
				D3DXVECTOR3 Getpos = ((CEnemy*)pScene)->GetPos();
				D3DXVECTOR3 Getrot = ((CEnemy*)pScene)->GetRot();
				D3DXVECTOR3 Getsize = ((CEnemy*)pScene)->GetSize();

				float c = sqrtf(size.x * size.x + Getsize.x * Getsize.x);
				float fAngle = atan2f(pos.x - Getpos.x, pos.z - Getpos.z);

				if (Getpos != pos)
				{
					// 当たり判定
					if (CCollision::SphereCollision(pos, size.x, Getpos, Getsize.x) == true)
					{
						// 戻す
						//m_pos -= (D3DXVECTOR3(cosf(fAngle), 0.0f, sinf(fAngle)));
						pos.x -= -sinf(rot.y + D3DXToRadian(2))*0.4f;
						pos.z -= -cosf(rot.y + D3DXToRadian(2))*0.4f;
					}
				}
			}
			// 次のポインタの受け取り
			pScene = pScene->GetSceneNext();
		}
	} while (pScene != NULL);

	// セット
	SetPos(pos);
}

//=============================================================================
// 各種設定
//=============================================================================
void CEnemy::SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, ENEMYSTATE EnemyState)
{
	SetObjType(OBJTYPE_ENEMY); //オブジェクトタイプの設定
	SetPos(pos);
	SetRot(rot);
	SetSize(size);
	m_EnemyState = EnemyState;
	SetLife(ENEMY_LIFE);
}