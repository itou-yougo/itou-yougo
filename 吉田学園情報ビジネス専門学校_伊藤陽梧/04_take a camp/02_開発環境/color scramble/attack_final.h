////=============================================================================
////
//// 必殺技の処理 [attack_final.h]
//// Author : 佐藤颯紀
////
////=============================================================================
//
//#ifndef _ATTACK_FINAL_H_
//#define _ATTACK_FINAL_H_
//
////=============================================================================
//// インクルードファイル
////=============================================================================
//#include "scene.h"
//#include "resource_final_attack.h"
//
////=============================================================================
//// 前方宣言
////=============================================================================
//class CPlayer;
//class CAttackArea;
//class CColorTile;
//class CPeintCollision;
//
////=============================================================================
//// マクロ定義
////=============================================================================
//#define MAX_ATTACK_FINAL_AREA_NUM (128)
//#define MAX_FINAL_PEINT	(128)
////=============================================================================
//// クラス定義
////=============================================================================
//class CAttackFinal : public CScene
//{
//public:
//	// 列挙
//	typedef enum
//	{
//		FINAL_ATTACK_STATE_NONE = -1,
//		FINAL_ATTACK_STATE_NOMAL,		// 通常状態
//		FINAL_ATTACK_STATE_ATTACK,		// 攻撃状態
//		FINAL_ATTACK_STATE_MAX
//	}FINAL_ATTACK_STATE;
//
//	CAttackFinal();		// コンストラクタ
//	~CAttackFinal();	// デストラクタ
//
//	HRESULT Init(void);	// 初期化処理
//	void Uninit(void);	// 終了処理
//	void Update(void);	// 更新処理
//	void Draw(void);	// 描画処理
//	
//	void AttackFinalSwitch(void);			// 必殺スイッチ処理
//	void AttackFinal(int AttackFinalType);	// 必殺関数
//
//	void SetAttackFinalType(CResourceCharacter::CHARACTER_TYPE AttackFinal) { m_FinalAttackType = AttackFinal; }						// 必殺技タイプ設定
//	CResourceCharacter::CHARACTER_TYPE GetAttackFinalType(void) {return m_FinalAttackType;}												// 必殺技タイプの取得
//
//	void SetFinalAttackSquare(CFinalAttackManager::FINAL_ATTACK_SQUARE_DATA FinalAttackSquare) { m_FinalAttackSquare = FinalAttackSquare; }	// 必殺技マスデータの設定
//	CFinalAttackManager::FINAL_ATTACK_SQUARE_DATA GetFinalAttackSquare(void) { return m_FinalAttackSquare; }								// 必殺技マスデータの取得
//
//	void		SetPos(D3DXVECTOR3 pos) { m_pos = pos; }		// 位置設定
//	D3DXVECTOR3 GetPos(void)			{ return m_pos; }		// 位置取得
//	void		SetRot(D3DXVECTOR3 rot) { m_rot = rot; }		// 向き設定
//	D3DXVECTOR3 GetRot(void)			{ return m_rot; }		// 向き取得
//	void		SetAttackFinalFlag(bool bAttackFinal)	{ m_bAttackFinal = bAttackFinal; }	// 必殺技フラグ設定
//	bool		GetAttackFinalFlag(void)				{ return m_bAttackFinal; }			// 必殺技フラグ取得
//	void		SetPlayer(CPlayer* pPlayer)				{ m_pPlayer = pPlayer; }			// プレイヤ情報取得
//	CPlayer*	GetPlayer(void)							{ return m_pPlayer; }				// プレイヤー情報設定
//	void		SetState(FINAL_ATTACK_STATE State)		{ m_FinalAttackState = State; }		// 状態設定
//	FINAL_ATTACK_STATE GetState(void)					{ return m_FinalAttackState; }		// 状態取得
//	virtual void AttackFinalCreate(void) = 0;						// 必殺技生成処理
//	void		VisualizationAttackArea(int AttackFinalType = 0);	// 攻撃の範囲のブロックの枠の色を変える処理
//	void        ResetAttackArea(void);								// 攻撃範囲ポリゴンのリセット
//private:
//	CPlayer* m_pPlayer;		// プレイヤークラス
//	CAttackArea *	m_apAttackArea[MAX_ATTACK_FINAL_AREA_NUM];			// 攻撃範囲ポインタ
//	D3DXVECTOR3 m_pos;						// 位置
//	D3DXVECTOR3 m_rot;						// 向き
//	FINAL_ATTACK_STATE m_FinalAttackState;	// 状態
//	bool m_bAttackFinal;					// 攻撃フラグ
//	CResourceCharacter::CHARACTER_TYPE			m_FinalAttackType;		// 攻撃タイプ
//	CFinalAttackManager::FINAL_ATTACK_SQUARE_DATA m_FinalAttackSquare;	// 必殺技マスデータ
//	CPeintCollision* m_pPeintCollision[MAX_FINAL_PEINT];				// 色
//};
//
//#endif // !_ATTACK_FINAL_H_
