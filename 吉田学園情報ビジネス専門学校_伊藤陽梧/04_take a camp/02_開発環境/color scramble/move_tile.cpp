////////////////////////////////////////////////////
//
//    動くタイルの処理[move_tile.cpp]
//    Author:吉田 悠人
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "move_tile.h"
#include "game.h"
#include "player.h"
#include "collision.h"

//*****************************
// マクロ定義
//*****************************
#define MOVE_SPEED (20)				// 移動が終わるまでのフレーム
#define MOVE_DIST  (TILE_ONE_SIDE)	// 移動距離

//******************************
// コンストラクタ
//******************************
CMoveTile::CMoveTile()
{
	m_bReversal = false;
	m_bStep = false;
	m_nMoveCount = 0;
	m_MoveState = MOVE_STATE_NORMAL;
	ZeroMemory(&m_Move, sizeof(m_Move));
}

//******************************
// デストラクタ
//******************************
CMoveTile::~CMoveTile()
{
}

//******************************
// 初期化関数
//******************************
HRESULT CMoveTile::Init(void)
{

	//タイルの初期化処理
	CTile::Init();
	//色の設定
	SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	m_MoveState = MOVE_STATE_NORMAL;

	return S_OK;
}

//******************************
// 更新処理
//******************************
void CMoveTile::Update(void)
{
	CTile::Update();
	switch (m_MoveState)
	{
	case MOVE_STATE_NORMAL:
		break;
	case MOVE_STATE_MOVE:
		//移動処理
		Move();
		//当たり判定
		HitTile();
		
		break;
	case MOVE_STATE_STOP:
		
		//プレイヤーが何らかの攻撃で死んでいる時
		if (!GetHitPlayerFlag())
		{
			//タイルのステートを変化
			m_MoveState = MOVE_STATE_NORMAL;
			//タイルに乗れるフラグを立てる
			SetRide(false);
		}
		break;
	default:
		
		break;
	}
}

//******************************
// プレイヤーとヒット時の処理
//******************************
void CMoveTile::HitPlayerAction(CPlayer * pPlayer)
{
	switch (m_MoveState)
	{

	case MOVE_STATE_NORMAL:
		//タイルのステートを変化
		m_MoveState = MOVE_STATE_MOVE;
		TileCheck();
		//タイルに乗れなくなるフラグを立てる
		SetRide(true);
		break;

	case MOVE_STATE_MOVE:
		//プレイヤーの状況確認
		if (pPlayer->GetState() != CPlayer::PLAYER_STATE_STOP
			&&pPlayer->GetState() != CPlayer::PLAYER_STATE_DEATH)
		{
			//プレイヤーが動いてないときにステートを停止状態に変更
			if (pPlayer->GetMoveFlag())pPlayer->SetState(CPlayer::PLAYER_STATE_STOP);
		}
		//プレイヤーがストップ状態の時
		else if (pPlayer->GetState() == CPlayer::PLAYER_STATE_STOP)
		{
			//現在位置
			D3DXVECTOR3 pos = GetPos();
			//プレイヤーを移動させる処理
			pPlayer->SetPos(D3DXVECTOR3(pos.x, pPlayer->GetPos().y, pos.z));
		}
		break;

	case MOVE_STATE_STOP:
		//プレイヤーのステートを停止状態に変更
		pPlayer->SetState(CPlayer::PLAYER_STATE_NORMAL);
		break;

	default:
		//タイルのステートを変化
		m_MoveState = MOVE_STATE_NORMAL;
		break;

	}
}

//******************************
// プレイヤーが降りた処理
//******************************
void CMoveTile::HitPlayerActionRelease(void)
{
	if (m_MoveState == MOVE_STATE_STOP)
	{
		//タイルのステートを変化
		m_MoveState = MOVE_STATE_NORMAL;
		//タイルに乗れるフラグを立てる
		SetRide(false);
	}
}

//******************************
// タイルの移動処理
//******************************
void CMoveTile::Move(void)
{

	//現在位置
	D3DXVECTOR3 pos = GetPos();
	//位置計算
	pos += (m_Move - pos) / (float)(MOVE_SPEED - m_nMoveCount);
	//位置設定
	SetPos(pos);

	//カウントアップ
	m_nMoveCount++;

	//カウントが一定に達したら
	if (MOVE_SPEED <= m_nMoveCount)
	{
		// カウント初期化
		m_nMoveCount = 0;
		// 反転しているか
		MoveRot(m_bReversal);
	}
}

//******************************
// 他のタイルとの当たり判定
//******************************
void CMoveTile::HitTile(void)
{
	//現在位置
	D3DXVECTOR3 Hitpos = D3DXVECTOR3((m_Move.x), GetPos().y, (m_Move.z));
	//タイルポインタ取得
	CTile * pTile = CTile::GetHitTile(Hitpos);
	
	//NULLチェック
	if (pTile != NULL
		&&pTile != (CTile*)this)
	{
		//移動方向反転
		if (!m_bReversal)m_bReversal = true;
		else m_bReversal = false;
		// 反転しているか
		MoveRot(m_bReversal);
		//ステートを通常状態に変更
		m_MoveState = MOVE_STATE_STOP;
	}
}

