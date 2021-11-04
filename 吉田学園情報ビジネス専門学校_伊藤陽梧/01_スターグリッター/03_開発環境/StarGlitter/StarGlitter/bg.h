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

	CBg();  // コンストラク
	~CBg();	// デストラクタ

	static HRESULT Load(void); // ロード
	static void Unload(void);  // アンロード
	static CBg *Create(BGTYPE bgtype, OBJTYPE objType); // クリエイト

	HRESULT Init();    // 初期化処理
	void Uninit(void); // 終了処理
	void Update(void); // 更新処理
	void Draw(void);   // 描画処理

	void SetBG(BGTYPE bgtype, OBJTYPE objType) { // 背景の設定
		m_BgType = bgtype; SetObjType(objType);
	}
	void BgCreate(BGTYPE BgType); // 背景のポリゴンを作る処理
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BG_TEXTURE]; // テクスチャのポインタ
	CScene2D *m_apScene[MAX_BG_TEXTURE];				   // CScene2Dのポインタ
	BGTYPE m_BgType;									   // 背景の種類
};
#endif