//=============================================================================
//
// エクストラアタックの処理 [extraattack.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _EXTRAATTACK_H_
#define _EXTRAATTACK_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_EXTRAATTACK_TEXTURE (4) //テクスチャの最大数

//=============================================================================
// エクストラアタッククラス
//=============================================================================
class CExtraattck :public CScene2D
{
public:
	typedef enum
	{
		EXTRAATTCK_PLAYER_NONE = 0,
		EXTRAATTCK_PLAYER1,		    // プレイヤー1のエクストラアタック
		EXTRAATTCK_PLAYER2,		    // プレイヤー2のエクストラアタック
		EXTRAATTCK_PLAYER_MAX,
	}EXTRAATTCKPLAYERNUM;

	typedef enum
	{
		EXTRAATTACK_BLINKING = 0,  // チカチカしながら相手の方に行くエクストラアタック
		EXTRAATTACK_AIM,		   // 相手を狙うエクストラアタック
		EXTRAATTACK_EXPLOSION,	   // 爆発するエクストラアタック
		EXTRAATTACK_LOCKET,		   // 上にあがるエクストラアタック
		EXTRAATTACK_MAX,
	}EXTRAATTACK;

	CExtraattck();  // コンストラク
	~CExtraattck();	// デストラクタ

	static HRESULT Load(void); // ロード
	static void Unload(void);  // アンロード
	static CExtraattck *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size,
		EXTRAATTCKPLAYERNUM Player, EXTRAATTACK Extraattack, OBJTYPE objType); // クリエイト

	HRESULT Init();     // 初期化処理
	void Uninit(void);  // 終了処理
	void Update(void);  // 更新処理
	void Draw(void);    // 描画処理

	void SetExtraAttack(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size,
		EXTRAATTCKPLAYERNUM Player, EXTRAATTACK Extraattack, OBJTYPE objType) { //エクストラアタックの設定
		SetPosition(pos); SetSize(size);
		m_pos = pos; m_move = move; m_size = size;
		m_ExtraPlayerNum = Player; m_ExtraAttack = Extraattack;
		SetObjType(objType);
	}

	void Blinking(void);  // チカチカする処理
	void Aim(void);		  // 相手を狙う処理
	void Explosion(void); // 爆発する処理
	void Locket(void);	  // 上にあがる処理
	EXTRAATTACK GetExtraAttack(void); // エクストラアタックを返す処理
	EXTRAATTCKPLAYERNUM GetExtraPlayerNum(void); // エクストラアタックのプレイヤーの番号を返す処理
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_EXTRAATTACK_TEXTURE];  // テクスチャへのポインタ
	D3DXVECTOR3	m_pos;					   // 座標
	D3DXVECTOR3	m_move;					   // 速さ
	D3DXVECTOR3 m_Getpos;				   // 受け取った座標
	D3DXVECTOR3	m_size;					   // 大きさ
	float	m_fAngle;					   // 角度
	int		m_nCountColor;				   // 色のカウント
	EXTRAATTCKPLAYERNUM m_ExtraPlayerNum;  // どのプレイヤーか
	EXTRAATTACK m_ExtraAttack;			   // エクストラアタックのタイプ
};
#endif