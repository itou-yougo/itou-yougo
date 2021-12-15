//=============================================================================
//
// モデル処理 [ModelHirarchy.cpp]
// Author : 増澤未来
//
//=============================================================================
#include "model_hierarchy.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
//コンストラクタ
//=============================================================================
CModelHierarchy::CModelHierarchy(int nPriority) :CScene(nPriority)
{
	// 変数のクリア
	memset(&m_model, 0, sizeof(m_model));
	m_nNumParts = 0;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	for (int nCnt = 0; nCnt < MAX_PARTS_NUM; nCnt++)
	{
		m_model[nCnt].size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	}
}

//=============================================================================
//デストラクタ
//=============================================================================
CModelHierarchy::~CModelHierarchy()
{
}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CModelHierarchy::Init(void)
{

	return S_OK;
}

HRESULT CModelHierarchy::Init(CResourceModelHierarchy::MODEL_HIERARCHY_TYPE modelType)
{
	//LoadHierarchy(model, pPath);
	//// 引数の代入
	//m_nNumParts = nNumParts;
	CResourceModelHierarchy::ModelHierarchy modelData = CResourceModelHierarchy::GetModel (modelType);
	m_nNumParts = modelData.nPartsNum;

	for (int nCnt = 0; nCnt < m_nNumParts; nCnt++)
	{
		m_model[nCnt] = modelData.aModelData[nCnt];

		for (int nCntMat = 0; nCntMat < (int)m_model[nCnt].nNumMat; nCntMat++)
		{
			m_model[nCnt].defMat[nCntMat] = ((D3DXMATERIAL*)m_model[nCnt].pBuffMat->GetBufferPointer())[nCntMat];
		}
	}

	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void CModelHierarchy::Uninit(void)
{
	//オブジェクトの破棄
	Release();
}

//=============================================================================
//更新処理
//=============================================================================
void CModelHierarchy::Update(void)
{
}

//=============================================================================
//描画処理
//=============================================================================
void CModelHierarchy::Draw(void)
{
	// 座標、サイズ、回転の設定
	SetWorldmtx();
	// モデルの描画処理
	DrawModel();
}

//=============================================================================
//モデルデータのセット
//=============================================================================
void CModelHierarchy::SetModelData(CResourceModel::Model *pModel)
{
	for (int nCnt = 0; nCnt < m_nNumParts; nCnt++)
	{
		m_model[nCnt].pos = pModel[nCnt].pos;
		m_model[nCnt].rot = pModel[nCnt].rot;
	}
}

//=============================================================================
//ワールドマトリックスの設定
//=============================================================================
void CModelHierarchy::SetWorldmtx(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// 回転、位置、サイズ行列
	D3DXMATRIX mtxRot, mtxTrans, mtxScail;

	for (int nCntParts = 0; nCntParts < m_nNumParts; nCntParts++)
	{

		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&m_model[nCntParts].mtxWorld);

		if (m_model[nCntParts].nParent == -1)
		{// 自分が一番の親のとき
		
			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, m_model[nCntParts].rot.y, m_model[nCntParts].rot.x, m_model[nCntParts].rot.z);
			D3DXMatrixMultiply(&m_model[nCntParts].mtxWorld, &m_model[nCntParts].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxRot, m_model[nCntParts].pos.x, m_model[nCntParts].pos.y, m_model[nCntParts].pos.z);
			D3DXMatrixMultiply(&m_model[nCntParts].mtxWorld, &m_model[nCntParts].mtxWorld, &mtxRot);

			//スケールの反映（スケール座標の変換行列）
			D3DXMatrixScaling(&mtxScail, m_size.x, m_size.y, m_size.z);
			D3DXMatrixMultiply(&m_model[nCntParts].mtxWorld, &m_model[nCntParts].mtxWorld, &mtxScail);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
			D3DXMatrixMultiply(&m_model[nCntParts].mtxWorld, &m_model[nCntParts].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
			D3DXMatrixMultiply(&m_model[nCntParts].mtxWorld, &m_model[nCntParts].mtxWorld, &mtxTrans);

		}
		else
		{// 自分が一番の親じゃないとき

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, m_model[nCntParts].rot.y, m_model[nCntParts].rot.x, m_model[nCntParts].rot.z);
			D3DXMatrixMultiply(&m_model[nCntParts].mtxWorld, &m_model[nCntParts].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, m_model[nCntParts].pos.x, m_model[nCntParts].pos.y, m_model[nCntParts].pos.z);
			D3DXMatrixMultiply(&m_model[nCntParts].mtxWorld, &m_model[nCntParts].mtxWorld, &mtxTrans);

			// 親のワールドマトリックスを掛け合わせる
			D3DXMatrixMultiply(&m_model[nCntParts].mtxWorld, &m_model[nCntParts].mtxWorld, &m_model[m_model[nCntParts].nParent].mtxWorld);
		}
	}
}

//=============================================================================
//モデルの描画処理
//=============================================================================
void CModelHierarchy::DrawModel(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DMATERIAL9 matDef;	//現在のマテリアル保持用
	D3DXMATERIAL*pMat;	//マテリアルデータへのポインタ

	for (int nCntParts = 0; nCntParts < m_nNumParts; nCntParts++)
	{
		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &m_model[nCntParts].mtxWorld);

		//現在のマテリアルを取得する
		pDevice->GetMaterial(&matDef);

		//マテリアルデータへのポインタを取得

		pMat = (D3DXMATERIAL*)m_model[nCntParts].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_model[nCntParts].nNumMat; nCntMat++)
		{
			//マテリアルのアンビエントにディフューズカラーを設定
			pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
			// テクスチャ
			pDevice->SetTexture(0, m_model[nCntParts].apTexture[nCntMat]);
			//モデルパーツの描画
			m_model[nCntParts].pMesh->DrawSubset(nCntMat);

			pMat[nCntMat] = m_model[nCntParts].defMat[nCntMat];
		}

		//保持していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
		// テクスチャの初期化
		pDevice->SetTexture(0, 0);
	}
}
