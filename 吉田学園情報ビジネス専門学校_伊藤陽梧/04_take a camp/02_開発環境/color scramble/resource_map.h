//=============================================================================
//
// マップ読み込みクラス [resource_map.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _MAP_BASIS_H_
#define _MAP_BASIS_H_
//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "model.h"
#include "scene.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_STAGE_SIZE_X	(50)	//最大ブロック数
#define MAX_STAGE_SIZE_Y	(50)	//最大ステージサイズ
#define MAX_STAGE_COUNT		(1)		//最大ステージ数

//=============================================================================
// クラス定義
//=============================================================================
class CMapManager 
{
public:
	typedef struct //一行のブロック情報
	{
		int			nBlockType[MAX_STAGE_SIZE_X];	// ブロックデータ
		int			nStageSizeX;					// その行のブロック数
	}BLOCK_DATA;

	typedef struct	//ステージ情報
	{
		BLOCK_DATA	BlockData[MAX_STAGE_SIZE_Y];	// ブロック
		int			nStageSizeY;					// ブロックの列
		D3DXVECTOR3	m_pos;							// 位置		
	}MAP_DATA;

	typedef enum	//タイルの種類
	{
		BLOCK_TYPE_NONE = 0,	// なし
		BLOCK_TYPE_1P_START,	// 1Pスタート位置
		BLOCK_TYPE_2P_START,	// 2Pスタート位置
		BLOCK_TYPE_3P_START,	// 3Pスタート位置
		BLOCK_TYPE_4P_START,	// 4Pスタート位置
		BLOCK_TYPE_BLOCK,		// ノーマルブロック
		BLOCK_TYPE_NEEDLE_BLOCK,// とげブロック
		BLOCK_TYPE_AROUND_MOVE,	// 前後移動ブロック
		BLOCK_TYPE_SIDEWAYS_MOVE, // 横移動ブロック
		BLOCK_TYPE_WARP_1,		// ワープタイル1
		BLOCK_TYPE_WARP_2,		// ワープタイル2
		BLOCK_TYPE_DUMMY,		// ダミー
	}BLOCK_TYPE;

	typedef enum	//マップの種類
	{
		MAP_TYPE_NONE = -1,
		MAP_TYPE_1,	       // マップ1
		MAP_TYPE_2,        // マップ2
		MAP_TYPE_3,        // マップ3
		MAP_TYPE_TUTORIAL, // チュートリアルマップ*一番下にあると助かります by_Masuzawa
		MAP_TYPE_MAX
	}MAP_TYPE;

	//関数定義
	CMapManager();
	~CMapManager();
	static CMapManager *Create(void);					// クラス生成
	static void			Release(void);					// クラス破棄
	static MAP_DATA		GetMapData(MAP_TYPE MapData);

private:
	void	Load(void);

	static char*		m_pFileName[MAP_TYPE_MAX];	// ファイルネーム
	static CMapManager*	m_pMapBasis;				// マップクラスのポインタ
	MAP_DATA			m_MapData[MAP_TYPE_MAX];	// ステージの情報
};
#endif