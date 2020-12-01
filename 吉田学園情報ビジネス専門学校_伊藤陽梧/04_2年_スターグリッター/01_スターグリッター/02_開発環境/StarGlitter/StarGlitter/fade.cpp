//=============================================================================
//
// フェードの処理 [fade.cpp]
// Author :　伊藤陽梧
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "fade.h"
#include "renderer.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define FADE_RATE (0.05f)

//=============================================================================
// フェードクラスのコンストラクタ
//=============================================================================
CFade::CFade() :CScene(OBJTYPE_FADE)
{
	m_pVtxBuff = NULL;
	m_fade = FADE_NOME;
	m_modeNext = CManager::MODE_TITLE;
	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f); //黒い画面(不透明)
}

//=============================================================================
// フェードクラスのデストラクタ
//=============================================================================
CFade::~CFade()
{

}

//=============================================================================
// フェードクラスのクリエイト
//=============================================================================
CFade * CFade::Create()
{
	// CFadeのポインタ
	CFade *pFade = NULL;

	// メモリの確保
	pFade = new CFade;

	// pFadeがNULLじゃないとき
	if (pFade != NULL)
	{
		// 初期化処理
		pFade->Init();
	}

	// pFadeを返す
	return pFade;
}

//=============================================================================
// フェードクラスの初期化処理
//=============================================================================
HRESULT CFade::Init()
{
	SetObjType(OBJTYPE_FADE);

	// インスタンス生成したものを受け取る
	CRenderer *pRenderer = CManager::GetRenderer();

	// デバイスを受け取る
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	VERTEX_2D *pVtx;//頂点情報のポインタ

	//オブジェクトの頂点バッファ生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定（右回りで設定する）
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラー
	pVtx[0].col = m_colorFade;
	pVtx[1].col = m_colorFade;
	pVtx[2].col = m_colorFade;
	pVtx[3].col = m_colorFade;

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点データアンロック
	m_pVtxBuff->Unlock();

	m_fade = FADE_IN;
	return S_OK;
}

//=============================================================================
// フェードクラスの終了処理
//=============================================================================
void CFade::Uninit(void)
{
	//頂点バッファの開放
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	Release();
}

//=============================================================================
// フェードクラスの更新処理
//=============================================================================
void CFade::Update(void)
{
	VERTEX_2D *pVtx;

	if (m_fade != FADE_NOME)
	{//フェードイン処理
		if (m_fade == FADE_IN)
		{//フェードイン処理
			m_colorFade.a -= FADE_RATE;
			//α値を減算して後ろの画面を浮き上がらせる
			if (m_colorFade.a <= 0.0f)
			{
				//フェード処理終了
				m_colorFade.a = 0.0f;
				m_fade = FADE_NOME;
			}
		}
		else if (m_fade == FADE_OUT)
		{//フェードアウト処理
			m_colorFade.a += FADE_RATE;
			//α値を減算して後ろの画面を消していく
			if (m_colorFade.a >= 1.0f)
			{
				//フェードイン処理に切り替え
				m_fade = FADE_IN;
				m_colorFade.a = 1.0f;
				//モード設定
				CManager::SetMode(m_modeNext);
			}
		}
		//頂点データの範囲をロックし、頂点バッファへのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//頂点カラーを設定（0～255の値で設定する）
		pVtx[0].col = m_colorFade;
		pVtx[1].col = m_colorFade;
		pVtx[2].col = m_colorFade;
		pVtx[3].col = m_colorFade;

		//頂点データをアンロックする
		m_pVtxBuff->Unlock();
	}
}

//=============================================================================
// フェードクラスの描画処理
//=============================================================================
void CFade::Draw(void)
{
	// インスタンス生成したものを受け取る
	CRenderer *pRenderer = CManager::GetRenderer();

	// デバイスを受け取る
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	pDevice->SetTexture(0, NULL);
}

//=============================================================================
// フェードクラスのセット
//=============================================================================
void CFade::SetFade(CManager::MODE modeNext)
{
	m_fade = FADE_OUT;
	m_modeNext = modeNext;
}

//=============================================================================
// フェードの取得状況
//=============================================================================
CFade::FADE CFade::GetFade(void)
{
	return m_fade;
}