//=============================================================================
//
// Player_Modelヘッダ [Player_Model.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _PLAYER_MODEL_H_
#define _PLAYER_MODEL_H_

//*****************************
// インクルード
//*****************************
#include "main.h"
#include "model_hierarchy.h"
#include "resource_character.h"

//*****************************
// 前方宣言
//*****************************
class CMotion;

//*****************************
// マクロ定義
//****************************
#define RIM_POWER	(1.5f)			// リムライトの強さ

//*****************************
// クラス定義
//*****************************

// プレイヤークラス
class CPlayerModel : public CModelHierarchy
{
public:

	//メンバ関数
	CPlayerModel();
	~CPlayerModel();
	static CPlayerModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CResourceCharacter::CHARACTER_TYPE charaType);

	HRESULT Init(void);
	void Update(void);

	D3DXCOLOR GetRimColor(void) { return m_RimColor; }
	void SetRimColor(D3DXCOLOR col) { m_RimColor = col; }
	D3DXCOLOR GetTexColor(void) { return m_TexColor; }
	void SetTexColor(D3DXCOLOR col) { m_TexColor = col; }
	CResourceCharacter::CHARACTER_TYPE GetCharacterType(void) { return m_charaType; }
	void SetCharacterType(CResourceCharacter::CHARACTER_TYPE type);

	CMotion*GetMotion(int nIndex) { return m_apMotion[nIndex]; }
private:
	void ManageMotion(void);// モーション管理
	void DrawModel(void);	                                                          // モデルの描画処理
	void SetShaderVariable(LPD3DXEFFECT pEffect, CResourceModel::Model * pModelData); // シェーダに値を送る

	// モーション用変数
	CResourceCharacter::CHARACTER_TYPE m_charaType;
	CMotion *m_apMotion[CResourceCharacter::MOTION_MAX];  // アニメーションポインタ
	D3DXCOLOR m_RimColor; // リムから―
	D3DXCOLOR m_TexColor; // テクスチャカラー
};

#endif