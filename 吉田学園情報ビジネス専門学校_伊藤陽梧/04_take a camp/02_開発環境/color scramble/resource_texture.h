//=============================================================================
//
// textureヘッダ [texture.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//*****************************
//インクルード
//*****************************
#include "main.h"

//*****************************
//クラス定義
//*****************************

//テクスチャクラス
class CResourceTexture
{
public:
	// 列挙
	// テクスチャ種類
	typedef enum
	{
		TEXTURE_TITLE = 0,			// タイトル
		TEXTURE_TUTORIAL,			// チュートリアル
		TEXTURE_TUTORIAL_FLAG,		// チュートリアル(はたあげ)
		TEXTURE_TUTORIAL_FRY,		// チュートリアル(連打)
		TEXTURE_TUTORIAL_REMEMBER,	// チュートリアル(記憶)
		TEXTURE_RESULT_KNIGHT,		// リザルト(ナイトの背景)
		TEXTURE_RESULT_LANCER,		// リザルト(ランサーの背景)
		TEXTURE_RESULT_WIZARD,		// リザルト(ウィザードの背景)
		TEXTURE_RESULT_THIEF,		// リザルト(シーフの背景)
		TEXTURE_RESULT_MAGICIAN,	// リザルト(奇術師の背景)
		TEXTURE_RESULT_ARCHER,		// リザルト(アーチャーの背景)
		TEXTURE_RESULT_KILL,		// リザルトのキルUI
		TEXTURE_RESULT_TILE,		// リザルトのタイルUI
		TEXTURE_PARTICLE_SQUARE,    // パーティクル*ダイヤ
		TEXTURE_PARTICLE_SKILL,		// パーティクル*涙
		TEXTURE_PARTICLE_CIRCLE,	// パーティクル*円
		TEXTURE_PARTICLE_GURUGURU,	// ぐるぐる
		TEXTURE_NUMBER,				// ナンバー
		TEXTURE_FRAME,				// 枠
		TEXTURE_CROSS_MARK,			// ×マーク
		TEXTURE_NEEDLE,				// とげ穴
		TEXTURE_SHADOW,				// 影
		TEXTURE_PLAYERNUMBER,		// プレイヤー番号
		TEXTURE_NONE,				// NONE
		TEXTURE_CONTROLLER,			// コントローラーアイコン
		TEXTURE_KEYBOARD,			// キーボードアイコン
		TEXTURE_CHARASELECT_BACK,	// キャラ選択背景
		TEXTURE_BUTTON_START,		// タイトルのボタン(スタート)
		TEXTYRE_BUTTON_TUTORIAL,	// タイトルのボタン(チュートリアル)
		TEXTURE_MAX_COLOR_EFFECT,	// 最大塗段階時のエフェクト
		TEXTURE_ATTACK_AREA,		// 攻撃範囲
		TEXTURE_CLOCK_FRAME,		// 時計の枠
		TEXTURE_CLOCK_HANDS,		// 時計の針
		TEXTURE_TOON_SHADOW,		// トゥーンシャドウ
		TEXTURE_TILE_CHARGE,		// タイルのチャージ
		TEXTURE_ICON_BG,			// アイコンの背景
		TEXTURE_SWORD_ICON,		 	// 剣アイコン
		TEXTURE_STAGE_NAME_UI,		// ステージ名
		TEXTURE_STAGE_SELECT_BG,
		TEXTURE_MAX					// テクスチャ数
	}TEXTURE_TYPE;
	// テクスチャ種類
	typedef enum
	{
		TECTURE_CUBE_SLY,        // キューブテクスチャ(空)
		TEXTURE_CUBE_MAX              // テクスチャ数
	}TEXTURE_CUBE_TYPE;

	// メンバ関数
	static CResourceTexture * Create(void);                  // クラス生成
	static void Release(void);                               // クラス破棄
	static LPDIRECT3DTEXTURE9 GetTexture(TEXTURE_TYPE type); // テクスチャの取得処理*引数：取得したいテクスチャ
	static LPDIRECT3DCUBETEXTURE9 GetCubeTexture(TEXTURE_CUBE_TYPE type); // テクスチャの取得処理*引数：取得したいテクスチャ
private:
	CResourceTexture();//隠しコンストラクタ
public:
	~CResourceTexture();

private:
	void Load(void); // テクスチャ読み込み
	void Unload(void); // テクスチャ破棄

	// メンバ変数
	static const std::string m_aTexPath[TEXTURE_MAX]; // テクスチャのパス
	static const std::string m_aCubeTexPath[TEXTURE_CUBE_MAX]; // テクスチャのパス
	static CResourceTexture *m_pSingleTex;			  // テクスチャクラスのポインタ*シングルトン用
	LPDIRECT3DTEXTURE9 m_apTexture[TEXTURE_MAX];      // テクスチャのポインタ
	LPDIRECT3DCUBETEXTURE9 m_apCubeTexture[TEXTURE_CUBE_MAX];      // テクスチャのポインタ
};

#endif