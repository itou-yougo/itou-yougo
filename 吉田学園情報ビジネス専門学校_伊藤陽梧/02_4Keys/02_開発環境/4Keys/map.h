//=============================================================================
//
// プレイヤーの処理 [player.h]
// Author : 
//
//=============================================================================
#ifndef _MAP_H_
#define _MAP_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "scene.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_MATERIAL (50)

//=============================================================================
// 前方宣言
//=============================================================================
class CModel;

//=============================================================================
// プレイヤークラス
//=============================================================================
class CMap :public CScene
{
public:
	CMap(int nPriority = CScene::OBJTYPE_NONE);//コンストラクタ
	~CMap();//デストラクタ

	static CMap *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);//生成処理
	static HRESULT Load(void);//テクスチャの読み込み
	static void Unload(void);//テクスチャの破棄
	static HRESULT LoadTexture(void);
	HRESULT Init(void);//初期化処理
	void Uninit(void);//終了処理
	void Update(void);//更新処理
	void Draw(void);//描画処理

					//初期設定
	void SetMap(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);

	//受け渡し処理
	D3DXVECTOR3 GetPos(void) { return m_pos; }//場所
	D3DXVECTOR3 GetRot(void) { return m_rot; }//角度
	LPD3DXMESH GetMapMesh(void) { return m_pMesh; }
private:
	static LPD3DXMESH m_pMesh;	  // メッシュ情報のポインタ
	static LPD3DXBUFFER m_pBuffMat; // マテリアル情報のポインタ
	static DWORD m_nNumMat;		  // マテリアル情報の数
	static D3DXMATRIX m_mtxWorld;	  // 行列計算用
	static char* m_apFileName;	  // ファイルの名前
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_MATERIAL];

	D3DXVECTOR3 m_pos;					// 場所
	D3DXVECTOR3 m_rot;					// 角度
	D3DXVECTOR3 m_size;					// 大きさ
	CModel *m_pModel; // モデルクラスのポインタ
};

#endif