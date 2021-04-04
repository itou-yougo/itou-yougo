//=============================================================================
//
// 敵の爆発の処理 [enemyexplosion.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _ENEMYEXPLOSION_H_
#define _ENEMYEXPLOSION_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_ENEMYEXPLOSION_TEXTURE (2)

//=============================================================================
// 前方宣言
//=============================================================================
class CSound;

//=============================================================================
// 敵の爆発クラス
//=============================================================================
class CEnemyexplosion :public CScene2D
{
public:
	typedef enum
	{
		EXPLOSIONTYPE_NONE = 0,
		EXPLOSIONTYPE_PLAYER,  // PLAYER1の爆発
		EXPLOSIONTYPE_PLAYER2, // PLAYER2の爆発
		EXPLOSIONTYPE_MAX,
	}EXPLOSIONTYPE;

	typedef enum
	{
		EXPLOSIONTEXTURE_1 = 0, // 弾に当たって倒されたときのテクスチャ
		EXPLOSIONTEXTURE_2,		// 爆発に当たって倒されたときのテクスチャ
	}EXPLOSIONTEXTURE;

	CEnemyexplosion();  // コンストラク
	~CEnemyexplosion();	// デストラクタ

	static HRESULT Load(void); // ロード
	static void Unload(void);  // アンロード
	static CEnemyexplosion *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, 
		EXPLOSIONTYPE ExplosionType, EXPLOSIONTEXTURE ExplosionTexture, OBJTYPE objType); // クリエイト
	void SetExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 size, 
		EXPLOSIONTYPE ExplosionType, EXPLOSIONTEXTURE ExplosionTexture, OBJTYPE objType) { // 敵の爆発の処理
		m_pos = pos; m_size = size;
		m_ExplosionType = ExplosionType; m_ExplosionTexture = ExplosionTexture;
		SetPosition(pos); SetSize(size);
		SetObjType(objType);
	}

	HRESULT Init();    // 初期化処理
	void Uninit(void); // 終了処理
	void Update(void); // 更新処理
	void Draw(void);   // 描画処理

	void Hit(void); // 当たったときの処理
	EXPLOSIONTYPE GetExplosionType(void); // 爆発のタイプを返す
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_ENEMYEXPLOSION_TEXTURE]; // テクスチャへのポインタ
	D3DXVECTOR3		  m_pos;			  // 座標
	D3DXVECTOR3		  m_size;			  // 大きさ
	int				  m_nCounterAnim;	  // アニメーションのカウント
	int				  m_nPatternAnim;	  // アニメーションのパターン
	int				  m_nTimeAnim;		  // アニメーションの時間
	EXPLOSIONTYPE	  m_ExplosionType;	  // 爆発のタイプ
	EXPLOSIONTEXTURE  m_ExplosionTexture; // 爆発のテクスチャ
};
#endif