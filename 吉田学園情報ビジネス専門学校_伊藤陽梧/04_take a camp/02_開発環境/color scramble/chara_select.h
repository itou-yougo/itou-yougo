//=============================================================================
//
// chara_slectヘッダ [chara_slect.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _CHARA_SELECT_H_
#define _CHARA_SELECT_H_

//*****************************
//インクルード
//*****************************
#include "scene.h"
#include "game.h"
#include "resource_character.h"

//=============================
// 前方宣言
//=============================

//*****************************
//マクロ定義
//*****************************

//*****************************
//クラス定義
//*****************************

//キャラ選択クラス
class CCharaSelect : public CScene
{
public:
	//*****************************
	// 列挙定義
	//*****************************

	//*****************************
	// 構造体定義
	//*****************************
	struct Entry_Data
	{
		int nControllNum; // コントローラー番号
		bool bController; // コントローラーフラグ*trueならコントローラーfalseならキーボード
		int nColorNum;    // カラー番号
		CResourceCharacter::CHARACTER_TYPE charaType; // キャラタイプ
		bool bEntry;      // エントリー状態
		bool bReady;
	};

	//*****************************
	// メンバ関数
	//*****************************
	CCharaSelect();
	~CCharaSelect();

	static CCharaSelect *Create(void); // クラス生成

	HRESULT Init(void); // 初期化
	void Uninit(void);  // 終了
	void Update(void);  // 更新
	void Draw(void);    // 描画
	static Entry_Data GetEntryData(int nIndex) { return m_aEntryData[nIndex]; }
	static void SetEntryData(int nIndex, Entry_Data data) { m_aEntryData[nIndex] = data; }
	static int GetEntryPlayerNum(void) { return m_nEntryPlayerNum; }
	static void ResetEntryPlayer(void);
private:
	void FadeGameScene(void);
	void EntryPlayer(void);
	void CountEntryPlayerNum(void);
	void CharacterSelect(int nCntData);

	//*****************************
	// メンバ変数
	//*****************************
	static Entry_Data m_aEntryData[MAX_PLAYER]; // エントリーデータ
	static int m_nEntryPlayerNum;               // エントリー人数
	bool m_abUseJoy[MAX_PLAYER];           // 使っているコントローラーのフラグ
	bool m_abUseKey[MAX_PLAYER];           // 使っているコントローラーのフラグ
	int m_anWaitCnt[MAX_PLAYER];                             // キャラ変更から次変更可能までのカウント
};

#endif