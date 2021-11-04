//=============================================================================
//
// おじゃまの処理 [ojama.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _OJAMA_H_
#define _OJAMA_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"
#include "player.h"

//=============================================================================
// おじゃまプレイヤークラス
//=============================================================================
class COjama :public CScene2D
{
public:
	typedef enum
	{
		OJAMA_TYPE_NONE = 0,
		OJAMA_TYPE_CURVE,   // 曲がるおじゃま
		OJAMA_TYPE_THROUGH, // まっすぐ動くおじゃま
		OJAMA_TYPE_FALL,	// 落ちるおじゃま
		OJAMA_TYPE_MAX,
	}OJAMATYPE;

	typedef enum
	{
		OJAMAPLAYER_1P, // 1Pのおじゃま
		OJAMAPLAYER_2P, // 2Pのおじゃま
		OJAMAPLAYER_MAX,
	}OJAMAPLAYERNUM;

	COjama();  // コンストラク
	~COjama(); // デストラクタ

	static HRESULT Load(void); // ロード
	static void Unload(void);  // アンロード
	static COjama *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size,
		int nCount, D3DXVECTOR3 Accele, OJAMATYPE OjamaType,
		OJAMAPLAYERNUM OjamaPlayer, OBJTYPE objType); // クリエイト

	HRESULT Init();    // 初期化処理
	void Uninit(void); // 終了処理
	void Update(void); // 更新処理
	void Draw(void);   // 描画処理

	void SetCOjama(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, 
		int nCount, D3DXVECTOR3 Accele, OJAMATYPE OjamaType, 
		OJAMAPLAYERNUM OjamaPlayer, OBJTYPE objType) { // おじゃまの設定
		SetPosition(pos); SetSize(size);
		m_pos = pos; m_move = move; m_size = size;
		m_nCount = nCount; m_accele = Accele;
		m_OjamaType = OjamaType; m_OjamaPlayerNum = OjamaPlayer;
		SetObjType(objType);
	}

	void Curve(void);   // 曲がって動く処理
	void Through(void); // まっすぐ動く処理
	void Fall(void);    // 落ちて動く処理

	void Hit(void); // 当たったとき処理
	void HitBullet(CScene *pScene); // 弾に当たったとき処理
	void HitExplosion(CScene *pScene); // 爆発に当たったとき処理
	void ExtraAttackCreate(CPlayer::PLAYERNUM PlayerNum); // エクストラアタックを作る処理

	OJAMAPLAYERNUM GetOjamaPlayerNum(void); // おじゃまのプレイヤーの番号を返す
private:
	static LPDIRECT3DTEXTURE9 m_pTexture; // テクスチャへのポインタ
	D3DXVECTOR3	m_pos;					  // 座標
	D3DXVECTOR3	m_move;					  // 速さ
	D3DXVECTOR3 m_Getpos;				  // 受け取った座標
	D3DXVECTOR3 m_Fallpos;				  // 落ちる座標
	D3DXVECTOR3	m_middle;				  // 中心の座標
	D3DXVECTOR3	m_accele;				  // 加速度
	D3DXVECTOR3	m_size;					  // 大きさ
	D3DXVECTOR3 m_GetSize;				  // 受け取った大きさ
	float	m_fAngle;					  // 角度
	int		m_nCount;					  // 何回目のクリエイトかのカウント
	int		m_nOjamaCount;				  // おじゃまのカウント
	bool	m_bFirstmove;				  // 一回目の動きをする判定
	bool	m_bSecondmove;				  // 二回目の動きをする判定
	OJAMATYPE m_OjamaType;				  // おじゃまのタイプ
	OJAMAPLAYERNUM m_OjamaPlayerNum;	  // おじゃまのプレイヤーの番号
};
#endif