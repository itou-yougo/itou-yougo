//=============================================================================
//
// プレイヤーの処理 [player.h]
// Author : 伊藤陽梧
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "player.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "sound.h"
#include "life.h"
#include "game.h"
#include "chargeshot.h"
#include "charge.h"
#include "gauge.h"
#include "extraattack.h"
#include "bomb.h"
#include "bossattack.h"
#include "effect.h"
#include "ojama.h"
#include "select.h"
#include "collision.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CPlayer::m_apTexture[PLAYER_MAX] = {};
int	CPlayer::m_nDamage = 0;

//=============================================================================
// プレイヤークラスのコンストラクタ
//=============================================================================
CPlayer::CPlayer():CScene2D(OBJTYPE_PLAYER)
{
	m_pLife = NULL;
	m_pChargeShot = NULL;
	m_pEffect = NULL;
	memset(m_pBomb, 0, sizeof(m_pBomb));
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Getpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_GetSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fAngle = 0.0f;
	m_nLife = 0;
	m_nBulletShotCount = 0;
	m_nInvincibleTime = 0;
	m_nRigorTime = 0;
	m_nExtraAttackCount = 0;
	m_nPressTime = 0;
	m_bExtraAttack = false;
	m_bEffectCreate = true;
	m_PlayerState = PLAYERSTATE_NONE;
}

//=============================================================================
// プレイヤークラスのデストラクタ
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// プレイヤークラスのテクスチャの読み込み
//=============================================================================
HRESULT CPlayer::Load(void)
{
	// インスタンス生成したものを受け取る
	CRenderer *pRenderer = CManager::GetRenderer();

	// デバイスを受け取る
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PLAYER, &m_apTexture[PLAYER_1P]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PLAYER2, &m_apTexture[PLAYER_2P]);

	return S_OK;
}

//=============================================================================
// プレイヤークラスのテクスチャの破棄
//=============================================================================
void CPlayer::Unload(void)
{
	for (int nCount = 0; nCount < PLAYER_MAX; nCount++)
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
// プレイヤークラスのインスタンス生成
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nLife, PLAYERNUM PlayerNum, OBJTYPE objType)
{
	// CPlayerのポインタ
	CPlayer *pPlayer = NULL;

	// メモリの確保
	pPlayer = new CPlayer;

	// pPlayerがNULLじゃないとき
	if (pPlayer != NULL)
	{
		// プレイヤーのセット
		pPlayer->SetPlayer(pos, move, size, nLife, PlayerNum, objType);

		// 初期化処理
		pPlayer->Init();
	}

	// pPlayerを返す
	return pPlayer;
}

//=============================================================================
// プレイヤークラスの初期化処理
//=============================================================================
HRESULT CPlayer::Init()
{
	switch (m_PlayerNum)
	{
	case PLAYER_1P:
		// ライフの生成
		m_pLife = CLife::Create(m_nLife, CLife::LIFE_TYPE_PLAYER, OBJTYPE_LIFE);

		// チャージショットの生成
		m_pChargeShot = CChargeshot::Create(D3DXVECTOR3(251.0f, SCREEN_HEIGHT - 80.0f, 0.0f), D3DXVECTOR3(362.0f, 40.0f, 0.0f),
			CChargeshot::CHARGESHOTTYPE_PLAYER, OBJTYPE_BG);

		// ボムの生成
		for (int nCount = 0; nCount < PLAYER_BOMB_MAX; nCount++)
		{
			m_pBomb[nCount] = CBomb::Create(D3DXVECTOR3(SCREEN_CENTER_X - (BOMB_SIZE_X * (nCount + 1)), SCREEN_HEIGHT - BOMB_SIZE_Y, 0.0f),
				D3DXVECTOR3(BOMB_SIZE_X, BOMB_SIZE_Y, 0.0f), CBomb::BOMB_TYPE_PLAYER, OBJTYPE_BG);
		}
		break;

	case PLAYER_2P:
		// ライフの生成
		m_pLife = CLife::Create(m_nLife, CLife::LIFE_TYPE_PLAYER2, OBJTYPE_LIFE);

		// チャージショットの生成
		m_pChargeShot = CChargeshot::Create(D3DXVECTOR3(PLAYER2_MOVABLE_RANGE_L - 181.0f, SCREEN_HEIGHT - 80.0f, 0.0f),
			D3DXVECTOR3(362.0f, 40.0f, 0.0f), CChargeshot::CHARGESHOTTYPE_PLAYER2, OBJTYPE_BG);

		// ボムの生成
		for (int nCount = 0; nCount < PLAYER_BOMB_MAX; nCount++)
		{
			m_pBomb[nCount] = CBomb::Create(D3DXVECTOR3(SCREEN_CENTER_X + (BOMB_SIZE_X * (nCount + 1)), SCREEN_HEIGHT - BOMB_SIZE_Y, 0.0f),
				D3DXVECTOR3(BOMB_SIZE_X, BOMB_SIZE_Y, 0.0f), CBomb::BOMB_TYPE_PLAYER2, OBJTYPE_BG);
		}
		break;
	default:
		break;
	}
	

	// CScene2Dの初期化処理
	CScene2D::Init();

	// テクスチャの設定
	BindTexture(m_apTexture[m_PlayerNum]);

	srand((unsigned int)time(NULL));

	return S_OK;
}

//=============================================================================
// プレイヤークラスの終了処理
//=============================================================================
void CPlayer::Uninit(void)
{
	// CScene2Dの終了処理
	CScene2D::Uninit();
}

//=============================================================================
// プレイヤークラスの更新処理
//=============================================================================
void CPlayer::Update(void)
{
	// CScene2Dの更新処理
	CScene2D::Update();

	// 座標を受け取る
	m_pos = GetPosition();
	m_size = GetSize();

	//弾を撃つカウント
	m_nBulletShotCount++;

	// 通常の状態の時
	if (m_PlayerState == PLAYERSTATE_NOMAL)
	{
		m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// ゲームパッドの処理
		GamePad();

		// キーボードの処理
		keyBoard();
	}

	// 敵に当たってカウントが入ったら
	if (m_nRigorTime > 0)
	{
		m_nRigorTime--;
	}

	// m_nRigorTimeが0の時
	if (m_nRigorTime == 0)
	{
		// プレイヤーの状態をノーマルにする
		m_PlayerState = PLAYERSTATE_NOMAL;
	}

	// 敵に当たってカウントが入ったら
	if (m_nInvincibleTime > 0)
	{
		// 点滅させる
		SetTransparency(true);

		// m_nInvincibleTimeの減算
		m_nInvincibleTime--;
	}

	// m_nInvincibleTimeが0の時
	if (m_nInvincibleTime == 0)
	{
		// 点滅させない
		SetTransparency(false);

		// 敵に当たったとき
		HitEnemy();

		// おじゃまに当たったとき
		HitOjama();
		
		switch (m_PlayerNum)
		{
		case PLAYER_1P:
			// エクストラアタックに当たったとき
			HitExtraAttack(CExtraattck::EXTRAATTCK_PLAYER2);
			break;

		case PLAYER_2P:
			// エクストラアタックに当たったとき
			HitExtraAttack(CExtraattck::EXTRAATTCK_PLAYER1);
			break;

		default:
			break;
		}
		
		// ボスアタックに当たったとき
		HitBossAttack();
	
	}

	// ダメージを受けた状態の時
	if (m_PlayerState == PLAYERSTATE_DAMAGE)
	{
		// ダメージを受けた状態の時の処理
		DamageState();
	}

	m_pos += m_move;

	switch (m_PlayerNum)
	{
	case PLAYER_1P:
		// 移動できる範囲の制限
		if (m_pos.x < PLAYER_MOVABLE_RANGE_S + (PLAYER_SIZE_X / 2))
		{
			m_pos.x = PLAYER_MOVABLE_RANGE_S + (PLAYER_SIZE_X / 2);
		}
		if (m_pos.x > PLAYER_MOVABLE_RANGE_L - (PLAYER_SIZE_X / 2))
		{
			m_pos.x = PLAYER_MOVABLE_RANGE_L - (PLAYER_SIZE_X / 2);
		}
		if (m_pos.y < 0 + (PLAYER_SIZE_Y / 2))
		{
			m_pos.y = 0 + (PLAYER_SIZE_Y / 2);
		}
		if (m_pos.y > SCREEN_HEIGHT - (PLAYER_SIZE_Y / 2))
		{
			m_pos.y = SCREEN_HEIGHT - (PLAYER_SIZE_Y / 2);
		}
		break;

	case PLAYER_2P:
		// 移動できる範囲の制限
		if (m_pos.x < PLAYER2_MOVABLE_RANGE_S + (PLAYER_SIZE_X / 2))
		{
			m_pos.x = PLAYER2_MOVABLE_RANGE_S + (PLAYER_SIZE_X / 2);
		}
		if (m_pos.x > PLAYER2_MOVABLE_RANGE_L - (PLAYER_SIZE_X / 2))
		{
			m_pos.x = PLAYER2_MOVABLE_RANGE_L - (PLAYER_SIZE_X / 2);
		}
		if (m_pos.y < 0 + (PLAYER_SIZE_Y / 2))
		{
			m_pos.y = 0 + (PLAYER_SIZE_Y / 2);
		}
		if (m_pos.y > SCREEN_HEIGHT - (PLAYER_SIZE_Y / 2))
		{
			m_pos.y = SCREEN_HEIGHT - (PLAYER_SIZE_Y / 2);
		}
		break;

	default:
		break;
	}


	// 座標とサイズを渡す
	SetPosition(m_pos);
	SetSize(m_size);	

	// 負けた状態じゃないとき
	if (m_PlayerState != PLAYERSTATE_LOSE)
	{
		// 体力が0以下になったとき
		if (m_nLife <= 0)
		{
			// 自身を負けた状態にする
			m_PlayerState = PLAYERSTATE_LOSE;

			// ゲームの状態を終わらせる
			CGame::SetGameState(CGame::GAMESTATE_END);
		}
	}
}

//=============================================================================
// プレイヤークラスの描画処理
//=============================================================================
void CPlayer::Draw(void)
{
	// CScene2Dの描画処理
	CScene2D::Draw();
}

//=============================================================================
// プレイヤークラスのダメージの処理
//=============================================================================
void CPlayer::PlayerDamage(int nDamage)
{
	// 体力の受け取りとダメージの計算とセット
	if (m_pLife != NULL)
	{
		m_nLife = m_pLife->GetLife();
		m_nLife -= nDamage;
		m_pLife->SetLife(m_nLife);
		m_pLife->Damage();
	}

	// チャージしたゲージを下げる
	m_pChargeShot->GetCharge()->SetExtend(-300.0f, m_pChargeShot->GetGauge()->GetMaxExtend(), 0.0f, 0.0f);
}

//=============================================================================
// プレイヤークラスの回復の処理
//=============================================================================
void CPlayer::PlayerAddLife(int nLife)
{
	// 体力の受け取り
	m_nLife = m_pLife->GetLife();

	// m_nLifeがPLAYER_LIFEより少ないとき
	if (m_nLife < PLAYER_LIFE)
	{
		// ライフの加算とセット
		m_nLife += nLife;
		m_pLife->SetLife(m_nLife);
		m_pLife->Cure();
	}
}

//=============================================================================
// プレイヤークラスのゲームパッドの処理
//=============================================================================
void CPlayer::GamePad(void)
{
	CInputJoypad *pInputJoypad = CManager::GetInputJoypad();

	//コントローラーの情報を取得する
	DIJOYSTATE2 Controller = pInputJoypad->GetController(m_PlayerNum);

	// 通常の状態の時
	if (m_PlayerState == PLAYERSTATE_NOMAL)
	{
		// ゲームパッドの操作
		//スティックが倒れているなら移動
		if (Controller.lY != 0 || Controller.lX != 0)
		{
			//スティックの角度を求める
			float fAngle = atan2f((float)Controller.lX, (float)Controller.lY);//スティックの角度を求める
			// 求めた角度の方に動かす
			m_move.x = sinf(fAngle)*PLAYER_SPEED;
			m_move.y = cosf(fAngle)*PLAYER_SPEED;
		}

		if (pInputJoypad->GetJoypadRelease(m_PlayerNum, CInputJoypad::BUTTON_X) == true && m_nBulletShotCount >= 10)
		{
			switch (m_pChargeShot->GetCharge()->GetChargeType())
			{
				// チャージなし
			case CCharge::CHARGETYPE_NONE:
				// 弾を撃つ処理
				Shot();
				break;

				// チャージ1段階目
			case CCharge::CHARGETYPE_1:
				// チャージショットの処理
				ChargeShot();
				break;

				// チャージ2段階目(エキストラアタック)
			case CCharge::CHARGETYPE_2:
				// エクストラアタックの処理
				ExtraAttack();
				break;

				// チャージ3段階目(ボスアタック)
			case CCharge::CHARGETYPE_3:
				// ボスアタックの処理
				BossAttack();
				break;

			default:
				break;
			}
		}

		// Xを押したとき
		if (pInputJoypad->GetJoypadPress(m_PlayerNum, CInputJoypad::BUTTON_X) && m_nBulletShotCount >= 10)
		{
			// チャージ中の処理
			Charging();
		}
		else
		{
			// ボタンが押されてないとき
			m_pChargeShot->GetCharge()->SetExtend(-2.0f, m_pChargeShot->GetGauge()->GetMaxExtend(), 0.0f, 0.0f);
		}

		// ゲームの状態がGAMESTATE_STARTの時
		if (CGame::GetGameState() == CGame::GAMESTATE_START)
		{
			// ゲームパッドの操作
			// ボムを使う時
			if (pInputJoypad->GetJoypadTrigger(m_PlayerNum, CInputJoypad::BUTTON_A))
			{
				for (int nCount = PLAYER_BOMB_MAX - 1; nCount > -1; nCount--)
				{
					if (m_pBomb[nCount] != NULL)
					{
						// ボムを使う状態にする
						m_pBomb[nCount]->UseBomb();
						m_pBomb[nCount] = NULL;

						m_nInvincibleTime = PLAYER_INVINCIBLE;
						m_nRigorTime = PLAYER_RIGORE;
						break;
					}
				}
			}

			// エクストラアタックを発動する処理
			ExtraAttackInvocating();
		}
	}
}

//=============================================================================
// プレイヤークラスのキーパッドの処理
//=============================================================================
void CPlayer::keyBoard(void)
{
	// CInputのポインタのインスタンス生成の受け取り
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// 斜めの移動の計算
	float r = sqrtf((PLAYER_SPEED*PLAYER_SPEED) + (PLAYER_SPEED*PLAYER_SPEED));

	// 通常の状態の時
	if (m_PlayerState == PLAYERSTATE_NOMAL)
	{
		switch (m_PlayerNum)
		{
		case PLAYER_1P:
			// キーボードの操作
			//上
			if (pInputKeyboard->GetKeyboardPress(DIK_W))
			{
				// 上を押してるときに右、左を押したとき
				m_move.y -= pInputKeyboard->GetKeyboardPress(DIK_A) || pInputKeyboard->GetKeyboardPress(DIK_D) ? (r / 2) : PLAYER_SPEED;
			}
			//左
			if (pInputKeyboard->GetKeyboardPress(DIK_A))
			{
				// 左を押してるときに上、下を押したとき
				m_move.x -= pInputKeyboard->GetKeyboardPress(DIK_W) || pInputKeyboard->GetKeyboardPress(DIK_S) ? (r / 2) : PLAYER_SPEED;
			}
			//下
			if (pInputKeyboard->GetKeyboardPress(DIK_S))
			{
				// 下を押してるときに右、左を押したとき
				m_move.y += pInputKeyboard->GetKeyboardPress(DIK_A) || pInputKeyboard->GetKeyboardPress(DIK_D) ? (r / 2) : PLAYER_SPEED;
			}
			//右
			if (pInputKeyboard->GetKeyboardPress(DIK_D))
			{
				// 右を押してるときに上、下を押したとき
				m_move.x += pInputKeyboard->GetKeyboardPress(DIK_S) || pInputKeyboard->GetKeyboardPress(DIK_W) ? (r / 2) : PLAYER_SPEED;
			}

			// キーボード
			if (pInputKeyboard->GetKeyboardRelease(DIK_SPACE) == true && m_nBulletShotCount >= 10)
			{
				switch (m_pChargeShot->GetCharge()->GetChargeType())
				{
					// チャージなし
				case CCharge::CHARGETYPE_NONE:
					// 弾を撃つ処理
					Shot();
					break;

					// チャージ1段階目
				case CCharge::CHARGETYPE_1:
					// チャージショットの処理
					ChargeShot();
					break;

					// チャージ2段階目(エキストラアタック)
				case CCharge::CHARGETYPE_2:
					// エクストラアタックの処理
					ExtraAttack();
					break;

					// チャージ3段階目(ボスアタック)
				case CCharge::CHARGETYPE_3:
					// ボスアタックの処理
					BossAttack();
					break;

				default:
					break;
				}
			}
			// NUMPADENTERを押したとき
			if (pInputKeyboard->GetKeyboardPress(DIK_SPACE) && m_nBulletShotCount >= 10)
			{
				// チャージ中の処理
				Charging();
			}

			// ゲームの状態がGAMESTATE_STARTの時
			if (CGame::GetGameState() == CGame::GAMESTATE_START)
			{
				// キーボードの操作
				// ボムを使う時
				if (pInputKeyboard->GetKeyboardTrigger(DIK_B))
				{
					// 後ろの番号のボムから使っていく
					for (int nCount = PLAYER_BOMB_MAX - 1; nCount > -1; nCount--)
					{
						if (m_pBomb[nCount] != NULL)
						{
							// ボムを使う状態にする
							m_pBomb[nCount]->UseBomb();
							m_pBomb[nCount] = NULL;

							m_nInvincibleTime = PLAYER_INVINCIBLE;
							m_nRigorTime = PLAYER_RIGORE;
							break;
						}
					}
				}
				// エクストラアタックを発動する処理
				ExtraAttackInvocating();
			}
			break;

		case PLAYER_2P:
			// キーボードの操作
			//上
			if (pInputKeyboard->GetKeyboardPress(DIK_UP))
			{
				// 上を押してるときに右、左を押したとき
				m_move.y -= pInputKeyboard->GetKeyboardPress(DIK_LEFT) || pInputKeyboard->GetKeyboardPress(DIK_RIGHT) ? (r / 2) : PLAYER_SPEED;
			}
			// 左
			if (pInputKeyboard->GetKeyboardPress(DIK_LEFT))
			{
				// 左を押してるときに上、下を押したとき
				m_move.x -= pInputKeyboard->GetKeyboardPress(DIK_UP) || pInputKeyboard->GetKeyboardPress(DIK_DOWN) ? (r / 2) : PLAYER_SPEED;
			}
			// 下
			if (pInputKeyboard->GetKeyboardPress(DIK_DOWN))
			{
				// 下を押してるときに右、左を押したとき
				m_move.y += pInputKeyboard->GetKeyboardPress(DIK_LEFT) || pInputKeyboard->GetKeyboardPress(DIK_RIGHT) ? (r / 2) : PLAYER_SPEED;
			}
			// 右
			if (pInputKeyboard->GetKeyboardPress(DIK_RIGHT))
			{
				// 右を押してるときに上、下を押したとき
				m_move.x += pInputKeyboard->GetKeyboardPress(DIK_DOWN) || pInputKeyboard->GetKeyboardPress(DIK_UP) ? (r / 2) : PLAYER_SPEED;
			}

			// キーボード
			if (pInputKeyboard->GetKeyboardRelease(DIK_NUMPADENTER) == true && m_nBulletShotCount >= 10)
			{
				switch (m_pChargeShot->GetCharge()->GetChargeType())
				{
					// チャージなし
				case CCharge::CHARGETYPE_NONE:
					// 弾を撃つ処理
					Shot();
					break;

					// チャージ1段階目
				case CCharge::CHARGETYPE_1:
					// チャージショットの処理
					ChargeShot();
					break;

					// チャージ2段階目(エキストラアタック)
				case CCharge::CHARGETYPE_2:
					// エクストラアタックの処理
					ExtraAttack();
					break;

					// チャージ3段階目(ボスアタック)
				case CCharge::CHARGETYPE_3:
					// ボスアタックの処理
					BossAttack();
					break;

				default:
					break;
				}
			}
			// NUMPADENTERを押したとき
			if (pInputKeyboard->GetKeyboardPress(DIK_NUMPADENTER) && m_nBulletShotCount >= 10)
			{
				// チャージ中の処理
				Charging();
			}

			// ゲームの状態がGAMESTATE_STARTの時
			if (CGame::GetGameState() == CGame::GAMESTATE_START)
			{
				// キーボードの操作
				// ボムを使う時
				if (pInputKeyboard->GetKeyboardTrigger(DIK_NUMPAD0))
				{
					// 後ろの番号のボムから使っていく
					for (int nCount = PLAYER_BOMB_MAX - 1; nCount > -1; nCount--)
					{
						if (m_pBomb[nCount] != NULL)
						{
							// ボムを使う状態にする
							m_pBomb[nCount]->UseBomb();
							m_pBomb[nCount] = NULL;

							m_nInvincibleTime = PLAYER_INVINCIBLE;
							m_nRigorTime = PLAYER_RIGORE;
							break;
						}
					}
				}
				// エクストラアタックを発動する処理
				ExtraAttackInvocating();
			}
			break;

		default:
			break;
		}

		
	}
}

//=============================================================================
// プレイヤークラスの弾を撃つの処理
//=============================================================================
void CPlayer::Shot(void)
{
	// サウンドの再生
	CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_BULLET_SE);

	switch (m_PlayerNum)
	{
	case PLAYER_1P:
		// 弾の生成
		CBullet::Create(m_pos, D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f),
			200, 1, CBullet::BULLET_TYPE_1P, CBullet::CHARGEBULLET_TYPE_NOMAL, CScene::OBJTYPE_BULLET);
		break;

	case PLAYER_2P:
		// 弾の生成
		// 弾の生成
		CBullet::Create(m_pos, D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f),
			200, 1, CBullet::BULLET_TYPE_2P, CBullet::CHARGEBULLET_TYPE_NOMAL, CScene::OBJTYPE_BULLET);
		break;
	default:
		break;
	}

	// m_nBulletShotCountの初期化
	m_nBulletShotCount = 0;

	// m_pEffectがNULLじゃないとき
	if (m_pEffect != NULL)
	{
		// m_pEffectの終了処理
		m_pEffect->Uninit();
		m_pEffect = NULL;
	}

	// エフェクトを出せるようにする
	m_bEffectCreate = true;

	//押す時間の初期化
	m_nPressTime = 0;
}

//=============================================================================
// プレイヤークラスのチャージショットの処理
//=============================================================================
void CPlayer::ChargeShot(void)
{
	// サウンドの再生
	CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_CHARGESHOT);

	switch (m_PlayerNum)
	{
	case PLAYER_1P:
		// 弾の生成
		CBullet::Create(m_pos, D3DXVECTOR3(0.0f, -20.0f, 0.0f), D3DXVECTOR3(CHARGEBULLET_SIZE_X + 10.0f, CHARGEBULLET_SIZE_Y + 10.0f, 0.0f),
			200, 10, CBullet::BULLET_TYPE_1P, CBullet::CHARGEBULLET_TYPE_CHARGE, CScene::OBJTYPE_BULLET);
		break;

	case PLAYER_2P:
		// 弾の生成
		CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - LASERBULLET_SIZE_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(LASERBULLET_SIZE_X, LASERBULLET_SIZE_Y, 0.0f), 80, 10,
			CBullet::BULLET_TYPE_2P, CBullet::CHARGEBULLET_TYPE_LASER, CScene::OBJTYPE_BULLET);
		break;
	default:
		break;
	}

	// チャージしたゲージを下げる
	m_pChargeShot->GetCharge()->SetExtend(-300.0f, m_pChargeShot->GetGauge()->GetMaxExtend(), 0.0f, 0.0f);

	// m_nBulletShotCountの初期化
	m_nBulletShotCount = 0;

	// m_pEffectがNULLじゃないとき
	if (m_pEffect != NULL)
	{
		// m_pEffectの終了処理
		m_pEffect->Uninit();
		m_pEffect = NULL;
	}

	// エフェクトを出せるようにする
	m_bEffectCreate = true;

	//押す時間の初期化
	m_nPressTime = 0;
}

//=============================================================================
// プレイヤークラスのエクストラアタックの処理
//=============================================================================
void CPlayer::ExtraAttack(void)
{
	// サウンドの再生
	CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_BULLET_SE);

	// チャージしたゲージを下げる
	m_pChargeShot->GetCharge()->SetExtend(-300.0f, m_pChargeShot->GetGauge()->GetMaxExtend(), 0.0f, 0.0f);

	// ゲージの最大量を下げる
	m_pChargeShot->GetGauge()->SetExtend(-92.0f, 0.0f);

	// エクストラアタックを発動
	m_bExtraAttack = true;

	// m_nBulletShotCountの初期化
	m_nBulletShotCount = 0;

	// m_pEffectがNULLじゃないとき
	if (m_pEffect != NULL)
	{
		// m_pEffectの終了処理
		m_pEffect->Uninit();
		m_pEffect = NULL;
	}

	// エフェクトを出せるようにする
	m_bEffectCreate = true;

	//押す時間の初期化
	m_nPressTime = 0;
}

//=============================================================================
// プレイヤークラスのボスアタックの処理
//=============================================================================
void CPlayer::BossAttack(void)
{
	// サウンドの再生
	CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_BOSSCREATE);

	switch (m_PlayerNum)
	{
	case PLAYER_1P:
		// ボスアタックの生成
		CBossattck::Create(D3DXVECTOR3(PLAYER2_START_POS, 300.0f, 0.0f), D3DXVECTOR3(5.0f, 0.0f, 0.0f), 20,
			CBossattck::BOSSATTCK_PLAYER1, CBossattck::BOSSATTACK_BULLET, OBJTYPE_BOSSATTACK);
		break;

	case PLAYER_2P:
		// ボスアタックの生成
		CBossattck::Create(D3DXVECTOR3(PLAYER_START_POS, 300.0f, 0.0f), D3DXVECTOR3(5.0f, 0.0f, 0.0f), 20,
			CBossattck::BOSSATTCK_PLAYER2, CBossattck::BOSSATTACK_BEAM, OBJTYPE_BOSSATTACK);
		break;
	default:
		break;
	}

	// チャージしたゲージを下げる
	m_pChargeShot->GetCharge()->SetExtend(-300.0f, m_pChargeShot->GetGauge()->GetMaxExtend(), 0.0f, 0.0f);

	// ゲージの最大量を下げる
	m_pChargeShot->GetGauge()->SetExtend(-184.0f, 0.0f);

	// m_nBulletShotCountの初期化
	m_nBulletShotCount = 0;

	// m_pEffectがNULLじゃないとき
	if (m_pEffect != NULL)
	{
		// m_pEffectの終了処理
		m_pEffect->Uninit();
		m_pEffect = NULL;
	}

	// エフェクトを出せるようにする
	m_bEffectCreate = true;

	//押す時間の初期化
	m_nPressTime = 0;
}

//=============================================================================
// プレイヤークラスのエクストラアタックを発動するときの処理
//=============================================================================
void CPlayer::ExtraAttackInvocating(void)
{
	// エクストラアタックを発動したとき
	if (m_bExtraAttack == true)
	{
		//　m_nExtraAttackCountの加算
		m_nExtraAttackCount++;

		//　m_nExtraAttackCountが8で割れる数の時
		if (m_nExtraAttackCount % 8 == 0)
		{
			switch (m_PlayerNum)
			{
			case PLAYER_1P:
				// エクストラアタック生成
				CExtraattck::Create(m_pos, D3DXVECTOR3(-10.0f, -10.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f),
					CExtraattck::EXTRAATTCK_PLAYER1, CExtraattck::EXTRAATTACK_BLINKING, OBJTYPE_EXTRAATTACK);
				break;

			case PLAYER_2P:
				// エクストラアタック生成
				CExtraattck::Create(m_pos, D3DXVECTOR3(-10.0f, -10.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f),
					CExtraattck::EXTRAATTCK_PLAYER2, CExtraattck::EXTRAATTACK_AIM, OBJTYPE_EXTRAATTACK);
				break;
			default:
				break;
			}
		}
		//　m_nExtraAttackCountが32より大きいとき
		if (m_nExtraAttackCount >= 32)
		{
			// エクストラアタックを終わらせる
			m_bExtraAttack = false;

			//　m_nExtraAttackCountの初期化
			m_nExtraAttackCount = 0;
		}
	}
}

//=============================================================================
// プレイヤークラスの敵に当たったときの処理
//=============================================================================
void CPlayer::HitEnemy(void)
{
	// 敵に当たったとき
	CScene *pScene = CScene::GetSceneTop(CScene::OBJTYPE_ENEMY);

	// プレイヤーのシーンの受け取り
	CScene *pScene2 = CScene::GetSceneTop(CScene::OBJTYPE_PLAYER);
	do
	{
		if (pScene != NULL)
		{
			// オブジェタイプの受け取り
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_ENEMY)
			{
				if (CCollision::PRectangleCollision(m_pos, m_size, pScene) == true)
				{
					if (m_nLife > 1)
					{
						// プレイヤーのダメージ
						PlayerDamage(1);
					}

					if (m_move == D3DXVECTOR3(0.0f, 0.0f, 0.0f))
					{
						// ノックバックの角度と移動量の計算
						m_fAngle = (float)(rand() % (int)((D3DX_PI * 2) * 100));
						m_move.x = cosf(m_fAngle) * PLAYER_SPEED * 3.0f;
						m_move.y = sinf(m_fAngle) * PLAYER_SPEED * 3.0f;
					}
					else
					{
						m_move *= -3.0f;
					}

					// ライフの回復
					do
					{
						if (pScene2 != NULL)
						{
							//オブジェタイプの受け取り
							OBJTYPE objType = pScene2->GetObjType();
							if (objType == OBJTYPE_PLAYER)
							{
								switch (m_PlayerNum)
								{
								case PLAYER_1P:
									if (((CPlayer*)pScene2)->GetPlayerNum() == CPlayer::PLAYER_2P)
									{
										// プレイヤー2のライフを回復
										((CPlayer*)pScene2)->PlayerAddLife(1);
									}
									break;

								case PLAYER_2P:
									if (((CPlayer*)pScene2)->GetPlayerNum() == CPlayer::PLAYER_1P)
									{
										// プレイヤー2のライフを回復
										((CPlayer*)pScene2)->PlayerAddLife(1);
									}
									break;

								default:
									break;
								}
							}
							pScene2 = pScene2->GetSceneNext();
						}
					} while (pScene2 != NULL);

					// m_nInvincibleTimeの代入
					m_nInvincibleTime = PLAYER_INVINCIBLE;
					m_nRigorTime = PLAYER_RIGORE;

					// プレイヤーの状態をダメージを受けた状態にする
					m_PlayerState = PLAYERSTATE_DAMAGE;
					return;
				}
			}
			pScene = pScene->GetSceneNext();
		}
	} while (pScene != NULL);
}

//=============================================================================
// プレイヤークラスのおじゃまに当たったときの処理
//=============================================================================
void CPlayer::HitOjama(void)
{
	// おじゃまに当たったとき
	CScene *pScene = CScene::GetSceneTop(CScene::OBJTYPE_OJAMA);
	do
	{
		if (pScene != NULL)
		{
			// オブジェタイプの受け取り
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_OJAMA)
			{
				switch (m_PlayerNum)
				{
				case PLAYER_1P:

					// 当たり判定
					if (CCollision::PRectangleCollision(m_pos, m_size, pScene) == true)
					{
						// 2Pによって送られてきたおじゃまだったら
						if (((COjama*)pScene)->GetOjamaPlayerNum() == COjama::OJAMAPLAYER_2P)
						{
							// プレイヤーのダメージ
							PlayerDamage(1);

							// m_nInvincibleTimeの代入
							m_nInvincibleTime = PLAYER_INVINCIBLE;
							m_nRigorTime = PLAYER_RIGORE;

							// プレイヤーの状態をダメージを受けた状態にする
							m_PlayerState = PLAYERSTATE_DAMAGE;

							// おじゃまの終了処理
							((COjama*)pScene)->Uninit();
						}
						return;
					}
					break;

				case PLAYER_2P:
					// 当たり判定
					if (CCollision::PRectangleCollision(m_pos, m_size, pScene) == true)
					{
						// 1Pによって送られてきたおじゃまだったら
						if (((COjama*)pScene)->GetOjamaPlayerNum() == COjama::OJAMAPLAYER_1P)
						{
							// プレイヤーのダメージ
							PlayerDamage(1);

							// m_nInvincibleTimeの代入
							m_nInvincibleTime = PLAYER_INVINCIBLE;
							m_nRigorTime = PLAYER_RIGORE;

							// プレイヤーの状態をダメージを受けた状態にする
							m_PlayerState = PLAYERSTATE_DAMAGE;

							// おじゃまの終了処理
							((COjama*)pScene)->Uninit();
						}
						return;
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
// プレイヤークラスのエクストラアタックに当たったときの処理
//=============================================================================
void CPlayer::HitExtraAttack(CExtraattck::EXTRAATTCKPLAYERNUM ExtraAttackPlayerNum)
{
	// エクストラアタックに当たったとき
	CScene *pScene = CScene::GetSceneTop(CScene::OBJTYPE_EXTRAATTACK);
	do
	{
		if (pScene != NULL)
		{
			// オブジェタイプの受け取り
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_EXTRAATTACK)
			{
				switch (((CExtraattck*)pScene)->GetExtraAttack())
				{
					// 爆発するエクストラアタック
				case CExtraattck::EXTRAATTACK_EXPLOSION:
					// 当たり判定
					if (CCollision::PRectangleCollision(m_pos, m_size, pScene) == true)
					{
						if (((CExtraattck*)pScene)->GetExtraPlayerNum() == ExtraAttackPlayerNum)
						{
							// プレイヤーのダメージ
							PlayerDamage(1);

							// m_nInvincibleTimeの代入
							m_nInvincibleTime = PLAYER_INVINCIBLE;
							m_nRigorTime = PLAYER_RIGORE;

							// プレイヤーの状態をダメージを受けた状態にする
							m_PlayerState = PLAYERSTATE_DAMAGE;
						}
						break;
					}
					break;

					// 上にあがるエクストラアタック
				case CExtraattck::EXTRAATTACK_LOCKET:
					// 当たり判定
					if (CCollision::PRectangleCollision(m_pos, m_size, pScene) == true)
					{
						if (((CExtraattck*)pScene)->GetExtraPlayerNum() == ExtraAttackPlayerNum)
						{
							// プレイヤーのダメージ
							PlayerDamage(1);

							// m_nInvincibleTimeの代入
							m_nInvincibleTime = PLAYER_INVINCIBLE;
							m_nRigorTime = PLAYER_RIGORE;

							// プレイヤーの状態をダメージを受けた状態にする
							m_PlayerState = PLAYERSTATE_DAMAGE;
						}
						break;
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
// プレイヤークラスのボスアタックに当たったときの処理
//=============================================================================
void CPlayer::HitBossAttack(void)
{
	// ボスアタックに当たったとき
	CScene *pScene = CScene::GetSceneTop(CScene::OBJTYPE_BULLET);
	do
	{
		if (pScene != NULL)
		{
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_BULLET)
			{
				// 弾のタイプがBULLET_TYPE_BOSSの時
				if (((CBullet*)pScene)->GetBulletType() == CBullet::BULLET_TYPE_BOSS)
				{
					switch (((CBullet*)pScene)->GetChargeBulletType())
					{
						// 普通の弾
					case CBullet::CHARGEBULLET_TYPE_NOMAL:
						// 当たり判定
						if (CCollision::PRectangleCollision(m_pos, m_size, pScene) == true)
						{
							// プレイヤーのダメージ
							PlayerDamage(1);

							// m_nInvincibleTimeの代入
							m_nInvincibleTime = PLAYER_INVINCIBLE;
							m_nRigorTime = PLAYER_RIGORE;

							// プレイヤーの状態をダメージを受けた状態にする
							m_PlayerState = PLAYERSTATE_DAMAGE;
							break;
						}
						break;

						// ボスのレーザー弾
					case CBullet::CHARGEBULLET_TYPE_BOSSLASER:
						// 当たり判定
						if (CCollision::PRectangleCollision(m_pos, m_size, pScene) == true)
						{
							// プレイヤーのダメージ
							PlayerDamage(1);

							// m_nInvincibleTimeの代入
							m_nInvincibleTime = PLAYER_INVINCIBLE;
							m_nRigorTime = PLAYER_RIGORE;

							// プレイヤーの状態をダメージを受けた状態にする
							m_PlayerState = PLAYERSTATE_DAMAGE;
							break;
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

//=============================================================================
// プレイヤークラスのダメージ状態のときの処理
//=============================================================================
void CPlayer::DamageState(void)
{
	// 移動量を減らす
	if (m_move.x < 0.0f)
	{
		m_move.x += (m_move.x / 10) * -1.0f;
	}
	else if (m_move.x > 0.0f)
	{
		m_move.x -= m_move.x / 10;
	}
	if (m_move.y < 0.0f)
	{
		m_move.y += (m_move.y / 10) * -1.0f;
	}
	else if (m_move.y > 0.0f)
	{
		m_move.y -= m_move.y / 10;
	}
	// 移動量を0になるようにする
	if (m_move.y == 0.0f)
	{
		m_move.y = 0.0f;
	}
	if (m_move.x == 0.0f)
	{
		m_move.x = 0.0f;
	}

	switch (m_PlayerNum)
	{
	case PLAYER_1P:
		// 壁に当たったら反射するようにする
		if (m_pos.x < PLAYER_MOVABLE_RANGE_S + (PLAYER_SIZE_X / 2))
		{
			m_move *= -1.0f;
		}
		if (m_pos.x > PLAYER_MOVABLE_RANGE_L - (PLAYER_SIZE_X / 2))
		{
			m_move *= -1.0f;
		}
		if (m_pos.y < 0 + (PLAYER_SIZE_Y / 2))
		{
			m_move *= -1.0f;
		}
		if (m_pos.y > SCREEN_HEIGHT - (PLAYER_SIZE_Y / 2))
		{
			m_move *= -1.0f;
		}
		break;

	case PLAYER_2P:
		// 壁に当たったら反射するようにする
		if (m_pos.x < PLAYER2_MOVABLE_RANGE_S + (PLAYER_SIZE_X / 2))
		{
			m_move *= -1.0f;
		}
		if (m_pos.x > PLAYER2_MOVABLE_RANGE_L - (PLAYER_SIZE_X / 2))
		{
			m_move *= -1.0f;
		}
		if (m_pos.y < (PLAYER_SIZE_Y / 2))
		{
			m_move *= -1.0f;
		}
		if (m_pos.y > SCREEN_HEIGHT - (PLAYER_SIZE_Y / 2))
		{
			m_move *= -1.0f;
		}
		break;

	default:
		break;
	}

	// m_pEffectがNULLじゃないとき
	if (m_pEffect != NULL)
	{
		// m_pEffectの終了処理
		m_pEffect->Uninit();
		m_pEffect = NULL;
	}
	// エフェクトを出せるようにする
	m_bEffectCreate = true;

	// m_nPressTimeの初期化
	m_nPressTime = 0;

	// ダメージを受けた時
	if (m_nDamage > 0)
	{
		m_nLife -= m_nDamage;
		m_nDamage = 0;
	}
}

//=============================================================================
// プレイヤークラスのチャージ中の処理
//=============================================================================
void CPlayer::Charging(void)
{
	// チャージ中のゲージを伸ばす
	m_pChargeShot->GetCharge()->SetExtend(1.5f, m_pChargeShot->GetGauge()->GetMaxExtend(), 0.0f, 0.0f);

	// m_nPressTimeの加算
	m_nPressTime++;

	// m_nPressTimeが10以上の時
	if (m_nPressTime >= 10)
	{
		// エフェクトが出せる状態の時
		if (m_bEffectCreate == true)
		{
			// サウンドの再生
			CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_CHARGE);

			// エフェクトのクリエイト
			m_pEffect = m_pEffect->Create(D3DXVECTOR3(m_pos.x, m_pos.y - 50.0f, m_pos.x), D3DXVECTOR3(100.0f, 100.0f, 0.0f),
				0, 255, 255, 255, 255, CEffect::EFFECTTYPE_CHARGESTATE, OBJTYPE_EFFECT);

			// エフェクトが出せない状態にする
			m_bEffectCreate = false;
		}
	}
	switch (m_pChargeShot->GetCharge()->GetChargeType())
	{
		// チャージなし
	case CCharge::CHARGETYPE_NONE:
		if (m_pEffect != NULL)
		{
			// エフェクトの座標のセットとアニメーションセット
			m_pEffect->SetPosition(D3DXVECTOR3(m_pos.x, m_pos.y - 50.0f, m_pos.x));
			m_pEffect->SetAnimationSelect(3, 3, 0, 10);
		}
		break;

		// チャージ1段階目
	case CCharge::CHARGETYPE_1:
		if (m_pEffect != NULL)
		{
			// エフェクトの座標のセットとアニメーションセット
			m_pEffect->SetPosition(D3DXVECTOR3(m_pos.x, m_pos.y - 50.0f, m_pos.x));
			m_pEffect->SetAnimationSelect(3, 3, 1, 10);
		}
		break;

		// チャージ2段階目(エキストラアタック)
	case CCharge::CHARGETYPE_2:
		if (m_pEffect != NULL)
		{
			// エフェクトの座標のセットとアニメーションセット
			m_pEffect->SetPosition(D3DXVECTOR3(m_pos.x, m_pos.y - 50.0f, m_pos.x));
			m_pEffect->SetAnimationSelect(3, 3, 2, 10);
		}
		break;

		// チャージ3段階目(ボスアタック)
	case CCharge::CHARGETYPE_3:
		if (m_pEffect != NULL)
		{
			// エフェクトの座標のセットとアニメーションセット
			m_pEffect->SetPosition(D3DXVECTOR3(m_pos.x, m_pos.y - 50.0f, m_pos.x));
			m_pEffect->SetAnimationSelect(3, 3, 2, 10);
		}
		break;

	default:
		break;
	}
}

//=============================================================================
// プレイヤークラスのチャージショットポインタを返す処理
//=============================================================================
CChargeshot* CPlayer::GetChargeShot(void)
{
	return m_pChargeShot;
}

//=============================================================================
// プレイヤークラスのをプレイヤーの状態を返す処理
//=============================================================================
CPlayer::PLAYERSTATE CPlayer::GetPlayerState(void)
{
	return m_PlayerState;
}

//=============================================================================
// プレイヤークラスのをプレイヤー番号を返す処理
//=============================================================================
CPlayer::PLAYERNUM CPlayer::GetPlayerNum(void)
{
	return m_PlayerNum;
}
