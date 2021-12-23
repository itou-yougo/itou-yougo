//=============================================================================
//
// ゲーム開始の処理 [game_start.h]
// Author : 佐藤颯紀
//
//=============================================================================
#ifndef _GAME_START_H_
#define _GAME_START_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "scene.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CPolygon;
class CPlayer;
class CTime;
//=============================================================================
// マクロ定義
//=============================================================================
#define START_UI_SIZE D3DXVECTOR3(480.0f,120.0f,0.0f)
#define START_UI_POS_Y	(360.0f)

//=============================================================================
// クラス宣言
//=============================================================================
class CGameStart :public CScene
{
public:
	// UIの種類
	typedef enum
	{
		START_TYPE_READEY = 0,
		START_TYPE_GO,
		START_TYPE_PLAY,
		START_TYPE_MAX
	}START_TYPE;

	CGameStart();						// コンストラクタ
	~CGameStart();						// デストラクタ

	static CGameStart*Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// 生成処理

	HRESULT Init(void);					// 初期化処理
	void Uninit(void);					// 終了処理
	void Update(void);					// 更新処理
	void Draw(void);					// 描画処理	

	// タイプの取得
	void SetStartType(START_TYPE type) { m_type = type; }
	START_TYPE GetType(void) { return m_type; }

private:
	// メンバ関数
	void GoChange(void);		// Goのときの処理
	void PlayChange(void);		// Playのときの処理
	void StartPlayer(void);		// sutartしたときの処理

	// メンバ変数
	CPolygon*   m_pPolygon;		// ライフ描画用のポリゴン
	D3DXVECTOR3 m_pos;			// 位置
	D3DXVECTOR3 m_size;			// サイズ
	D3DXCOLOR   m_col;			// カラー
	int			m_nCount;		// カウント
	START_TYPE  m_type;			// UIのタイプ
	bool m_bStart;				// スタートしたかしてないか
};
#endif // !_GAME_START_H_
