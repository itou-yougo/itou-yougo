////////////////////////////////////////////////////
//
//    resource_model_hierarchyクラスの処理[resource_model_hierarchy.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "resource_model_hierarchy.h"
#include "renderer.h"
#include "manager.h"

//******************************
// マクロ定義
//******************************

//******************************
// 静的メンバ変数宣言
//******************************
CResourceModelHierarchy *CResourceModelHierarchy::m_pSingle = NULL; //モデルクラスのポインタ*シングルトン用
// モデルのパス
const std::string CResourceModelHierarchy::m_aModelPath[CResourceModelHierarchy::MODEL_HIERARCHY_MAX]
{
	"data/Text/hierarchy/Knight.txt",
	"data/Text/hierarchy/Lancer.txt",
	"data/Text/hierarchy/wizard.txt",
	"data/Text/hierarchy/thief.txt",
	"data/Text/hierarchy/magician.txt",
	"data/Text/hierarchy/archer.txt",
};

//===================================
// コンストラクタ
//===================================
CResourceModelHierarchy::CResourceModelHierarchy()
{
	memset(&m_aModelHierarchy, 0, sizeof(m_aModelHierarchy));
}

//===================================
// デストラクタ
//===================================
CResourceModelHierarchy::~CResourceModelHierarchy()
{
}

//=============================================================================
//モデルクラスのクリエイト処理
//=============================================================================
CResourceModelHierarchy * CResourceModelHierarchy::Create(void)
{
	if (m_pSingle == NULL)
	{
		// メモリ確保
		m_pSingle = new CResourceModelHierarchy;

		if (m_pSingle != NULL)
		{
			// メモリ確保に成功したとき
			m_pSingle->Load();
		}
		else
		{
			// メモリ確保に失敗したとき
			return NULL;
		}
	}

	return m_pSingle;
}

//===================================
// クラスの破棄
//===================================
void CResourceModelHierarchy::Release(void)
{
	if (m_pSingle != NULL)
	{
		// テクスチャ破棄
		m_pSingle->Unload();
		// メモリの破棄
		delete m_pSingle;
		m_pSingle = NULL;
	}
}

//===================================
// モデル取得
//===================================
CResourceModelHierarchy::ModelHierarchy CResourceModelHierarchy::GetModel(CResourceModelHierarchy::MODEL_HIERARCHY_TYPE type)
{
	if (m_pSingle != NULL)
	{
		return m_pSingle->m_aModelHierarchy[type];
	}
	else
	{
		return ModelHierarchy();
	}
}

//===================================
// テクスチャ読み込み
//===================================
void CResourceModelHierarchy::Load(void)
{
	for (int nCntHierarchy = 0; nCntHierarchy < MODEL_HIERARCHY_MAX; nCntHierarchy++)
	{
		LoadModels(m_aModelPath[nCntHierarchy].c_str(), &m_aModelHierarchy[nCntHierarchy]);
		LoadHierarchy(m_aModelHierarchy[nCntHierarchy].aModelData, m_aModelPath[nCntHierarchy].c_str());
	}
}

//===================================
// テキストファイル読み込み
//===================================
void CResourceModelHierarchy::LoadModels(const char * pPath, ModelHierarchy *data)
{
	// ファイルオープン
	FILE*pFile = NULL;
	pFile = fopen(pPath, "r");

	if (pFile != NULL)
	{
		// テキストファイルの解析

		char chChar[256] = {};
		fscanf(pFile, "%s", chChar);

		// "NUM_MODEL"読み込むまでループ
		while (strcmp(chChar, "NUM_MODEL") != 0)
		{
			fscanf(pFile, "%s", chChar);
		}

		// 読み込むモデルの数
		fscanf(pFile, "%*s %d # %*s", &data->nPartsNum);

		// デバイスの取得
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		for (int nCnt = 0; nCnt < data->nPartsNum; nCnt++)
		{
			// 読み込んだ文字格納用
			char chPath[64] = {};
			// "MODEL_FILENAME"を読み込むまでループ
			while (strcmp(chChar, "MODEL_FILENAME") != 0)
			{
				fscanf(pFile, "%s", chChar);
			}
			// ファイルパスの読み込み
			fscanf(pFile, "%*s %s", chPath);

			// Xファイルの読み込み
			D3DXLoadMeshFromX(chPath,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&data->aModelData[nCnt].pBuffMat,
				NULL,
				&data->aModelData[nCnt].nNumMat,
				&data->aModelData[nCnt].pMesh);

			// テクスチャ読み込み
			if (data->aModelData[nCnt].nNumMat != 0)
			{
				D3DXMATERIAL*pMat = (D3DXMATERIAL*)data->aModelData[nCnt].pBuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)data->aModelData[nCnt].nNumMat; nCntMat++)
				{
					data->aModelData[nCnt].defMat[nCntMat] = pMat[nCntMat];
					if (pMat[nCntMat].pTextureFilename != NULL)
					{
						char cPath[128] = {};
						sprintf(cPath, "./data/Textures/%s", pMat[nCntMat].pTextureFilename);
						// テクスチャの生成
						D3DXCreateTextureFromFile(pDevice, cPath, &data->aModelData[nCnt].apTexture[nCntMat]);
					}
				}
			}

			// 次の文字を読み込む
			fscanf(pFile, "%s", chChar);
		}

		fclose(pFile);
	}
}

//===================================
// 階層構造の読み込み
//===================================
void CResourceModelHierarchy::LoadHierarchy(CResourceModel::Model * model, const char * pPath)
{
	// ファイルオープン
	FILE*pFile = NULL;
	pFile = fopen(pPath, "r");

	// パーツ数
	int nPartsNum = 0;

	if (pFile != NULL)
	{
		// テキストファイルの解析

		char chChar[256] = {};
		fscanf(pFile, "%s", chChar);

		// "SCRIPT"読み込むまでループ
		while (strcmp(chChar, "CHARACTERSET") != 0)
		{
			fscanf(pFile, "%s", chChar);
		}

		// 文字排除用
		char cString[32] = {};

		fscanf(pFile, "%s %s %d", &cString, &cString, &nPartsNum);

		// "END_PARTSSET"読み込むまでループ
		while (strcmp(chChar, "END_CHARACTERSET") != 0)
		{
			fscanf(pFile, "%s", chChar);
			if (strcmp(chChar, "PARTSSET") == 0)
			{
				// インデックス一時保管用
				int nIndex = 0;
				// インデックスの読み込み
				fscanf(pFile, "%*s %*s %d # %*s", &nIndex);
				// 親番号の読み込み
				fscanf(pFile, "%*s %*s %d # %*s", &model[nIndex].nParent);
				// 座標の読み込み
				fscanf(pFile, "%*s %*s %f %f %f", &model[nIndex].pos.x, &model[nIndex].pos.y, &model[nIndex].pos.z);
				// 回転の読み込み
				fscanf(pFile, "%*s %*s %f %f %f", &model[nIndex].rot.x, &model[nIndex].rot.y, &model[nIndex].rot.z);

				fscanf(pFile, "%*s");
			}

		}
		fclose(pFile);
	}
}

//===================================
// 破棄
//===================================
void CResourceModelHierarchy::Unload(void)
{
	for (int nCnt = 0; nCnt < MODEL_HIERARCHY_MAX; nCnt++)
	{
		for (int nCntParts = 0; nCntParts < m_aModelHierarchy[nCnt].nPartsNum; nCntParts++)
		{
			// メッシュの解放
			if (m_aModelHierarchy[nCnt].aModelData[nCntParts].pMesh != NULL)
			{
				m_aModelHierarchy[nCnt].aModelData[nCntParts].pMesh->Release();
				m_aModelHierarchy[nCnt].aModelData[nCntParts].pMesh = NULL;
			}
			// バッファの解放
			if (m_aModelHierarchy[nCnt].aModelData[nCntParts].pBuffMat != NULL)
			{
				m_aModelHierarchy[nCnt].aModelData[nCntParts].pBuffMat->Release();
				m_aModelHierarchy[nCnt].aModelData[nCntParts].pBuffMat = NULL;
			}

			// マテリアル数分ループ
			for (int nCntTex = 0; nCntTex < (int)m_aModelHierarchy[nCnt].aModelData[nCnt].nNumMat; nCntTex++)
			{
				// テクスチャの解放
				if (m_aModelHierarchy[nCnt].aModelData[nCntParts].apTexture[nCntTex] != NULL)
				{
					m_aModelHierarchy[nCnt].aModelData[nCntParts].apTexture[nCntTex]->Release();
					m_aModelHierarchy[nCnt].aModelData[nCntParts].apTexture[nCntTex] = NULL;
				}
			}
		}
	}
}
