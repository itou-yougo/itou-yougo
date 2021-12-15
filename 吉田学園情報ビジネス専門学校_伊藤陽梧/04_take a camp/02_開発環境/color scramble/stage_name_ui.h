//=============================================================================
//
// stage_name_uiヘッダ [stage_name_ui.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _STAGE_NAME_UI_H_
#define _STAGE_NAME_UI_H_

//*****************************
// インクルード
//*****************************
#include "scene.h"
#include "resource_map.h"
#include "stage_select.h"

//*****************************
// 前方宣言
//*****************************
class CScene2d;

//=============================
// マクロ定義
//=============================

//*****************************
//クラス定義
//*****************************

//ゲージクラス
class CStageNameUi : public CScene
{
public:

	//============
	// メンバ関数
	//============
	CStageNameUi();
	~CStageNameUi();

	// static
	static CStageNameUi *Create(int nSelectNum = 0); // クラス生成

	HRESULT Init(void); // 初期化
	void Uninit(void);  // 終了
	void Update(void);  // 更新
	void Draw(void);    // 描画

	void SetSelectNum(int nNum) { m_nSelectNum = nNum; } // セレクト番号のセット
private:
	// メンバ変数
	CScene2d * m_apNamePolygon[SELECT_STAGE_NUM]; // 名前ポリゴン
	int m_nSelectNum; // 選んでいるステージナンバー
};

#endif