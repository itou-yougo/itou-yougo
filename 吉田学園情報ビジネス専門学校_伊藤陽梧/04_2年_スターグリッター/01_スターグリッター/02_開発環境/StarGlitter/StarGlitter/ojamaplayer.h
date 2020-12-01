//=============================================================================
//
// おじゃまプレイヤーの処理 [ojamaplayer.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _OJAMAPLAYER_H_
#define _OJAMAPLAYER_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"
#include "bullet.h"

//=============================================================================
// おじゃまプレイヤークラス
//=============================================================================
class COjamaplayer :public CScene2D
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

	COjamaplayer();
	~COjamaplayer();

	static HRESULT Load(void);
	static void Unload(void);
	static COjamaplayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fSizeX, float fSizeY, int nCount, D3DXVECTOR3 Accele, OJAMATYPE OjamaType, OBJTYPE objType);

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetCOjama(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fSizeX, float fSizeY, int nCount, D3DXVECTOR3 Accele, OJAMATYPE OjamaType, OBJTYPE objType) {
		SetPosition(pos); SetSize(fSizeX, fSizeY);
		m_pos = pos; m_move = move;
		m_fSizeX = fSizeX; m_fSizeY = fSizeY;
		m_nCount = nCount; m_accele = Accele;
		m_OjamaType = OjamaType; SetObjType(objType);
	}

private:
	static LPDIRECT3DTEXTURE9 m_pTexture; // テクスチャへのポインタ
	D3DXVECTOR3	m_pos;					  // 座標
	D3DXVECTOR3	m_move;					  // 速さ
	D3DXVECTOR3 m_Getpos;				  // 受け取った座標
	D3DXVECTOR3	m_middle;				  // 中心の座標
	D3DXVECTOR3 m_posPlayer2;			  // プレイヤー2の座標
	D3DXVECTOR3 m_GetposPlayer2;		  // プレイヤー2の受け取った座標
	D3DXVECTOR3	m_accele;				  // 加速度
	float	m_fSizeX;					  // 横の大きさ
	float	m_fSizeY;					  // 縦の大きさ
	float	m_fGetSizeX;				  // 受け取った横の大きさ
	float	m_fGetSizeY;				  // 受け取った縦の大きさ
	float	m_fAngle;					  // 角度
	int		m_nCount;					  // 何回目のクリエイトかのカウント
	int		m_nOjamaCount;				  // おじゃまのカウント
	bool	m_bFirstmove;				  // 一回目の動きをする判定
	bool	m_bSecondmove;				  // 二回目の動きをする判定
	OJAMATYPE m_OjamaType;				  // おじゃまのタイプ
};
#endif