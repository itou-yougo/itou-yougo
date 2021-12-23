//=============================================================================
//
// gameヘッダ [game.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _GAME_H_
#define _GAME_H_

//*****************************
//インクルード
//*****************************
#include "main.h"
#include "scene.h"
#include "map.h"

//=============================
// 前方宣言
//=============================
class CCamera;
class CRuleManager;
class CMapManager;
class CGameStart;
//*****************************
//マクロ定義
//*****************************

//*****************************
//クラス定義
//*****************************

//ゲームクラス
class CGame : public CScene
{
public:
	//*****************************
	// 列挙定義
	//*****************************

	//*****************************
	// メンバ関数
	//*****************************
	CGame();
	~CGame();

	static CGame *Create(void); // クラス生成

	HRESULT Init(void); // 初期化
	void Uninit(void);  // 終了
	void Update(void);  // 更新
	void Draw(void);    // 描画

	// 取得処理
	static CRuleManager *GetRuleManager(void) { return m_pRuleManager; } // ルールマネージャーポインタ
	static CMap* GetStage(void) { return m_pMap; }
	static CMapManager::MAP_TYPE GetMapType(void) { return m_MapType; }
	static void SetMapType(CMapManager::MAP_TYPE MapType) { m_MapType = MapType; }

private:

	//*****************************
	// メンバ変数
	//*****************************
	static CRuleManager* m_pRuleManager; // ルールマネージャー
	static CMap *m_pMap;			 // ステージポインタ
	static CMapManager::MAP_TYPE m_MapType;// マップのタイプ
	CGameStart * m_pGameStart;
};	

#endif