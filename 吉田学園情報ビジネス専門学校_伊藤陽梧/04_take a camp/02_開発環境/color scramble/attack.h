//=============================================================================
//
// 攻撃範囲 [attack.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _ATTACK_H_
#define _ATTACK_H_

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "scene.h"
#include "resource_attack.h"
//*****************************
// 前方宣言
//*****************************
class CPlayer;
class CAttackArea;
class CColorTile;
class CPeintCollision;

//*****************************
// マクロ定義
//*****************************
#define MAX_ATTACK (4)	//攻撃の最大回数
#define MAX_ATTACK_AREA_NUM (128)
#define MAX_FINAL_PEINT	(128)

//=============================================================================
// クラス定義
//=============================================================================
class CAttackBased : public CScene
{
public:

	// ステート
	typedef enum
	{
		ATTACK_STATE_NORMAL = 0,			// 通常状態
		ATTACK_STATE_CHARGE,				// チャージ状態
		ATTACK_STATE_ATTACK,				// 攻撃状態
		ATTACK_STATE_FINALATTACKWAITING,	// 必殺技待機
		ATTACK_STATE_FINALATTACK,			// 必殺技使用状態
	}ATTACK_STATE;

	//関数定義
	CAttackBased();
	~CAttackBased();
	static CAttackBased * Create(CPlayer* pPlayer, CResourceCharacter::CHARACTER_TYPE Type);
	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);
	void	Attack(int AttackType);		// 攻撃処理
	void	ChargeFlag(void);			// チャージ開始処理
	void	AttackSwitch(void);			// 攻撃スイッチ関数
	void	AttackFinalFlag(void);		// 必殺待機フラグ処理
	void    AttackFinalSwitch(void);	// 必殺スイッチ関数
	void	CancelSwitch(void);			// 攻撃キャンセルスイッチ関数
	virtual void AttackCreate(void);						// 攻撃生成処理 
	void	VisualizationAttackArea(int nAttackType = 0);	// 攻撃範囲の可視化
	void	ResetAttackArea(void);							// 攻撃範囲ポリゴンのリセット
	void	ReleaseAttakcArea(void);                        // 攻撃範囲のリリース

	//============================
	//セッター・ゲッター
	//============================
	//攻撃マスデータ
	CAttackManager::ATTACK_SQUARE_DATA GetAttackSquare(void);			
	// レベル
	void		SetLevel(int nLevel) { m_nLevel = nLevel; }			
	// プレイヤー
	void		SetPlayer(CPlayer* pPlayer) { m_pPlayer = pPlayer; }	
	CPlayer*	GetPlayer(void) { return m_pPlayer; }					
	// ステート
	void		SetState(ATTACK_STATE State) { m_AttackState = State; }	
	ATTACK_STATE GetState(void) { return m_AttackState; }				
	// 必殺技フラグ
	void		SetAttackFlag(bool bAttack) { m_bAttack = bAttack; }	
	bool		GetAttackFlag(void) { return m_bAttack; }				
	// 攻撃タイプ
	void		SetType(CResourceCharacter::CHARACTER_TYPE type) { m_nAttackType = type; }
private:
	virtual void CreateEffect(D3DXVECTOR3 pos); // エフェクト生成
	void		Charge(void);								    // 攻撃のチャージ処理

	CPlayer *		m_pPlayer;												// プレイヤークラス
	CAttackArea *	m_apAttackArea[MAX_ATTACK_AREA_NUM];					// 攻撃範囲ポインタ
	CResourceCharacter::CHARACTER_TYPE	m_nAttackType;						// 攻撃タイプ
	CAttackManager::ATTACK_SQUARE_DATA	m_AttackSquare[MAX_ATTACK_LEVEL];	// 攻撃マスデータ
	CPeintCollision* m_pPeintCollision[MAX_FINAL_PEINT];					// 色
	ATTACK_STATE	m_AttackState;						// 攻撃ステート
	bool			m_bAttack;							// 必殺フラグ
	bool			m_bChargeTile;						// チャージタイルフラグ
	bool			m_bCancel;							// キャンセルフラグ
	int				m_nLevel;							// 攻撃のレベル
	int				m_nMaxLevel;						// 最大レベル保存用
	int				m_nChargeCount;						// チャージ用のカウント
	int				m_anChargeValue[MAX_ATTACK_LEVEL];  // チャージ目標値
	int				m_nCancelCount;						// キャンセルカウント
	int				m_nAttackCount;		//攻撃までのカウント
	int				m_nType;			//攻撃の間隔用のタイプ

};

#endif