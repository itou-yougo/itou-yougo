//=============================================================================
//
// stage_slectヘッダ [stage_slect.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _STAGE_SELECT_H_
#define _STAGE_SELECT_H_

//*****************************
// インクルード
//*****************************
#include "scene.h"
#include "resource_map.h"

//*****************************
// 前方宣言
//*****************************
class CStageNameUi;
class CStageSelectPolygon;
//*****************************
// マクロ定義
//*****************************
#define SELECT_STAGE_NUM (CMapManager::MAP_TYPE_MAX - 1)

//*****************************
//クラス定義
//*****************************

//ステージセレクトクラス
class CStageSelect : public CScene
{
public:
	//*****************************
	// メンバ関数
	//*****************************
	CStageSelect();
	~CStageSelect();

	static CStageSelect *Create(void); // クラス生成

	HRESULT Init(void); // 初期化
	void Uninit(void);  // 終了
	void Update(void);  // 更新
	void Draw(void);    // 描画

private:
	void SetObject(void);  // オブジェクトの設置
	void SelectStageType(void);// ステージタイプの選択処理

	// メンバ変数
	static CMapManager::MAP_TYPE m_selectStageType; // 選択しているステージのタイプ
	CStageNameUi* m_pStageName;                      // ステージ名クラス
	CStageSelectPolygon* m_pStagePolygon;
	int m_nWaitCnt;
};

#endif