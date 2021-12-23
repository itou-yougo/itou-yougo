//=============================================================================
//
// キャラクターポリゴンの処理 [character_polygon.cpp]
// Author : 増澤未来
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "character_polygon.h"
#include "dynamic_texture.h"
#include "player_model.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define CHARACTER_POS (D3DXVECTOR3(0.0f,-8.8f,0.0f))
#define CHARACTER_ROT (D3DXVECTOR3(0.0f,D3DXToRadian(180.0f),0.0f))
#define CHARACTER_ADD_ROT (D3DXVECTOR3(0.0f, 0.01f, 0.0f))

//=============================================================================
// コンストラクタ
//=============================================================================
CCharacterPolygon::CCharacterPolygon() :CScene2d(OBJTYPE_UI_2)
{
	m_pDynamicTex = NULL;
	m_pCharacterModel = NULL;
	m_charaType = CResourceCharacter::CHARACTER_NONE;
}

//=============================================================================
// デストラクタ
//=============================================================================
CCharacterPolygon::~CCharacterPolygon()
{

}

//=============================================================================
// 生成処理
//=============================================================================
CCharacterPolygon * CCharacterPolygon::Create(D3DXVECTOR3 pos, CharaPolygonMode mode)
{
	// メモリの確保
	CCharacterPolygon *pCharacterPolygon;
	pCharacterPolygon = new CCharacterPolygon;

	// 初期化
	pCharacterPolygon->Init();

	// 各値の代入
	pCharacterPolygon->SetPos(pos);
	pCharacterPolygon->SetPriority(OBJTYPE_UI_2);
	pCharacterPolygon->m_mode = mode;

	return pCharacterPolygon;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCharacterPolygon::Init(void)
{
	// 初期化処理
	CScene2d::Init();
	// サイズの設定
	SetSize(DEFAULT_CHARACTER_POLYGON_SIZE);
	// 動的テクスチャの生成
	m_pDynamicTex = CDynamicTexture::Create(D3DXVECTOR2(DEFAULT_CHARACTER_POLYGON_SIZE.x, DEFAULT_CHARACTER_POLYGON_SIZE.y));
	// キャラクターモデルの生成*NONEだとモデル情報がないのでとりあえず騎士で生成
	m_pCharacterModel = CPlayerModel::Create(CHARACTER_POS, CHARACTER_ROT, CResourceCharacter::CHARACTER_KNIGHT);
	// リスト構造から外す
	m_pCharacterModel->OutList();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CCharacterPolygon::Uninit(void)
{
	// モデルの解放
	if (m_pCharacterModel != NULL)
	{
		m_pCharacterModel->Uninit();
		delete m_pCharacterModel;
		m_pCharacterModel = NULL;
	}
	// 動的テクスチャの解放
	if (m_pDynamicTex != NULL)
	{
		m_pDynamicTex->Uninit();
		delete m_pDynamicTex;
		m_pDynamicTex = NULL;
	}

	// 終了処理
	CScene2d::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CCharacterPolygon::Update(void)
{
	if (m_pCharacterModel == NULL) return;

	switch (m_mode)
	{
	case CCharacterPolygon::MODE_NONE:
		break;
	case CCharacterPolygon::MODE_ROTATION:
		// モデルの更新処理

		m_pCharacterModel->SetRot(m_pCharacterModel->GetRot() + CHARACTER_ADD_ROT);

		break;
	default:
		break;
	}

	m_pCharacterModel->Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CCharacterPolygon::Draw(void)
{
	// キャラクタータイプがNONEの時は描画しない
	if (m_charaType == CResourceCharacter::CHARACTER_NONE) return;

	
	if (m_pCharacterModel != NULL)
	{
		// テクスチャのモデルを書き込み
		m_pDynamicTex->Begin();
		m_pCharacterModel->Draw();
		// レンダリングターゲットを戻す
		m_pDynamicTex->End();
	}
	// テクスチャの割り当て
	BindTexture(m_pDynamicTex->GetTexture());

	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// サンプラーステートの設定
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_BORDER); // テクスチャU値の繰り返し設定
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_BORDER); // テクスチャV値の繰り返し設定

	// 描画処理
	CScene2d::Draw();

	// サンプラーステートの設定
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP); // テクスチャU値の繰り返し設定
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP); // テクスチャV値の繰り返し設定
}

//=============================================================================
// キャラタイプのセット
//=============================================================================
void CCharacterPolygon::SetCharaType(CResourceCharacter::CHARACTER_TYPE type)
{
	if (m_charaType == type) return;
	// タイプセット
	m_charaType = type;

	// モデルのタイプセット
	if (type != CResourceCharacter::CHARACTER_NONE)
	{
		m_pCharacterModel->SetCharacterType(m_charaType);
		m_pCharacterModel->SetRot(CHARACTER_ROT);
	}
}

//=============================================================================
// リムカラーのセット
//=============================================================================
void CCharacterPolygon::SetRimColor(D3DXCOLOR col)
{
	m_pCharacterModel->SetRimColor(col);
}

//=============================================================================
// Texカラーのセット
//=============================================================================
void CCharacterPolygon::SetTexColor(D3DXCOLOR col)
{
	m_pCharacterModel->SetTexColor(col);
}
