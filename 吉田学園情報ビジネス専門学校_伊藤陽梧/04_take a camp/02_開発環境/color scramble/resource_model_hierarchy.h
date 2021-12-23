//=============================================================================
//
// resource_model_hierarchyヘッダ [resource_model_hierarchy.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _RESOURCEMODEL_HIERARCHY_H_
#define _RESOURCEMODEL_HIERARCHY_H_

//*****************************
//インクルード
//*****************************
#include "main.h"
#include "resource_model.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define MAX_PARTS_NUM 32 // パーツの最大数

//*****************************
//クラス定義
//*****************************

// 階層構造モデルリソースクラス
class CResourceModelHierarchy
{
public:

	//============
	//構造体
	//============
	// モデルデータ
	typedef struct
	{
		CResourceModel::Model aModelData[MAX_PARTS_NUM];
		int nPartsNum;
	}ModelHierarchy;

	// 列挙
	// モデル種類
	typedef enum
	{
		MODEL_HIERARCHY_KNIGHT = 0, // 騎士
		MODEL_HIERARCHY_LANCER,     // 槍兵
		MODEL_HIERARCHY_WIZARD,     // 魔法使い
		MODEL_HIERARCHY_THIEF,      // 盗賊
		MODEL_HIERARCHY_MAGICIAN,   // 奇術師
		MODEL_HIERARCHY_ARCHER,     // 弓使い
		MODEL_HIERARCHY_MAX        // 全体数
	}MODEL_HIERARCHY_TYPE;

	// メンバ関数
	static CResourceModelHierarchy * Create(void);                  // クラス生成
	static void Release(void);                               // クラス破棄
	static ModelHierarchy GetModel(MODEL_HIERARCHY_TYPE type); // モデルの取得処理*引数：取得したいモデル

private:
	CResourceModelHierarchy();//隠しコンストラクタ
public:
	~CResourceModelHierarchy();

private:
	void Load(void);     // モデル読み込み
	void LoadModels(const char * pPath, ModelHierarchy *data);    // テキストファイルの読み込み
	void LoadHierarchy(CResourceModel::Model *model, const char*pPath); // 階層構造の読み込み
	void Unload(void); // モデル破棄

					   // メンバ変数
	static const std::string m_aModelPath[MODEL_HIERARCHY_MAX]; // モデルのパス
	static CResourceModelHierarchy *m_pSingle;              // モデルクラスのポインタ*シングルトン用
	ModelHierarchy m_aModelHierarchy[MODEL_HIERARCHY_MAX];               // モデルのポインタ
};

#endif