////////////////////////////////////////////////////
//
//    ステージ選択ポリゴンクラスの処理[stage_select_polygon.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//=============================
// インクルード
//=============================
#include "stage_select_polygon.h"
#include "scene2d.h"
#include "stage_texture.h"
#include "resource_texture.h"
#include "resource_shader.h"
#include "manager.h"
#include "light.h"

//=============================
// マクロ定義
//=============================
#define POS  (D3DXVECTOR3( SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f, 0.0f))  // Y座標
#define SIZE_0  (D3DXVECTOR3( SCREEN_WIDTH*1.3f,SCREEN_HEIGHT*1.3f, 0.0f)) // サイズ
#define SIZE_1 SIZE_2*1.2f
#define SIZE_2 (D3DXVECTOR3( SCREEN_WIDTH*0.6f,SCREEN_HEIGHT*0.6f, 0.0f)) // サイズ
#define MAP_WIDTH  600
#define MAP_HEIGHT 600
#define BLUR_WEIGHT 5.0f

//=============================
// コンストラクタ
//=============================
CStageSelectPolygon::CStageSelectPolygon()
{
	// 変数のクリア
	ZeroMemory(&m_apPolygon, sizeof(m_apPolygon));
	ZeroMemory(&m_afWeight, sizeof(m_afWeight));
	m_weightHandle = NULL;
}

//=============================
// デストラクタ
//=============================
CStageSelectPolygon::~CStageSelectPolygon()
{
}

//=============================
// クリエイト
//=============================
CStageSelectPolygon * CStageSelectPolygon::Create(void)
{
	// メモリの確保
	CStageSelectPolygon *pPointa = new CStageSelectPolygon;
	// 初期化
	pPointa->Init();

	return pPointa;
}

//=============================
// 初期化処理
//=============================
HRESULT CStageSelectPolygon::Init(void)
{

	for (int nCntUi = 0; nCntUi < STAGE_SELECT_POLYGON_NUM; nCntUi++)
	{
		// ポリゴン生成
		m_apPolygon[nCntUi] = CScene2d::Create();
		m_apPolygon[nCntUi]->SetPos(POS);
		
		m_apPolygon[nCntUi]->OutList();
	}

	// サイズの設定
	m_apPolygon[0]->SetSize(SIZE_0);
	m_apPolygon[1]->SetSize(SIZE_1);
	m_apPolygon[2]->SetSize(SIZE_2);

	// 背景テクスチャ
	m_apPolygon[1]->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_STAGE_SELECT_BG));
	SetPriority(OBJTYPE_UI_1);

	// ライトの向きの設定
	CManager::GetLight()->SetDir(LIGHT_DIR_BASE);

	return S_OK;
}

//=============================
// 終了処理
//=============================
void CStageSelectPolygon::Uninit(void)
{
	for (int nCntUi = 0; nCntUi < STAGE_SELECT_POLYGON_NUM; nCntUi++)
	{
		if (m_apPolygon[nCntUi] != NULL)
		{
			m_apPolygon[nCntUi]->Uninit();
			delete m_apPolygon[nCntUi];
			m_apPolygon[nCntUi] = NULL;
		}
	}

	// 開放処理
	Release();
}

//=============================
// 更新処理
//=============================
void CStageSelectPolygon::Update(void)
{
}

//=============================
// 描画処理
//=============================
void CStageSelectPolygon::Draw(void)
{
	CStageTexture::GetStateTexturePointa()->DrawStageInTex();

	for (int nCntUi = 0; nCntUi < STAGE_SELECT_POLYGON_NUM; nCntUi++)
	{
		if (m_apPolygon[nCntUi] != NULL)
		{
			if (nCntUi != 1)m_apPolygon[nCntUi]->BindTexture(CStageTexture::GetStateTexturePointa()->GetTexture());

			// ブラー描画
			if (nCntUi == 0) DrawBlur();
			// 通常描画
			else             m_apPolygon[nCntUi]->Draw();
		}
	}
}

//=============================
// 描画処理*ブラー
//=============================
void CStageSelectPolygon::DrawBlur(void)
{
	// シェーダー情報の取得
	CResourceShader::Shader shader = CResourceShader::GetShader(CResourceShader::SHADER_BLUR);

	if (shader.pEffect != NULL)
	{
		if (m_weightHandle == NULL)
		{
			m_weightHandle = shader.pEffect->GetParameterByName(NULL, "weight");
			UpdateWeight(BLUR_WEIGHT);
		}

		// パス数の取得
		UINT numPass = 0;
		shader.pEffect->Begin(&numPass, 0);

		shader.pEffect->SetFloat("MAP_WIDTH", MAP_WIDTH);
		shader.pEffect->SetFloat("MAP_HEIGHT", MAP_HEIGHT);
		// パス数分描画処理のループ
		for (int nCntPass = 0; nCntPass < (int)numPass; nCntPass++)
		{
			// シェーダパスの描画開始
			shader.pEffect->BeginPass(nCntPass);

			m_apPolygon[0]->Draw();

			shader.pEffect->EndPass();
		}
		shader.pEffect->End();
	}
}

void CStageSelectPolygon::UpdateWeight(float fDispersion)
{
	float fTotal = 0;
	for (int nCntWeight = 0; nCntWeight<WEIGHT_MUN; nCntWeight++)
	{
		m_afWeight[nCntWeight] = expf(-0.5f*(FLOAT)(nCntWeight*nCntWeight) / fDispersion);
		if (0 == nCntWeight)
		{
			fTotal += m_afWeight[nCntWeight];
		}
		else
		{
			// 中心以外は、２回同じ係数を使うので２倍
			fTotal += 2.0f*m_afWeight[nCntWeight];
		}
	}
	// 規格化
	for (int nCntWeight = 0; nCntWeight < WEIGHT_MUN; nCntWeight++)
	{
		m_afWeight[nCntWeight] /= fTotal;
	}

	CResourceShader::Shader shader = CResourceShader::GetShader(CResourceShader::SHADER_BLUR);

	if (shader.pEffect)
	{
		shader.pEffect->SetFloatArray(m_weightHandle, m_afWeight, WEIGHT_MUN);
	}
}
