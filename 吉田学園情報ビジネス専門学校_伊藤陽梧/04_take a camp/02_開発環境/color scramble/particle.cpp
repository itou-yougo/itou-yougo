////////////////////////////////////////////////////
//
//    particleクラスの処理[particle.cpp]
//    Author:齋藤大行
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "particle.h"
#include "manager.h"
#include "renderer.h"
#include "resource_texture.h"

//*****************************
// マクロ定義
//*****************************

//******************************
// 静的メンバ変数宣言
//*****************************

//******************************
// コンストラクタ
//******************************
CParticle::CParticle()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	m_nLife = 0;
	m_type = PARTICLE_SQUARE;
	m_bFadeoutFlag = true;
	m_fRotAngle = 0.0f;
	m_fFadeout = 0.0f; 
	

}

//******************************
// デストラクタ
//******************************
CParticle::~CParticle()
{
}

//******************************
// クリエイト
//******************************
CParticle * CParticle::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXVECTOR3 size, const int nLife, const D3DXCOLOR col,const float fadeout, const PARTICLE_TYPE type)
{
	// メモリの確保
	CParticle *pParticle;
	pParticle = new CParticle;

	// タイプの設定
	pParticle->m_type = type;

	// 初期化
	pParticle->Init();

	// 各値の代入・セット
	pParticle->SetPos(pos);                  // 座標
	pParticle->m_move = move;                // 移動量
	pParticle->m_size = size;				 // サイズ代入
	pParticle->SetSize(size);                // サイズ
	pParticle->m_nLife = nLife;				 // 寿命
	pParticle->m_col = col;					 // 代入
	pParticle->m_fFadeout = fadeout;		 // フェードアウト
	pParticle->m_fRotAngle = 0.0f;           // 回転角度
	pParticle->SetColor(col);                // カラー設定
	pParticle->SetAngle((float)(rand() % 360));       // 回転角度をランダム
	pParticle->SetAddMode(false);             // 加算合成
	

	switch (type)
	{
	case PARTICLE_SQUARE:
		
		break;

	case PARTICLE_TEARS:
		break;

	case PARTICLE_CIRCLE:
		break;

	default:
		break;
	}
	
	return pParticle;
}

//******************************
// 初期化処理
//******************************
HRESULT CParticle::Init(void)
{
	if (FAILED(CBillboard::Init()))
	{
		return E_FAIL;
	}

	m_apTexture[PARTICLE_SQUARE] = CResourceTexture::GetTexture(CResourceTexture::TEXTURE_PARTICLE_SQUARE);
	m_apTexture[PARTICLE_TEARS] = CResourceTexture::GetTexture(CResourceTexture::TEXTURE_PARTICLE_SKILL);
	m_apTexture[PARTICLE_CIRCLE] = CResourceTexture::GetTexture(CResourceTexture::TEXTURE_PARTICLE_CIRCLE);
	m_apTexture[PARTICLE_GURUGURU] = CResourceTexture::GetTexture(CResourceTexture::TEXTURE_PARTICLE_GURUGURU);
	// テクスチャ割り当て
	BindTexture(m_apTexture[m_type]);

	SetPriority(OBJTYPE_PARTICLE);
	return S_OK;
}

//******************************
// 終了処理
//******************************
void CParticle::Uninit(void)
{
	CBillboard::Uninit();
}

//******************************
// 更新処理
//******************************
void CParticle::Update(void)
{
	// 移動
	SetPos(GetPos() + m_move);

	switch (m_type)
	{
	case PARTICLE_SQUARE:
		m_col.a -= m_fFadeout;
		SetColor(m_col);

		break;

	case PARTICLE_TEARS:
		break;

	case PARTICLE_CIRCLE:
		break;
	case PARTICLE_GURUGURU:
		m_col.a -= m_fFadeout;
		SetColor(m_col);
		break;
	
	default:
		break;
	}

	SetAngle(GetAngle() + m_fRotAngle);

	if (m_col.a <= 0)
	{
		m_bFadeoutFlag = false;
	}

	if (!m_bFadeoutFlag)
	{
		Uninit();
	}

	// 寿命
	/*m_nLife--;
	if (m_nLife <= 0)
	{
		Uninit();
	}*/
}

//******************************
// 描画処理
//******************************
void CParticle::Draw(void)
{
	CBillboard::Draw();
}
