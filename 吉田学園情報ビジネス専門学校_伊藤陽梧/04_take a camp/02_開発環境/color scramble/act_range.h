//=============================================================================
//
// 行動範囲ヘッダ [act_range.h]
// Author : 吉田 悠人
//
//=============================================================================

//二重インクルード防止
#ifndef _ACT_RAGE_H_
#define _ACT_RAGE_H_

//*****************************
// インクルード
//*****************************
#include "main.h"
#include "scene.h"
#include "map.h"
#include "game.h"

//*****************************
// 前方宣言
//*****************************
class CPlayer;

//*****************************
// クラス定義
//*****************************
// 行動範囲クラス
class CActRange : public CScene
{
public:
	typedef enum	//移動できる方向
	{
		PLAYER_MOVE_UP = 0,	//上
		PLAYER_MOVE_DOWN,	//下
		PLAYER_MOVE_LEFT,	//左
		PLAYER_MOVE_RIGHT,	//右
		PLAYER_MOVE_MAX
	}PLAYER_MOVE;
		
	typedef struct
	{
		D3DXVECTOR3 OtherActPos;	// 位置
		D3DXVECTOR3 OtherNewActPos;	// 移動位置
		bool		bMove;			// 移動フラグ
		bool		bDeath;			// 死亡フラグ
	}OTHER_ACT;


	//メンバ関数
	CActRange();
	~CActRange();
	void PlayerPos(void);					// プレイヤーがどの位置にいるか
	bool ActMove(int nMoveX, int nMoveZ);	// プレイヤーがその方向に移動できるか
	void OtherPlayer(void);					// 他のプレイヤーにぶつかり止まる判定
	void ActRange(void);					// プレイヤーの移動範囲
	static CActRange *Create(CPlayer* pPlayer);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool GetPlayerMove(int nPlayerMove) { return m_bPlayerMove[nPlayerMove]; }	// プレイヤーの移動できる方向ゲッター
	D3DXVECTOR3 GetActPos(void) { return m_ActPos; }							// マップ上のプレイヤーの位置ゲッター
	D3DXVECTOR3 GetNewActPos(void) { return m_NewActPos; }						// マップ上のプレイヤーの移動位置ゲッター
	void SetDeath(bool bDeath) { m_bDeath = bDeath; }
	bool GetDeath(void) { return m_bDeath; }
	void SetMove(bool bMove) { m_bMove = bMove; }
	bool GetMove(void) { return m_bMove; }
private:
	CPlayer*		 m_pPlayer;							// プレイヤーポインタ
	CMapManager::MAP_DATA m_MapData;					// マップデータ
	D3DXVECTOR3		 m_ActPos;							// マップ上のプレイヤーの位置
	D3DXVECTOR3		 m_NewActPos;						// マップ上のプレイヤーの移動後の位置
	OTHER_ACT		 m_OtherAct[PLAYER_MOVE_MAX - 1];	// 他プレイヤーの情報
	bool			 m_bPlayerMove[PLAYER_MOVE_MAX];	// プレイヤーが移動できるか
	bool			 m_bDeath;							// 死亡フラグ
	bool			 m_bMove;							// 移動フラグ
	

};

#endif