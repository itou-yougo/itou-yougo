//=============================================================================
//
// 攻撃範囲タイプ騎士 [attack_knight.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "attack_lancer.h"
#include "tile.h"
#include "player.h"
#include "attack.h"
#include "skill_effect.h"
#include "skill_circle.h"
#include "color_manager.h"
//=============================================================================
// コンストラクタ
//=============================================================================
CAttackLancer::CAttackLancer()
{
	/*m_nAttackCount = 0;
	m_nType = 0;*/
}

//=============================================================================
// デストラクタ
//=============================================================================
CAttackLancer::~CAttackLancer()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CAttackLancer * CAttackLancer::Create(CPlayer* pPlayer)
{
	//メモリ確保
	CAttackLancer* pAttackLancer = NULL;
	pAttackLancer = new CAttackLancer;

	if (pAttackLancer != NULL)
	{
		pAttackLancer->SetType(CResourceCharacter::CHARACTER_LANCER);
		pAttackLancer->SetPlayer(pPlayer);	// プレイヤークラス取得
		pAttackLancer->Init();				// 初期化処理
	}
	return pAttackLancer;
}

//=============================================================================
// エフェクト生成
//=============================================================================
void CAttackLancer::CreateEffect(D3DXVECTOR3 pos)
{
	CPlayer *pPlaryer = GetPlayer();
	//エフェクト生成
	CSkill_effect::Create(pPlaryer->GetPos() + pos + NORMAL_SKIIL_POS, NORMAL_SKIIL_SIZE, GET_COLORMANAGER->GetStepColor(pPlaryer->GetColorNumber(), pPlaryer->GetChargeTilelevel()),
		GET_COLORMANAGER->GetStepColor(pPlaryer->GetColorNumber(), pPlaryer->GetChargeTilelevel() - 1),
		GET_COLORMANAGER->GetStepColor(pPlaryer->GetColorNumber(), pPlaryer->GetChargeTilelevel() + 1), CSkill_effect::SKILLTYPE_KNIGHT);
}

////=============================================================================
//// 攻撃生成関数
////=============================================================================
//void CAttackLancer::AttackCreate(void)
//{
//	//プレイヤーのポインタ
//	CPlayer *pPlaryer = GetPlayer();
//
//	//攻撃フラグが立っているか
//	if (GetState() == ATTACK_STATE_ATTACK
//		|| GetState() == ATTACK_STATE_FINALATTACK)
//	{
//		//カウントアップ
//		m_nAttackCount++;
//
//		// 攻撃範囲の可視化
//		VisualizationAttackArea(m_nType);
//
//		//スキルエフェクトの生成
//		if (m_nType == MIN_HIT_TYPE)
//		{
//			for (int nCnt = 0; nCnt < GetAttackSquare().nMaxHitRange; nCnt++)
//			{
//
//				//行列計算
//				D3DXVECTOR3 CreatePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//				D3DXVECTOR3 AttackPos = GetAttackSquare().SquareData[nCnt].AttackPos * TILE_ONE_SIDE;
//				CreatePos.x = ((cosf(pPlaryer->GetRot().y)*AttackPos.x) + (sinf(pPlaryer->GetRot().y)*AttackPos.z));
//				CreatePos.y = 1 * AttackPos.y;
//				CreatePos.z = ((-sinf(pPlaryer->GetRot().y)*AttackPos.x) + (cosf(pPlaryer->GetRot().y)*AttackPos.z));
//
//				//エフェクト生成
//				CSkill_effect::Create(pPlaryer->GetPos() + CreatePos + NORMAL_SKIIL_POS, NORMAL_SKIIL_SIZE, GET_COLORMANAGER->GetStepColor(pPlaryer->GetColorNumber(), pPlaryer->GetChargeTilelevel()),
//					GET_COLORMANAGER->GetStepColor(pPlaryer->GetColorNumber(), pPlaryer->GetChargeTilelevel() - 1),
//					GET_COLORMANAGER->GetStepColor(pPlaryer->GetColorNumber(), pPlaryer->GetChargeTilelevel() + 1), CSkill_effect::SKILLTYPE_KNIGHT);
//			}
//
//		}
//
//		//カウントが一定になったら
//		if (m_nAttackCount >= GetAttackSquare().nAttackFrame[m_nType])
//		{
//			//攻撃処理
//			Attack(m_nType);
//			//タイプが一定になったら
//			if (m_nType == MAX_HIT_TYPE)
//			{
//				//フラグの初期化
//				SetState(ATTACK_STATE_NORMAL);
//				//タイプ初期化
//				m_nType = 0;
//				//レベルの初期化
//				CAttackBased::SetLevel(0);
//			}
//			else
//			{
//				//次の攻撃タイプへ
//				m_nType++;
//			}
//			//カウント初期化
//			m_nAttackCount = 0;
//
//		}
//	}
//}