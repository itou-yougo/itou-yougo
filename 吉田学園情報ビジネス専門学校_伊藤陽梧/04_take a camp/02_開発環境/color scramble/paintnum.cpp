//===================================================
//
// 塗った数のUIの処理[paintnum.cpp]
// Author : 伊藤陽梧
//
//====================================================

//**********************************
// インクルード
//**********************************
#include "paintnum.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "color_manager.h"
#include "polygon.h"
#include "color_tile.h"
#include "chara_select.h"
#include "resource_texture.h"

//==================================
// マクロ定義
//==================================
#define SIZE_CHANGE_RATE (0.05f)

//==================================
// コンストラクタ
//==================================
CPaintnum::CPaintnum()
{
	m_pVtxBuff = nullptr;
	ZeroMemory(&m_apPolygon, sizeof(m_apPolygon));
	m_pColorGauge = nullptr;
	ZeroMemory(&m_pos, sizeof(m_pos));
	ZeroMemory(&m_size, sizeof(m_size));
	ZeroMemory(&m_PaintInfo, sizeof(m_nRank));
	ZeroMemory(&m_nRank, sizeof(m_fChangeSize));
	ZeroMemory(&m_fChangeSize, sizeof(m_fChangeSize));
}

//==================================
// デストラクタ
//==================================
CPaintnum::~CPaintnum()
{
}

//==================================
// クリエイト
// pos：座標
// size：大きさ
//==================================
CPaintnum * CPaintnum::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	// メモリの確保
	CPaintnum * pPaintnum = new CPaintnum;

	pPaintnum->m_pos = pos;
	pPaintnum->m_size = size;
	pPaintnum->SetPriority(OBJTYPE_UI_2);

	// 初期化処理
	pPaintnum->Init();

	return pPaintnum;
}

//==================================
// 初期化処理
//==================================
HRESULT CPaintnum::Init()
{
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		if (CCharaSelect::GetEntryData(nCount).bEntry)
		{
			// ポリゴンの各情報の設定
			m_PaintInfo[nCount].size = D3DXVECTOR3(m_size.x / (float)CCharaSelect::GetEntryPlayerNum(), m_size.y / 2.0f, m_size.z);
			m_PaintInfo[nCount].pos = D3DXVECTOR3(m_PaintInfo[nCount].size.x + ShiftSize(nCount) - m_pos.x + SUBTRACT_GAUGE_SIZE.x, m_pos.y, 0.0f);
			m_PaintInfo[nCount].col = GET_COLORMANAGER->GetIconColor(nCount);

			if (!m_apPolygon[nCount])
			{
				// ポリゴンの生成
				m_apPolygon[nCount] = CPolygon::Create(
					m_PaintInfo[nCount].pos,
					m_PaintInfo[nCount].size,
					m_PaintInfo[nCount].col);
			}

			// 徐々に変えるやつを初期化
			m_fChangeSize[nCount] = m_PaintInfo[nCount].size.x;

			// ポリゴンの座標をセット
			SetPolygonPos(nCount);
		}
	}

	if (!m_pColorGauge)
	{
		m_pColorGauge = CPolygon::Create(m_pos, m_size + SUBTRACT_GAUGE_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pColorGauge->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_COLOR_GAUGE));
	}

	return S_OK;
}

//==================================
// 終了処理
//==================================
void CPaintnum::Uninit()
{
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		if (m_apPolygon[nCount])
		{
			// 終了処理
			m_apPolygon[nCount]->Uninit();

			// メモリの解放
			delete m_apPolygon[nCount];
			m_apPolygon[nCount] = nullptr;
		}
	}

	if (m_pColorGauge)
	{
		// 終了処理
		m_pColorGauge->Uninit();

		// メモリの解放
		delete m_pColorGauge;
		m_pColorGauge = nullptr;
	}

	// オブジェクトの破棄
	Release();
}

//==================================
// 更新処理
//==================================
void CPaintnum::Update()
{
	// タイルの総数
	int nAllTileNum = 0;

	// タイルの総数を出す
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		nAllTileNum += CColorTile::GetTileNum(nCount);
	}

	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		// キャラクターがちゃんとエントリーしているか
		if (CCharaSelect::GetEntryData(nCount).bEntry)
		{
			// プレイヤーごとのタイルの数の割合
			if (nAllTileNum > 0)
			{
				float fRatio = (float)CColorTile::GetTileNum(nCount) / (float)nAllTileNum;
				m_PaintInfo[nCount].size = D3DXVECTOR3(m_size.x * fRatio, m_size.y / 2.0f, m_size.z);
			}

			// 本来の大きさと徐々に変えていく大きさの差
			float fDist = m_PaintInfo[nCount].size.x - m_fChangeSize[nCount];
			// 倍率を掛けて加算する
			m_fChangeSize[nCount] += fDist * SIZE_CHANGE_RATE;

			// 座標をずらす処理
			m_PaintInfo[nCount].pos = D3DXVECTOR3(m_fChangeSize[nCount] + ShiftSize(nCount) + (SUBTRACT_GAUGE_SIZE.x / 2.0f), m_pos.y, 0.0f);

			// ポリゴンの座標をセット
			SetPolygonPos(nCount);
		}
	}

	// プレイヤーごとの順位
	PlayerRank();
}

//==================================
// 描画処理
//==================================
void CPaintnum::Draw()
{
	// 描画
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		if (m_apPolygon[nCount])
		{
			m_apPolygon[nCount]->Draw();
		}
	}

	if (m_pColorGauge)
	{
		m_pColorGauge->Draw();
	}
}

//==================================
// ずらす大きさの計算
//==================================
float CPaintnum::ShiftSize(int nCount)
{
	float fSize = 0.0f;

	// 大きさの加算
	for (int nPlayerCount = 0; nPlayerCount < nCount; nPlayerCount++)
	{
		fSize += m_fChangeSize[nPlayerCount];
	}

	// 大きさの半分だけ小さくする
	fSize -= m_fChangeSize[nCount] / 2.0f;

	return fSize;
}

//==================================
// プレイヤーごとの順位
//==================================
void CPaintnum::PlayerRank(void)
{
	for (int nCompare = 0; nCompare < MAX_PLAYER; nCompare++)
	{
		int nRank = 0;
		for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
		{
			// 比べる方が小さいなら加算
			if (CColorTile::GetTileNum(nCompare) < CColorTile::GetTileNum(nCount)
				&& nCompare != nCount)
			{
				nRank++;
			}
		}

		// 順位を入れる
		m_nRank[nCompare] = nRank + 1;
	}
}

//==================================
// ポリゴンの座標
//==================================
void CPaintnum::SetPolygonPos(int nCount)
{
	// 頂点座標の設定
	D3DXVECTOR3 Pos[NUM_VERTEX];

	// 頂点座標の設定
	Pos[0] = D3DXVECTOR3(m_PaintInfo[nCount].pos.x - m_fChangeSize[nCount] / 2.0f, m_PaintInfo[nCount].pos.y - m_PaintInfo[nCount].size.y, 0.0f);
	Pos[1] = D3DXVECTOR3(m_PaintInfo[nCount].pos.x + m_fChangeSize[nCount] / 2.0f, m_PaintInfo[nCount].pos.y - m_PaintInfo[nCount].size.y, 0.0f);
	Pos[2] = D3DXVECTOR3(m_PaintInfo[nCount].pos.x - m_fChangeSize[nCount] / 2.0f, m_PaintInfo[nCount].pos.y + m_PaintInfo[nCount].size.y, 0.0f);
	Pos[3] = D3DXVECTOR3(m_PaintInfo[nCount].pos.x + m_fChangeSize[nCount] / 2.0f, m_PaintInfo[nCount].pos.y + m_PaintInfo[nCount].size.y, 0.0f);

	if (m_apPolygon[nCount])
	{
		// 頂点ごとの情報をセット
		m_apPolygon[nCount]->SetVertexPos(Pos);
	}
}
