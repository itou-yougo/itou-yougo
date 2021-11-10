//=============================================================================
//
// ボムの処理 [bomb.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _BOMB_H_
#define _BOMB_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// ボムクラス
//=============================================================================
class CBomb :public CScene2D
{
public:
	typedef enum
	{
		BOMB_TYPE_NONE = 0,
		BOMB_TYPE_PLAYER,  // プレイヤー1のボム
		BOMB_TYPE_PLAYER2, // プレイヤー2のボム
		BOMB_TYPE_MAX,
	}BOMBTTYPE;

	CBomb();  // コンストラク
	~CBomb(); // デストラクタ

	static HRESULT Load(void); // ロード
	static void Unload(void);  // アンロード
	static CBomb *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, BOMBTTYPE BombType, OBJTYPE objType); // クリエイト

	HRESULT Init();    // 初期化処理
	void Uninit(void); // 終了処理
	void Update(void); // 更新処理
	void Draw(void);   // 描画処理

	void SetBomb(D3DXVECTOR3 pos, D3DXVECTOR3 size, BOMBTTYPE BombType, OBJTYPE objType) { // ボムの設定
		SetPosition(pos); SetSize(size);
		m_pos = pos; m_BombType = BombType;
		SetObjType(objType);
	}

	void UseBomb(void); // ボムを使うときの処理
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;  // テクスチャへのポインタ
	D3DXVECTOR3	m_pos;					   // ボムの座標
	D3DXVECTOR3 m_Getpos;				   // 受けっとった座標
	bool	m_bUse;						   // ボムを使ったかどうか
	BOMBTTYPE m_BombType;				   // ボムのタイプ
};
#endif