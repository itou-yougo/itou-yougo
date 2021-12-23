////////////////////////////////////////////////////
//
//    playerクラスの処理[player.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "player_model.h"
#include "motion.h"
#include "chara_select.h"
#include "manager.h"
#include "renderer.h"
#include "resource_shader.h"
#include "resource_texture.h"
#include "color_manager.h"
#include "camera_base.h"
#include "light.h"

//******************************
// コンストラクタ
//******************************
CPlayerModel::CPlayerModel() :CModelHierarchy(OBJTYPE_BG)
{
	m_charaType = CResourceCharacter::CHARACTER_NONE;
	memset(&m_apMotion, 0, sizeof(m_apMotion));	// アニメーションポインタ
	m_RimColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_TexColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

//******************************
// デストラクタ
//******************************
CPlayerModel::~CPlayerModel()
{
}

//******************************
// クラス生成
//******************************
CPlayerModel * CPlayerModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CResourceCharacter::CHARACTER_TYPE charaType)
{
	// メモリの確保
	CPlayerModel *pPlayerModel;
	pPlayerModel = new CPlayerModel;

	// 初期化
	pPlayerModel->Init();
	// initで使うから先に代入
	pPlayerModel->SetCharacterType(charaType);

	// 各値の代入・セット
	pPlayerModel->SetPos(pos);
	pPlayerModel->SetRot(rot);
	pPlayerModel->SetPriority(OBJTYPE_BG); // オブジェクトタイプ

	return pPlayerModel;
}

//******************************
// 初期化処理
//******************************
HRESULT CPlayerModel::Init(void)
{
	// キャラデータの取得
	SetCharacterType(m_charaType);

	return S_OK;
}

//******************************
// 更新処理
//******************************
void CPlayerModel::Update(void)
{
	ManageMotion();
}

//******************************
// キャラタイプのセット
//******************************
void CPlayerModel::SetCharacterType(CResourceCharacter::CHARACTER_TYPE type)
{
	// キャラタイプの取得
	if (m_charaType == type)
	{
		return;
	}
	// タイプの切り替え
	m_charaType = type;
	// キャラデータの取得
	CResourceCharacter::CharacterData charaData = CResourceCharacter::GetResourceCharacter()->GetCharacterData(m_charaType);
	// モデルの初期化
	CModelHierarchy::Init(charaData.modelType);

	for (int nCntAnim = 0; nCntAnim < CResourceCharacter::MOTION_MAX; nCntAnim++)
	{
		if (m_apMotion[nCntAnim] != NULL)
		{// 既存のモーションの削除
			m_apMotion[nCntAnim]->OutList();
			m_apMotion[nCntAnim]->Uninit();
			delete m_apMotion[nCntAnim];
			m_apMotion[nCntAnim] = NULL;
		}
		// 新しいモーションの生成
		m_apMotion[nCntAnim] = CMotion::Create(GetPartsNum(), charaData.aMotionTextPath[nCntAnim].c_str(), GetModelData());
	}
	// アイドルモーションの再生
	m_apMotion[CResourceCharacter::MOTION_IDLE]->SetActiveMotion(true);
}

//******************************
// モーション管理
//******************************
void CPlayerModel::ManageMotion(void)
{
	for (int nCntMotion = 0; nCntMotion < CResourceCharacter::MOTION_MAX; nCntMotion++)
	{
		if (m_apMotion[CResourceCharacter::MOTION_IDLE]->GetActiveMotion())
		{
			if (nCntMotion == CResourceCharacter::MOTION_IDLE)
			{
				continue;
			}

			if (m_apMotion[nCntMotion]->GetActiveMotion())
			{
				m_apMotion[CResourceCharacter::MOTION_IDLE]->SetActiveMotion(false);
			}
		}
		else
		{
			if (nCntMotion == CResourceCharacter::MOTION_IDLE)
			{
				continue;
			}
			if (m_apMotion[nCntMotion]->GetActiveMotion())
			{
				break;
			}
			m_apMotion[CResourceCharacter::MOTION_IDLE]->SetActiveMotion(true);
		}
	}
}

//******************************
// モデル描画処理
//******************************
void CPlayerModel::DrawModel(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DMATERIAL9 matDef;	//現在のマテリアル保持用
	D3DXMATERIAL*pMat;	//マテリアルデータへのポインタ

	CResourceModel::Model *pModelData = GetModelData();

	for (int nCntParts = 0; nCntParts < GetPartsNum(); nCntParts++)
	{
		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &pModelData[nCntParts].mtxWorld);

		//現在のマテリアルを取得する
		pDevice->GetMaterial(&matDef);

		// シェーダー情報の取得
		CResourceShader::Shader shader = CResourceShader::GetShader(CResourceShader::SHADER_PLAYER);

		if (shader.pEffect != NULL)
		{
			// シェーダープログラムに値を送る
			SetShaderVariable(shader.pEffect, &pModelData[nCntParts]);

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)pModelData[nCntParts].pBuffMat->GetBufferPointer();

			// パス数の取得
			UINT numPass = 0;
			shader.pEffect->Begin(&numPass, 0);

			// パス数分描画処理のループ
			for (int nCntMat = 0; nCntMat < (int)pModelData[nCntParts].nNumMat; nCntMat++)
			{
				//マテリアルのアンビエントにディフューズカラーを設定
				pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				// テクスチャ
				pDevice->SetTexture(0, pModelData[nCntParts].apTexture[nCntMat]);
				// テクスチャをシェーダーに送る
				shader.pEffect->SetTexture("Tex", pModelData[nCntParts].apTexture[nCntMat]);
				// 色
				shader.pEffect->SetFloatArray("DiffuseColor", (float*)&pMat[nCntMat].MatD3D.Diffuse, 4);

				if (pModelData[nCntParts].apTexture[nCntMat] == NULL)
				{
					// シェーダパスの描画開始
					shader.pEffect->BeginPass(0);
				}
				else
				{
					// シェーダパスの描画開始
					shader.pEffect->BeginPass(1);
				}

				// モデルパーツの描画
				pModelData[nCntParts].pMesh->DrawSubset(nCntMat);
				// シェーダパスの終了
				shader.pEffect->EndPass();

				pMat[nCntMat] = pModelData[nCntParts].defMat[nCntMat];

			}
			// シェーダー終了
			shader.pEffect->End();
		}

		//保持していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
		// テクスチャの初期化
		pDevice->SetTexture(0, 0);
	}
}


//=============================
// シェーダーに値を送る
//=============================
void CPlayerModel::SetShaderVariable(LPD3DXEFFECT pEffect, CResourceModel::Model * pModelData)
{
	if (pEffect != NULL)
	{
		// シェーダーに情報を渡す
		D3DXMATRIX mat;
		D3DXMatrixIdentity(&mat);
		mat = pModelData->mtxWorld * (*CManager::GetCamera()->GetViewMtx())* (*CManager::GetCamera()->GetProjectionMtx());
		// ワールドプロジェクション
		pEffect->SetMatrix("WorldViewProj", &mat);
		// ワールド座標
		pEffect->SetMatrix("World", &pModelData->mtxWorld);
		// ライトディレクション
		D3DXVECTOR3 lightDir = CManager::GetLight()->GetDir();
		pEffect->SetFloatArray("LightDirection", (float*)&D3DXVECTOR3(lightDir.x, -lightDir.y, -lightDir.z), 3);
		// 視点位
		D3DXVECTOR3 eye = CManager::GetCamera()->GetPosV();
		pEffect->SetFloatArray("Eye", (float*)&D3DXVECTOR3(eye.x, eye.y, eye.z), 3);
		// スペキュラの情報を送る
		pEffect->SetFloatArray("SpecularColor", (float*)&D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 4);
		// リムカラーの情報を送る
		pEffect->SetFloatArray("RimColor", (float*)&m_RimColor, 4);
		pEffect->SetFloat("RimPower", RIM_POWER);
		// テクスチャカラーの情報を送る
		pEffect->SetFloatArray("TexColor", (float*)&m_TexColor, 4);
		// キューブテクスチャ
		pEffect->SetTexture("CubeTex", CResourceTexture::GetCubeTexture(CResourceTexture::TEXTURE_CUBE_SLY));
		// トゥーンシャドウテクスチャをシェーダーに送る
		pEffect->SetTexture("ToonTex", CResourceTexture::GetTexture(CResourceTexture::TEXTURE_TOON_SHADOW));
	}
}
