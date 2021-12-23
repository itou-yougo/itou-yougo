//=============================================================================
//
// resource_characterヘッダ [resource_character.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _RESOURCE_CHARACTER_H_
#define _RESOURCE_CHARACTER_H_

//*****************************
//インクルード
//*****************************
#include "main.h"
#include "resource_model_hierarchy.h"

//*****************************
// マクロ定義
//*****************************
#define ATTACK_PATTARN_NUM (8) // 攻撃パターン数

//*****************************
//クラス定義
//*****************************

//テクスチャクラス
class CResourceCharacter
{
public:

	// 列挙
	// キャラクターの種類
	typedef enum
	{
		CHARACTER_NONE = -1,	// NONE
		CHARACTER_KNIGHT,		// 騎士
		CHARACTER_LANCER,		// 槍兵
		CHARACTER_WIZARD,		// 魔術師
		CHARACTER_THIEF,		// 盗賊
		CHARACTER_MAGICIAN,		// 奇術師
		CHARACTER_ARCHER,		// 弓使い
		CHARACTER_MAX			// キャラクタ数
	}CHARACTER_TYPE;
	//モーション
	typedef enum
	{
		MOTION_IDLE = 0,     // ニュートラル
		MOTION_CHARGE,       // チャージ
		MOTION_ATTACK,       // 攻撃
		MOTION_ROLL,         // カランカラン
		MOTION_MAX
	}MOTION_TYPE;

	// 構造体定義
	//characterデータ
	typedef struct
	{
		CResourceModelHierarchy::MODEL_HIERARCHY_TYPE modelType; // モデルタイプ番号

		int nMoveFrame;                        // 移動フレーム数
		int nMoveFrameDash;                    // 移動フレーム数*ダッシュ時
		int nMoveFrameInitial;				   // 初動フレーム数
		int nMoveCount;						   // 移動速度までの回数
		std::string attackTextPath;            // 攻撃テキストのパス
		int nFinalAttackTime;                  // 必殺技発動可能時間
		int anChargeTime[ATTACK_PATTARN_NUM];  // 各攻撃のチャージタイムのリスト
		std::string aMotionTextPath[MOTION_MAX]; // モーションファイルパスリスト
	}CharacterData;

	// キャラクターラベルデータ
	typedef struct
	{
		std::string labelName; // ラベルネーム
		CResourceModelHierarchy::MODEL_HIERARCHY_TYPE modelType; // モデルタイプ
	}LabelData;

private:
	CResourceCharacter();  //隠しコンストラクタ
public:
	~CResourceCharacter(); // デストラクタ
	// メンバ関数
	static CResourceCharacter * Create(void); // クラス生成
	static void Release(void);                // クラス破棄
	static CResourceCharacter*GetResourceCharacter(void) { return m_pInstance; } // インスタンスの取得処理
	CharacterData GetCharacterData(CHARACTER_TYPE type) { return m_aCharacterData[type]; }// キャラクターデータの取得処理

private:
	void Load(void); // テクスチャ読み込み

	// メンバ変数
	static CResourceCharacter* m_pInstance;           // インスタンスの保持
	static const std::vector<LabelData> m_aLabelList; // キャラクターラベルリスト
	static const std::string m_aCharacterDataTxtPath[CHARACTER_MAX]; // キャラクターデータのテキストのパス
	CharacterData m_aCharacterData[CHARACTER_MAX];    // キャラクターデータ
};

#endif