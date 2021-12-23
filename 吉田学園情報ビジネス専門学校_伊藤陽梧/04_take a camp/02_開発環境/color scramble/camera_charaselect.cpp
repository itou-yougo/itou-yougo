////////////////////////////////////////////////////
//
//    カメラクラスの処理[camera.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "camera_charaselect.h"
#include "manager.h"
#include "renderer.h"
#include "character_polygon.h"

//******************************
// マクロ定義
//******************************
#define CAMERA_POS   D3DXVECTOR3(0.0f,0.0f,25.0f)
#define CAMERA_POS_R D3DXVECTOR3(0.0f,0.0f,0.0f) 

//******************************
// 静的メンバ変数宣言
//******************************

//******************************
// コンストラクタ
//******************************
CCharaSelectCamera::CCharaSelectCamera()
{

}

//******************************
// デストラクタ
//******************************
CCharaSelectCamera::~CCharaSelectCamera()
{
}

//******************************
// クリエイト
//******************************
CCharaSelectCamera * CCharaSelectCamera::Create(void)
{
	CCharaSelectCamera * pCamera = new CCharaSelectCamera;
	pCamera->Init();

	return pCamera;
}

//******************************
// 初期化処理
//******************************
HRESULT CCharaSelectCamera::Init(void)
{
	// カメラクラスの初期化
	CCamera::Init();
	// 座標の初期化
	SetPosV(CAMERA_POS);
	// 注視点の初期化
	SetPosR(CAMERA_POS_R);

	return S_OK;
}

//******************************
// カメラセット
//******************************
void CCharaSelectCamera::SetCamera(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIXA16 matWorld;
	D3DXMATRIX *mtxView = GetViewMtx();
	D3DXMATRIX *mtxProjection = GetProjectionMtx();
	//ビューマトリックスの初期化
	D3DXMatrixIdentity(mtxView);
	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(mtxView, &GetPosV(), &GetPosR(), &GetVecU());
	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, mtxView);

	//プロジェクトマトリックスの初期化
	D3DXMatrixIdentity(mtxProjection);

	D3DXMatrixPerspectiveFovLH(mtxProjection,
		GetFov(), (float)DEFAULT_CHARACTER_POLYGON_SIZE.x / (float)DEFAULT_CHARACTER_POLYGON_SIZE.y, CAMERA_VIEW_MIN, CAMERA_VIEW_MAX);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, mtxProjection);
}
