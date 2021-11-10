//=============================================================================
//
// ボムの爆発の処理 [bombexplosion.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _BOMBEXPLOSION_H_
#define _BOMBEXPLOSION_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CSound;

//=============================================================================
// ボムの爆発クラス
//=============================================================================
class CBombexplosion :public CScene2D
{
public:
	typedef enum
	{
		BOMBEXPLOSION_NONE = 0,
		BOMBEXPLOSION_PLAYER,  // プレイヤー1のボムの爆発
		BOMBEXPLOSION_PLAYER2, // プレイヤー2のボムの爆発
		BOMBEXPLOSION_MAX,
	}BOMBEXPLOSIONTYPE;

	CBombexplosion();  // コンストラク
	~CBombexplosion(); // デストラクタ

	static HRESULT Load(void); // ロード
	static void Unload(void);  // アンロード
	static CBombexplosion *Create(D3DXVECTOR3 pos, int nLife, BOMBEXPLOSIONTYPE bombexplosiontype, OBJTYPE objType); // クリエイト

	HRESULT Init();    // 初期化処理
	void Uninit(void); // 終了処理
	void Update(void); // 更新処理
	void Draw(void);   // 描画処理

	void SetBombexplosion(D3DXVECTOR3 pos, int nLife, BOMBEXPLOSIONTYPE bombexplosiontype, OBJTYPE objType) { // ボムの爆発の設定
		m_pos = pos; m_nLife = nLife; 
		SetPosition(pos); m_BombExplosionType = bombexplosiontype; SetObjType(objType);
	}
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;  // テクスチャのポインタ
	D3DXVECTOR3		  m_pos;			   // 爆発の座標
	int				  m_nLife;			   // 体力
	BOMBEXPLOSIONTYPE m_BombExplosionType; // ボムの爆発のタイプ
};
#endif