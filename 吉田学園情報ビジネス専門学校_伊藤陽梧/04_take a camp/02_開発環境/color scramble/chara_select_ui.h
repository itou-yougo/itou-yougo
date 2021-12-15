//=============================================================================
//
// chara_slect_uiヘッダ [chara_slect_ui.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _CHARA_SELECT_UI_H_
#define _CHARA_SELECT_UI_H_

//*****************************
//インクルード
//*****************************
#include "scene.h"
#include "game.h"

//=============================
// 前方宣言
//=============================
class CScene2d;
class CCharacterPolygon;

//*****************************
//マクロ定義
//*****************************

//*****************************
//クラス定義
//*****************************

//ゲームクラス
class CCharaSelectUi : public CScene
{
public:
	//*****************************
	// 列挙定義
	//*****************************

	//*****************************
	// 構造体定義
	//*****************************
	struct CharaSelect_UI
	{
		CScene2d * pBack;         // 背景
		CScene2d * pPlayerNumber; // プレイヤー番号
		CScene2d * pControllIcon; // コントローラータイプアイコン
		CCharacterPolygon * pCharaPolygon;
		D3DXVECTOR3 pos;          // 座標
	};
	//*****************************
	// メンバ関数
	//*****************************
	CCharaSelectUi();
	~CCharaSelectUi();

	static CCharaSelectUi *Create(void); // クラス生成

	HRESULT Init(void); // 初期化
	void Uninit(void);  // 終了
	void Update(void);  // 更新
	void Draw(void);    // 描画
private:

	//*****************************
	// メンバ変数
	//*****************************
	CharaSelect_UI m_aPolygon[MAX_PLAYER];

	int m_nCntAnim;       // アニメーションカウント
	int m_nAnimY;         // アニメーションY軸
};

#endif