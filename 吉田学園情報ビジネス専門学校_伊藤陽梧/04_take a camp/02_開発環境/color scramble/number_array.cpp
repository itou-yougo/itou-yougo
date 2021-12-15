//===================================================
//
// ナンバークラスの処理[number_array.cpp]
// Author:伊藤陽梧
//
//====================================================

//**********************************
// インクルード
//**********************************
#include "number_array.h"
#include "manager.h"
#include "number.h"
#include "billboard.h"
#include "keyboard.h"
#include "resource_texture.h"
#include "renderer.h"
#include "player.h" 
#include "color_tile.h"

//==================================
// マクロ定義
//==================================
#define MAX_TEXTURE_PATTARN (10)
#define KERNING_DIVISION (3.6f)								// 間隔を割る数(間隔をいじるときは個々の数値を変えて)
#define ODD_NUMBER_DIVISION (2.0f * KERNING_DIVISION)		// 奇数を割る数
#define EVEN_NUMBER_DIVISION (20.0f * KERNING_DIVISION)	    // 偶数を割る数
#define NUMBER_POS_Y 35.0f
//==================================
// コンストラクタ
//==================================
CNumberArray::CNumberArray():CScene(OBJTYPE_UI_2)
{
	memset(&m_apNumber, NULL, sizeof(m_apNumber));
	m_nNumber = 0;
	memset(&m_pos, 0, sizeof(m_pos));
	memset(&m_size, 0, sizeof(m_size));
	memset(&m_col, 0, sizeof(m_col));
	m_bZeroCheck = false;
}

//==================================
// デストラクタ
//==================================
CNumberArray::~CNumberArray()
{
}

//==================================
// クリエイト
//==================================
CNumberArray * CNumberArray::Create(const int nNum, const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXCOLOR col, const int nColorNum)
{
	// メモリの確保
	CNumberArray * pNumberArray = new CNumberArray;

	pNumberArray->m_nNumber = nNum;
	pNumberArray->m_pos = pos;
	pNumberArray->m_size = size;
	pNumberArray->m_col = col;
	pNumberArray->m_nPlayerNum = nColorNum;

	// 初期化処理
	pNumberArray->Init();

	return pNumberArray;
}

//==================================
// 初期化処理
//==================================
HRESULT CNumberArray::Init()
{
	// 表示する数字の設定
	SetNumber();

	return S_OK;
}

//==================================
// 終了処理
//==================================
void CNumberArray::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_ARRAY_NUM; nCount++)
	{
		// 中身が入ってたら消す
		if (m_apNumber[nCount] != NULL)
		{
			m_apNumber[nCount]->Uninit();

			delete m_apNumber[nCount];
			m_apNumber[nCount] = NULL;
		}
	}
}

//==================================
// 更新処理
//==================================
void CNumberArray::Update(void)
{
	// キーボードの取得
	CInputKeyboard * pKey = CManager::GetKeyboard();

	m_nNumber = CColorTile::GetTileNum(m_nPlayerNum);

	for (int nCount = 0; nCount < MAX_ARRAY_NUM; nCount++)
	{
		// 中身が入ってたら更新
		if (m_apNumber[nCount] != NULL)
		{
			m_apNumber[nCount]->Update();
		}
	}

	// 表示する数字の設定
	SetNumber();
}

//==================================
// 描画処理
//==================================
void CNumberArray::Draw(void)
{
	// Zバッファを無効に
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

	for (int nCount = 0; nCount < MAX_ARRAY_NUM; nCount++)
	{
		// 中身が入ってたら描画
		if (m_apNumber[nCount] != NULL)
		{
			m_apNumber[nCount]->Draw();
		}
	}

	// Zバッファを戻す
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
}

//==================================
// 数字の間隔の設定
//==================================
float CNumberArray::Kerning(void)
{
	int nDigitNum = 0;		// 桁数
	float fKerning = 0.0f;	// 間隔

	// 桁数を数える
	nDigitNum = std::to_string(m_nNumber).length() - 1;
	
	// 奇数と偶数で値を変える
	if (nDigitNum % 2 == 0)
	{
		fKerning = -((((float)nDigitNum) * m_size.x / EVEN_NUMBER_DIVISION) * m_size.x);
	}
	else
	{
		fKerning = -(((float)nDigitNum) * m_size.x / ODD_NUMBER_DIVISION);
	}

	return fKerning;
}

//==================================
// 表示する数字の設定
//==================================
void CNumberArray::SetNumber(void)
{
	int nIndex = 0;				// 指数　(スコア表示用)
	const float fRadix = 10.0f;		// 基数　(スコア表示用)
	float fKerning = Kerning();	// 文字の間隔

	m_bZeroCheck = false; // フラグの初期化

	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot;													// 行列計算用マトリクス

	D3DXVECTOR3 Getpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	CPlayer * pPlayer = (CPlayer*)GetTop(OBJTYPE_PLAYER);
	while (pPlayer != NULL)
	{
		if (pPlayer->GetPlayerNumber() == m_nPlayerNum)
		{
			Getpos = pPlayer->GetPos();
		}

		pPlayer = (CPlayer*)pPlayer->GetNext();
	}

	// 数字の設定
	for (nIndex = 0; nIndex < MAX_ARRAY_NUM; nIndex++)
	{
		// 1桁ごとに数字を出す
		int nScore = (int)powf(fRadix, MAX_ARRAY_NUM - (float)nIndex - 1);
		int nScore2 = (int)powf(fRadix, MAX_ARRAY_NUM - (float)nIndex);
		int nAnswer = (m_nNumber % nScore2) / nScore;

		// 値が入ってないなら生成してテクスチャのバインド
		if (m_apNumber[nIndex] == NULL)
		{
			m_apNumber[nIndex] = CBillboard::Create(D3DXVECTOR3(m_pos.x + fKerning, m_pos.y, m_pos.z), m_size);
			m_apNumber[nIndex]->OutList();
			m_apNumber[nIndex]->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_NUMBER));
		}

		// 値が入ってたら
		if (m_apNumber[nIndex] != NULL)
		{
			// 各ナンバーのセット
			m_apNumber[nIndex]->SetTextureManualUV(MAX_TEXTURE_PATTARN, nAnswer);

			// カメラの向きを取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxRot);

			// 行列から角度を取得
			const float fAngle = atan2f(mtxRot._31, mtxRot._33);
			const float fAngle2 = atan2f(mtxRot._11, mtxRot._13);

			// 座標の設定
			m_apNumber[nIndex]->SetPos(Getpos +
			D3DXVECTOR3(cosf(fAngle) * (fKerning) + sinf(fAngle2) * (fKerning),
				NUMBER_POS_Y,
				-cosf(fAngle2) * (fKerning) + sinf(fAngle) * (fKerning)));
		}

		// 1桁目以外が0でチェックが入ってなかったら透明に、ほかは間隔をずらして色付け
		if (nAnswer == 0 && m_bZeroCheck == false && nIndex != MAX_ARRAY_NUM - 1)
		{
			m_apNumber[nIndex]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}
		else
		{
			// 色づけと間隔の計算
			m_apNumber[nIndex]->SetColor(m_col);
			fKerning += m_size.x / KERNING_DIVISION;

			// 下の方の桁の0を消さないようにフラグ立て
			m_bZeroCheck = true;
		}
	}
}