////////////////////////////////////////////////////
//
//    tile_factoryクラスの処理[tile_factory.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "tile_factory.h"
#include "tile.h"
#include "color_tile.h"
#include "needle_tile.h"
#include "spawn_tile.h"
#include "move_around_tile.h"
#include "move_sideways_tile.h"
#include "warp_tile.h"
#include "dummy_tile.h"

//*****************************
// マクロ定義
//*****************************
#define TILE_DATA_TEXT ("data/Text/tile_data.csv")

//*****************************
// 静的メンバ変数宣言
//*****************************
std::vector<CTile::SENTENCE_FUNC> CTileFactory::m_CreateSentence = {};
CTileFactory* CTileFactory::m_pInstance = NULL;
const std::vector<CTileFactory::LabelData> CTileFactory::m_cLabelData = 
{
	{ "TILE_NONE"   , NULL},
	{ "TILE_"       , NULL },
	{ "TILE_NORMAL" , CColorTile::Create },
	{ "TILE_PLAYER" , CSpawnTile::Create },
	{ "TILE_NEEDLE" , CNeedleTile::Create },
	{ "TILE_AROUND_MOVE", CAroundTile::Create },
	{ "TILE_SIDEWAYS_MOVE",CSidewaysTile::Create },
	{ "TILE_WARP_1" , CWarpTile::Create_1 },
	{ "TILE_WARP_2" , CWarpTile::Create_2 },
	{ "TILE_DUMMY",CDummyTile::Create },
};

//******************************
// コンストラクタ
//******************************
CTileFactory::CTileFactory()
{
}

//******************************
// デストラクタ
//******************************
CTileFactory::~CTileFactory()
{
}

//******************************
// クラス生成
//******************************
CTileFactory* CTileFactory::Create(void)
{
	// メモリの確保
	if (m_pInstance == NULL)
	{
		m_pInstance = new CTileFactory;
		// 初期化
		m_pInstance->Init();
	}
	
	return m_pInstance;
}

//******************************
// 初期化処理
//******************************
HRESULT CTileFactory::Init(void)
{
	// データの読み込み
	LoadTileData();

	return S_OK;
}

//******************************
// 終了処理
//******************************
void CTileFactory::Uninit(void)
{
	m_CreateSentence.clear();
}

//******************************
// 解放処理
//******************************
void CTileFactory::Release(void)
{
	m_pInstance->Uninit();
	delete m_pInstance;
	m_pInstance = NULL;
}

//******************************
// タイルデータのロード処理
//******************************
void CTileFactory::LoadTileData(void)
{
	//ファイルポインタ
	FILE*	pFile = NULL;
	//読み込み用データ
	char cFileString[256];
	ZeroMemory(cFileString, sizeof(cFileString));

	//ファイル読み込み
	fopen_s(&pFile, TILE_DATA_TEXT, "r");

	if (pFile != NULL)
	{
		// データ数
		int nDataNum = 0;
		fscanf(pFile, "Tile_Data_Num,,%d", &nDataNum);

		m_CreateSentence.resize(nDataNum);

		for (int nCntData = 0; nCntData < nDataNum; nCntData++)
		{
			// 配列番号の読み込み
			int nIndex = 0;
			fscanf(pFile, "%d%s", &nIndex, cFileString);

			// 余計な文字を消す用のストリング型
			std::string str = cFileString;

			// "TILE_"の位置の検索
			int nTileDatNum = str.find("TILE_");
			
			// 不正な値が入らないようにする
			if (nTileDatNum < 0 || (int)str.length() < nTileDatNum)
			{
				continue;
			}

			// 余計な文字を消す
			sscanf(&str.c_str()[nTileDatNum], "%s", cFileString);

			for (int nCntLabelData = 0; nCntLabelData < (int)m_cLabelData.size(); nCntLabelData++)
			{
				// 読み込んだ文字列とラベルデータの比較
				if (strcmp(m_cLabelData.at(nCntLabelData).strLabelName.c_str(), cFileString) == 0)
				{
					// 一致してたら関数ポインタ配列に格納
					m_CreateSentence.at(nIndex) = m_cLabelData.at(nCntLabelData).createFunction;
				}
			}
		}
		
		// ファイルクローズ
		fclose(pFile);
	}
}
