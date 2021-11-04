//=============================================================================
//
// ポリゴンの描画の処理 [explosion.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_EXPLOSION_TEXTUTE (2)

//=============================================================================
// 前方宣言
//=============================================================================
class CSound;

//=============================================================================
// エクスプロージョンクラス
//=============================================================================
class CExplosion :public CScene2D
{
public:
	typedef enum
	{
		EXPLOSIONTYPE_NOMAL = 0, // 弾の爆発
		EXPLOSIONTYPE_BOSS,		 // ボスアタックの爆発
	}EXPLOSIONTYPE;

	CExplosion();  // コンストラク
	~CExplosion(); // デストラクタ

	static HRESULT Load(void); // ロード
	static void Unload(void);  // アンロード
	static CExplosion *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, 
		EXPLOSIONTYPE ExplosionType, OBJTYPE objType); // クリエイト

	HRESULT Init();    // 初期化処理
	void Uninit(void); // 終了処理
	void Update(void); // 更新処理
	void Draw(void);   // 描画処理

	void SetExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 size, 
		EXPLOSIONTYPE ExplosionType, OBJTYPE objType) { // 爆発の設定
		m_pos = pos; m_size = size;
		SetPosition(pos); SetSize(size);
		m_ExplosionType = ExplosionType; SetObjType(objType);
	}
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_EXPLOSION_TEXTUTE]; // テクスチャへのポインタ
	D3DXVECTOR3		  m_pos;		   // 座標
	D3DXVECTOR3		  m_size;		   // 大きさ
	int				  m_nCounterAnim;  // アニメーションのカウント
	EXPLOSIONTYPE	  m_ExplosionType; // 爆発のタイプ
};
#endif