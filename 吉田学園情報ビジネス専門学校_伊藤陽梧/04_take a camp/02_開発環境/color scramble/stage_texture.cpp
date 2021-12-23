//===================================================
//
//    ステージテクスチャクラスの処理[stage_tecture.cpp]
//    Author:増澤 未来
//
//====================================================

//**********************************
// インクルード
//**********************************
#include "stage_texture.h"
#include "scene.h"

//**********************************
// 静的メンバ変数宣言
//**********************************
const std::vector<int> CStageTexture::m_anDrawObjNum =
{
	CScene::OBJTYPE_BG,
	CScene::OBJTYPE_TILE,
	CScene::OBJTYPE_COLOR_TILE,
	CScene::OBJTYPE_MAP,

};
CStageTexture*CStageTexture::m_pInstance = NULL;
//**********************************
// コンストラクタ
//**********************************
CStageTexture::CStageTexture()
{
}

//**********************************
// デストラクタ
//**********************************
CStageTexture::~CStageTexture()
{
}

//**********************************
// クラス生成
//**********************************
CStageTexture * CStageTexture::Create(D3DXVECTOR2 size)
{
	if (m_pInstance == NULL)
	{
		m_pInstance = new CStageTexture;
		m_pInstance->Init(size);
	}
	return m_pInstance;
}

//**********************************
// 解放処理
//**********************************
void CStageTexture::Release(void)
{
	if (m_pInstance != NULL)
	{
		m_pInstance->Uninit();
		delete m_pInstance;
		m_pInstance = NULL;
	}
}

//**********************************
// テクスチャにステージの描画
//**********************************
void CStageTexture::DrawStageInTex(void)
{
	// テクスチャにオブジェクトを書き込む
	Begin();
	for (int nCntObj = 0; nCntObj < (int)m_anDrawObjNum.size(); nCntObj++)
	{
		CScene*pScene = CScene::GetTop(m_anDrawObjNum[nCntObj]);
		while (pScene != NULL)
		{
			// 描画
			pScene->Draw();

			// ネクスト
			pScene = pScene->GetNext();
		}
	}
	// レンダーターゲットを戻す
	End();
}

