////////////////////////////////////////////////////
//
//    キルカウント[kill_count.cpp]
//    Author : 吉田 悠人
//
////////////////////////////////////////////////////

//=============================
// インクルード
//=============================
#include "kill_count.h"
#include "number.h"
#include "player.h"

//*****************************
// 静的メンバ変数宣言
//*****************************
int CKillCount::m_nTotalKill[MAX_PLAYER] = {};

//=============================
// コンストラクタ
//=============================
CKillCount::CKillCount()
{
	memset(&pNumber,0,sizeof(pNumber));
	memset(&m_nKillCount, 0, sizeof(m_nKillCount));
	m_nKillCount = 0;

}

//=============================
// デストラクタ
//=============================
CKillCount::~CKillCount()
{
}

//=============================
// クリエイト
//=============================
CKillCount * CKillCount::Create(int nPlayer)
{
	// メモリの確保
	CKillCount *pKillCount = NULL;
	pKillCount = new CKillCount;
	
	//NULLチェック
	if (pKillCount != NULL)
	{
		//プレイヤー番号取得
		pKillCount->SetPlayer(nPlayer);
		// 初期化
		pKillCount->Init();
	}
	return pKillCount;
}

//=============================
// 初期化処理
//=============================
HRESULT CKillCount::Init(void)
{
	m_nKillCount = 0;

	return S_OK;
}

//=============================
// 終了処理
//=============================
void CKillCount::Uninit(void)
{
	// 開放処理
	Release();
}

//=============================
// 更新処理
//=============================
void CKillCount::Update(void)
{

}

//=============================
// 描画処理
//=============================
void CKillCount::Draw(void)
{

}

//=============================
// キル数加算処理
//=============================
void CKillCount::AddKill(void)
{
	m_nKillCount++;
}

//=============================
// キル数加算処理
//=============================
void CKillCount::AddTotalKill(void)
{
	//数値の初期化
	ZeroMemory(&m_nTotalKill,sizeof(m_nTotalKill));
	
	//リスト取得
	CPlayer* pPlayer = (CPlayer*)GetTop(OBJTYPE_PLAYER);

	//NULLチェック
	while (pPlayer != NULL)
	{
		//カウントのポインタ取得
		CKillCount *pKillCount = pPlayer->GetKillCount();
		
		if (pKillCount != NULL)
		{
			m_nTotalKill[pKillCount->GetPlayer()] = pKillCount->GetKill();
		}
		// リストを進める
		pPlayer = (CPlayer*)pPlayer->GetNext();
	}
}
