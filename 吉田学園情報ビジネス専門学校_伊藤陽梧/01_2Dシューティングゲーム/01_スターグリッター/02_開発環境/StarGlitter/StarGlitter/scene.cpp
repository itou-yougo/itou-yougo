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
int CScene::m_nNumAll = 0;
int CScene::m_nNext = 0;
bool CScene::m_bPause = false;
CScene *CScene::m_pTop[OBJTYPE_MAX] = {}; // 先頭のオブジェクトへのポインタ
CScene *CScene::m_pCur[OBJTYPE_MAX] = {}; // 現在のオブジェクトへのポインタ

//=============================================================================
// オブジェクトクラスのコンストラクタ
//=============================================================================
CScene::CScene(int nPriority)
{
	m_objType = OBJTYPE_NONE;
	m_bDeath = true;

	// リストの先頭が存在しない場合
	if (m_pTop[nPriority] == NULL)
	{
		m_pTop[nPriority] = this;
	}
	// 現在のオブジェクト(m_pCur)が存在しない場合
	if (m_pCur[nPriority] == NULL)
	{
		m_pCur[nPriority] = this;
	}

	// 現在のオブジェクト(m_pCur)の次のオブジェクトを自分にする
	m_pCur[nPriority]->m_pNext = this;
	if (this == m_pCur[nPriority])
	{
		this->m_pPrev = NULL;
	}
	else
	{
		this->m_pPrev = m_pCur[nPriority];
	}

	// 現在のオブジェクト(m_pCur)を自分にする
	m_pCur[nPriority] = this;

	// 自分の次のオブジェクトをNULLにする
	this->m_pNext = NULL;

	m_nPriority = nPriority;
	m_nNumAll++;

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
	// ポーズの状態じゃないとき
	if (m_bPause == false)
	{
		// OBJTYPEの数分回す
		for (int nPriority = 0; nPriority < OBJTYPE_MAX; nPriority++)
		{
			// Topの情報の保持
			CScene *pScene = m_pTop[nPriority];
			while (pScene != NULL)
			{
				// Nextの情報の保持
				CScene *pSceneNext = pScene->m_pNext;

				// 死亡フラグが立ってないとき
				if (pScene->m_bDeath != false)
				{
					pScene->Update();
				}

				// Nextの情報をpSceneに入れる
				pScene = pSceneNext;
			}
		}

		for (int nPriority = 0; nPriority < OBJTYPE_MAX; nPriority++)
		{
			// Topの情報の保持
			CScene *pScene = m_pTop[nPriority];
			while (pScene != NULL)
			{
				// Nextの情報の保持
				CScene *pSceneNext = pScene->m_pNext;

				// 死亡フラグが立ってるとき
				if (pScene->m_bDeath == false)
				{
					// リストのつなぎなおしをして消す
					pScene->ConnectionList();
					delete pScene;
				}

				// Nextの情報をpSceneに入れる
				pScene = pSceneNext;
			}
		}
	}

	// ポーズの状態のとき
	if (m_bPause == true)
	{
		// OBJTYPEの数分回す
		for (int nPriority = 0; nPriority < OBJTYPE_MAX; nPriority++)
		{
			// Topの情報の保持
			CScene *pScene = m_pTop[nPriority];
			while (pScene != NULL && pScene->GetObjType() == OBJTYPE_TEXT)
			{
				// Nextの情報の保持
				CScene *pSceneNext = pScene->m_pNext;

				// 死亡フラグが立ってないとき
				if (pScene->m_bDeath != false)
				{
					pScene->Update();
				}

				// Nextの情報をpSceneに入れる
				pScene = pSceneNext;
			}
		}

		for (int nPriority = 0; nPriority < OBJTYPE_MAX; nPriority++)
		{
			// Topの情報の保持
			CScene *pScene = m_pTop[nPriority];
			while (pScene != NULL)
			{
				// Nextの情報の保持
				CScene *pSceneNext = pScene->m_pNext;

				// 死亡フラグが立ってるとき
				if (pScene->m_bDeath == false)
				{
					// リストのつなぎなおしをして消す
					pScene->ConnectionList();
					delete pScene;
				}

				// Nextの情報をpSceneに入れる
				pScene = pSceneNext;
			}
		}
	}
}

//=============================================================================
// オブジェクトクラスの描画処理
//=============================================================================
void CScene::DrawAll(void)
{
	// OBJTYPEの数分回す
	for (int nPriority = 0; nPriority < OBJTYPE_MAX; nPriority++)
	{
		// Topの情報の保持
		CScene *pScene = m_pTop[nPriority];
		while (pScene != NULL)
		{
			// Nextの情報の保持
			CScene *pSceneNext = pScene->m_pNext;

			// 死亡フラグが立ってないとき
			if (pScene->m_bDeath != false)
			{
				pScene->Draw();
			}

			// Nextの情報をpSceneに入れる
			pScene = pSceneNext;
		}
	}
}

//=============================================================================
// オブジェクトクラスの終了処理
//=============================================================================
void CScene::ReleaseAll(void)
{
	// OBJTYPEの数分回す
	for (int nPriority = 0; nPriority < OBJTYPE_MAX; nPriority++)
	{
		// Topの情報の保持
		CScene *pScene = m_pTop[nPriority];
		while (pScene != NULL)
		{
			// Nextの情報の保持
			CScene *pSceneNext = pScene->m_pNext;

			// 死亡フラグを立てる
			pScene->Release();

			// Nextの情報をpSceneに入れる
			pScene = pSceneNext;
		}
	}
}

//=============================================================================
// オブジェクトクラスのフェードを抜いた終了処理
//=============================================================================
void CScene::NotFadeReleaseAll(void)
{
	// OBJTYPEの数分回す
	for (int nPriority = 0; nPriority < OBJTYPE_MAX; nPriority++)
	{
		// Topの情報の保持
		CScene *pScene = m_pTop[nPriority];
		while (pScene != NULL && pScene->m_objType != OBJTYPE_FADE)
		{
			// Nextの情報の保持
			CScene *pSceneNext = pScene->m_pNext;

			// 死亡フラグを立てる
			pScene->Release();

			// Nextの情報をpSceneに入れる
			pScene = pSceneNext;
		}
	}
}

//=============================================================================
// オブジェクトクラスのリストのつなぎなおし
//=============================================================================
void CScene::ConnectionList(void)
{
	// 前の情報を持っているとき
	if (m_pPrev != NULL)
	{
		m_pPrev->m_pNext = m_pNext;
	}

	// 次の情報を持っているとき
	if (m_pNext != NULL)
	{
		m_pNext->m_pPrev = m_pPrev;
	}

	// 自分が先頭と現在のオブジェクトだったとき
	if (this == m_pTop[m_nPriority] && this == m_pCur[m_nPriority])
	{
		m_pTop[m_nPriority] = NULL;
		m_pCur[m_nPriority] = NULL;
	}

	// 自分が先頭のオブジェクトだったとき
	if (this == m_pTop[m_nPriority])
	{
		m_pTop[m_nPriority] = m_pNext;
	}

	// 自分が現在のオブジェクトだったとき
	if (this == m_pCur[m_nPriority])
	{
		m_pCur[m_nPriority] = m_pPrev;
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
// オブジェクトクラスのメモリの開放
//=============================================================================
void CScene::Release(void)
{
	// 死亡フラグを立てる
	m_bDeath = false;

	// オブジェクトの総数の減算
	m_nNumAll--;
}