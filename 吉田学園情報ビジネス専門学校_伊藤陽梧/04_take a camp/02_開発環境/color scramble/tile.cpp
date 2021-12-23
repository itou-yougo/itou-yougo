////////////////////////////////////////////////////
//
//    tileクラスの処理[tile.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "tile.h"
#include "manager.h"
#include "renderer.h"
#include "resource_shader.h"
#include "camera_base.h"
#include "light.h"
#include "collision.h"
#include "bullet.h"
#include "player.h"
#include "peint_collision.h"
#include "color_tile.h"
#include "attack_area.h"

#ifdef _DEBUG
#include "keyboard.h"
#endif

//*****************************
// マクロ定義
//*****************************
#define POS_Y_RATE_BASE		(0.03f)
#define POS_Y_RATE_UP		(0.1f)
#define BULLET_HIT_POS_Y	(TILE_POS_Y + 6.0f)

//*****************************
// 静的メンバ変数宣言
//*****************************
std::vector<CTile*> CTile::m_aTileList = {};

//******************************
// コンストラクタ
//******************************
CTile::CTile() :CModel(OBJTYPE_TILE)
{                       
	m_color = TILE_DEFAULT_COLOR;
	m_pCollison = NULL;
	m_fDistPosY = TILE_POS_Y;			// 座標Yの目標値
	m_fDistPosYRate = POS_Y_RATE_BASE;	// 座標Yの変更時の係数
	m_bHitOld = false;
	m_bHitPlayer = false;        // プレイヤーが当たっているフラグ
	m_bHitBullet = false;        // 弾が当たっているフラグ
	m_bRide		 = false;		 // 乗れるかフラグ
	m_aTileList.push_back(this);
}

//******************************
// デストラクタ
//******************************
CTile::~CTile()
{
}

//******************************
// クラス生成
//******************************
void CTile::Create(D3DXVECTOR3 pos , D3DXCOLOR col )
{
	// メモリの確保
	CTile *pTile;
	pTile = new CTile;

	// 初期化
	pTile->Init();

	// 各値の代入・セット
	pTile->SetPos(pos);
	pTile->SetPriority(OBJTYPE_TILE); // オブジェクトタイプ
}

//******************************
// 指定座標の当たっているタイルの取得
//******************************
CTile * CTile::GetHitTile(D3DXVECTOR3 pos)
{
	CCollision*pCollision = CCollision::CreateSphere(pos, TILE_ONE_SIDE / 4);

	for (size_t nCntTile = 0; nCntTile< m_aTileList.size(); nCntTile++)
	{
		if (CCollision::CollisionSphere(pCollision, m_aTileList[nCntTile]->GetCollision()))
		{
			if (pCollision != NULL)
			{
				pCollision->OutList();
				pCollision->Uninit();
				delete pCollision;
				pCollision = NULL;
			}

			return m_aTileList[nCntTile];
		}
	}

	if (pCollision != NULL)
	{
		pCollision->OutList();
		pCollision->Uninit();
		delete pCollision;
		pCollision = NULL;
	}

	return NULL;
}

//******************************
// 初期化処理
//******************************
HRESULT CTile::Init(void)
{
	if (FAILED(CModel::Init()))
	{
		return E_FAIL;
	}

	// モデル割り当て
	BindModel(CResourceModel::GetModel(CResourceModel::MODEL_GENERAL_BOX));

	// サイズの設定
	SetSize(TILE_SIZE);

	// 変数の初期化
	m_color			= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); // 色
	m_fDistPosY		= TILE_POS_Y;						 // 座標Yの目標値
	m_fDistPosYRate = POS_Y_RATE_BASE;					 // 座標Yの変更時の係数
	m_bHitOld		= false;							 // 一個前のフレームで当たっていたか保存するよう 
	m_bHitPlayer	= false;							 // プレイヤーが当たっているフラグ
	m_bHitBullet	= false;							 // 弾が当たっているフラグ

	if (m_pCollison == NULL)
	{
		m_pCollison = CCollision::CreateSphere(D3DXVECTOR3(GetPos().x, GetPos().y + TILE_ONE_SIDE / 2, GetPos().z), TILE_ONE_SIDE / 2);
	}
	return S_OK;
}

//******************************
// 終了処理
//******************************
void CTile::Uninit(void)
{
	CModel::Uninit();
}

//******************************
// 更新処理
//******************************
void CTile::Update(void)
{
	// 高さの調整
	D3DXVECTOR3 pos = GetPos();
	pos.y += (m_fDistPosY - pos.y)*m_fDistPosYRate;

	SetPos(pos);

	m_fDistPosY = TILE_POS_Y;
	m_fDistPosYRate = POS_Y_RATE_BASE;
	
	if (m_pCollison->GetPos() != D3DXVECTOR3(GetPos().x, GetPos().y + TILE_ONE_SIDE / 2, GetPos().z))
	{
		m_pCollison->SetPos(D3DXVECTOR3(GetPos().x, GetPos().y + TILE_ONE_SIDE / 2, GetPos().z));
	}

	// プレイヤーとの当たり判定
	m_bHitPlayer = CollisionPlayer();

	// 弾との当たり判定
	m_bHitBullet = CollisionBullet();

	//塗り判定との当たり判定
	CollisionPeint();
}

//******************************
// 描画処理
//******************************
void CTile::Draw(void)
{
	/////////////////////////////　
	//仮
	// 色の設定
	D3DXMATERIAL* mat = (D3DXMATERIAL*)GetModelData()->pBuffMat->GetBufferPointer();
	mat->MatD3D.Ambient = m_color;
	mat->MatD3D.Diffuse = m_color;
	mat->MatD3D.Specular = m_color;
	mat->MatD3D.Emissive = m_color;

	////////////////////////////

	CModel::Draw();
}

//******************************
// モデル描画処理
//******************************
void CTile::DrawModel(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DMATERIAL9 matDef; //現在のマテリアル保持用
	D3DXMATERIAL*pMat;   //マテリアルデータへのポインタ

	// モデルデータの取得
	CResourceModel::Model * pModelData = GetModelData();

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &pModelData->mtxWorld);

	//現在のマテリアルを取得する
	pDevice->GetMaterial(&matDef);

	// シェーダー情報の取得
	CResourceShader::Shader shader = CResourceShader::GetShader(CResourceShader::SHADER_TILE);
	if (shader.pEffect != NULL)
	{
		// シェーダープログラムに値を送る
		SetShaderVariable(shader.pEffect, pModelData);
		if (pModelData->pBuffMat != NULL)
		{
			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)pModelData->pBuffMat->GetBufferPointer();

			// パス数の取得
			UINT numPass = 0;
			shader.pEffect->Begin(&numPass, 0);

			// パス数分描画処理のループ
			for (int nCntEffect = 0; nCntEffect < (int)numPass; nCntEffect++)
			{
				for (int nCntMat = 0; nCntMat < (int)pModelData->nNumMat; nCntMat++)
				{
					//マテリアルのアンビエントにディフューズカラーを設定
					pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

					//マテリアルの設定
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
					// テクスチャ
					pDevice->SetTexture(0, pModelData->apTexture[nCntMat]);

					// 色の情報を送る
					shader.pEffect->SetFloatArray("DiffuseColor", (float*)&m_color, 4);

					// シェーダパスの描画開始
					shader.pEffect->BeginPass(nCntEffect);
					//モデルパーツの描画
					pModelData->pMesh->DrawSubset(nCntMat);
					// シェーダパスの終了
					shader.pEffect->EndPass();

					pMat[nCntMat] = pModelData->defMat[nCntMat];
				}
			}
			// シェーダー終了
			shader.pEffect->End();
		}
	}
	//保持していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
	// テクスチャ情報の初期化
	pDevice->SetTexture(0, 0);
}


//=============================
// シェーダーに値を送る
//=============================
void CTile::SetShaderVariable(LPD3DXEFFECT pEffect, CResourceModel::Model * pModelData)
{
	if (pEffect != NULL)
	{
		// シェーダーに情報を渡す
		D3DXMATRIX mat;
		D3DXMatrixIdentity(&mat);
		mat = pModelData->mtxWorld * (*CManager::GetCamera()->GetViewMtx())* (*CManager::GetCamera()->GetProjectionMtx());
		// ワールドプロジェクション
		pEffect->SetMatrix("WorldViewProj", &mat);
		// ワールド座標
		pEffect->SetMatrix("World", &pModelData->mtxWorld);
		// ライトディレクション
		D3DXVECTOR3 lightDir = LIGHT_DIR_BASE;
		pEffect->SetFloatArray("LightDirection", (float*)&D3DXVECTOR3(lightDir.x, lightDir.y, lightDir.z), 3);

		// 視点位置
		D3DXVECTOR3 eye = CManager::GetCamera()->GetPosV();
		pEffect->SetFloatArray("Eye", (float*)&D3DXVECTOR3(eye.x, eye.y, eye.z), 3);

		// スペキュラの情報を送る
		pEffect->SetFloatArray("SpecularColor", (float*)&D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), 4);
	}
}

//******************************
// プレイヤーとの当たり判定
//******************************
bool CTile::CollisionPlayer(void)
{
	CPlayer * pPlayer = (CPlayer*)GetTop(OBJTYPE_PLAYER);

	while (pPlayer != NULL)
	{
		if (CCollision::CollisionSphere(m_pCollison, pPlayer->GetCollision()))
		{
			if (!m_bHitOld)
			{
				HitPlayerActionTrigger(pPlayer);
			}
			HitPlayerAction(pPlayer);
			// ヒットフラグの保存*当たってる
			m_bHitOld = true;
			return true;
		}
		pPlayer = (CPlayer*)pPlayer->GetNext();
	}
	
	if (m_bHitOld)
	{
		HitPlayerActionRelease();
	}

	// ヒットフラグの保存*当たってない
	m_bHitOld = false;
	return false;
}

//******************************
// プレイヤーと当たったときのアクション*プレス
//******************************
void CTile::HitPlayerAction(CPlayer * pPlayer)
{
}

//******************************
// プレイヤーと当たったときのアクション*トリガー
//******************************
void CTile::HitPlayerActionTrigger(CPlayer * pPlayer)
{
}

//******************************
// プレイヤーと当たったときのアクション*リリース
//******************************
void CTile::HitPlayerActionRelease(void)
{
}



//******************************
// 弾との当たり判定
//******************************
bool CTile::CollisionBullet(void)
{
	CBullet * pBullet = (CBullet*)GetTop(OBJTYPE_BULLET);

	while (pBullet != NULL)
	{
		if (CCollision::CollisionSphere(m_pCollison, pBullet->GetCollision()))
		{
			HitBulletAction(pBullet);
			return true;
		}
		pBullet = (CBullet*)pBullet->GetNext();
	}

	return false;
}
//******************************
// 塗り判定に当たった時
//******************************
bool CTile::CollisionPeint(void)
{
	CPeintCollision * pPeint = (CPeintCollision*)GetTop(OBJTYPE_PEINT);

	while (pPeint != NULL)
	{
		if (CCollision::CollisionSphere(m_pCollison, pPeint->GetCollision()))
		{
			HItPeint(pPeint);
			return true;
		}
		pPeint = (CPeintCollision*)pPeint->GetNext();
	}
	return false;
}

//******************************
// 塗り判定と当たった時のアクション
//******************************
void CTile::HItPeint(CPeintCollision * pPeint)
{
}

//******************************
// 弾と当たったときのアクション
//******************************
void CTile::HitBulletAction(CBullet * pBullet)
{
	m_fDistPosY = BULLET_HIT_POS_Y;
	m_fDistPosYRate = POS_Y_RATE_UP;
}
