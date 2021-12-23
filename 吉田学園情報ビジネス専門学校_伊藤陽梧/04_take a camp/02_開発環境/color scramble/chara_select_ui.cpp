////////////////////////////////////////////////////
//
//    キャラ選択UIクラスの処理[chara_select_ui.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//=============================
// インクルード
//=============================
#include "chara_select_ui.h"
#include "chara_select.h"
#include "scene2d.h"
#include "resource_texture.h"
#include "color_manager.h"
#include "character_polygon.h"

//=============================
// マクロ定義
//=============================
#define BACK_SIZE D3DXVECTOR3(320.0f,720.0f,0.0f)            // ボードサイズ
#define CONTOROll_ICON_SIZE D3DXVECTOR3(180.0f,180.0f,0.0f)  // コントローラーアイコンのサイズ
#define PLAYERNUMBER_SIZE D3DXVECTOR3(240.0f,60.0f,0.0f)     // プレイヤー番号のサイズ
#define READY_SIZE D3DXVECTOR3(48.0f*5.0f,18.6f*5.0f,0.0f)            // ボードサイズ
#define PLAYERNUMBER_TEX_ANIM_MAX_X 1                        // 順位テクスチャ分割数*横
#define PLAYERNUMBER_TEX_ANIM_MAX_Y 4                        // 順位テクスチャ分割数*縦
#define ANIMATION_INTERVAL 15                                // アニメーション移行フレーム数
#define UI_SPACE 320.0f                                      // UI間の左右のスペース
#define BACK_DEFAULT_COLOR D3DXCOLOR(0.7f,0.7f,0.7f,1.0f)    // デフォルトのカラー
#define ICON_COLOR_ON      D3DXCOLOR(1.0f,1.0f,1.0f,1.7f)    // アイコンのカラー
#define ICON_COLOR_OFF     D3DXCOLOR(1.0f,1.0f,1.0f,0.0f)    // アイコンのカラー
#define PLAYER_NUMBER_POS_Y 60.0f
#define CHARACTER_MODEL_POS_Y 340.0f
#define READY_ICON_POS_Y  450.0f

//=============================
// 静的メンバ変数宣言
//=============================

//=============================
// コンストラクタ
//=============================
CCharaSelectUi::CCharaSelectUi()
{
	// 変数のクリア
	ZeroMemory(&m_aPolygon, sizeof(m_aPolygon));
	m_nCntAnim = 0;       // アニメーションカウント
	m_nAnimY = 0;         // アニメーションY軸
}

//=============================
// デストラクタ
//=============================
CCharaSelectUi::~CCharaSelectUi()
{
}

//=============================
// クリエイト
//=============================
CCharaSelectUi * CCharaSelectUi::Create(void)
{
	// メモリの確保
	CCharaSelectUi *pUi= new CCharaSelectUi;
	// 初期化
	pUi->Init();

	return pUi;
}

//=============================
// 初期化処理
//=============================
HRESULT CCharaSelectUi::Init(void)
{
	D3DXVECTOR3 boardPos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	boardPos.x = boardPos.x - (UI_SPACE*(MAX_PLAYER - 1)) / 2;

	D3DXVECTOR2 uv[NUM_VERTEX];
	float fu = 1.0f / PLAYERNUMBER_TEX_ANIM_MAX_X;
	float fv = 1.0f / PLAYERNUMBER_TEX_ANIM_MAX_Y;

	uv[0] = D3DXVECTOR2(fu*0.0f     , fv*m_nAnimY);
	uv[1] = D3DXVECTOR2(fu*0.0f + fu, fv*m_nAnimY);
	uv[2] = D3DXVECTOR2(fu*0.0f     , fv*m_nAnimY + fv);
	uv[3] = D3DXVECTOR2(fu*0.0f + fu, fv*m_nAnimY + fv);

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		// 背景の生成
		m_aPolygon[nCntPlayer].pBack = CScene2d::Create();
		m_aPolygon[nCntPlayer].pBack->SetSize(BACK_SIZE);
		m_aPolygon[nCntPlayer].pBack->SetPos(boardPos);
		m_aPolygon[nCntPlayer].pBack->SetColor(BACK_DEFAULT_COLOR);
		m_aPolygon[nCntPlayer].pBack->SetPriority(OBJTYPE_UI_2);
		m_aPolygon[nCntPlayer].pBack->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_CHARASELECT_BACK));

		// アイコンの生成
		m_aPolygon[nCntPlayer].pControllIcon = CScene2d::Create();
		m_aPolygon[nCntPlayer].pControllIcon->SetSize(CONTOROll_ICON_SIZE);
		m_aPolygon[nCntPlayer].pControllIcon->SetPos(boardPos);
		m_aPolygon[nCntPlayer].pControllIcon->SetColor(ICON_COLOR_OFF);
		m_aPolygon[nCntPlayer].pControllIcon->SetPriority(OBJTYPE_UI_2);

		// プレイヤー番号の生成
		m_aPolygon[nCntPlayer].pPlayerNumber = CScene2d::Create();
		m_aPolygon[nCntPlayer].pPlayerNumber->SetSize(PLAYERNUMBER_SIZE);
		m_aPolygon[nCntPlayer].pPlayerNumber->SetPos(D3DXVECTOR3(boardPos.x, PLAYER_NUMBER_POS_Y, boardPos.z));
		m_aPolygon[nCntPlayer].pPlayerNumber->SetPriority(OBJTYPE_UI_2);
		m_aPolygon[nCntPlayer].pPlayerNumber->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_NONE_UI));
		m_aPolygon[nCntPlayer].pPlayerNumber->SetTextureUV(uv);

		// モデルポリゴンの生成
		m_aPolygon[nCntPlayer].pCharaPolygon = CCharacterPolygon::Create(D3DXVECTOR3(boardPos.x, CHARACTER_MODEL_POS_Y, boardPos.z),CCharacterPolygon::MODE_ROTATION);

		// アイコンの生成
		m_aPolygon[nCntPlayer].pReadyIcon = CScene2d::Create();
		m_aPolygon[nCntPlayer].pReadyIcon->SetSize(READY_SIZE);
		m_aPolygon[nCntPlayer].pReadyIcon->SetPos(D3DXVECTOR3(boardPos.x, READY_ICON_POS_Y, boardPos.z));
		m_aPolygon[nCntPlayer].pReadyIcon->SetColor(ICON_COLOR_OFF);
		m_aPolygon[nCntPlayer].pReadyIcon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_READEY));
		m_aPolygon[nCntPlayer].pReadyIcon->SetPriority(OBJTYPE_UI_2);

		boardPos.x += UI_SPACE;
	}

	// 変数の初期化
	m_nCntAnim = 0;       // アニメーションカウント
	m_nAnimY = 0;         // アニメーションY軸

	return S_OK;
}

//=============================
// 終了処理
//=============================
void CCharaSelectUi::Uninit(void)
{
	// 開放処理
	Release();
}

//=============================
// 更新処理
//=============================
void CCharaSelectUi::Update(void)
{
	// アニメーション
	m_nCntAnim++;
	if (m_nCntAnim%ANIMATION_INTERVAL == 0)
	{
		m_nAnimY++;
	}

	D3DXVECTOR2 uv[NUM_VERTEX];
	float fu = 1.0f / PLAYERNUMBER_TEX_ANIM_MAX_X;
	float fv = 1.0f / PLAYERNUMBER_TEX_ANIM_MAX_Y;

	uv[0] = D3DXVECTOR2(fu*0.0f     , fv*m_nAnimY);
	uv[1] = D3DXVECTOR2(fu*0.0f + fu, fv*m_nAnimY);
	uv[2] = D3DXVECTOR2(fu*0.0f     , fv*m_nAnimY + fv);
	uv[3] = D3DXVECTOR2(fu*0.0f + fu, fv*m_nAnimY + fv);

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		// エントリーデータの取得
		CCharaSelect::Entry_Data entryData = CCharaSelect::GetEntryData(nCntPlayer);
		if (entryData.bEntry)
		{// エントリー時
			m_aPolygon[nCntPlayer].pBack->SetColor(GET_COLORMANAGER->GetIconColor(entryData.nColorNum));
			m_aPolygon[nCntPlayer].pCharaPolygon->SetRimColor(GET_COLORMANAGER->GetStepColor(entryData.nColorNum,1));
			m_aPolygon[nCntPlayer].pCharaPolygon->SetTexColor(GET_COLORMANAGER->GetIconColor(entryData.nColorNum));
			m_aPolygon[nCntPlayer].pControllIcon->SetColor(ICON_COLOR_ON);

			if (entryData.bReady) m_aPolygon[nCntPlayer].pReadyIcon->SetColor(ICON_COLOR_ON);
			else m_aPolygon[nCntPlayer].pReadyIcon->SetColor(ICON_COLOR_OFF);

			if (entryData.bController)
			{
				m_aPolygon[nCntPlayer].pControllIcon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_CONTROLLER));
			}
			else
			{
				m_aPolygon[nCntPlayer].pControllIcon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_KEYBOARD));
			}

			D3DXVECTOR2 uv[NUM_VERTEX];
			float fu = 1.0f / PLAYERNUMBER_TEX_ANIM_MAX_X;
			float fv = 1.0f / PLAYERNUMBER_TEX_ANIM_MAX_Y;

			uv[0] = D3DXVECTOR2(fu*0.0f     , fv*nCntPlayer);
			uv[1] = D3DXVECTOR2(fu*0.0f + fu, fv*nCntPlayer);
			uv[2] = D3DXVECTOR2(fu*0.0f     , fv*nCntPlayer + fv);
			uv[3] = D3DXVECTOR2(fu*0.0f + fu, fv*nCntPlayer + fv);
			m_aPolygon[nCntPlayer].pPlayerNumber->SetTextureUV(uv);
			m_aPolygon[nCntPlayer].pPlayerNumber->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_PLAYERNUMBER));

		}
		else
		{// 非エントリー時
			m_aPolygon[nCntPlayer].pBack->SetColor(BACK_DEFAULT_COLOR);
			m_aPolygon[nCntPlayer].pControllIcon->SetColor(ICON_COLOR_OFF);
			m_aPolygon[nCntPlayer].pReadyIcon->SetColor(ICON_COLOR_OFF);
			m_aPolygon[nCntPlayer].pPlayerNumber->SetTextureUV(uv);
			m_aPolygon[nCntPlayer].pPlayerNumber->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_NONE_UI));
		}

		// キャラタイプの設定
		m_aPolygon[nCntPlayer].pCharaPolygon->SetCharaType(entryData.charaType);
	}
}

//=============================
// 描画処理
//=============================
void CCharaSelectUi::Draw(void)
{
}
