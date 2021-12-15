//=============================================================================
//
// 背景オブジェクトの処理 [building.h]
// Author : 西潟栞那汰
//
//=============================================================================
#ifndef _BUILDING_H_
#define _BUILDING_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "model.h"

//=============================================================================
// 前方宣言
//=============================================================================

//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// クラス宣言
//=============================================================================
class CBuilding : public CModel
{
public:
	//建物タイプ
	typedef enum
	{
		BUILDING_TYPE_TREE = 0,//
		BUILDING_TYPE_MATO,		//
		BUILDING_TYPE_BUKIKAKE,
		BUILDING_TYPE_CHEST,
		BUILDING_TYPE_TARU,
		BUILDING_TYPE_GAITOU,
		BUILDING_TYPE_HATA,
		BUILDING_TYPE_SAKU,
		BUILDING_TYPE_ENOGU,
		BUILDING_TYPE_ENPITU,
		BUILDING_TYPE_MAGCUP,
		BUILDING_TYPE_MAX
	}BUILDING_TYPE;

	CBuilding();	// コンストラクタ
	~CBuilding();	// デストラクタ

	static CBuilding * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, BUILDING_TYPE type);	// 生成処理

	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	static void Load(void);

	void SetBuildType(BUILDING_TYPE BuildType) { m_BuildingType = BuildType; }
	BUILDING_TYPE GetBuildTypel(void) { return m_BuildingType; }

private:
	//=============================================================================
	// メンバ変数宣言
	//=============================================================================
	D3DXVECTOR3 m_size;		//大きさ
	D3DXVECTOR3 m_rot;		//角度
	D3DXVECTOR3 m_move;		//移動

	BUILDING_TYPE m_BuildingType;
};

#endif // !_ITEM_H_
