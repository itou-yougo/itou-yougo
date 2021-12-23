//=============================================================================
//
// 攻撃種類 [attack.cpp]
// Author : 吉田悠人
//
//=============================================================================
//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "attack.h"
#include "attack_knight.h"
#include "attack_wizard.h"
#include "attack_lancer.h"
#include "attack_thief.h"
#include "attack_magician.h"
#include "attack_archer.h"
#include "tile.h"
#include "resource_attack.h"
#include "player.h"
#include "bullet.h"
#include "scene3d.h"
#include "attack_area.h"
#include "color_tile.h"
#include "peint_collision.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define ATTACK_AREA_EFFECT_POS (D3DXVECTOR3(0.0f,10.0f,0.0f))
#define CHARGE_COUNT (60*1)		// チャージにかかる時間
#define LEVEL_MAX    (4)		// 最大レベル
#define CANCEL_COUNT (60*0.1f)	// 攻撃キャンセルのカウント
//=============================================================================
// コンストラクタ
//=============================================================================
CAttackBased::CAttackBased() :CScene(OBJTYPE_SYSTEM)
{
	//初期化処理
	memset(&m_AttackSquare, 0, sizeof(m_AttackSquare));
	m_pPlayer		= NULL;
	m_nLevel		= 0;
	m_nCancelCount	= 0;
	m_nChargeCount	= 0;
	m_AttackState = ATTACK_STATE_NORMAL;
	ZeroMemory(&m_apAttackArea, sizeof(m_apAttackArea));
	ZeroMemory(&m_anChargeValue, sizeof(m_anChargeValue));
	m_bAttack = false;	// 必殺フラグ
	m_bChargeTile = false;
	m_bCancel = false;
	m_nAttackCount = 0;
	m_nType = 0;

}

//=============================================================================
// デストラクタ
//=============================================================================
CAttackBased::~CAttackBased()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CAttackBased * CAttackBased::Create(CPlayer * pPlayer, CResourceCharacter::CHARACTER_TYPE Type)
{
	//メモリ確保
	CAttackBased* pAttack = NULL;

	switch (Type)
	{
	case CResourceCharacter::CHARACTER_KNIGHT:
		pAttack = CAttackKnight::Create(pPlayer);
		break;
	case CResourceCharacter::CHARACTER_LANCER:
		pAttack = CAttackLancer::Create(pPlayer);
		break;
	case CResourceCharacter::CHARACTER_WIZARD:
		pAttack = CAttackWizard::Create(pPlayer);
		break;
	case CResourceCharacter::CHARACTER_THIEF:
		pAttack = CAttackThief::Create(pPlayer);
		break;
	case CResourceCharacter::CHARACTER_MAGICIAN:
		pAttack = CAttackMagician::Create(pPlayer);
		break;
	case CResourceCharacter::CHARACTER_ARCHER:
		pAttack = CAttackArcher::Create(pPlayer);
		break;
	default:
		break;
	}

	//pAttack = new CAttackBased;
	//if (pAttack != NULL)
	//{
	//	pAttack->SetPlayer(pPlayer);		//プレイヤークラス取得
	//	pAttack->Init();					//初期化処理
	//}
	return pAttack;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CAttackBased::Init(void)
{
	int nMaxAttackNum = 0;
	
	//攻撃タイプセット
	for (int nLevel = 0; nLevel < MAX_ATTACK_LEVEL; nLevel++)
	{
		m_AttackSquare[nLevel] = CAttackManager::GetAttack(m_nAttackType, nLevel);
		if (nMaxAttackNum < m_AttackSquare[nLevel].nMaxHitRange)
		{
			nMaxAttackNum = m_AttackSquare[nLevel].nMaxHitRange;
		}
		
		// チャージ時間の取得
		m_anChargeValue[nLevel] = CResourceCharacter::GetResourceCharacter()->GetCharacterData(m_nAttackType).anChargeTime[nLevel];
	}

	for(int nCntArea = 0 ; nCntArea < nMaxAttackNum; nCntArea++)
	{
		m_apAttackArea[nCntArea] = CAttackArea::Create();
	}

	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CAttackBased::Uninit(void)
{
	//オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新関数
//=============================================================================
void CAttackBased::Update(void)
{
	//ステートごとの処理
	switch (m_AttackState)
	{
	case ATTACK_STATE_NORMAL:	//通常状態
	{
		//数値の初期化
		if (m_nLevel != 0)
		{
			m_nLevel = 0;
			m_nChargeCount = 0;
			m_nAttackCount = 0;
			m_nType = 0;
		}
		
		//攻撃範囲のリセット
		ResetAttackArea();
		//チャージタイルフラグが立っている際
		if (m_bChargeTile == true)
		{
			// チャージをしているプレイヤーの取得
			CColorTile * pColorTile = (CColorTile*)GetTop(OBJTYPE_COLOR_TILE);

			while (pColorTile != NULL)
			{
				//チャージをしているタイル取得
				if (pColorTile->GetColorTileState() == CColorTile::COLOR_TILE_CHARGE
					&&pColorTile->GetLasthitPlayerNum() == m_pPlayer->GetPlayerNumber())
				{
					//タイルステート
					pColorTile->SetColorTileState(CColorTile::COLOR_TILE_NORMAL);
					return;
				}
				// リストを進める
				pColorTile = (CColorTile*)pColorTile->GetNext();
			}
		}

		//キャンセルフラグが立っているか
		if (m_bCancel == true)
		{
			//カウントアップ
			m_nCancelCount++;

			if (m_nCancelCount >= CANCEL_COUNT)
			{
				//キャンセルフラグを回収
				m_bCancel = false;
				//キャンセルカウント初期化
				m_nCancelCount = 0;
				//チャージカウント初期化
				m_nChargeCount = 0;
			}

		}
	}
	break;

	
	case ATTACK_STATE_CHARGE:		// チャージ状態	
		VisualizationAttackArea();	// 攻撃範囲表示
		Charge();					// チャージ処理
		break;

	case ATTACK_STATE_ATTACK:		// 攻撃状態			
		AttackCreate();				// 攻撃生成処理
		break;

	case ATTACK_STATE_FINALATTACKWAITING:	// 必殺技待機状態	
		VisualizationAttackArea();		// 攻撃範囲表示
		m_nLevel = LEVEL_MAX - 1;		// レベルを最大値にする
		break;

	case ATTACK_STATE_FINALATTACK:		// 必殺技使用状態			
		AttackCreate();					// 攻撃生成処理
		break;


	default:							//それ以外の状態
		m_AttackState = ATTACK_STATE_NORMAL;
		break;
	}
}

//=============================================================================
// 描画関数
//=============================================================================
void CAttackBased::Draw(void)
{
}


//=============================================================================
// 攻撃関数
//=============================================================================
void CAttackBased::Attack(int AttackType)
{
	for (int nAttack = 0; nAttack < m_AttackSquare[m_nLevel].nMaxHitRange; nAttack++)
	{
		//タイプが一致しているか
		if (m_AttackSquare[m_nLevel].SquareData[nAttack].RangeType == AttackType + (int)CAttackManager::ATTACK_RANGE_HIT_1)
		{
			//行列計算
			D3DXVECTOR3 CreatePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			//位置取得
			D3DXVECTOR3 pos = m_pPlayer->GetPos();
			//向き取得
			D3DXVECTOR3 rot = m_pPlayer->GetRotDest();

			//攻撃位置
			D3DXVECTOR3 AttackPos = m_AttackSquare[m_nLevel].SquareData[nAttack].AttackPos * TILE_ONE_SIDE;
			CreatePos.x = ((cosf(rot.y)*AttackPos.x) + (sinf(rot.y)*AttackPos.z));
			CreatePos.y = 1 * AttackPos.y;
			CreatePos.z = ((-sinf(rot.y)*AttackPos.x) + (cosf(rot.y)*AttackPos.z));
			//当たり判定生成
			CBullet::Create(CreatePos + pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_pPlayer->GetPlayerNumber());

			// 必殺技の打てるレベルなら
			if (m_nLevel == LEVEL_MAX - 1)
			{
				// 色塗る処理
				m_pPeintCollision[nAttack] = CPeintCollision::Create(CreatePos + pos, m_pPlayer->GetPlayerNumber());
			}
		}
	}
}

//=============================================================================
// チャージフラグ処理関数
//=============================================================================
void CAttackBased::ChargeFlag(void)
{
	//現在の状態が通常の場合
	if (m_AttackState == ATTACK_STATE_NORMAL)
	{
		if (!m_bCancel)
		{
			// 当たっているタイルの取得
			CColorTile*pHitTile = CColorTile::GetHitColorTile(m_pPlayer->GetPos());

			//触れているタイルの識別(NULLチェック, カラーの確認)
			if (pHitTile != NULL&&pHitTile->GetPeintNum() == m_pPlayer->GetColorNumber())
			{
				//タイルがチャージ出来るか取得
				if (pHitTile->ChargeFlag(m_pPlayer->GetPlayerNumber()))
				{
					//チャージタイルフラグを立てる
					m_bChargeTile = true;
					//チャージ状態に移行
					m_AttackState = ATTACK_STATE_CHARGE;
					//レベルの最大値の取得
					m_nMaxLevel = pHitTile->GetStepNum() - 1;
				}
			}
		}
		else
		{
			m_nCancelCount = 0;
		}
	}
}

//=============================================================================
// エフェクト生成
//=============================================================================
void CAttackBased::CreateEffect(D3DXVECTOR3 pos)
{
}

//=============================================================================
// チャージ処理関数
// Akuthor: 吉田 悠人、増澤未来
//=============================================================================
void CAttackBased::Charge(void)
{
	//カウントアップ
	m_nChargeCount++;

	for (int nCntLevel = 0; nCntLevel < MAX_ATTACK_LEVEL; nCntLevel++)
	{
		// 最大レベルの判定
		if (nCntLevel > m_nMaxLevel)
		{
			break;
		}
		// チャージ時間に応じたレベルにする
		if (m_nChargeCount > m_anChargeValue[nCntLevel])
		{
			m_nLevel = nCntLevel;
		}
	}
}

//=============================================================================
// 攻撃スイッチ関数
//=============================================================================
void CAttackBased::AttackSwitch(void)
{
	//攻撃をしていなかったら
	if (m_AttackState == ATTACK_STATE_CHARGE)
	{
		//攻撃状態に移行
		m_AttackState = ATTACK_STATE_ATTACK;
		//カウント初期化
		m_nChargeCount = 0;
	
		// チャージをしているプレイヤーの取得
		CColorTile * pColorTile = (CColorTile*)GetTop(OBJTYPE_COLOR_TILE);

		while (pColorTile != NULL)
		{
			//チャージをしているタイル取得
			if (pColorTile->GetColorTileState() == CColorTile::COLOR_TILE_CHARGE
				&&pColorTile->GetLasthitPlayerNum()== m_pPlayer->GetPlayerNumber())
			{
				//塗り段階の消費
				pColorTile->ColorDown(m_nLevel+1);
				//タイルステート
				pColorTile->SetColorTileState(CColorTile::COLOR_TILE_NORMAL);
				return;
			}
			// リストを進める
			pColorTile = (CColorTile*)pColorTile->GetNext();
		}
	}
}

//=============================================================================
// 必殺待機フラグ関数
//=============================================================================
void CAttackBased::AttackFinalFlag(void)
{
	//キャンセルフラグが立っていないか
	if (!m_bCancel)
	{
		// 攻撃状態じゃないなら
		if (m_AttackState == CAttackBased::ATTACK_STATE_NORMAL
			|| m_AttackState == CAttackBased::ATTACK_STATE_FINALATTACKWAITING)
		{
			SetState(CAttackBased::ATTACK_STATE_FINALATTACKWAITING);
		}
	}
	else
	{
		m_nCancelCount = 0;
	}
}

//=============================================================================
// 必殺技スイッチ関数
//=============================================================================
void CAttackBased::AttackFinalSwitch(void)
{
	// 必殺技待機中なら
	if (m_AttackState == ATTACK_STATE_FINALATTACKWAITING)
	{
		//必殺技使用状態に移行
		m_AttackState = ATTACK_STATE_FINALATTACK;
	}
}

//=============================================================================
// 攻撃キャンセルスイッチ関数
//=============================================================================
void CAttackBased::CancelSwitch(void)
{

	//攻撃をチャージしていたら
	if (m_AttackState == ATTACK_STATE_CHARGE)
	{
		// チャージをしているプレイヤーの取得
		CColorTile * pColorTile = (CColorTile*)GetTop(OBJTYPE_COLOR_TILE);
		while (pColorTile != NULL)
		{
			//チャージをしているタイル取得
			if (pColorTile->GetColorTileState() == CColorTile::COLOR_TILE_CHARGE
				&&pColorTile->GetLasthitPlayerNum() == m_pPlayer->GetPlayerNumber())
			{
				//タイルステート
				pColorTile->SetColorTileState(CColorTile::COLOR_TILE_NORMAL);
				break;
			}
			// リストを進める
			pColorTile = (CColorTile*)pColorTile->GetNext();
		}
	}

	//攻撃範囲のリセット
	ResetAttackArea();
	//攻撃キャンセル状態
	m_bCancel = true;
	//通常状態に移行
	m_AttackState = ATTACK_STATE_NORMAL;
}

//=============================================================================
// 攻撃生成処理
//=============================================================================
void CAttackBased::AttackCreate(void)
{
	//プレイヤーのポインタ
	CPlayer *pPlaryer = GetPlayer();

	//攻撃フラグが立っているか
	if (GetState() == ATTACK_STATE_ATTACK
		|| GetState() == ATTACK_STATE_FINALATTACK)
	{
		//カウントアップ
		m_nAttackCount++;

		// 攻撃範囲の可視化
		VisualizationAttackArea(m_nType);

		//カウントが一定になったら
		if (m_nAttackCount >= GetAttackSquare().nAttackFrame[m_nType])
		{
			//攻撃処理
			Attack(m_nType);
      
			for (int nCnt = 0; nCnt < m_AttackSquare[m_nLevel].nMaxHitRange; nCnt++)
			{
				if (GetAttackSquare().SquareData[nCnt].RangeType == m_nType + 2)
				{
					//行列計算
					D3DXVECTOR3 CreatePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					D3DXVECTOR3 AttackPos = GetAttackSquare().SquareData[nCnt].AttackPos * TILE_ONE_SIDE;
					CreatePos.x = ((cosf(pPlaryer->GetRotDest().y)*AttackPos.x) + (sinf(pPlaryer->GetRotDest().y)*AttackPos.z));
					CreatePos.y = 1 * AttackPos.y;
					CreatePos.z = ((-sinf(pPlaryer->GetRotDest().y)*AttackPos.x) + (cosf(pPlaryer->GetRotDest().y)*AttackPos.z));

					CreateEffect(CreatePos);
				}
			}
					
				
			//タイプが一定になったら
			if (m_nType == MAX_HIT_TYPE)
			{
				//フラグの初期化
				SetState(ATTACK_STATE_NORMAL);
				//タイプ初期化
				m_nType = 0;
				//レベルの初期化
				CAttackBased::SetLevel(0);
			}
			else
			{
				//次の攻撃タイプへ
				m_nType++;
			}
			//カウント初期化
			m_nAttackCount = 0;


		}

	}

}

//=============================================================================
// 攻撃マスデータゲッター関数
//=============================================================================
CAttackManager::ATTACK_SQUARE_DATA CAttackBased::GetAttackSquare()
{
	return m_AttackSquare[m_nLevel];
}


//=============================================================================
// 攻撃範囲の枠の色を変える処理
// Akuthor: 増澤 未来
//=============================================================================
void CAttackBased::VisualizationAttackArea(int nAttackType)
{
	//攻撃フラグと必殺技フラグが立っているか
	if (m_AttackState == ATTACK_STATE_ATTACK
		|| m_AttackState == ATTACK_STATE_FINALATTACK)
	{
		//タイプが一致しているか
		for (int nAttack = 0; nAttack < m_AttackSquare[m_nLevel].nMaxHitRange; nAttack++)
		{
			//タイプが一致しているか
			if (m_AttackSquare[m_nLevel].SquareData[nAttack].RangeType >= nAttackType + (int)CAttackManager::ATTACK_RANGE_HIT_1)
			{
				//位置取得
				D3DXVECTOR3 pos = m_pPlayer->GetPos();
				//向き取得
				D3DXVECTOR3 rot = m_pPlayer->GetRot();
				//行列計算
				D3DXVECTOR3 CreatePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				//攻撃位置
				D3DXVECTOR3 AttackPos = m_AttackSquare[m_nLevel].SquareData[nAttack].AttackPos * TILE_ONE_SIDE;
				CreatePos.x = ((cosf(rot.y)*AttackPos.x) + (sinf(rot.y)*AttackPos.z));
				CreatePos.y = 1 * AttackPos.y;
				CreatePos.z = ((-sinf(rot.y)*AttackPos.x) + (cosf(rot.y)*AttackPos.z));

				if (m_apAttackArea[nAttack] != NULL)
				{
					m_apAttackArea[nAttack]->SetColor(GET_COLORMANAGER->GetIconColor(GetPlayer()->GetColorNumber()));
					m_apAttackArea[nAttack]->SetPos(CreatePos + pos + ATTACK_AREA_EFFECT_POS);
					m_apAttackArea[nAttack]->SetDrawFlag(true);
				}
			}
			else
			{
				if (m_apAttackArea[nAttack] != NULL)
				{
					m_apAttackArea[nAttack]->SetDrawFlag(false);
				}
			}
		}
	}
	else
	{
		if (m_nLevel < 0)
		{
			return;
		}
		// タイプが一致しているか
		for (int nAttack = 0; nAttack < m_AttackSquare[m_nLevel].nMaxHitRange; nAttack++)
		{
			//行列計算
			D3DXVECTOR3 CreatePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			//攻撃位置
			D3DXVECTOR3 AttackPos = m_AttackSquare[m_nLevel].SquareData[nAttack].AttackPos * TILE_ONE_SIDE;
			CreatePos.x = ((cosf(GetPlayer()->GetRotDest().y)*AttackPos.x) + (sinf(GetPlayer()->GetRotDest().y)*AttackPos.z));
			CreatePos.y = 1 * AttackPos.y;
			CreatePos.z = ((-sinf(GetPlayer()->GetRotDest().y)*AttackPos.x) + (cosf(GetPlayer()->GetRotDest().y)*AttackPos.z));

			if (m_apAttackArea[nAttack] != NULL)
			{
				m_apAttackArea[nAttack]->SetColor(GET_COLORMANAGER->GetIconColor(GetPlayer()->GetColorNumber()));
				m_apAttackArea[nAttack]->SetPos(CreatePos + GetPlayer()->GetPos() + ATTACK_AREA_EFFECT_POS);
				m_apAttackArea[nAttack]->SetDrawFlag(true);
			}

		}
	}
}

//=============================================================================
// 攻撃範囲ポリゴンのリセット
// Akuthor: 増澤 未来
//=============================================================================
void CAttackBased::ResetAttackArea(void)
{
	for (int nCntArea = 0; nCntArea < MAX_ATTACK_AREA_NUM; nCntArea++)
	{
		if (m_apAttackArea[nCntArea] != NULL)
		{
			m_apAttackArea[nCntArea]->SetDrawFlag(false);
			m_apAttackArea[nCntArea]->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_apAttackArea[nCntArea]->SetSize(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
	}
}

//=============================================================================
// 攻撃範囲のリリース
// Akuthor: 増澤 未来
//=============================================================================
void CAttackBased::ReleaseAttakcArea(void)
{
	//攻撃エリアの解放
	for (int nCntArea = 0; nCntArea < MAX_ATTACK_AREA_NUM; nCntArea++)
	{
		if (m_apAttackArea[nCntArea] != NULL)
		{
			m_apAttackArea[nCntArea]->OutList();
			m_apAttackArea[nCntArea]->Uninit();
			delete m_apAttackArea[nCntArea];
			m_apAttackArea[nCntArea] = NULL;
		}
	}
}
