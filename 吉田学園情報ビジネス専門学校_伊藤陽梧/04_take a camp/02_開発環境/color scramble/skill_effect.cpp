//=============================================================================
//
// スキルサークル処理 [skill_circle.cpp]
// Author : 齋藤大行
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "skill_circle.h"
#include "skill_effect.h"
#include "base_Cylinder.h"
#include "resource_texture.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define KNIGHT_POSSHIFT D3DXVECTOR3(3.0f, 0.0f, 3.0f)



//=============================================================================
//静的メンバー変数
//=============================================================================


CSkill_effect::CSkill_effect()
{
	m_type = SKILLTYPE_KNIGHT;
}

CSkill_effect::~CSkill_effect()
{
}

void CSkill_effect::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXCOLOR col1, const D3DXCOLOR col2, const D3DXCOLOR col3, const SKILLTYPE type)
{	

	switch (type)
	{
	case SKILLTYPE_KNIGHT:

		CSkill_circle::Create(pos, size, col1, CSkill_circle::EFFECTTYPE_SKIIL);
		CSkill_circle::Create(pos, size + KNIGHT_POSSHIFT, col2, CSkill_circle::EFFECTTYPE_SKIILMINI);
		break;

	case SKILLTYPE_ARCHER:

		break;

	case SKILLTYPE_WIZARD:

		break;

	case SKILLTYPE_LANCER:

		break;

	case SKILLTYPE_MAGICIAN:

		break;

	case SKILLTYPE_THIER:

		break;

	default:
		break;
	}
}
