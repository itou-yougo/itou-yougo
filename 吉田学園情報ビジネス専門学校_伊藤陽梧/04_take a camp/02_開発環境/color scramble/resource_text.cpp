//====================================================
//
// resource_textの処理[resource_text.cpp]
// Author : 伊藤陽梧
//
//====================================================

//******************************
// インクルード
//******************************
#include "resource_text.h"
#include "renderer.h"
#include "manager.h"
#include <map>
#include "text.h"
#include <fstream>

//******************************
// マクロ定義
//******************************
#define TUTORIAL_FILENAME ("data/Text/tutorial.txt")

//******************************
// 静的メンバ変数宣言
//******************************
CResourceText *CResourceText::m_pSingle = nullptr; // テキストポインタ*シングルトン用

//===================================
// コンストラクタ
//===================================
CResourceText::CResourceText()
{
}

//===================================
// デストラクタ
//===================================
CResourceText::~CResourceText()
{
}

//=============================================================================
//モデルクラスのクリエイト処理
//=============================================================================
CResourceText * CResourceText::Create(void)
{
	if (m_pSingle == NULL)
	{
		// メモリ確保
		m_pSingle = new CResourceText;

		if (m_pSingle != NULL)
		{
			// メモリ確保に成功したとき
			m_pSingle->Load();
		}
		else
		{
			// メモリ確保に失敗したとき
			return NULL;
		}
	}

	return m_pSingle;
}

//===================================
// クラスの破棄
//===================================
void CResourceText::Release(void)
{
	if (m_pSingle != NULL)
	{
		// テクスチャ破棄
		m_pSingle->Unload();

		// メモリの破棄
		delete m_pSingle;
		m_pSingle = NULL;
	}
}

//===================================
// テクスチャ読み込み
//===================================
void CResourceText::Load(void)
{
	// ファイルポイント
	FILE *pFile = NULL;

	// 変数宣言
	int nTextNum = 0;		// タイプのナンバー

	// ファイル読み込み
	std::ifstream ifs(TUTORIAL_FILENAME);

	// 文字列保持用
	std::string str;

	if (ifs)
	{
		// SCRIPTの文字が見つかるまで
		while (str.find("SCRIPT") != 0)
		{
			getline(ifs, str);
		}
		// strがSCRIPTの時
		if (str.find("SCRIPT") == 0)
		{
			// strがEND_SCRIPTになるまで
			while (str.find("END_SCRIPT") != 0)
			{
				getline(ifs, str);

				// strがTEXT_DATASETの時
				if (str.find("TEXT_DATASET") == 0)
				{
					m_TextMap[nTextNum] = str;
					nTextNum++;

					// strがEND_TEXT_DATASETになるまで
					while (str.find("END_TEXT_DATASET") != 0)
					{
						getline(ifs, str);

						m_TextMap[nTextNum] = str;
						nTextNum++;
					}
				}
			}
		}
	}
}

//===================================
// 破棄
//===================================
void CResourceText::Unload(void)
{
	// マップのクリア
	m_TextMap.clear();
}