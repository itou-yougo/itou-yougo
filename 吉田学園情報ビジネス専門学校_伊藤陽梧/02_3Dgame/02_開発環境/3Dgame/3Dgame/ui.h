//=============================================================================
//
// プレイヤーの処理 [ui.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _UI_H_
#define _UI_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "scene2d.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TEXTURE_TITLE		("data/TEXTURE/title.png")
#define TEXTURE_TUTORIAL	("data/TEXTURE/tutorial01.jpg")
#define TEXTURE_GAMEOVER	("data/TEXTURE/gameover.png")
#define TEXTURE_RESULT		("data/TEXTURE/result.jpg")
#define TEXTURE_HP			("data/TEXTURE/hp.png")
#define TEXTURE_HPFLAME		("data/TEXTURE/hpflame.png")
#define TEXTURE_HPBACK		("data/TEXTURE/hpback.png")
#define TEXTURE_ENEMYREMAINDER		("data/TEXTURE/enemyrimainder.png")
#define PLAYER_HP_COLOR		(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f))
#define ENEMY_HP_COLOR		(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f))

//=============================================================================
// UIクラス
//=============================================================================
class CUi :public CScene2D
{
public:
	CUi(int nPriority);
	~CUi();

	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_TITLE,
		TYPE_TUTORIAL,
		TYPE_GAMEOVER,
		TYPE_RESULT,
		TYPE_PLAYER_LIFE,
		TYPE_HP,
		TYPE_HPFLAME,
		TYPE_HPBACK,
		TYPE_ENEMYREMAINDER,
		TYPE_MAX
	}TYPE;
	
	static CUi*Create(D3DXVECTOR3 pos,D3DXVECTOR3 size,TYPE type);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[TYPE_MAX];
	D3DXVECTOR3				m_pos;					// ポリゴンの位置
	D3DXVECTOR3				m_size;
	TYPE                    m_type;
};
#endif // !_UI_H_
