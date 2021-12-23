//====================================================
//
// resource_textヘッダ [resource_text.h]
// Author : 伊藤陽梧
//
//====================================================

//二重インクルード防止
#ifndef _RESOURCE_TEXT_H_
#define _RESOURCE_TEXT_H_

//====================================================
//インクルード
//====================================================
#include "main.h"
#include <map>

//====================================================
//マクロ定義
//====================================================

//*****************************
//クラス定義
//*****************************

// テキストリソースクラス
class CResourceText
{
public:

	// メンバ関数
	static CResourceText * Create(void);	// クラス生成
	static void Release(void);				// クラス破棄

	CResourceText();
	~CResourceText();

	static CResourceText *GetResourceText(void) { return m_pSingle; };	// リソーステキストポインタの取得
	std::string GetMapString(int nCountLine) { return m_TextMap[nCountLine]; };	// マップに入ってるテキストの情報取得
private:
	void Load(void);     // モデル読み込み
	void Unload(void); // モデル破棄

	static CResourceText *m_pSingle;		// モデルクラスのポインタ*シングルトン用
	std::map<int, std::string> m_TextMap;	// テキスト情報保持用のマップ
};

#endif