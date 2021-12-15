////////////////////////////////////////////////////
//
//    攻撃範囲クラスの処理[attack_area.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "attack_area.h"
#include "tile.h"
#include "resource_texture.h"

//******************************
// マクロ定義
//******************************
#define POLYGON_SIZE_MAX (D3DXVECTOR3(TILE_ONE_SIDE - 5.0f, 0.0f, TILE_ONE_SIDE - 5.0f))   // サイズ最大
#define POLYGON_SIZE_MIN (D3DXVECTOR3(TILE_ONE_SIDE - 15.0f, 0.0f, TILE_ONE_SIDE - 15.0f)) // サイズ最小
#define SIZE_RATE 0.03f // サイズ係数
#define ADD_ROT (D3DXVECTOR3( 0.0f, 0.05f, 0.0f)) // 回転量
#define ALPHA_RATE 0.1f

//******************************
// コンストラクタ
//******************************
CAttackArea::CAttackArea()
{
	m_bDraw = false;
	m_bExpansion = false;
}

//******************************
// デストラクタ
//******************************
CAttackArea::~CAttackArea()
{
}

//******************************
// クラス生成
//******************************
CAttackArea * CAttackArea::Create(void)
{
	// クラス生成
	CAttackArea * pInstace = new CAttackArea;
	// 初期化処理
	pInstace->Init();

	return pInstace;
}

//******************************
// 初期化処理
//******************************
HRESULT CAttackArea::Init(void)
{
	// 初期化
	CScene3d::Init();

	// テクスチャの割り当て
	BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_ATTACK_AREA));

	// サイズの設定
	SetSize(POLYGON_SIZE_MAX);

	// 描画フラグ
	m_bDraw = false;
	// 拡大フラグ
	m_bExpansion = false;

	// プライオリティ
	SetPriority(OBJTYPE_EFFECT);

	return S_OK;
}

//******************************
// 更新処理
//******************************
void CAttackArea::Update(void)
{
	SetRot(GetRot() + ADD_ROT);

	// サイズの調整
	D3DXVECTOR3 size = GetSize();
	if(m_bExpansion)
	{ 
		size += (POLYGON_SIZE_MAX - size)*SIZE_RATE;

		if (size.x >= POLYGON_SIZE_MAX.x - 2.0f)
		{
			m_bExpansion = false;
		}
	}
	else
	{
		size += (POLYGON_SIZE_MIN - size)*(SIZE_RATE*1.5f);

		if (size.x <= POLYGON_SIZE_MIN.x + 2.0f)
		{
			m_bExpansion = true;
		}
	}
	SetSize(size);

	D3DXCOLOR col = GetColor();
	if (m_bDraw)
	{
		col.a += (1.0f - col.a)*ALPHA_RATE;
	}
	else
	{
		col.a += (0.0f - col.a)*ALPHA_RATE;
	}
	SetColor(col);
}

//******************************
// 描画処理
//******************************
void CAttackArea::Draw(void)
{
	CScene3d::Draw();
}
