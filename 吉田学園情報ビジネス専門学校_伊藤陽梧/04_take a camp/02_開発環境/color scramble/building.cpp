////////////////////////////////////////////////////
//
//    アイテムクラスの処理[item.cpp]
//    Author:西潟栞那汰
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "building.h"
#include "manager.h"
#include "keyboard.h"
#include "game.h"

//*****************************
// マクロ定義
//*****************************
#define MODEL_SIZE		(D3DXVECTOR3( 0.6f, 0.6f, 0.6f))
#define ITEM_ONE_SIDE	(10.0f)

//******************************
// コンストラクタ
//******************************
CBuilding::CBuilding() : CModel(OBJTYPE_ITEM)
{
	m_rot = D3DXVECTOR3(0.5f, 0.5f, 0.5f);//角度
	m_move = D3DXVECTOR3(0.5f, 0.5f, 0.5f);//移動
}

//******************************
// デストラクタ
//******************************
CBuilding::~CBuilding()
{
}

//******************************
// クラス生成
//******************************
CBuilding * CBuilding::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, BUILDING_TYPE type)
{
	//メモリの確保
	CBuilding *pBuilding;
	pBuilding = new CBuilding;

	//オブジェクトタイプセット
	pBuilding->SetBuildType(type);

	//初期化処理
	pBuilding->Init();

	//位置,角度セット
	pBuilding->SetPos(pos);
	pBuilding->SetRot(rot);
	return pBuilding;
}

//******************************
// 初期化処理
//******************************
HRESULT CBuilding::Init(void)
{
	//モデル初期化
	CModel::Init();

	// モデル割り当て
	switch (m_BuildingType)
	{
	case BUILDING_TYPE_TREE:
		BindModel(CResourceModel::GetModel(CResourceModel::MODEL_TREE));
		break;
	case BUILDING_TYPE_MATO:
		BindModel(CResourceModel::GetModel(CResourceModel::MODEL_MATO));
		break;
	case BUILDING_TYPE_BUKIKAKE:
		BindModel(CResourceModel::GetModel(CResourceModel::MODEL_BUKITATE));
		break;
	case BUILDING_TYPE_CHEST:
		BindModel(CResourceModel::GetModel(CResourceModel::MODEL_CHEST));
		break;
	case BUILDING_TYPE_TARU:
		BindModel(CResourceModel::GetModel(CResourceModel::MODLE_TARU));
		break;
	case BUILDING_TYPE_GAITOU:
		BindModel(CResourceModel::GetModel(CResourceModel::MODEL_GAITOU));
		break;
	case BUILDING_TYPE_HATA:
		BindModel(CResourceModel::GetModel(CResourceModel::MODEL_HATA));
		break;
	case BUILDING_TYPE_SAKU:
		BindModel(CResourceModel::GetModel(CResourceModel::MODEL_SAKU));
		break;
	case BUILDING_TYPE_ENOGU:
		BindModel(CResourceModel::GetModel(CResourceModel::MODEL_ENOGU));
		break;
	case BUILDING_TYPE_ENPITU:
		BindModel(CResourceModel::GetModel(CResourceModel::MODEL_ENPITU));
		break;
	case BUILDING_TYPE_MAGCUP:
		BindModel(CResourceModel::GetModel(CResourceModel::MODEL_MAGCUP));
		break;
	default:
		break;
	}

	// モデルのサイズの設定
	SetSize(MODEL_SIZE);

	return E_NOTIMPL;
}

//******************************
// 終了処理
//******************************
void CBuilding::Uninit(void)
{
	//モデルの終了処理
	CModel::Uninit();
}

//******************************
// 更新処理
//******************************
void CBuilding::Update(void)
{

}

//******************************
// 描画処理
//******************************
void CBuilding::Draw(void)
{
	//モデルの描画
	CModel::Draw();
}

//******************************
//背景オブジェクト読み込み処理
//******************************
void CBuilding::Load(void)
{
	FILE* pFile = NULL;
	D3DXVECTOR3 buildPos = {};
	D3DXVECTOR3 buildRot = {};
	BUILDING_TYPE type = BUILDING_TYPE_TREE;

	if (CGame::GetMapType() == CMapManager::MAP_TYPE_1)pFile = fopen("data/Text/stage/bgObj/BuildingInfo_1.txt", "r");
	else if (CGame::GetMapType() == CMapManager::MAP_TYPE_2)pFile = fopen("data/Text/stage/bgObj/BuildingInfo_2.txt", "r");
	else if (CGame::GetMapType() == CMapManager::MAP_TYPE_3)pFile = fopen("data/Text/stage/bgObj/BuildingInfo_3.txt", "r");

	if (pFile != NULL)
	{
		//タイプが取得できなくなるまでループ
		while (fscanf(pFile, "%d", &type) != EOF)
		{
			//座標取得
			fscanf(pFile, "%f %f %f", &buildPos.x, &buildPos.y, &buildPos.z);
			//角度取得
			fscanf(pFile, "%f %f %f", &buildRot.x, &buildRot.y, &buildRot.z);
			CBuilding::Create(buildPos, buildRot, type);
		}
	}
	fclose(pFile);
}