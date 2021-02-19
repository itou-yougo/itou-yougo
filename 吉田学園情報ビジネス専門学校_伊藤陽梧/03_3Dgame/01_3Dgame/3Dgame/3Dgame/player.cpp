//=============================================================================
//
// プレイヤーの処理 [player.cpp]
// Author : 伊藤陽梧
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "joystick.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "motion.h"
#include "collision.h"
#include "sound.h"
#include "camera.h"
#include "slash.h"
#include "debugcollision.h"
#include "swordeffect.h"
#include "spark.h"
#include "spesialattackeffect.h"
#include "magiccircle.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
bool CPlayer::m_bDeath = false;

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer::CPlayer(int nPriority) : CCharacter(nPriority)
{
	m_fNotControl = 0.0f;
	m_bAttackHit = false;

	//ダメージモーション
	m_nDamageMotionCnt = 0;
	m_bDamageMotion = false;

	//死亡モーション
	m_nDeathMotionCnt = 0;
	m_bDeathMotion = false;

	//死亡フラグ
	m_bDeath = false;

	m_nSwordEffectTime = 0;

	m_pEnemy = NULL;
	m_Playerstate = PLAYERSTATE_NOMAL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// 生成処理
//=============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CPlayer *pPlayer;
	pPlayer = new CPlayer;
	pPlayer->SetPlayer(pos, rot, size);
	pPlayer->Init();
	return pPlayer;
}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CPlayer::Init(void)
{
	SetObjType(OBJTYPE_PLAYER);
	SetType(CHARACTERTYPE_PLAYER);
	LoadInitialPosition(MOTION_PLAYER_TEXT);
	CCharacter::Init();

	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void CPlayer::Uninit(void)
{
	// フェードの生成
	CManager::CreateFade(CManager::MODE_GAMEOVER);

	CCharacter::Uninit();

	// リリース
	Release();
}

//=============================================================================
//更新処理
//=============================================================================
void CPlayer::Update(void)
{
	CCharacter::Update();

	// コントロールできない時間が0以下だったら
	if (m_fNotControl <= 0.0f)
	{
		m_Playerstate = PLAYERSTATE_NOMAL;
	}

	// ゴールしたら
	if (GetPos().z >= 830.0f)
	{
		if (CScene::GetUpdateStop() == false)
		{
			//サウンドの停止
			CManager::GetSound()->StopSound(CSound::SOUND_LABEL_BGM_GAME);
			CManager::GetSound()->StopSound(CSound::SOUND_LABEL_SE_DASH);

			//フェードの生成
			CManager::CreateFade(CManager::MODE_RESULT);
		}
	}
	
	// 剣の先と持ち手の位置の距離
	D3DXVECTOR3 Top = D3DXVECTOR3(GetModelParts(12)->GetMtxWorld()._41, GetModelParts(12)->GetMtxWorld()._42, GetModelParts(12)->GetMtxWorld()._43);
	D3DXVECTOR3 Bottom = D3DXVECTOR3(GetModelParts(11)->GetMtxWorld()._41, GetModelParts(11)->GetMtxWorld()._42, GetModelParts(11)->GetMtxWorld()._43);
	D3DXVECTOR3 Distance = D3DXVECTOR3(Top.x - Bottom.x, Top.y - Bottom.y, Top.z - Bottom.z);

	// 死んでいないなら
	if (m_bDeath == false)
	{
		if (m_Playerstate == PLAYERSTATE_NOMAL)
		{
			//ゲームパッド操作
			GamePad();
			
			// 当たり判定を復活させる
			m_bAttackHit = false;
		}
		if (m_Playerstate == PLAYERSTATE_ATTACK)
		{
			//攻撃の処理
			Attack(Distance);
		}

		// 剣のエフェクトの処理
		Swordeffect(Distance);
	}

	// 死んだなら
	if (m_bDeath == true)
	{
		if (m_bDeathMotion == false)
		{
			//// 死亡モーション
			//GetMotion()->SetMotion(CMotion::MOTION_DEATH);
			m_bDeathMotion = true;
			//サウンドの停止
			CManager::GetSound()->StopSound(CSound::SOUND_LABEL_SE_DASH);
			return;
		}
		//死亡モーション中なら
		if (m_bDeathMotion == true)
		{
			m_nDeathMotionCnt++;
			//120フレームでリセット
			if (m_nDeathMotionCnt % 120 == 0)
			{
				m_bDeathMotion = false;
				m_nDeathMotionCnt = 0;
				Uninit();
				CManager::CreateFade(CManager::MODE_GAMEOVER);
			}
		}
	}

#ifdef _DEBUG
	// 当たり判定の可視化
	D3DXVECTOR3 GetDistance = Distance / SWORD_EFFECT_NUM;
	for (int nCount = 0; nCount < SWORD_EFFECT_NUM; nCount++)
	{
		CDebugCollision::Create(D3DXVECTOR3(GetModelParts(11)->GetMtxWorld()._41,
			GetModelParts(11)->GetMtxWorld()._42,
			GetModelParts(11)->GetMtxWorld()._43) + (GetDistance * (float)nCount),
			D3DXVECTOR3(5.0f, 5.0f, 5.0f), CDebugCollision::TYPE_SQUARE);
	}

	CDebugCollision::Create(GetPos(), GetSize(), CDebugCollision::TYPE_SQUARE);

	CDebugCollision::Create(GetPos(), D3DXVECTOR3(GetSize().y, GetSize().y, GetSize().y), CDebugCollision::TYPE_SPHERE);
#endif
}

//=============================================================================
//描画処理
//=============================================================================
void CPlayer::Draw(void)
{
	CCharacter::Draw();
}

//=============================================================================
//ゲームパッド処理
//=============================================================================
void CPlayer::GamePad(void)
{
	//コントローラーの取得処理
	DIJOYSTATE pStick = {};
	CInputJoystick *pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 pJoystickDevice = CInputJoystick::GetDevice();
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	if (pJoystickDevice != NULL)
	{
		pJoystickDevice->Poll();
		pJoystickDevice->GetDeviceState(sizeof(DIJOYSTATE), &pStick);
	}
	if (pJoystickDevice != NULL)
	{
		//ダメージモーション中でないなら
		if (m_bDamageMotion == false)
		{
			//通常モーション
			GetMotion()->SetMotion(MOTION_IDLE);
		}

		//--------------------------
		//移動
		//--------------------------
		// スティックの入力があったら
		if (pStick.lY != 0 || pStick.lX != 0)
		{
			// スティックの角度を求める
			float fAngle = atan2(pStick.lX * -1.0f, pStick.lY);

			// スティックの角度から移動する方向を決める
			pos.x -= sinf(CManager::GetCamera()->GetAngle() + fAngle) * MOVE_SPEED;
			pos.z -= cosf(CManager::GetCamera()->GetAngle() + fAngle) * MOVE_SPEED;

			// キャラの向きを変える
			rot.y = CManager::GetCamera()->GetAngle() + fAngle;

			// 走るモーション
			GetMotion()->SetMotion(MOTION_RUN);
		}

		if (rot.y > D3DX_PI)
		{
			rot.y -= D3DX_PI * 2;
		}
		if (rot.y < -D3DX_PI)
		{
			rot.y += D3DX_PI * 2;
		}

		// Xボタンを押したら
		if (pInputJoystick->GetJoystickTrigger(CInputJoystick::BUTTON_X))
		{
			// 斬るモーション
			GetMotion()->SetMotion(MOTION_SLASH);
			m_Playerstate = PLAYERSTATE_ATTACK;
			m_fNotControl = SLASH_FLAME;
		}

		// Yボタンを押したら
		if (pInputJoystick->GetJoystickTrigger(CInputJoystick::BUTTON_Y))
		{
			// 魔法陣の生成
			CMagiccercle::Create(D3DXVECTOR3(pos.x, 0.0f, pos.z), MAGICCERCLE_DEFAULT_ROT, MAGICCERCLE_DEFAULT_SIZE, MAGICCERCLE_DEFAULT_COLOR, 1200);
			
			// 必殺技のエフェクトの生成
			CSpesialattackeffect::Create(GetPos(), SPESIALATTACKEFFECT_SIZE,
				SPESIALATTACKEFFECT_COLOR, SPESIALATTACKEFFECT_COUNTANIM * SPESIALATTACKEFFECT_PATTERNANIM * SPESIALATTACKEFFECT_TIMEANIM);
		}

	}

	// 座標と回転のセット
	SetPos(pos);
	SetRot(rot);
}

//=============================================================================
// 攻撃処理
//=============================================================================
void CPlayer::Attack(D3DXVECTOR3 Distance)
{
	D3DXVECTOR3 rot = GetRot();
	D3DXVECTOR3 GetDistance = Distance / SWORD_EFFECT_NUM;
	// 操作できない時間
	if (m_fNotControl > 0.0f)
	{
		if (m_fNotControl < SLASH_FLAME - SLASH_FLAME_EFFECT_START && m_fNotControl > 10.0f)
		{
			// 移動の角度を決める
			D3DXVECTOR3 moveAngle = D3DXVECTOR3(sinf(rot.y) * -1, 0.0f, cosf(rot.y) * -1);

			//CSlash::Create(D3DXVECTOR3(GetModelParts(11)->GetMtxWorld()._41,
			//	GetModelParts(11)->GetMtxWorld()._42,
			//	GetModelParts(11)->GetMtxWorld()._43) + Distance,
			//	SLASH_SIZE, moveAngle,
			//	SLASH_COLOR, SLASH_LIFE, CSlash::TYPE_SLASH_1);

			// 敵への当たり判定
			CScene *pScene = CScene::GetSceneTop(CScene::OBJTYPE_ENEMY);
			do
			{
				if (pScene != NULL)
				{
					OBJTYPE objType = pScene->GetObjType();
					if (objType == OBJTYPE_ENEMY)
					{
						// 座標とサイズの受け取り
						D3DXVECTOR3 pos = ((CEnemy*)pScene)->GetPos();
						D3DXVECTOR3 Size = ((CEnemy*)pScene)->GetSize();

						for (int nCount = 0; nCount < SWORD_EFFECT_NUM; nCount++)
						{
							if (m_bAttackHit == false)
							{
								// 当たり判定
								if (CCollision::RectangleCollision3D(D3DXVECTOR3(GetModelParts(11)->GetMtxWorld()._41,
									GetModelParts(11)->GetMtxWorld()._42,
									GetModelParts(11)->GetMtxWorld()._43) + (GetDistance * (float)nCount),
									SWORD_COLISION_SIZE, pos, Size) == true)
								{
									CSpark::Create(D3DXVECTOR3(GetModelParts(11)->GetMtxWorld()._41,
										GetModelParts(11)->GetMtxWorld()._42,
										GetModelParts(11)->GetMtxWorld()._43) + (GetDistance * (float)nCount),
										D3DXVECTOR3(200.0f, 200.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), SPARK_COUNTANIM * SPARK_PATTERNANIM * SPARK_TIMEANIM);

									// 当たり判定をなくす
									m_bAttackHit = true;

									// 敵へのダメージ
									((CEnemy*)pScene)->HitDamage(5);
								}
							}
						}
					}
					pScene = pScene->GetSceneNext();
				}
			} while (pScene != NULL);
		}

		m_fNotControl -= SUBTRACT_FLAME;
	}
}

//=============================================================================
// 剣のエフェクトの処理
//=============================================================================
void CPlayer::Swordeffect(D3DXVECTOR3 Distance)
{
	D3DXVECTOR3 GetDistance = (float)(rand() % SWORD_EFFECT_NUM) * (Distance / SWORD_EFFECT_NUM);

	m_nSwordEffectTime++;
	if (m_nSwordEffectTime >= SWORD_EFFECT_CREATE_TIME)
	{
		// 剣のエフェクト
		CSwordeffect::Create(D3DXVECTOR3(GetModelParts(11)->GetMtxWorld()._41,
			GetModelParts(11)->GetMtxWorld()._42,
			GetModelParts(11)->GetMtxWorld()._43) + GetDistance,
			SWORD_EFFECT_SIZE, D3DXVECTOR3(0.0f, 0.1f, 0.0f),
			SWORD_EFFECT_COLOR, SWORD_EFFECT_LIFE);
		m_nSwordEffectTime = 0;
	}
}

//=============================================================================
// 初期設定
//=============================================================================
void CPlayer::SetPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	SetObjType(OBJTYPE_PLAYER); //オブジェクトタイプの設定
	SetPos(pos);
	SetRot(rot);
	SetSize(size);
	SetLife(PLAYER_LIFE);
}

//=============================================================================
//プレイヤーがダメージを受けたら
//=============================================================================
void CPlayer::HitDamage(int nDamage)
{
	//サウンドの再生
	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_PLAYER_DAMAGE);

	if (m_bDamageMotion == false)
	{	
		////ダメージモーション
		//GetMotion()->SetMotion(CMotion::MOTION_DAMAGE);
		m_bDamageMotion = true;
	}
}

//=============================================================================
//死亡フラグ
//=============================================================================
void CPlayer::DeathFlag(void)
{
	m_bDeath = true;
}