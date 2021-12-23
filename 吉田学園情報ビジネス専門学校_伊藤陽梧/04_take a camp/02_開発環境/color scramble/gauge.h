//=============================================================================
//
// gaugeヘッダ [gauge.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _GAUGE_H_
#define _GAUGE_H_

//*****************************
//インクルード
//*****************************
#include "main.h"
#include "scene.h"

//*****************************
//前方宣言
//*****************************
class CPolygon;

//*****************************
// マクロ定義
//*****************************
#define DEFAULT_GAUGE_RATE (0.03f)
//*****************************
//クラス定義
//*****************************

//ゲージクラス
class CGauge : public CScene
{
public:

	//============
	// 列挙定義
	//============
	enum MODE
	{
		MODE_VALUE_AUTO = 0, // 内部数値を管理*自動
		MODE_VALUE_SELF,	 // 内部数値を管理*手動
		MODE_HEIGHT_AUTO,	 // ゲージの高さを直接を管理*自動
		MODE_HEIGHT_SELF,	 // ゲージの高さを直接を管理*手動
	};

	//============
	// メンバ関数
	//============

	CGauge();
	~CGauge();

	// static
	static CGauge *Create(D3DXVECTOR3 leftPos, float fBarWidht, float fBarHeight, float fMaxNum, D3DXCOLOR frontCol); // クラス生成

	HRESULT Init(void); // 初期化
	void Uninit(void);  // 終了
	void Update(void);  // 更新
	void Draw(void);    // 描画

	// ゲージ内部数値
	void SetValue(float fValue) { m_fValue = fValue; }
	float GetValue(void) { return m_fValue; }
	// ゲージ内部数値の目標値
	void SetValueDist(float fValueDist) { m_fValueDist = fValueDist; }
	float GetValueDist(void) { return m_fValueDist; }
	// ゲージ高さ
	void SetHeight(float fHeight) { m_fHeight = fHeight; }
	float GetHeight(void) { return m_fHeight; }
	// ゲージ高さの目標値
	void SetHeightDist(float fHeightDist) { m_fHeightDist = fHeightDist; }
	float GetHeightDist(void) { return m_fHeightDist; }
	// 係数
	void SetRate(float fRate) { m_fGaugeRate = fRate; }
	float GetRate(void) { return m_fGaugeRate; }
	// ゲージモード
	MODE GetMode(void) { return m_mode; }
	void SetMode(MODE mode);

private:
	void UpdateValue(void);
	// メンバ変数
	CPolygon*   m_pPolygon;   // ライフ描画用のポリゴン
	D3DXVECTOR3 m_pos;        // ゲージの位置(底)
	float       m_fBarWidht;  // 幅
	float       m_fBarHeight; // 高さ最大
	float       m_fHeightDist;// 高さ目標
	float       m_fHeight;    // 高さ
	float       m_fMaxNum;    // 最大数
	float       m_fValue;     // ゲージ内部数値
	float       m_fValueDist; // ゲージ内部数値目標値
	float       m_fGaugeRate; // ゲージ偏移時の係数
	D3DXCOLOR   m_frontCol;   // フロントのカラー
	MODE        m_mode;       // ゲージのモード
};

#endif