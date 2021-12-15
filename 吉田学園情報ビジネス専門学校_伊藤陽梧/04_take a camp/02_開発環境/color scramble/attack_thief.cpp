//=============================================================================
//
// 攻撃範囲タイプ盗賊 [attack_knight.cpp]
// Author : 増澤 未来
//
//=============================================================================

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "attack_thief.h"
#include "tile.h"
#include "player.h"
#include "attack.h"
#include "skill_effect.h"
#include "skill_circle.h"
#include "color_manager.h"


//=============================================================================
// コンストラクタ
//=============================================================================
CAttackThief::CAttackThief()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CAttackThief::~CAttackThief()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CAttackThief * CAttackThief::Create(CPlayer* pPlayer)
{
	//メモリ確保
	CAttackThief* pAttackKnight = NULL;
	pAttackKnight = new CAttackThief;

	if (pAttackKnight != NULL)
	{
		pAttackKnight->SetType(CResourceCharacter::CHARACTER_THIEF);
		pAttackKnight->SetPlayer(pPlayer);	// プレイヤークラス取得
		pAttackKnight->Init();				// 初期化処理
	}
	return pAttackKnight;
}

//=============================================================================
// エフェクト生成
//=============================================================================
void CAttackThief::CreateEffect(D3DXVECTOR3 pos)
{
	//プレイヤーのポインタ
	CPlayer *pPlaryer = GetPlayer();
	//エフェクト生成
	CSkill_effect::Create(pPlaryer->GetPos() + pos + NORMAL_SKIIL_POS, NORMAL_SKIIL_SIZE, GET_COLORMANAGER->GetStepColor(pPlaryer->GetColorNumber(), pPlaryer->GetChargeTilelevel()),
		GET_COLORMANAGER->GetStepColor(pPlaryer->GetColorNumber(), pPlaryer->GetChargeTilelevel() - 1),
		GET_COLORMANAGER->GetStepColor(pPlaryer->GetColorNumber(), pPlaryer->GetChargeTilelevel() + 1), CSkill_effect::SKILLTYPE_KNIGHT);
}
