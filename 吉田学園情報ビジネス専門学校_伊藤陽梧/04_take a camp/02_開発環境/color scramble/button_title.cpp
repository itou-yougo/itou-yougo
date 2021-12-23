//=============================================================================
//
// タイトルのボタンの処理 [button_title.cpp]
// Author : 佐藤颯紀
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "button_title.h"
#include "keyboard.h"
#include "manager.h"
#include "fade.h"
#include "resource_texture.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define BUTTON_SIZE D3DXVECTOR3(350.0f,100.0f,0.0f)	// サイズ
#define BUTTON_COLOR D3DXCOLOR(1.0f,1.0f,1.0f,1.0f)		// カラー
#define NOT_BUTTON_COLOR D3DXCOLOR(1.0f,1.0f,1.0f,0.5f)	// 選択されてないときのカラー

//=============================================================================
// コンストラクタ
//=============================================================================
CButton_Title::CButton_Title()
{
	m_nButton = 0;
	m_type = BUTTON_NONE;
	m_color = BUTTON_COLOR;
}

//=============================================================================
// デストラクタ
//=============================================================================
CButton_Title::~CButton_Title()
{

}

//=============================================================================
// 生成処理
//=============================================================================
CButton_Title * CButton_Title::Create(D3DXVECTOR3 pos, BUTTON_TYPE type)
{
	// メモリの確保
	CButton_Title *pButton_Title;
	pButton_Title = new CButton_Title;

	// 初期化
	pButton_Title->Init();

	// 各値の代入
	pButton_Title->SetPos(pos);
	pButton_Title->SetPriority(OBJTYPE_UI_2);
	pButton_Title->m_type = type;

	// タイプがスタートだった場合
	if (pButton_Title->m_type == BUTTON_START)
	{
		pButton_Title->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_BUTTON_START));
	}
	// タイプがチュートリアルだった場合
	if (pButton_Title->m_type == BUTTON_TUTORIAL)
	{
		pButton_Title->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTYRE_BUTTON_TUTORIAL));
	}

	return pButton_Title;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CButton_Title::Init(void)
{
	// 初期化処理
	CButton::Init();

	// サイズ設定
	SetSize(BUTTON_SIZE);

	// カラー設定
	SetColor(BUTTON_COLOR);

	// 初期ボタン
	m_nButton = BUTTON_START;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CButton_Title::Uninit(void)
{
	// 終了処理
	CButton::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CButton_Title::Update(void)
{
	// 更新処理
	CButton::Update();

	// 選択処理
	Select();
	// 色の処理
	Collar();
}

//=============================================================================
// 選択処理
//=============================================================================
void CButton_Title::Select(void)
{
	// キーボード情報の取得
	CInputKeyboard * pKey = CManager::GetKeyboard();

	// 上キーを押したとき
	if (pKey->GetKeyTrigger(DIK_UP))
	{
		// 現在のボタンを減算する
		m_nButton--;
	}

	// 下キーを押したとき
	if (pKey->GetKeyTrigger(DIK_DOWN))
	{
		// 現在のボタンを加算する
		m_nButton++;
	}

	// ０より下にいったら
	if (m_nButton <= -1)
	{
		m_nButton = BUTTON_TUTORIAL;
	}

	// 最大値より上にいったら初期値に戻す
	if (m_nButton >= BUTTON_MAX)
	{
		m_nButton = 0;
	}

	// エンターを押したとき
	if (pKey->GetKeyTrigger(DIK_RETURN))
	{
		// ボタンの種類がスタートだった場合
		if (m_nButton == BUTTON_START)
		{
			// ゲーム画面に遷移
			CManager::GetFade()->SetFade(CManager::MODE_CHARA_SELECT);
			CManager::SetDecMode(CManager::MODE_GAME);
		}
		// ボタンの種類がチュートリアルだった場合
		if (m_nButton == BUTTON_TUTORIAL)
		{
			// チュートリアル画面に遷移
			CManager::GetFade()->SetFade(CManager::MODE_CHARA_SELECT);
			CManager::SetDecMode(CManager::MODE_TUTORIAL);
		}
	}
}

//=============================================================================
// 色の処理
//=============================================================================
void CButton_Title::Collar(void)
{
	// ボタンが選択されていたら
	if (m_type == m_nButton)
	{
		// 色設定
		SetColor(BUTTON_COLOR);
	}

	// ボタンが選択されていなかったら
	if (m_type != m_nButton)
	{
		// 色設定
		SetColor(NOT_BUTTON_COLOR);
	}
}