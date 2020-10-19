//=============================================================================
//
// ポリゴンの描画の処理 [bg.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CScene2D;

//=============================================================================
// 背景クラス
//=============================================================================
class CBg :public CScene
{
public:
	typedef enum
	{
		BGTYPE_GAME = 0, // ゲームの背景
		BGTYPE_FRAME,	 // ゲームの枠
		BGTYPE_TUTORIAL, // チュートリアルの背景
		BGTYPE_RESULT,	 // リザルトの背景
	}BGTYPE;

	CBg();
	~CBg();

	static HRESULT Load(void);
	static void Unload(void);
	static CBg *Create(BGTYPE bgtype, OBJTYPE objType);

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetBG(BGTYPE bgtype, OBJTYPE objType) {
		m_bgtype = bgtype; SetObjType(objType);
	}
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BG_TEXTURE]; // テクスチャのポインタ
	CScene2D *m_apScene[MAX_BG_TEXTURE];				   // CScene2Dのポインタ
	BGTYPE m_bgtype;									   // 背景の種類
};
#endif