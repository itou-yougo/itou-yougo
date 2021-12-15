//=============================================================================
//
// 必殺技の処理 [attack_final.cpp]
// Author : 佐藤颯紀
//
//=============================================================================

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "attack_final.h"
#include "tile.h"
#include "resource_attack.h"
#include "player.h"
#include "scene3d.h"
#include "bullet.h"
#include "color_tile.h"
#include "attack_area.h"
#include "peint_collision.h"
#include "collision.h"
#include "base_Cylinder.h"
//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// 静的メンバー変数宣言
//=============================================================================

//=============================================================================
// コンストラクタ
//=============================================================================
CAttackFinal::CAttackFinal() : CScene(OBJTYPE_SYSTEM)
{
	m_pos = VEC3_ZERO;		// 位置
	m_rot = VEC3_ZERO;		// 向き
	memset(&m_FinalAttackSquare, 0, sizeof(m_FinalAttackSquare));
	memset(&m_apAttackArea, 0, sizeof(m_apAttackArea));
	m_bAttackFinal = false;	// 必殺技フラグ
	m_pPlayer = NULL;		// プレイヤー情報
}

//=============================================================================
// デストラクタ
//=============================================================================
CAttackFinal::~CAttackFinal()
{

}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CAttackFinal::Init(void)
{
	int nMaxAttackNum = 0;

	// 攻撃タイプのセット
	m_FinalAttackSquare = CFinalAttackManager::GetFinalAttack(m_FinalAttackType);

	if (nMaxAttackNum < m_FinalAttackSquare.nMaxHitRange)
	{
		nMaxAttackNum = m_FinalAttackSquare.nMaxHitRange;
	}

	for (int nCntArea = 0; nCntArea < nMaxAttackNum; nCntArea++)
	{
		m_apAttackArea[nCntArea] = CAttackArea::Create();
	}

	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CAttackFinal::Uninit(void)
{
	//オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新関数
//=============================================================================
void CAttackFinal::Update(void)
{
	//AttackFinalCreate();

	switch (m_FinalAttackState)
	{
	case FINAL_ATTACK_STATE_NOMAL:

	case FINAL_ATTACK_STATE_ATTACK:
		AttackFinalCreate();
		break;
	default:
		m_FinalAttackState = FINAL_ATTACK_STATE_NOMAL;
		break;
	}
}

//=============================================================================
// 描画関数
//=============================================================================
void CAttackFinal::Draw(void)
{

}

//=============================================================================
// 必殺スイッチ関数
//=============================================================================
void CAttackFinal::AttackFinalSwitch(void)
{
	// 攻撃されていなかったら
	if (m_bAttackFinal == false)
	{
		m_FinalAttackState = FINAL_ATTACK_STATE_ATTACK;
		// フラグオン
		SetAttackFinalFlag(true);
		// 位置取得
		SetPos(m_pPlayer->GetPos());
		// 向き取得
		SetRot(m_pPlayer->GetRot());
	}
}

//=============================================================================
// 必殺関数
//=============================================================================
void CAttackFinal::AttackFinal(int AttackFinalType)
{
	for (int nAttackFinal = 0; nAttackFinal < m_FinalAttackSquare.nMaxHitRange; nAttackFinal++)
	{
		// タイプが一致しているか
		if (m_FinalAttackSquare.SquareData[nAttackFinal].RangeType == AttackFinalType + (int)CFinalAttackManager::FINAL_ATTACK_RANGE_HIT_1)
		{
			// 行列計算
			D3DXVECTOR3 CreatePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			// 攻撃位置
			D3DXVECTOR3 AttackFinalPos = m_FinalAttackSquare.SquareData[nAttackFinal].AttackPos * TILE_ONE_SIDE;
			CreatePos.x = ((cosf(m_rot.y)*AttackFinalPos.x) + (sin(m_rot.y)*AttackFinalPos.z));
			CreatePos.y = 1 * AttackFinalPos.y;
			CreatePos.z = ((-sinf(m_rot.y)*AttackFinalPos.x) + (cosf(m_rot.y)*AttackFinalPos.z));
			// 当たり判定生成
			CBullet::Create(CreatePos + m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_pPlayer->GetPlayerNumber());

			// 色塗る処理
			m_pPeintCollision[nAttackFinal] = CPeintCollision::Create(CreatePos + m_pos, m_pPlayer->GetPlayerNumber());
		}
	}
}

//=============================================================================
// 攻撃範囲の枠の色を変える処理
// Akuthor: 増澤 未来
//=============================================================================
void CAttackFinal::VisualizationAttackArea(int AttackFinalType)
{
	//攻撃フラグが立っているか
	if (GetAttackFinalFlag())
	{
		//タイプが一致しているか
		for (int nAttack = 0; nAttack < GetFinalAttackSquare().nMaxHitRange; nAttack++)
		{
			if (m_FinalAttackSquare.SquareData[nAttack].RangeType >= AttackFinalType + (int)CFinalAttackManager::FINAL_ATTACK_RANGE_HIT_1)
			{
				//行列計算
				D3DXVECTOR3 CreatePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				//攻撃位置
				D3DXVECTOR3 AttackPos = GetFinalAttackSquare().SquareData[nAttack].AttackPos * TILE_ONE_SIDE;
				CreatePos.x = ((cosf(GetRot().y)*AttackPos.x) + (sinf(GetRot().y)*AttackPos.z));
				CreatePos.y = 1 * AttackPos.y;
				CreatePos.z = ((-sinf(GetRot().y)*AttackPos.x) + (cosf(GetRot().y)*AttackPos.z));

				if (m_apAttackArea[nAttack] != NULL)
				{
					m_apAttackArea[nAttack]->SetColor(GET_COLORMANAGER->GetIconColor(GetPlayer()->GetColorNumber()));
					m_apAttackArea[nAttack]->SetPos(CreatePos + m_pos + D3DXVECTOR3(0.0f, 10.0f, 0.0f));
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
		CColorTile*pHitTile = CColorTile::GetHitColorTile(GetPlayer()->GetPos());
		if (pHitTile != NULL)
		{
			//タイプが一致しているか
			for (int nAttack = 0; nAttack < GetFinalAttackSquare().nMaxHitRange; nAttack++)
			{
				//行列計算
				D3DXVECTOR3 CreatePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				//攻撃位置
				D3DXVECTOR3 AttackPos = GetFinalAttackSquare().SquareData[nAttack].AttackPos * TILE_ONE_SIDE;
				CreatePos.x = ((cosf(GetPlayer()->GetRotDest().y)*AttackPos.x) + (sinf(GetPlayer()->GetRotDest().y)*AttackPos.z));
				CreatePos.y = 1 * AttackPos.y;
				CreatePos.z = ((-sinf(GetPlayer()->GetRotDest().y)*AttackPos.x) + (cosf(GetPlayer()->GetRotDest().y)*AttackPos.z));

				if (m_apAttackArea[nAttack] != NULL)
				{
					m_apAttackArea[nAttack]->SetColor(GET_COLORMANAGER->GetIconColor(GetPlayer()->GetColorNumber()));
					m_apAttackArea[nAttack]->SetPos(CreatePos + GetPlayer()->GetPos() + D3DXVECTOR3(0.0f, 10.0f, 0.0f));
					m_apAttackArea[nAttack]->SetDrawFlag(true);
					
				}
			}
		}
	}
}

//=============================================================================
// 攻撃範囲ポリゴンのリセット
// Akuthor: 増澤 未来
//=============================================================================
void CAttackFinal::ResetAttackArea(void)
{
	for (int nCntArea = 0; nCntArea < MAX_ATTACK_FINAL_AREA_NUM; nCntArea++)
	{
		if (m_apAttackArea[nCntArea] != NULL)
		{
			m_apAttackArea[nCntArea]->SetDrawFlag(false);
			m_apAttackArea[nCntArea]->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_apAttackArea[nCntArea]->SetSize(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
	}
}