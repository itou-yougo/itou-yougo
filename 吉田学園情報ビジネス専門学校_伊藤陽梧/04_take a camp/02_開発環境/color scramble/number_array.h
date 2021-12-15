//=============================================================================
//
// number_arrayヘッダ [number_array.h]
// Author : 伊藤陽梧
//
//=============================================================================

//二重インクルード防止
#ifndef _NUMBER＿ARRAY_H_
#define _NUMBER＿ARRAY_H_

//=============================================================================
//インクルード
//=============================================================================
#include "main.h"
#include "scene.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CBillboard;

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_ARRAY_NUM (5)

//=============================================================================
//クラス定義
//=============================================================================

//ナンバークラス
class CNumberArray : public CScene
{
public:
	//============
	// メンバ関数
	//============

	CNumberArray();
	~CNumberArray();
	static CNumberArray *Create(const int nNum, const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXCOLOR col, const int nColorNum); // クラス生成

	HRESULT Init(void); // 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画

	float Kerning(void);	// 表示する数字の間隔
	void SetNumber(void);	// ナンバーのセット
private:
	//============
	// メンバ変数
	//============
	CBillboard *m_apNumber[MAX_ARRAY_NUM];	// 表示する数字
	int m_nNumber;					// ナンバー
	D3DXVECTOR3 m_pos;				// 座標
	D3DXVECTOR3 m_size;				// 大きさ
	D3DXCOLOR m_col;				// 色
	bool m_bZeroCheck;				// 0かどうかのチェック
	int m_nPlayerNum;				// 0かどうかのチェック
};

#endif