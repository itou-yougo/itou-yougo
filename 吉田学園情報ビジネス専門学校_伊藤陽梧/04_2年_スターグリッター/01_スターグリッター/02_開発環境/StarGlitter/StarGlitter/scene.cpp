//=============================================================================
//
// ポリゴンの描画の処理 [scene.cpp]
// Author : 伊藤陽梧
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include"main.h"
#include"scene.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CScene *CScene::m_apScene[MAX_DRAWORDER][MAX_POLYGON] = {};
int CScene::m_nNumAll = 0;
bool CScene::m_bPause = false;

//=============================================================================
// オブジェクトクラスのコンストラクタ
//=============================================================================
CScene::CScene(int nPriority)
{
	m_objType = OBJTYPE_NONE;
	for (int nCount = 0; nCount < MAX_POLYGON; nCount++)
	{
		if (m_apScene[nPriority][nCount] == NULL)
		{
			// CScene2Dでインスタンス生成したものをぶち込む
			m_apScene[nPriority][nCount] = this;
			m_nID = nCount;
			m_nPriority = nPriority;
			m_nNumAll++;
			break;
		}
	}
}

//=============================================================================
// オブジェクトクラスのデストラクタ
//=============================================================================
CScene::~CScene()
{

}

//=============================================================================
// オブジェクトクラスの更新処理
//=============================================================================
void CScene::UpdateAll(void)
{
	// ポーズ状態じゃないとき
	if (m_bPause == false)
	{
		for (int nPriority = 0; nPriority < MAX_DRAWORDER; nPriority++)
		{
			for (int nCount = 0; nCount < MAX_POLYGON; nCount++)
			{
				if (m_apScene[nPriority][nCount] != NULL)
				{
					// 更新処理
					m_apScene[nPriority][nCount]->Update();
				}
			}
		}

		for (int nCount = 0; nCount < MAX_POLYGON; nCount++)
		{
			if (m_apScene[OBJTYPE_GATTYANN][nCount] != NULL)
			{
				// 更新処理
				m_apScene[OBJTYPE_GATTYANN][nCount]->Update();
			}
		}
	}

	// ポーズ状態の時
	if (m_bPause == true)
	{
		for (int nPriority = 0; nPriority < MAX_DRAWORDER; nPriority++)
		{
			for (int nCount = 0; nCount < MAX_POLYGON; nCount++)
			{
				if (m_apScene[nPriority][nCount] != NULL && m_apScene[nPriority][nCount]->GetObjType() == OBJTYPE_TEXT)
				{
					// 更新処理
					m_apScene[nPriority][nCount]->Update();
				}
			}
		}
	}
}

//=============================================================================
// オブジェクトクラスの描画処理
//=============================================================================
void CScene::DrawAll(void)
{
	for (int nPriority = 0; nPriority < MAX_DRAWORDER; nPriority++)
	{
		for (int nCount = 0; nCount < MAX_POLYGON; nCount++)
		{
			if (m_apScene[nPriority][nCount] != NULL)
			{
				// 描画処理
				m_apScene[nPriority][nCount]->Draw();
			}
		}
	}
}

//=============================================================================
// オブジェクトクラスの終了処理
//=============================================================================
void CScene::ReleaseAll(void)
{
	for (int nPriority = 0; nPriority < MAX_DRAWORDER; nPriority++)
	{
		for (int nCount = 0; nCount < MAX_POLYGON; nCount++)
		{
			//pEnemyがNULLじゃないとき
			if (m_apScene[nPriority][nCount] != NULL)
			{
				//終了処理
				m_apScene[nPriority][nCount]->Uninit();
			}
		}
	}
}

//=============================================================================
// オブジェクトクラスのフェードを抜いた終了処理
//=============================================================================
void CScene::NotFadeReleaseAll(void)
{
	for (int nPriority = 0; nPriority < MAX_DRAWORDER; nPriority++)
	{
		for (int nCount = 0; nCount < MAX_POLYGON; nCount++)
		{
			//pEnemyがNULLじゃないとき
			if (m_apScene[nPriority][nCount] != NULL && m_apScene[nPriority][nCount]->m_objType != OBJTYPE_FADE)
			{
				//終了処理
				m_apScene[nPriority][nCount]->Uninit();
			}
		}
	}
}

//=============================================================================
// オブジェクトクラスのポーズを渡す処理
//=============================================================================
bool CScene::GetPause(void)
{
	return m_bPause;
}

//=============================================================================
// オブジェクトクラスのタイプを渡す処理
//=============================================================================
CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_objType;
}

//=============================================================================
// オブジェクトクラスのシーンを渡す処理
//=============================================================================
CScene * CScene::GetScene(int nPriority, int nCount)
{
	return m_apScene[nPriority][nCount];
}

//=============================================================================
// オブジェクトクラスのメモリの開放
//=============================================================================
void CScene::Release(void)
{
	//apEnemyがNULLじゃないとき
	if (m_apScene[m_nPriority][m_nID] != NULL)
	{
		int nID = m_nID;
		int nPriority = m_nPriority;

		//メモリの開放
		delete m_apScene[nPriority][nID];
		m_apScene[nPriority][nID] = NULL;
  		m_nNumAll--;
	}
}