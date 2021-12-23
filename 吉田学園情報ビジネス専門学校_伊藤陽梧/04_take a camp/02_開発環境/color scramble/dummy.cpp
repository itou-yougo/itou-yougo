//=============================================================================
//
// dummyクラスの処理[dummy.cpp]
// Author : 伊藤陽梧
//
//=============================================================================

//=============================
// インクルード
//=============================
#include "dummy.h"
#include "manager.h"
#include "collision.h"
#include "light.h"
#include "camera_base.h"
#include "motion.h"
#include "tutorial.h"

//=============================
// マクロ定義
//=============================
#define COLLISION_RADIUS		(18.0f)								 // 当たり判定の大きさ
#define MODEL_COLOR				(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	 // モデルカラー
#define MODEL_SIZE				(D3DXVECTOR3(1.4f,1.4f,1.4f))		 // モデルサイズ
#define RESPAWN_MAX_COUNT		(120)								 // リスポーンまでの最大カウント

//=============================
// コンストラクタ
//=============================
CDummy::CDummy() : CModel(OBJTYPE_DUMMY)
{
	m_color = MODEL_COLOR;
	m_nRespawnCount = 0;
	m_pCollision = nullptr;
	m_nColor = 0;
	memset(&m_RespawnPos, 0, sizeof(D3DXVECTOR3));
	m_DummyState = DUMMY_STATE_NORMAL;
}

//=============================
// デストラクタ
//=============================
CDummy::~CDummy()
{
}

//=============================
// クラス生成
//=============================
CDummy * CDummy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// メモリの確保
	CDummy *pDummy;
	pDummy = new CDummy;

	// オブジェクトタイプ
	pDummy->SetPriority(OBJTYPE_DUMMY);

	// 初期化
	pDummy->Init();

	// 各値の代入・セット
	pDummy->SetPos(pos);
	pDummy->SetRot(rot);
	pDummy->m_RespawnPos = pos;

	return pDummy;
}

//=============================
// 初期化処理
//=============================
HRESULT CDummy::Init(void)
{
	// モデルの初期化
	if (FAILED(CModel::Init()))
	{
		return E_FAIL;
	}

	// モデルの割り当て
	BindModel(CResourceModel::GetModel(CResourceModel::MODEL_DUMMY));

	// モデルのサイズの設定
	//SetSize(MODEL_SIZE);

	// 色設定
	m_color = MODEL_COLOR;
	return S_OK;
}

//=============================
// 終了処理
//=============================
void CDummy::Uninit(void)
{
	// 当たり判定の終了処理
	if (m_pCollision != NULL)
	{
		m_pCollision->OutList();
		m_pCollision->Uninit();
		delete m_pCollision;
		m_pCollision = NULL;
	}

	// モデルの終了
	CModel::Uninit();
}

//=============================
// 更新処理
//=============================
void CDummy::Update(void)
{
	// ステートごとの処理
	switch (m_DummyState)
	{
	case DUMMY_STATE_NORMAL: //通常状態
		// 当たり判定の位置
		if (m_pCollision == NULL)
		{
			m_pCollision = CCollision::CreateSphere(D3DXVECTOR3(GetPos().x, GetPos().y + COLLISION_RADIUS / 2, GetPos().z), COLLISION_RADIUS / 2);
		}
		break;

	case DUMMY_STATE_DEATH: //死亡状態
		//リスポーン処理
		Respawn();
		break;

	default:
		break;
	}

	// 当たり判定の位置更新処理
	if (m_pCollision != NULL) m_pCollision->SetPos(D3DXVECTOR3(GetPos().x, GetPos().y + COLLISION_RADIUS / 2, GetPos().z));

	// モデルの更新
	CModel::Update();
}

//=============================
// 描画処理
//=============================
void CDummy::Draw(void)
{
	// 色の設定
	for (int nCntMat = 0; nCntMat < (int)GetModelData()->nNumMat; nCntMat++)
	{
		D3DXMATERIAL* mat = (D3DXMATERIAL*)GetModelData()->pBuffMat->GetBufferPointer();
		mat[nCntMat].MatD3D.Ambient.a = m_color.a;
		mat[nCntMat].MatD3D.Diffuse.a = m_color.a;
		mat[nCntMat].MatD3D.Specular.a = m_color.a;
		mat[nCntMat].MatD3D.Emissive.a = m_color.a;
	}

	// モデルの描画
	CModel::Draw();
}

//=============================
// 死亡処理
//=============================
void CDummy::Death(void)
{
	// 死亡状態に移行
	SetState(DUMMY_STATE_DEATH);

	// 当たり判定を消す
	if (m_pCollision != NULL)
	{
		m_pCollision->OutList();
		m_pCollision->Uninit();
		delete m_pCollision;
		m_pCollision = NULL;
	}

	// 透明にする
	m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	// 位置セット
	SetPos(m_RespawnPos);
}

//=============================
// リスポーン処理
//=============================
void CDummy::Respawn(void)
{
	// ダミーステートが死亡状態の時
	if (m_DummyState == DUMMY_STATE_DEATH)
	{
		//カウントアップ
		m_nRespawnCount++;

		//カウントが一定までに達したとき
		if (m_nRespawnCount >= RESPAWN_MAX_COUNT)
		{
			// ステートを戻す
			m_DummyState = DUMMY_STATE_NORMAL;

			// 色を戻す
			m_color = MODEL_COLOR;

			// 位置セット
			SetPos(m_RespawnPos);

			// カウント初期化
			m_nRespawnCount = 0;
		}
	}
}