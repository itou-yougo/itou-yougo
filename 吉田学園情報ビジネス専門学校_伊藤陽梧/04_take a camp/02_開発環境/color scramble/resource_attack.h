//=============================================================================
//
// 攻撃範囲読み込みクラス [resource_attack.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _RESOURCE_ATTACK_H_
#define _RESOURCE_ATTACK_H_
//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "model.h"
#include "scene.h"
#include "resource_character.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_ATTACK_SIZE_X	(50)	//最大ブロック数
#define MAX_ATTACK_SIZE_Y	(50)	//最大ステージサイズ
#define MAX_ATTACK_LEVEL	(4)		//攻撃の最大レベル
#define MAX_HIT_TYPE		(8)		//ヒットマスタイプフレーム数の最大数
#define MIN_HIT_TYPE		(0)		//ヒットマスタイプフレーム数の最小数
//=============================================================================
// クラス定義
//=============================================================================
class CAttackManager
{
public:
	typedef struct	//一行の攻撃範囲情報
	{
		int			nRangeType[MAX_ATTACK_SIZE_X];	// ブロックデータ
		int			nAttackRangeX;					// その行のブロック数
	}RANGE_DATA;

	typedef struct	//攻撃情報
	{
		RANGE_DATA	RangeData[MAX_ATTACK_SIZE_Y];	// ブロック
		int			nAttackRangeY;					// ブロックの列
		int			nAttackFrame[MAX_HIT_TYPE];
	}ATTACK_RANGE_DATA;


	typedef enum	//攻撃タイルの種類
	{
		ATTACK_RANGE_NONE = 0,	//なし
		ATTACK_RANGE_CENTER,	//中心
		ATTACK_RANGE_HIT_1,		//攻撃(数値が上がるほど後に攻撃する)
		ATTACK_RANGE_HIT_2,
		ATTACK_RANGE_HIT_3,
		ATTACK_RANGE_HIT_4,
		ATTACK_RANGE_HIT_5,
		ATTACK_RANGE_HIT_6,
		ATTACK_RANGE_HIT_7,
		ATTACK_RANGE_HIT_8
	}ATTACK_RANGE_TYPE;

	typedef struct	//攻撃マス目情報
	{
		ATTACK_RANGE_TYPE	RangeType;	//攻撃マスタイプ 
		D3DXVECTOR3			AttackPos;	//攻撃のマス位置
	}SQUARE_DATA;

	typedef struct	//攻撃マス全体の情報
	{
		int			nMaxHitRange;										// 最大ヒットマス
		SQUARE_DATA SquareData[MAX_ATTACK_SIZE_Y*MAX_ATTACK_SIZE_X];	// 攻撃のマスデータ[読み込み限界の縦横]
		int			nAttackFrame[MAX_HIT_TYPE];							// 攻撃速度
		int			nTypeHitRange;										// タイプごとのヒットマス数
	}ATTACK_SQUARE_DATA;

	//関数定義
	CAttackManager();
	~CAttackManager();
	static CAttackManager * Create(void);	// クラス生成
	static void Release(void);				// クラス破棄
	static ATTACK_RANGE_DATA GetAttackData(CResourceCharacter::CHARACTER_TYPE type,int nLevel);
	static ATTACK_SQUARE_DATA GetAttack(CResourceCharacter::CHARACTER_TYPE type, int nLevel);

private:
	void	Load(void);		//攻撃範囲読み込み
	void	PosCalc(void);	//位置計算

	static CAttackManager*	m_pAttackBasis;						// 攻撃範囲クラスのポインタ
	ATTACK_RANGE_DATA		m_AttackData[CResourceCharacter::CHARACTER_MAX][MAX_ATTACK_LEVEL];		// 攻撃の情報
	ATTACK_SQUARE_DATA		m_AttackSwuare[CResourceCharacter::CHARACTER_MAX][MAX_ATTACK_LEVEL];	// 攻撃マスの情報

};
#endif