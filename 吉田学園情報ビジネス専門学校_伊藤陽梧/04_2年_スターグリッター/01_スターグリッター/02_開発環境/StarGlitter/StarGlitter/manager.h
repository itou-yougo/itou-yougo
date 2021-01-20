//=============================================================================
//
// マネージャーの処理 [manager.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "game.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CTitle;
class CGame;
class CResult;
class CRenderer;
class CScene2D;

class CInput;
class CInputKeyboard;
class CInputJoypad;
class CSound;
class CBg;
class CEnemy;
class CScore;
class CGauge;
class CFade;
class CTutorial;

//=============================================================================
// マネージャークラス
//=============================================================================
class CManager
{
public:
	typedef enum MyEnum
	{
		MODE_TITLE = 0,
		MODE_TUTORIAL,
		MODE_GAME,
		MODE_END,
	}MODE;
	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetNumFPS(int nCountFPS) { m_nCountFPS = nCountFPS; }
	static void SetMode(MODE mode);
	static MODE GetMode(void);
	static CRenderer *GetRenderer(void);
	static CInputKeyboard *GetInputKeyboard(void);
	static CInputJoypad *GetInputJoypad(void);
	static CSound *GetSound(void);
	static CFade* GetFade(void);

private:
	static CTitle		  *m_pTitle;		 // タイトルのポインタ
	static CTutorial	  *m_pTutorial;		 // チュートリアルのポインタ
	static CGame		  *m_pGame;			 // ゲームのポインタ
	static CResult		  *m_pResult;		 // リザルトのポインタ
	static CRenderer	  *m_pRenderer;		 // レンダラーのポインタ
	static CInputKeyboard *m_pInputkeyboard; // キーボードのポインタ
	static CInputJoypad	  *m_pInputJoypad;	 // ジョイパッドのポインタ
	static CSound		  *m_pSound;		 // サウンドのポインタ
	static CFade		  *m_pFade;			 // フェードのポインタ
	static MODE			  m_mode;			 // モード
	int					  m_nCountFPS;		 // FPSの値

};
#endif