//===================================================
//
// スキルゲージの処理[skill_gauge.cpp]
// Author:伊藤陽梧
//
//====================================================

//**********************************
// インクルード
//**********************************
#include "skill_gauge.h"
#include "manager.h"
#include "billboard.h"
#include "resource_texture.h"
#include "renderer.h"
#include "polygon.h"
#include "player.h"
#include "color_manager.h"
#include "keyboard.h"
#include "joypad.h"
#include "attack.h"

//==================================
// マクロ定義
//==================================
#define SKILLGAUGE_ADDPOS (D3DXVECTOR3(0.0f, 35.0f, 0.0f)) // スキルゲージの座標
#define SKILLGAUGE_SIZE (D3DXVECTOR3(20.0f, 20.0f, 0.0f))  // スキルゲージの大きさ
#define DEFAULT_COLOR (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))  // 色の初期値
#define SKILLGAUGE_FLAME (60.0f)                           // フレーム数
#define REPAINT_RATE (0.5f)                                // 塗替えした際の倍率
#define MINORADJUSSTMENT_POS (D3DXVECTOR3(0.5f,1.0f,0.0f)) // 微調整用の座標
#define DEFAULT_ANGLE (D3DXToRadian(-40.0f))               // ポリゴンを回転させる角度

//==================================
// コンストラクタ
//==================================
CSkillgauge::CSkillgauge()
{
	m_SkillGaugeType = SKILLGAUGE_STENCIL;
	memset(&m_pos, 0, sizeof(m_pos));
	memset(&m_size, 0, sizeof(m_size));
	memset(&m_col, 0, sizeof(m_col));
	m_nPlayerNum = 0;
	m_fGauge = 0.0f;
}

//==================================
// デストラクタ
//==================================
CSkillgauge::~CSkillgauge()
{
}

//==================================
// スキルゲージすべてのクリエイト
// nPlayerNum：プレイヤーの番号
//==================================
CSkillgauge* CSkillgauge::AllCreate(const int nPlayerNum)
{
	// アイコンとステンシル
	CSkillgauge::Create(SKILLGAUGE_SIZE, DEFAULT_COLOR, nPlayerNum, CSkillgauge::SKILLGAUGE_ICON);
	CSkillgauge * pSkillgauge = CSkillgauge::Create(SKILLGAUGE_SIZE, GET_COLORMANAGER->GetIconColor(nPlayerNum), nPlayerNum, CSkillgauge::SKILLGAUGE_STENCIL);

	return pSkillgauge;
}

//==================================
// クリエイト
// size：スキルゲージの大きさ
// col：スキルゲージの色
// nPlayerNum：プレイヤーの番号
// SkillGaugeType：スキルゲージのタイプ
//==================================
CSkillgauge * CSkillgauge::Create(const D3DXVECTOR3 size, const D3DXCOLOR col, const int nPlayerNum, const SKILLGAUGE_TYPE SkillGaugeType)
{
	// メモリの確保
	CSkillgauge * pSkillgauge = new CSkillgauge;

	pSkillgauge->m_size = size;
	pSkillgauge->m_col = col;
	pSkillgauge->m_nPlayerNum = nPlayerNum;
	pSkillgauge->m_SkillGaugeType = SkillGaugeType;
	pSkillgauge->SetPriority(OBJTYPE_UI_2);

	// 初期化処理
	pSkillgauge->Init();

	return pSkillgauge;
}

//==================================
// 初期化処理
//==================================
HRESULT CSkillgauge::Init()
{
	// 初期化処理
	CBillboard::Init();

	// 座標、サイズ、色のセット
	SetPos(m_pos);
	SetSize(m_size);
	SetColor(m_col);

	switch (m_SkillGaugeType)
	{
	case SKILLGAUGE_STENCIL:
		// ステンシルを表示する座標
		SetPolygonPos();
		break;

	case SKILLGAUGE_ICON:
		// キャラクターのタイプごとにテクスチャを変える
		switch (GetPlayerinfo(m_nPlayerNum)->GetCharacterType())
		{
		case CResourceCharacter::CHARACTER_TYPE::CHARACTER_KNIGHT:
			BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_SWORD_ICON));
			break;
		//case CResourceCharacter::CHARACTER_TYPE::CHARACTER_LANCER:
		//	BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_SWORD_ICON));
		//	break;
		//case CResourceCharacter::CHARACTER_TYPE::CHARACTER_WIZARD:
		//	BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_SWORD_ICON));
			break;
		default:
			break;
		}

		break;

	default:
		break;
	}

	return S_OK;
}

//==================================
// 終了処理
//==================================
void CSkillgauge::Uninit(void)
{
	// 終了処理
	CBillboard::Uninit();
}

//==================================
// 更新処理
//==================================
void CSkillgauge::Update(void)
{
	// 更新処理
	CBillboard::Update();

	// プレイヤーの座標を取得
	CPlayer * pPlayer = GetPlayerinfo(m_nPlayerNum);
	m_pos = pPlayer->GetPos();

	// 座標のセット
	SetPos(m_pos + SKILLGAUGE_ADDPOS);

	switch (m_SkillGaugeType)
	{
	case SKILLGAUGE_STENCIL:
		// ステンシルの更新
		UpdateStencil();
		break;

	default:
		break;
	}
}

//==================================
// 描画処理
//==================================
void CSkillgauge::Draw(void)
{
	// ステンシルバッファを使う
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ステンシルテストを有効に
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

	switch (m_SkillGaugeType)
	{
	case SKILLGAUGE_ICON:
		// ステンシルテストと比較する参照値設定
		pDevice->SetRenderState(D3DRS_STENCILREF, m_nPlayerNum + 0x01);

		// ステンシルテストの値に対してのマスク設定 0xff(全て真)
		pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);

		// この描画での参照値 == ステンシルバッファの参照値なら合格
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_GREATEREQUAL);

		// ステンシルテストの結果に対しての反映設定
		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
		pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
		pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
		break;

	case SKILLGAUGE_STENCIL:
		// ステンシルテストと比較する参照値設定
		pDevice->SetRenderState(D3DRS_STENCILREF, m_nPlayerNum + 0x01);

		// ステンシルテストの値に対してのマスク設定 0xff(全て真)
		pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);

		// この描画での参照値 == ステンシルバッファの参照値なら合格
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);

		// ステンシルテストの結果に対しての反映設定
		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
		pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
		pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
		break;

	default:
		break;
	}

	// 描画処理
	CBillboard::Draw();

	// ステンシルテストを無効に
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
}

//==================================
// プレイヤーの情報取得処理
//==================================
CPlayer * CSkillgauge::GetPlayerinfo(int nPlayerNum)
{
	// プレイヤーのポインタを取得
	CPlayer * pPlayer = (CPlayer*)GetTop(OBJTYPE_PLAYER);
	while (pPlayer != NULL)
	{
		if (pPlayer->GetPlayerNumber() == m_nPlayerNum)
		{
			break;
		}

		pPlayer = (CPlayer*)pPlayer->GetNext();
	}

	return pPlayer;
}

//==================================
// ステンシルの更新処理
//==================================
void CSkillgauge::UpdateStencil(void)
{
	// キャラデータの取得
	CResourceCharacter::CharacterData charaData =
		CResourceCharacter::GetResourceCharacter()->GetCharacterData(GetPlayerinfo(m_nPlayerNum)->GetCharacterType());

	// キャラクターごとの必殺技秒数*1秒間のフレーム数
	m_fGauge += m_size.y / ((float)charaData.nFinalAttackTime * SKILLGAUGE_FLAME);

	// サイズ分を超えないように
	if (m_fGauge > m_size.y)
	{
		m_fGauge = m_size.y;
	}
	
#ifdef _DEBUG
	// ゲージ満タンコマンド
	// キーボードの取得
	CInputKeyboard * pKey = CManager::GetKeyboard();
	if (pKey->GetKeyTrigger(DIK_F4))
	{
		m_fGauge = m_size.y;
	}
#endif // _DEBUG

	// ゲージが溜まったら
	if(m_fGauge == m_size.y)
	{
		// 必殺技のフラグ立て
		GetPlayerinfo(m_nPlayerNum)->SetFinalAttack(true);

		// 必殺技を打ったら
		if (GetPlayerinfo(m_nPlayerNum)->GetAttack()->GetState() == CAttackBased:: ATTACK_STATE_FINALATTACK)
		{
			GetPlayerinfo(m_nPlayerNum)->SetFinalAttack(false);
			m_fGauge = 0.0f;
		}
	}

	// ステンシルを表示する座標
	SetPolygonPos();
}

//==================================
// ステンシルを表示する座標
//==================================
void CSkillgauge::SetPolygonPos(void)
{
	// 頂点座標の設定
	D3DXVECTOR3 Pos[NUM_VERTEX];
	ZeroMemory(&Pos, sizeof(Pos));

	// 中心からの間隔
	float fDistance = sqrtf(powf(m_size.x / sqrtf(2.0f), 2) + powf(m_size.y / sqrtf(2.0f), 2));
	// 右上と左上の頂点
	float fAngle = atan2f(m_size.y / 2.0f, m_size.x / 2.0f);
	float fAngle2 = atan2f(m_size.y / 2.0f, -m_size.x / 2.0f);

	// 各頂点の座標
	Pos[0] = D3DXVECTOR3(cosf(-fAngle2 + DEFAULT_ANGLE) * fDistance + m_fGauge - MINORADJUSSTMENT_POS.x,
		sinf(-fAngle2 + DEFAULT_ANGLE) * fDistance + m_fGauge + MINORADJUSSTMENT_POS.y, 0.0f);
	Pos[1] = D3DXVECTOR3(cosf(-fAngle + DEFAULT_ANGLE) * fDistance + m_fGauge - MINORADJUSSTMENT_POS.x,
		sinf(-fAngle + DEFAULT_ANGLE) * fDistance + m_fGauge + MINORADJUSSTMENT_POS.y, 0.0f);
	Pos[2] = D3DXVECTOR3(cosf(-fAngle2 + DEFAULT_ANGLE) * fDistance - MINORADJUSSTMENT_POS.x,
		sinf(-fAngle2 + DEFAULT_ANGLE) * fDistance + MINORADJUSSTMENT_POS.y, 0.0f);
	Pos[3] = D3DXVECTOR3(cosf(-fAngle + DEFAULT_ANGLE) * fDistance - MINORADJUSSTMENT_POS.x,
		sinf(-fAngle + DEFAULT_ANGLE) * fDistance + MINORADJUSSTMENT_POS.y, 0.0f);

	// 頂点ごとの座標設定
	SetVertexPos(Pos);
}

//==================================
// 塗替えしたときゲージを加算する処理
//==================================
void CSkillgauge::Repaint_AddSkillGauge(void)
{
	// 倍率によって加算値を変える
	m_fGauge += REPAINT_RATE * (m_size.y / SKILLGAUGE_FLAME);
}