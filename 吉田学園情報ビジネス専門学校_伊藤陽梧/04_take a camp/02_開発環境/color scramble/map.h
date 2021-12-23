//=============================================================================
//
// マップクラス [map.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _MAP_1_H_
#define _MAP_1_H_

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "model.h"
#include "scene.h"
#include "resource_map.h"
//=============================================================================
// 前方宣言
//=============================================================================
class CItem;
//=============================================================================
// クラス定義
//=============================================================================
class CMap : public CScene
{
public:
	//関数定義
	CMap();
	~CMap();
	static CMap *Create(CMapManager::MAP_TYPE MapType);
	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);
	void	MapCreate(void);									// マップの生成

	void SetMapData(CMapManager::MAP_DATA MapData);
	CMapManager::MAP_DATA GetMapData(void);

private:
	void	ItemSpawn(void);		// アイテムの生成処理
	int		m_nItemSpawnCount;		// アイテムスポーンまでのカウント
	//CItem * m_pItem;				// アイテムのポインタ
	CMapManager::MAP_DATA m_MapData;
	CMapManager::MAP_TYPE m_MapType;
};
#endif